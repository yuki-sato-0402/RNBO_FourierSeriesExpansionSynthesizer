#include "RNBO_Utils.h"
#include "RNBO.h"
#include "RNBO_TimeConverter.h"
#include "RNBO_BinaryData.h"
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_dsp/juce_dsp.h>

class CustomAudioProcessor :public juce::AudioProcessor ,public juce::AudioProcessorValueTreeState::Listener{
public:
    //static CustomAudioProcessor* CreateDefault();
    CustomAudioProcessor();
    ~CustomAudioProcessor() override = default;
    // 必須の純粋仮想関数
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
   
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void parameterChanged(const juce::String& parameterID, float newValue) override;
    
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
  
    const juce::String getName() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;
    
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    RNBO::CoreObject& getRnboObject() { return rnboObject; }
private:
    juce::AudioProcessorValueTreeState parameters;  
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomAudioProcessor)

    double _lastBPM = -1.0;
    int _lastTimeSigNumerator = 0;
    int _lastTimeSigDenominator = 0;
    double _lastPpqPosition = -1.0;
    bool _lastIsPlaying = false;
    
    RNBO::TimeConverter preProcess(juce::MidiBuffer& midiMessages);
    void postProcess(RNBO::TimeConverter& timeConverter, juce::MidiBuffer& midiMessages);
    std::unordered_map<juce::String, RNBO::ParameterIndex> apvtsParamIdToRnboParamIndex;

    //juce::AudioParameterFloat* termsParam{nullptr};
    //juce::AudioParameterFloat* filterOnOffParam{nullptr};
    //juce::AudioParameterFloat* cutoffOvertoneParam{nullptr};
    //juce::AudioParameterFloat* attenuationParam{nullptr};
    //juce::AudioParameterFloat* ocillatorParam{nullptr};
    //juce::AudioParameterFloat* attackParam{nullptr};
    //juce::AudioParameterFloat* decayParam{nullptr};
    //juce::AudioParameterFloat* sustainParam{nullptr};
    //juce::AudioParameterFloat* releaseParam{nullptr};
    //juce::AudioParameterFloat* ampParam{nullptr};

    RNBO::CoreObject rnboObject;
    RNBO::MidiEventList						_midiInput;
    RNBO::MidiEventList						_midiOutput;
};

