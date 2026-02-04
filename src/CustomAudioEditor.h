#include "JuceHeader.h"
#include "RNBO.h"

class CustomAudioEditor : public juce::AudioProcessorEditor
{
public:
    CustomAudioEditor(CustomAudioProcessor& p,juce::AudioProcessorValueTreeState& vts);
    ~CustomAudioEditor() override = default;
    void paint (Graphics& g) override;
    void resized() override; 
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    typedef juce::AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
   
private:
    juce::LookAndFeel_V4 midnightLookAndFeel;
     // Get the background color from the midnight scheme
    juce::Colour backgroundColour = juce::LookAndFeel_V4::getMidnightColourScheme().getUIColour(juce::LookAndFeel_V4::ColourScheme::UIColour::windowBackground);

    juce::AudioProcessorValueTreeState& valueTreeState; // ✅ Hold by reference
    CustomAudioProcessor& audioProcessor; // ✅ Hold by reference
    juce::Slider termsSlider;
    juce::Slider cutoffOvertoneSlider;
    juce::Slider attenuationSlider;
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;
    juce::Slider ampSlider;
    juce::Slider cycleCountToAddSlider;
    juce::Slider cycleCountToSubtractSlider;
    juce::Slider termsToAddPerCountSlider;
    juce::Slider harmonicRatioSlider;
    
   
    juce::ToggleButton filterButton; 
    juce::ToggleButton posNegSyncButton;
    juce::ComboBox ocillatorComboBox;
    juce::ComboBox harmonicSeriesModeComboBox;
    juce::TextButton posButton;
    juce::TextButton negButton;
    


    juce::Label  ocillatorLabel;
    juce::Label  termsLabel;
    juce::Label  cutoffOvertoneLabel;
    juce::Label  attenuationLabel;
    juce::Label  attackLabel;
    juce::Label  decayLabel;
    juce::Label  sustainLabel;
    juce::Label  releaseLabel;
    juce::Label  ampLabel;
    juce::Label cycleCountToAddLabel;
    juce::Label cycleCountToSubtractLabel;
    juce::Label termsToAddPerCountLabel;
    juce::Label harmonicSeriesModeLabel;
    juce::Label harmonicRatioLabel;

    
    std::unique_ptr<SliderAttachment> termsSliderAttachment;
    std::unique_ptr<SliderAttachment> cutoffOvertoneSliderAttachment;
    std::unique_ptr<SliderAttachment> attenuationSliderAttachment;
    std::unique_ptr<SliderAttachment> attackSliderAttachment;
    std::unique_ptr<SliderAttachment> decaySliderAttachment;
    std::unique_ptr<SliderAttachment> sustainSliderAttachment;
    std::unique_ptr<SliderAttachment> releaseSliderAttachment;
    std::unique_ptr<SliderAttachment> ampSliderAttachment;
    std::unique_ptr<ButtonAttachment> button1Attachment;
    std::unique_ptr<ButtonAttachment> posButtonAttachment;
    std::unique_ptr<ButtonAttachment> negButtonAttachment;
    std::unique_ptr<SliderAttachment> cycleCountToAddSliderAttachment;
    std::unique_ptr<SliderAttachment> cycleCountToSubtractSliderAttachment;
    std::unique_ptr<SliderAttachment> termsToAddPerCountSliderAttachment;
    std::unique_ptr<SliderAttachment> harmonicRatioSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> ocillatorComboBoxAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> harmonicSeriesModeComboBoxAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomAudioEditor)
};
