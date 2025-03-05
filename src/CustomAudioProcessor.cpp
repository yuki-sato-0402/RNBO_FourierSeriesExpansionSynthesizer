#include "CustomAudioProcessor.h"
#include "CustomAudioEditor.h"
#include <json/json.hpp>

#ifdef RNBO_INCLUDE_DESCRIPTION_FILE
#include <rnbo_description.h>
#endif

//create an instance of our custom plugin, optionally set description, presets and binary data (datarefs)
CustomAudioProcessor* CustomAudioProcessor::CreateDefault() {
	nlohmann::json patcher_desc, presets;

#ifdef RNBO_BINARY_DATA_STORAGE_NAME
	extern RNBO::BinaryDataImpl::Storage RNBO_BINARY_DATA_STORAGE_NAME;
	RNBO::BinaryDataImpl::Storage dataStorage = RNBO_BINARY_DATA_STORAGE_NAME;
#else
	RNBO::BinaryDataImpl::Storage dataStorage;
#endif
	RNBO::BinaryDataImpl data(dataStorage);

#ifdef RNBO_INCLUDE_DESCRIPTION_FILE
	patcher_desc = RNBO::patcher_description;
	presets = RNBO::patcher_presets;
#endif
  return new CustomAudioProcessor(patcher_desc, presets, data);
}

CustomAudioProcessor::CustomAudioProcessor(
    const nlohmann::json& patcher_desc,
    const nlohmann::json& presets,
    const RNBO::BinaryData& data
    ) 
  : RNBO::JuceAudioProcessor(patcher_desc, presets, data) 
{
  
  parameters = std::make_unique<juce::AudioProcessorValueTreeState>(
    *this, nullptr, juce::Identifier("APVTSTutorial"),
    juce::AudioProcessorValueTreeState::ParameterLayout {
        std::make_unique<juce::AudioParameterFloat>(ParameterID { "terms",  1}, "terms",
        juce::NormalisableRange<float>(1, 40, 1), 1),
        std::make_unique<juce::AudioParameterFloat>(ParameterID { "filterOnOff",  1}, "filterOnOff",
        juce::NormalisableRange<float>(0, 1, 1), 0),
        std::make_unique<juce::AudioParameterFloat>(ParameterID { "cutoffOvertone",  1}, "cutoffOvertone",
        juce::NormalisableRange<float>(2, 40, 1), 2),
        std::make_unique<juce::AudioParameterFloat>(ParameterID { "attenuation",  1}, "attenuation",
        juce::NormalisableRange<float>(1.f, 100.f, 0.01f),1.f),
        std::make_unique<juce::AudioParameterFloat>(ParameterID { "ocillator",  1}, "ocillator",
        juce::NormalisableRange<float>(1, 3, 1), 1),
        std::make_unique<juce::AudioParameterFloat>(ParameterID { "attack",  1}, "attack",
        juce::NormalisableRange<float>(1.f, 1000.f, 0.01f), 10.f),
        std::make_unique<juce::AudioParameterFloat>(ParameterID { "decay",  1}, "decay",
        juce::NormalisableRange<float>(1.f, 1000.f, 0.01f), 100.f),
        std::make_unique<juce::AudioParameterFloat>(ParameterID { "sustain",  1}, "sustain",
        juce::NormalisableRange<float>(0.f, 100.f, 0.01f), 80.f),
        std::make_unique<juce::AudioParameterFloat>(ParameterID { "release",  1}, "release",
        juce::NormalisableRange<float>(0.f, 5000.f, 0.01f),1000.f),
        std::make_unique<juce::AudioParameterFloat>(ParameterID { "amp",  1}, "amp",
        juce::NormalisableRange<float>(0.f, 1.f, 0.01f),0.5f)
    }
  );
  if (!parameters){
        DBG("ERROR: parameters is nullptr!");
        jassertfalse;
  }else{
        DBG("parameters successfully created!");
        DBG("parameters state: " + parameters->state.toXmlString()); // 追加
  }
 
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
      jassert (parameters->getParameter (paramID) != nullptr);

      // If you hit these assertions then you need to fix the incorrect apvts
      // parameter range in createParameterLayout().
      jassert (info.min == parameters->getParameterRange (paramID).start);
      jassert (info.max == parameters->getParameterRange (paramID).end);
    
      if (paramID == "terms") {
          // パラメータのポインタを取得
        termsParameter = parameters->getRawParameterValue("terms");
        parameters->addParameterListener("terms", this);
        rnboObject.setParameterValue(i, *termsParameter);  // RNBO に適用
      }else if(paramID == "filterOnOff") {
        // パラメータのポインタを取得
        filterOnOffParameter = parameters->getRawParameterValue("filterOnOff");
        parameters->addParameterListener("filterOnOff", this);
        rnboObject.setParameterValue(i, *filterOnOffParameter);  // RNBO に適用
      }else if(paramID == "cutoffOvertone") {
        // パラメータのポインタを取得
        cutoffOvertoneParameter = parameters->getRawParameterValue("cutoffOvertone");
        parameters->addParameterListener("cutoffOvertone", this);
        rnboObject.setParameterValue(i, *cutoffOvertoneParameter);  // RNBO に適用
      }else if(paramID == "attenuation") {
        // パラメータのポインタを取得
        attenuationParameter = parameters->getRawParameterValue("attenuation");
        parameters->addParameterListener("attenuation", this);
        rnboObject.setParameterValue(i, *attenuationParameter);  // RNBO に適用
      }else if(paramID == "ocillator") {
        // パラメータのポインタを取得
        ocillatorParameter = parameters->getRawParameterValue("ocillator");
        parameters->addParameterListener("ocillator", this);
        rnboObject.setParameterValue(i, *ocillatorParameter);  // RNBO に適用
      }else if(paramID == "attack") {
        // パラメータのポインタを取得
        attackParameter = parameters->getRawParameterValue("attack");
        parameters->addParameterListener("attack", this);
        rnboObject.setParameterValue(i, *attackParameter);  // RNBO に適用
      }else if(paramID == "decay") {
        // パラメータのポインタを取得
        decayParameter = parameters->getRawParameterValue("decay");
        parameters->addParameterListener("decay", this);
        rnboObject.setParameterValue(i, *decayParameter);  // RNBO に適用
      }else if(paramID == "sustain") {
        // パラメータのポインタを取得
        sustainParameter  = parameters->getRawParameterValue("sustain");
        parameters->addParameterListener("sustain", this);
        rnboObject.setParameterValue(i, *sustainParameter );  // RNBO に適用
      }else if(paramID == "release") {
        // パラメータのポインタを取得
        releaseParameter  = parameters->getRawParameterValue("release");
        parameters->addParameterListener("release", this);
        rnboObject.setParameterValue(i, *releaseParameter );  // RNBO に適用
      }else{
        ampParameter = parameters->getRawParameterValue("amp");
        parameters->addParameterListener("amp", this);
        rnboObject.setParameterValue(i, *ampParameter);  // RNBO に適用
      }


    } 
  }
  
}

void CustomAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{

   // 受信した MIDI メッセージをログに出力
   for (const auto meta : midiMessages)
   {
       auto message = juce::MidiMessage(meta.data, (int)meta.numBytes);

       if (message.isNoteOn())
       {
           DBG("Note On: " << message.getNoteNumber() << " Velocity: " << message.getVelocity());
       }
       else if (message.isNoteOff())
       {
           DBG("Note Off: " << message.getNoteNumber());
       }
       else if (message.isController())
       {
           DBG("CC: " << message.getControllerNumber() << " Value: " << message.getControllerValue());
       }
   }
    auto samples = static_cast<RNBO::Index>(buffer.getNumSamples());
    //preProcess() と postProcess() は、JUCE の MIDI データを RNBOとやり取りするための処理
    //preProcess(): JUCE の MidiBuffer を RNBO 用のフォーマットに変換し、タイミング情報（BPM、拍子、PPQ 位置、再生状態など）を RNBO に送信
    //postProcess(): RNBO から出力された MIDI データを JUCE の MidiBuffer に戻す
	  auto tc = preProcess(midiMessages);
	  _rnboObject.process(
                        buffer.getArrayOfReadPointers(), static_cast<RNBO::Index>(buffer.getNumChannels()),
                        buffer.getArrayOfWritePointers(), static_cast<RNBO::Index>(buffer.getNumChannels()),
			  samples,
			  &_midiInput, &_midiOutput
			  );
	  postProcess(tc, midiMessages);
}


//このコールバック メソッドは、パラメータが変更されたときに AudioProcessorValueTreeStateによって呼び出されます。
void CustomAudioProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
  DBG("parameterChanged: " << parameterID << " = " << newValue);
    if (parameterID == "terms"){
      RNBO::ParameterIndex index = rnboObject.getParameterIndexForID("terms");
      rnboObject.setParameterValue(index, newValue);
    }else if(parameterID == "filterOnOff"){
      RNBO::ParameterIndex index = rnboObject.getParameterIndexForID("filterOnOff");
      rnboObject.setParameterValue(index, newValue);
    }else if(parameterID == "cutoffOvertone"){
      RNBO::ParameterIndex index = rnboObject.getParameterIndexForID("cutoffOvertone");
      rnboObject.setParameterValue(index, newValue);
    }else if(parameterID == "attenuation"){
      RNBO::ParameterIndex index = rnboObject.getParameterIndexForID("attenuation");
      rnboObject.setParameterValue(index, newValue);
    }else if(parameterID == "ocillator"){
      RNBO::ParameterIndex index = rnboObject.getParameterIndexForID("ocillator");
      rnboObject.setParameterValue(index, newValue);
    }else if(parameterID == "attack"){
      RNBO::ParameterIndex index = rnboObject.getParameterIndexForID("attack");
      rnboObject.setParameterValue(index, newValue);
    }else if(parameterID == "decay"){
      RNBO::ParameterIndex index = rnboObject.getParameterIndexForID("decay");
      rnboObject.setParameterValue(index, newValue);
    }else if(parameterID == "sustain"){
      RNBO::ParameterIndex index = rnboObject.getParameterIndexForID("sustain");
      rnboObject.setParameterValue(index, newValue);
    }else if(parameterID == "release"){
      RNBO::ParameterIndex index = rnboObject.getParameterIndexForID("release");
      rnboObject.setParameterValue(index, newValue);
    }else{
      RNBO::ParameterIndex index = rnboObject.getParameterIndexForID("amp");
      rnboObject.setParameterValue(index, newValue);
    }
}



CustomAudioProcessor::~CustomAudioProcessor()
{
    // リスナーを必ず削除
    if (parameters != nullptr)
    {
        parameters->removeParameterListener("terms", this);
        parameters->removeParameterListener("filterOnOff", this);
        parameters->removeParameterListener("cutoffOvertone", this);
        parameters->removeParameterListener("attenuation", this);
        parameters->removeParameterListener("ocillator", this);
        parameters->removeParameterListener("attack", this);
        parameters->removeParameterListener("decay", this);
        parameters->removeParameterListener("sustain", this);
        parameters->removeParameterListener("release", this);
        parameters->removeParameterListener("amp", this);
    }
}

void CustomAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = parameters->copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void CustomAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(parameters->state.getType()))
            parameters->replaceState(juce::ValueTree::fromXml(*xmlState));
}


AudioProcessorEditor* CustomAudioProcessor::createEditor()
{

    //AudioProcessorEditor側でAudioProcessorValueTreeStateにアクセスするための方法が必要です。
    //一般的なアプローチは、AudioProcessorからAudioProcessorValueTreeStateへの参照またはポインタを取得できるようにすること
    return new CustomAudioEditor (this, this->_rnboObject, *parameters);
    //RNBOのデフォルトエディター, 標準的なパラメータ表示, 追加のカスタマイズが限定的
   // return RNBO::JuceAudioProcessor::createEditor();
}



