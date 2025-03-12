#include "JuceHeader.h"
#include "RNBO.h"
#include "RNBO_JuceAudioProcessor.h"

class CustomAudioEditor : public AudioProcessorEditor, private AudioProcessorListener
{
public:
    CustomAudioEditor(RNBO::JuceAudioProcessor* const p, RNBO::CoreObject& rnboObject,juce::AudioProcessorValueTreeState& vts);
    ~CustomAudioEditor() override;
    void paint (Graphics& g) override;
    void resized() override; 
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    typedef juce::AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
   
private:
///コンストラクタでプロセッサ側から受け取るAPVTSの参照を格納するメンバを定義,パラメータとUIを紐づけるため。

    // LookAndFeel クラス
    juce::LookAndFeel_V4 midnightLookAndFeel;
    
    juce::AudioProcessorValueTreeState& valueTreeState; // ✅ 参照で保持
    juce::Slider dial1Slider;
    juce::Slider dial2Slider;
    juce::Slider dial3Slider;
    juce::Slider dial4Slider;
    juce::Slider dial5Slider;
    juce::Slider dial6Slider;
    juce::Slider dial7Slider;
    juce::Slider dial8Slider;
   
    juce::ToggleButton filterButton; 
    juce::ComboBox selectComboBox;

    juce::Label  label0;
    juce::Label  label1;
    juce::Label  label2;
    juce::Label  label3;
    juce::Label  label4;
    juce::Label  label5;
    juce::Label  label6;
    juce::Label  label7;
    juce::Label  label8;
    
   


    //AudioProcessorValueTreeState::SliderAttachmentのスマートポインタ
    std::unique_ptr<SliderAttachment> dial1Attachment;
    std::unique_ptr<SliderAttachment> dial2Attachment;
    std::unique_ptr<SliderAttachment> dial3Attachment;
    std::unique_ptr<SliderAttachment> dial4Attachment;
    std::unique_ptr<SliderAttachment> dial5Attachment;
    std::unique_ptr<SliderAttachment> dial6Attachment;
    std::unique_ptr<SliderAttachment> dial7Attachment;
    std::unique_ptr<SliderAttachment> dial8Attachment;
    std::unique_ptr<ButtonAttachment> button1Attachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> comboBoxAttachment;


    //JUCEの AudioProcessorListener インターフェースのメソッドをオーバーライドしたもので、
    //オーディオプロセッサーに関する変更を通知するために使用されるもの
    void audioProcessorChanged (AudioProcessor*, const ChangeDetails&) override { }
    void audioProcessorParameterChanged(AudioProcessor*, int parameterIndex, float) override;

protected:
    AudioProcessor                              *_audioProcessor;
    RNBO::CoreObject&                           _rnboObject;  
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomAudioEditor)
};
