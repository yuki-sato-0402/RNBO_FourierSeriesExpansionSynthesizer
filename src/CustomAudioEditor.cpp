#include "CustomAudioProcessor.h"
#include "CustomAudioEditor.h"

CustomAudioEditor::CustomAudioEditor (CustomAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), valueTreeState(vts)
{
    midnightLookAndFeel.setColourScheme(juce::LookAndFeel_V4::getMidnightColourScheme());

    addAndMakeVisible(termsSlider);
    termsSliderAttachment.reset (new SliderAttachment (valueTreeState, "terms", termsSlider));
    termsSlider.setSliderStyle(juce::Slider::IncDecButtons);
    termsSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, termsSlider.getTextBoxWidth(), termsSlider.getTextBoxHeight());
    termsSlider.setLookAndFeel(&midnightLookAndFeel);

    addAndMakeVisible(termsLabel);
    termsLabel.setText ("terms", juce::dontSendNotification);
    termsLabel.setJustificationType(juce::Justification::centred);
    
    addAndMakeVisible(filterButton);
    filterButton.setButtonText("filter On Off");
    button1Attachment.reset (new ButtonAttachment (valueTreeState, "filterOnOff", filterButton));
    filterButton.setLookAndFeel(&midnightLookAndFeel);
    
    addAndMakeVisible(cutoffOvertoneSlider);
    cutoffOvertoneSliderAttachment.reset (new SliderAttachment (valueTreeState, "cutoffOvertone", cutoffOvertoneSlider));
    cutoffOvertoneSlider.setSliderStyle(juce::Slider::IncDecButtons);  
    cutoffOvertoneSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, cutoffOvertoneSlider.getTextBoxWidth(), cutoffOvertoneSlider.getTextBoxHeight());
    cutoffOvertoneSlider.setLookAndFeel(&midnightLookAndFeel);

    addAndMakeVisible(cutoffOvertoneLabel);
    cutoffOvertoneLabel.setText ("cutoffOvertone", juce::dontSendNotification);
    cutoffOvertoneLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(attenuationSlider);
    attenuationSliderAttachment.reset (new SliderAttachment (valueTreeState, "attenuation", attenuationSlider));
    attenuationSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    attenuationSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, attenuationSlider.getTextBoxWidth(), attenuationSlider.getTextBoxHeight());
    attenuationSlider.setLookAndFeel(&midnightLookAndFeel);

    addAndMakeVisible(attenuationLabel);
    attenuationLabel.setText ("attenuation", juce::dontSendNotification);
    attenuationLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(selectComboBox);
    selectComboBox.addItem("Square", 1);
    selectComboBox.addItem("Triangle", 2);
    selectComboBox.addItem("Sawtooth", 3); 
    selectComboBox.setSelectedItemIndex(0);
    comboBoxAttachment.reset (new juce::AudioProcessorValueTreeState::ComboBoxAttachment (valueTreeState, "ocillator", selectComboBox));
    selectComboBox.setLookAndFeel(&midnightLookAndFeel);    
    addAndMakeVisible(ocillatorLabel);
    ocillatorLabel.setText ("ocillator", juce::dontSendNotification);
    ocillatorLabel.setJustificationType(juce::Justification::centred);


        // --- PosNeg UI ---
    addAndMakeVisible(posButton);
    addAndMakeVisible(negButton);
    posButton.setButtonText("Pos");
    negButton.setButtonText("Neg");
    posButton.setLookAndFeel(&midnightLookAndFeel);
    negButton.setLookAndFeel(&midnightLookAndFeel);
    posButton.setClickingTogglesState(true);
    negButton.setClickingTogglesState(true);
    posButton.setRadioGroupId(2001);
    negButton.setRadioGroupId(2001);
    posButton.setToggleState(true, juce::dontSendNotification);
    negButton.setToggleState(false, juce::dontSendNotification);
    posButton.onClick = [this]() {
        if (posButton.getToggleState()) {
            valueTreeState.getParameter("PosNeg")->beginChangeGesture();
            valueTreeState.getParameter("PosNeg")->setValueNotifyingHost(1.0f);
            valueTreeState.getParameter("PosNeg")->endChangeGesture();
        }
    };
    negButton.onClick = [this]() {
        if (negButton.getToggleState()) {
            valueTreeState.getParameter("PosNeg")->beginChangeGesture();
            valueTreeState.getParameter("PosNeg")->setValueNotifyingHost(0.0f);
            valueTreeState.getParameter("PosNeg")->endChangeGesture();
        }
    };

    addAndMakeVisible(posNegSyncButton);
    posNegSyncButton.setButtonText("PosNegSync");
    button1Attachment.reset (new ButtonAttachment (valueTreeState, "PosNegSync", posNegSyncButton));
    posNegSyncButton.setLookAndFeel(&midnightLookAndFeel);  
    posNegSyncButton.onClick = [this]() {
    if(posNegSyncButton.getToggleState()) {
        posButton.setEnabled(false);
        negButton.setEnabled(false);
        //posButton.setToggleState(true, juce::dontSendNotification);
    } else {
        posButton.setEnabled(true);
        negButton.setEnabled(true);
    }};

    addAndMakeVisible(cycleCountToAddSlider);
    cycleCountToAddSliderAttachment.reset (new SliderAttachment (valueTreeState, "cycleCountToAdd", cycleCountToAddSlider));
    cycleCountToAddSlider.setSliderStyle(juce::Slider::IncDecButtons);
    cycleCountToAddSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, cycleCountToAddSlider.getTextBoxWidth(), cycleCountToAddSlider.getTextBoxHeight());
    cycleCountToAddSlider.setLookAndFeel(&midnightLookAndFeel);

    addAndMakeVisible(cycleCountToAddLabel);
    cycleCountToAddLabel.setText ("cycleCountToAdd", juce::dontSendNotification);
    cycleCountToAddLabel.setJustificationType(juce::Justification::centred);    

    addAndMakeVisible(cycleCountToSubtractSlider);
    cycleCountToSubtractSliderAttachment.reset (new SliderAttachment (valueTreeState, "cycleCountToSubtract", cycleCountToSubtractSlider));
    cycleCountToSubtractSlider.setSliderStyle(juce::Slider::IncDecButtons);
    cycleCountToSubtractSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, cycleCountToSubtractSlider.getTextBoxWidth(), cycleCountToSubtractSlider.getTextBoxHeight());
    cycleCountToSubtractSlider.setLookAndFeel(&midnightLookAndFeel);

    addAndMakeVisible(cycleCountToSubtractLabel);
    cycleCountToSubtractLabel.setText ("cycleCountToSubtract", juce::dontSendNotification);
    cycleCountToSubtractLabel.setJustificationType(juce::Justification::centred);   

    addAndMakeVisible(termsToAddPerCountSlider);
    termsToAddPerCountSliderAttachment.reset (new SliderAttachment (valueTreeState, "termsToAddPerCount", termsToAddPerCountSlider));
    termsToAddPerCountSlider.setSliderStyle(juce::Slider::IncDecButtons);
    termsToAddPerCountSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, termsToAddPerCountSlider.getTextBoxWidth(), termsToAddPerCountSlider.getTextBoxHeight());
    termsToAddPerCountSlider.setLookAndFeel(&midnightLookAndFeel);

    addAndMakeVisible(termsToAddPerCountLabel);
    termsToAddPerCountLabel.setText ("termsToAddPerCount", juce::dontSendNotification);
    termsToAddPerCountLabel.setJustificationType(juce::Justification::centred);     

    addAndMakeVisible(attackSlider);
    attackSliderAttachment.reset (new SliderAttachment (valueTreeState, "attack", attackSlider));
    attackSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    attackSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, attackSlider.getTextBoxWidth(), releaseSlider.getTextBoxHeight());
    attackSlider.setLookAndFeel(&midnightLookAndFeel);    

    addAndMakeVisible(attackLabel);
    attackLabel.setText ("attack", juce::dontSendNotification);
    attackLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(decaySlider);
    decaySliderAttachment.reset (new SliderAttachment (valueTreeState, "decay", decaySlider));
    decaySlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    decaySlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, decaySlider.getTextBoxWidth(), releaseSlider.getTextBoxHeight());
    decaySlider.setLookAndFeel(&midnightLookAndFeel);    

    addAndMakeVisible(decayLabel);
    decayLabel.setText ("decay", juce::dontSendNotification);
    decayLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(sustainSlider);
    sustainSliderAttachment.reset (new SliderAttachment (valueTreeState, "sustain", sustainSlider));
    sustainSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    sustainSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, sustainSlider.getTextBoxWidth(), releaseSlider.getTextBoxHeight());
    sustainSlider.setLookAndFeel(&midnightLookAndFeel);    

    addAndMakeVisible(sustainLabel);
    sustainLabel.setText ("sustain", juce::dontSendNotification);
    sustainLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(releaseSlider);
    releaseSliderAttachment.reset (new SliderAttachment (valueTreeState, "release", releaseSlider));
    releaseSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    releaseSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, releaseSlider.getTextBoxWidth(), releaseSlider.getTextBoxHeight());
    releaseSlider.setLookAndFeel(&midnightLookAndFeel);    

    addAndMakeVisible(releaseLabel);
    releaseLabel.setText ("release", juce::dontSendNotification);
    releaseLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(ampSlider);
    ampSliderAttachment.reset (new SliderAttachment (valueTreeState, "amp", ampSlider));
    ampSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    ampSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, releaseSlider.getTextBoxWidth(), ampSlider.getTextBoxHeight());
    ampSlider.setLookAndFeel(&midnightLookAndFeel);    

    addAndMakeVisible(ampLabel);
    ampLabel.setText ("amp", juce::dontSendNotification);
    ampLabel.setJustificationType(juce::Justification::centred);

    setSize(900, 400);
}


void CustomAudioEditor::paint (Graphics& g)
{
    // Get the background color from the midnight scheme
    auto backgroundColour = juce::LookAndFeel_V4::getMidnightColourScheme().getUIColour(juce::LookAndFeel_V4::ColourScheme::UIColour::windowBackground);

    // Fill the entire component with this color
    g.fillAll(backgroundColour);
}

void CustomAudioEditor::resized()
{
    auto area = getLocalBounds();

    auto componentWidth2 = (area.getWidth() - 120)/5;
    auto componentHeight = (area.getHeight() - 80)/3;
    auto padding = 20;           

    selectComboBox.setBounds(padding,  padding + (componentHeight / 4), componentWidth2,  componentHeight / 2);
    termsSlider.setBounds(selectComboBox.getRight() + padding, padding + (componentHeight / 4),  componentWidth2 , componentHeight  / 2);
    filterButton.setBounds(termsSlider.getRight() + padding, padding, componentWidth2, componentHeight);
    cutoffOvertoneSlider.setBounds( filterButton.getRight() + padding, padding + (componentHeight / 4), componentWidth2 , componentHeight / 2);
    attenuationSlider.setBounds(cutoffOvertoneSlider.getRight() + padding, padding, componentWidth2,  componentHeight);

    posNegSyncButton.setBounds( padding + 10, attenuationSlider.getBottom() + padding, componentWidth2, componentHeight / 4);
    posButton.setBounds( padding + 10, posNegSyncButton.getBottom() + padding, componentWidth2,  componentHeight / 4);
    negButton.setBounds( posButton.getRight(), posNegSyncButton.getBottom() + padding, componentWidth2,  componentHeight / 4);
    cycleCountToAddSlider.setBounds( negButton.getRight() + padding + 10, attenuationSlider.getBottom() + padding + (componentHeight / 4), componentWidth2,  componentHeight  / 2);
    cycleCountToSubtractSlider.setBounds( cycleCountToAddSlider.getRight() + padding, attenuationSlider.getBottom() + padding + (componentHeight / 4), componentWidth2,  componentHeight  / 2);
    termsToAddPerCountSlider.setBounds( cycleCountToSubtractSlider.getRight() + padding, attenuationSlider.getBottom() + padding + (componentHeight / 4), componentWidth2,  componentHeight  / 2);

    ampSlider.setBounds(padding,  termsToAddPerCountSlider.getBottom() + padding + (componentHeight / 4), componentWidth2, componentHeight);
    attackSlider.setBounds(ampSlider.getRight() + padding, termsToAddPerCountSlider.getBottom() + padding + (componentHeight / 4), componentWidth2, componentHeight);
    decaySlider.setBounds(attackSlider.getRight() + padding, termsToAddPerCountSlider.getBottom() + padding + (componentHeight / 4), componentWidth2, componentHeight);
    sustainSlider.setBounds(decaySlider.getRight() + padding, termsToAddPerCountSlider.getBottom() + padding + (componentHeight / 4), componentWidth2, componentHeight);
    releaseSlider.setBounds(sustainSlider.getRight() + padding, termsToAddPerCountSlider.getBottom() + padding + (componentHeight / 4), componentWidth2, componentHeight);

    ocillatorLabel.setBounds(selectComboBox.getX(), selectComboBox.getY()-40, selectComboBox.getWidth(),selectComboBox.getHeight() );
    termsLabel.setBounds(termsSlider.getX(), termsSlider.getY()-20, termsSlider.getWidth(),termsSlider.getTextBoxHeight() );
    cutoffOvertoneLabel.setBounds(cutoffOvertoneSlider.getX(), cutoffOvertoneSlider.getY()-20, cutoffOvertoneSlider.getWidth(),cutoffOvertoneSlider.getTextBoxHeight() );
    attenuationLabel.setBounds(attenuationSlider.getX(), attenuationSlider.getY()-10, attenuationSlider.getWidth(),attenuationSlider.getTextBoxHeight() );
    attackLabel.setBounds(attackSlider.getX(), attackSlider.getY()-10, attackSlider.getWidth(),attackSlider.getTextBoxHeight() );
    decayLabel.setBounds(decaySlider.getX(), decaySlider.getY()-10, decaySlider.getWidth(),decaySlider.getTextBoxHeight() );
    sustainLabel.setBounds(sustainSlider.getX(), sustainSlider.getY()-10, sustainSlider.getWidth(),sustainSlider.getTextBoxHeight() );
    releaseLabel.setBounds(releaseSlider.getX(), releaseSlider.getY()-10, releaseSlider.getWidth(),releaseSlider.getTextBoxHeight() );
    ampLabel.setBounds(ampSlider.getX(), ampSlider.getY()-10, ampSlider.getWidth(),ampSlider.getTextBoxHeight() );
    cycleCountToAddLabel.setBounds(cycleCountToAddSlider.getX(), cycleCountToAddSlider.getY()-20, cycleCountToAddSlider.getWidth(),cycleCountToAddSlider.getTextBoxHeight() );
    cycleCountToSubtractLabel.setBounds(cycleCountToSubtractSlider.getX(), cycleCountToSubtractSlider.getY()-20, cycleCountToSubtractSlider.getWidth(),cycleCountToSubtractSlider.getTextBoxHeight() );
    termsToAddPerCountLabel.setBounds(termsToAddPerCountSlider.getX(), termsToAddPerCountSlider.getY()-20, termsToAddPerCountSlider.getWidth(),termsToAddPerCountSlider.getTextBoxHeight() );
}
