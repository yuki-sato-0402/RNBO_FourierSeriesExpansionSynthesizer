#include "RNBO_Utils.h"
#include "RNBO.h"
#include "RNBO_JuceAudioProcessor.h"
#include "RNBO_TimeConverter.h"
#include "RNBO_BinaryData.h"
#include <json/json.hpp>

class CustomAudioProcessor :public juce::AudioProcessor ,public juce::AudioProcessorValueTreeState::Listener{
public:
    //static CustomAudioProcessor* CreateDefault();
    CustomAudioProcessor();
    ~CustomAudioProcessor()override;
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    // APVTS の参照を取得する関数を追加
    juce::AudioProcessorValueTreeState& getValueTreeState() 
    { 
        jassert(parameters != nullptr);  // parameters が nullptr でないかチェック
        return *parameters; 
    }
    
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void parameterChanged(const juce::String& parameterID, float newValue) override;
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    // 必須の純粋仮想関数
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

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    
private:
 //AudioProcessorValueTreeStateクラスとパラメータ値を格納するポインタを準備します。
    std::unique_ptr<juce::AudioProcessorValueTreeState> parameters;  // ✅ ポインタにする
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomAudioProcessor)
    std::atomic<float>* Parameter1  = nullptr;

    double _lastBPM = -1.0;
    int _lastTimeSigNumerator = 0;
    int _lastTimeSigDenominator = 0;
    double _lastPpqPosition = -1.0;
    bool _lastIsPlaying = false;
    
    RNBO::TimeConverter preProcess(juce::MidiBuffer& midiMessages);
    void postProcess(RNBO::TimeConverter& timeConverter, juce::MidiBuffer& midiMessages);
    std::unordered_map<juce::String, RNBO::ParameterIndex> apvtsParamIdToRnboParamIndex;

    RNBO::CoreObject rnboObject;
    RNBO::MidiEventList						_midiInput;
    RNBO::MidiEventList						_midiOutput;
};

