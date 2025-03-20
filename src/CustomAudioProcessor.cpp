#include "CustomAudioProcessor.h"
#include "CustomAudioEditor.h"

CustomAudioProcessor::CustomAudioProcessor() 
: AudioProcessor (BusesProperties()
    .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
//コンストラクタの イニシャライザリスト で初期化
parameters(*this, nullptr, juce::Identifier("PARAMETERS"),
    juce::AudioProcessorValueTreeState::ParameterLayout {
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "terms",  1}, "terms",
        juce::NormalisableRange<float>(1, 40, 1, 1), 1),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "filterOnOff",  1}, "filterOnOff",
        juce::NormalisableRange<float>(0, 1, 1, 1), 0),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "cutoffOvertone",  1}, "cutoffOvertone",
        juce::NormalisableRange<float>(2, 40, 1, 1), 2),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "attenuation",  1}, "attenuation",
        juce::NormalisableRange<float>(1.f, 100.f, 0.01f, 1.f),1.f),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "ocillator",  1}, "ocillator",
        juce::NormalisableRange<float>(1, 3, 1, 1), 1),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "attack",  1}, "attack",
        juce::NormalisableRange<float>(1.f, 1000.f, 0.01f, 1.f), 10.f),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "decay",  1}, "decay",
        juce::NormalisableRange<float>(1.f, 1000.f, 0.01f, 1.f), 100.f),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "sustain",  1}, "sustain",
        juce::NormalisableRange<float>(0.f, 100.f, 0.01f, 1.f), 80.f),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "release",  1}, "release",
        juce::NormalisableRange<float>(0.f, 5000.f, 0.01f, 1.f),1000.f),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "amp",  1}, "amp",
        juce::NormalisableRange<float>(0.f, 1.f, 0.01f),0.5f)
    }
  )
{
 
 
  for (RNBO::ParameterIndex i = 0; i < rnboObject.getNumParameters(); ++i){
    RNBO::ParameterInfo info;
    rnboObject.getParameterInfo (i, &info);

    if (info.visible){
      auto paramID = juce::String (rnboObject.getParameterId (i));
      std::cout << "Parameter Index: " << i << std::endl;
      std::cout << "Min Value: " << info.min << std::endl;
      std::cout << "Max Value: " << info.max << std::endl;

      // Each apvts parameter id and range must be the same as the rnbo param object's.
      // If you hit this assertion then you need to fix the incorrect id in ParamIDs.h.
      jassert (parameters.getParameter (paramID) != nullptr);

      // If you hit these assertions then you need to fix the incorrect apvts
      // parameter range in createParameterLayout().
      jassert (info.min == parameters.getParameterRange (paramID).start);
      jassert (info.max == parameters.getParameterRange (paramID).end);

      apvtsParamIdToRnboParamIndex[paramID] = i;
    

    parameters.addParameterListener(paramID, this);
    rnboObject.setParameterValue(i, parameters.getRawParameterValue(paramID)->load());  // RNBO に適用
      
    } 
  }

}

void CustomAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    rnboObject.prepareToProcess (sampleRate, static_cast<size_t> (samplesPerBlock));
}
 
void CustomAudioProcessor::releaseResources()
{
}
 


void CustomAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{

    //auto samples = static_cast<RNBO::Index>(buffer.getNumSamples());
    //preProcess() と postProcess() は、JUCE の MIDI データを RNBOとやり取りするための処理
    //preProcess(): JUCE の MidiBuffer を RNBO 用のフォーマットに変換し、タイミング情報（BPM、拍子、PPQ 位置、再生状態など）を RNBO に送信
    //postProcess(): RNBO から出力された MIDI データを JUCE の MidiBuffer に戻す
	  // MIDI入力とタイミング情報の処理

    auto tc = preProcess(midiMessages);
	  rnboObject.process(
                        buffer.getArrayOfWritePointers(), static_cast<RNBO::Index>(buffer.getNumChannels()),
                        buffer.getArrayOfWritePointers(), static_cast<RNBO::Index>(buffer.getNumChannels()),
                        static_cast<RNBO::Index> (buffer.getNumSamples()),
			  &_midiInput, &_midiOutput
			  );
       // DBG("_midiInput size: " << _midiInput.size());
      
	  // MIDI出力の処理
    //postProcess(timeConverter, midiMessages);
    postProcess(tc, midiMessages);
}

////このコールバック メソッドは、パラメータが変更されたときに AudioProcessorValueTreeStateによって呼び出されます。
void CustomAudioProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
//  std::cout <<  "parameterID " <<  parameterID <<  " newValue " << newValue <<std::endl;
 rnboObject.setParameterValue (apvtsParamIdToRnboParamIndex[parameterID], newValue);
//    //auto index = static_cast<RNBO::ParameterIndex>(apvtsParamIdToRnboParamIndex[parameterID]);
    //auto range = parameters.getParameterRange(parameterID);  // パラメータ範囲の取得関数が必要
    //float normalizedValue = juce::jmap(newValue, range.start, range.end, 0.0f, 1.0f);
    //rnboObject.setParameterValueNormalized(index, normalizedValue, RNBO::RNBOTimeNow);
}


RNBO::TimeConverter CustomAudioProcessor::preProcess(juce::MidiBuffer& midiMessages) {
	RNBO::MillisecondTime time = rnboObject.getCurrentTime();

	//transport
	{
		AudioPlayHead* playhead = getPlayHead();
		if (playhead) {
			auto info = playhead->getPosition();
			if (info) {
				auto bpm = info->getBpm();
				if (bpm && *bpm != _lastBPM) {
					_lastBPM = *bpm;
					RNBO::TempoEvent event(time, _lastBPM);
					rnboObject.scheduleEvent(event);
				}

				auto timesig = info->getTimeSignature();
				if (timesig && (timesig->numerator != _lastTimeSigNumerator || timesig->denominator != _lastTimeSigDenominator)) {
					_lastTimeSigNumerator = timesig->numerator;
					_lastTimeSigDenominator = timesig->denominator;
					RNBO::TimeSignatureEvent event(time, _lastTimeSigNumerator, _lastTimeSigDenominator);
					rnboObject.scheduleEvent(event);
				}

				auto ppqPos = info->getPpqPosition();
				if (ppqPos && *ppqPos != _lastPpqPosition) {
					_lastPpqPosition = *ppqPos;
					RNBO::BeatTimeEvent event(time, _lastPpqPosition);
					rnboObject.scheduleEvent(event);
				}

				auto playing = info->getIsPlaying();
				if (playing != _lastIsPlaying) {
					_lastIsPlaying = playing;
					RNBO::TransportEvent event(time, _lastIsPlaying ? RNBO::TransportState::RUNNING : RNBO::TransportState::STOPPED);
					rnboObject.scheduleEvent(event);
				}
			}
		}
	}

    RNBO::TimeConverter timeConverter(rnboObject.getSampleRate(), time);

	// fill midi input 
	_midiInput.clear();  // make sure midi input starts clear
	for (auto meta: midiMessages)
	{
        RNBO::MillisecondTime t = timeConverter.convertSampleOffsetToMilliseconds(meta.samplePosition);
		_midiInput.addEvent(RNBO::MidiEvent(t, 0, meta.data, (RNBO::Index)meta.numBytes));
	}
	midiMessages.clear();		// clear the input that we consumed above so juce doesn't get confused
	return timeConverter;
}

void CustomAudioProcessor::postProcess(RNBO::TimeConverter& timeConverter, juce::MidiBuffer& midiMessages) {
	// consume midi output
	if (!_midiOutput.empty()) {
		for (const auto& ev: _midiOutput) {
			int sampleNumber = static_cast<int>(timeConverter.convertMillisecondsToSampleOffset(ev.getTime()));
			auto midiMessage = MidiMessage(ev.getData(), (int)ev.getLength());
			midiMessages.addEvent(midiMessage, sampleNumber);
		}
		_midiOutput.clear();
	}
}

juce::AudioProcessorEditor* CustomAudioProcessor::createEditor()
{
    //AudioProcessorEditor側でAudioProcessorValueTreeStateにアクセスするための方法が必要。
   return new CustomAudioEditor (*this,  parameters);
    //RNBOのデフォルトエディター, 標準的なパラメータ表示, 追加のカスタマイズが限定的
  // return RNBO::JuceAudioProcessor::createEditor();
}

bool CustomAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}


const juce::String CustomAudioProcessor::getName() const{
    return "Rnbo_FourierSeriesExpansionSynthesizer";
}

bool CustomAudioProcessor::acceptsMidi() const
{
    return true;
}

bool CustomAudioProcessor::producesMidi() const 
{
    return false;
}   
 
bool CustomAudioProcessor::isMidiEffect() const
{
    return false;
}

double CustomAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}
 
int CustomAudioProcessor::getNumPrograms()
{
    return 1;   
}
 
int CustomAudioProcessor::getCurrentProgram()
{
    return 0;
}
 
void CustomAudioProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused (index);
}
 
const juce::String CustomAudioProcessor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return {};
}
 
void CustomAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);
}


void CustomAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void CustomAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
}


