#include "CustomAudioEditor.h"

CustomAudioEditor::CustomAudioEditor (RNBO::JuceAudioProcessor* const p, RNBO::CoreObject& rnboObject, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (p)
, valueTreeState(vts)
, _audioProcessor(p) // 参照メンバーを初期化（必須）
, _rnboObject(rnboObject)
{
    // ルック＆フィールの設定
    midnightLookAndFeel.setColourScheme(juce::LookAndFeel_V4::getMidnightColourScheme());

    //terms
    addAndMakeVisible(dial1Slider);
    // デバッグ: vts の state を確認
    DBG("vts.state: " + valueTreeState.state.toXmlString());

    std::cout << "terms" << std::endl;
    //スライダーひAPVTSのパラメータを紐づけます。
    dial1Attachment.reset (new SliderAttachment (valueTreeState, "terms", dial1Slider));
    dial1Slider.setSliderStyle(juce::Slider::IncDecButtons);
    dial1Slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, dial1Slider.getTextBoxWidth(), dial1Slider.getTextBoxHeight());
    dial1Slider.setLookAndFeel(&midnightLookAndFeel);

    addAndMakeVisible(label1);
    label1.setText ("terms", juce::dontSendNotification);
    label1.setJustificationType(juce::Justification::centred);
    
    //filterOnOff
    addAndMakeVisible(filterButton);
    std::cout << "filterOnOff" << std::endl;
    filterButton.setButtonText("filter On Off");
    button1Attachment.reset (new ButtonAttachment (valueTreeState, "filterOnOff", filterButton));
    filterButton.setLookAndFeel(&midnightLookAndFeel);
    
    //cutoffOvertone
    addAndMakeVisible(dial2Slider);
    std::cout << "cutoffOvertone" << std::endl;
    dial2Attachment.reset (new SliderAttachment (valueTreeState, "cutoffOvertone", dial2Slider));
    dial2Slider.setSliderStyle(juce::Slider::IncDecButtons);  
    dial2Slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, dial2Slider.getTextBoxWidth(), dial2Slider.getTextBoxHeight());
    dial2Slider.setLookAndFeel(&midnightLookAndFeel);

    addAndMakeVisible(label2);
    label2.setText ("cutoffOvertone", juce::dontSendNotification);
    label2.setJustificationType(juce::Justification::centred);
    
    
    //attenuation
    addAndMakeVisible(dial3Slider);
    std::cout << "attenuation" << std::endl;
    dial3Attachment.reset (new SliderAttachment (valueTreeState, "attenuation", dial3Slider));
    dial3Slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    dial3Slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, dial3Slider.getTextBoxWidth(), dial3Slider.getTextBoxHeight());
    dial3Slider.setLookAndFeel(&midnightLookAndFeel);

    addAndMakeVisible(label3);
    label3.setText ("attenuation", juce::dontSendNotification);
    label3.setJustificationType(juce::Justification::centred);

    //ocillator
    addAndMakeVisible(selectComboBox);
    selectComboBox.addItem("Square", 1);
    selectComboBox.addItem("Triangle", 2);
    selectComboBox.addItem("Sawtooth", 3); 
    selectComboBox.setSelectedItemIndex(0);
    comboBoxAttachment.reset (new juce::AudioProcessorValueTreeState::ComboBoxAttachment (valueTreeState, "ocillator", selectComboBox));
    selectComboBox.setLookAndFeel(&midnightLookAndFeel);    
    addAndMakeVisible(label0);
    label0.setText ("ocillator", juce::dontSendNotification);
    label0.setJustificationType(juce::Justification::centred);

    //attack
    addAndMakeVisible(dial4Slider);
    std::cout << "attack" << std::endl;
    dial4Attachment.reset (new SliderAttachment (valueTreeState, "attack", dial4Slider));
    dial4Slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    dial4Slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, dial4Slider.getTextBoxWidth(), dial7Slider.getTextBoxHeight());
    dial4Slider.setLookAndFeel(&midnightLookAndFeel);    

    addAndMakeVisible(label4);
    label4.setText ("attack", juce::dontSendNotification);
    label4.setJustificationType(juce::Justification::centred);


    //decay
    addAndMakeVisible(dial5Slider);
    std::cout << "decay" << std::endl;
    dial5Attachment.reset (new SliderAttachment (valueTreeState, "decay", dial5Slider));
    dial5Slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    dial5Slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, dial5Slider.getTextBoxWidth(), dial7Slider.getTextBoxHeight());
    dial5Slider.setLookAndFeel(&midnightLookAndFeel);    

    addAndMakeVisible(label5);
    label5.setText ("decay", juce::dontSendNotification);
    label5.setJustificationType(juce::Justification::centred);


    //sustain
    addAndMakeVisible(dial6Slider);
    std::cout << "sustain" << std::endl;
    dial6Attachment.reset (new SliderAttachment (valueTreeState, "sustain", dial6Slider));
    dial6Slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    dial6Slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, dial6Slider.getTextBoxWidth(), dial7Slider.getTextBoxHeight());
    dial6Slider.setLookAndFeel(&midnightLookAndFeel);    

    addAndMakeVisible(label6);
    label6.setText ("sustain", juce::dontSendNotification);
    label6.setJustificationType(juce::Justification::centred);


    //release
    addAndMakeVisible(dial7Slider);
    std::cout << "release" << std::endl;
    dial7Attachment.reset (new SliderAttachment (valueTreeState, "release", dial7Slider));
    dial7Slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    dial7Slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, dial7Slider.getTextBoxWidth(), dial7Slider.getTextBoxHeight());
    dial7Slider.setLookAndFeel(&midnightLookAndFeel);    

    addAndMakeVisible(label7);
    label7.setText ("release", juce::dontSendNotification);
    label7.setJustificationType(juce::Justification::centred);

    //release
    addAndMakeVisible(dial8Slider);
    std::cout << "amp" << std::endl;
    dial8Attachment.reset (new SliderAttachment (valueTreeState, "amp", dial8Slider));
    dial8Slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    dial8Slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, dial7Slider.getTextBoxWidth(), dial8Slider.getTextBoxHeight());
    dial8Slider.setLookAndFeel(&midnightLookAndFeel);    

    addAndMakeVisible(label8);
    label8.setText ("amp", juce::dontSendNotification);
    label8.setJustificationType(juce::Justification::centred);


    
    _audioProcessor->addListener(this);
    setSize(900, 400);
}

CustomAudioEditor::~CustomAudioEditor()
{
    _audioProcessor->removeListener(this);
    
}

void CustomAudioEditor::paint (Graphics& g)
{
    // Get the background color from the midnight scheme
    auto backgroundColour = juce::LookAndFeel_V4::getMidnightColourScheme().getUIColour(juce::LookAndFeel_V4::ColourScheme::UIColour::windowBackground);

    // Fill the entire component with this color
    g.fillAll(backgroundColour);
    
    // Any additional painting code goes here

}

void CustomAudioEditor::resized()
{// Define some constants for consistent sizing and spacing
    auto area = getLocalBounds();
    const int componentWidth1 = (area.getWidth() - 80)/4;
    const int componentWidth2 = (area.getWidth() - 80)/4;
    const int componentWidth3 = (area.getWidth() - 100)/4;
    const int componentHeight = area.getHeight() / 3;
    const int padding = 20;            // Space between components

    // Top row: dial1 and ToggleButton1
    selectComboBox.setBounds(padding,  padding + 10, componentWidth2 ,  componentHeight / 2);
    dial1Slider.setBounds(selectComboBox.getRight() + padding, padding + 20,  componentWidth2 * 2, componentHeight / 2);
    dial8Slider.setBounds(dial1Slider.getRight() + padding, padding ,  componentWidth2 , componentHeight / 1.5  );

    // Second row: ToggleButton2, dial2, dial3
    filterButton.setBounds(padding, dial1Slider.getBottom() + padding + 10, componentWidth2, componentHeight);
    dial2Slider.setBounds( filterButton.getRight() + padding, dial1Slider.getBottom() + padding + 40 , componentWidth2 * 2, componentHeight / 2);
    dial3Slider.setBounds(dial2Slider.getRight() + padding, dial1Slider.getBottom() + padding + 10, componentWidth2,  componentHeight /1.5 );

    // Bottom row: dial4, dial5, dial6, dial7, dial8
    int bottomRowY = dial3Slider.getBottom() + padding;

    dial4Slider.setBounds(padding,  bottomRowY + 10, componentWidth3, componentHeight);
    dial5Slider.setBounds(dial4Slider.getRight() + padding, bottomRowY + 10, componentWidth3, componentHeight);
    dial6Slider.setBounds(dial5Slider.getRight() + padding, bottomRowY + 10, componentWidth3, componentHeight);
    dial7Slider.setBounds(dial6Slider.getRight() + padding, bottomRowY + 10, componentWidth3, componentHeight);

    label0.setBounds(selectComboBox.getX(), selectComboBox.getY()-40, selectComboBox.getWidth(),selectComboBox.getHeight() );
    label1.setBounds(dial1Slider.getX(), dial1Slider.getY()-20, dial1Slider.getWidth(),dial1Slider.getTextBoxHeight() );
    label2.setBounds(dial2Slider.getX(), dial2Slider.getY()-20, dial2Slider.getWidth(),dial2Slider.getTextBoxHeight() );
    label3.setBounds(dial3Slider.getX(), dial3Slider.getY()-10, dial3Slider.getWidth(),dial3Slider.getTextBoxHeight() );
    label4.setBounds(dial4Slider.getX(), dial4Slider.getY()-10, dial4Slider.getWidth(),dial4Slider.getTextBoxHeight() );
    label5.setBounds(dial5Slider.getX(), dial5Slider.getY()-10, dial5Slider.getWidth(),dial5Slider.getTextBoxHeight() );
    label6.setBounds(dial6Slider.getX(), dial6Slider.getY()-10, dial6Slider.getWidth(),dial6Slider.getTextBoxHeight() );
    label7.setBounds(dial7Slider.getX(), dial7Slider.getY()-10, dial7Slider.getWidth(),dial7Slider.getTextBoxHeight() );
    label8.setBounds(dial8Slider.getX(), dial8Slider.getY()-10, dial8Slider.getWidth(),dial8Slider.getTextBoxHeight() );
}


void CustomAudioEditor::audioProcessorParameterChanged (AudioProcessor*, int parameterIndex, float value)
{
   
}
