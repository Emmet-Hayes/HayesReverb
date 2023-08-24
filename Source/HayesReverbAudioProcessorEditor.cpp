#include "HayesReverbAudioProcessor.h"
#include "HayesReverbAudioProcessorEditor.h"

HayesReverbAudioProcessorEditor::HayesReverbAudioProcessorEditor (HayesReverbAudioProcessor& p, juce::UndoManager& um)
:   BaseAudioProcessorEditor { p }
,   processor            { p }
,   presetBar            { p }
,   freezeAttachment (*processor.apvts.getParameter (ParamIDs::freeze), freezeButton, &um)
{
    setLookAndFeel(&customLookAndFeel);
    const auto ratio = static_cast<double> (defaultWidth) / defaultHeight;
    setResizable(false, true);
    getConstrainer()->setFixedAspectRatio (ratio);
    getConstrainer()->setSizeLimits(defaultWidth, defaultHeight, defaultWidth * 2, defaultHeight * 2);
    image = juce::ImageCache::getFromMemory(BinaryData::bg_file_jpg, BinaryData::bg_file_jpgSize);

    sizeLabel.setText("Size", juce::dontSendNotification);
    dampLabel.setText("Damp", juce::dontSendNotification);
    widthLabel.setText("Width", juce::dontSendNotification);
    mixLabel.setText("Mix", juce::dontSendNotification);
    
    addAndMakeVisible(sizeLabel);
    addAndMakeVisible(dampLabel);
    addAndMakeVisible(widthLabel);
    addAndMakeVisible(mixLabel);

    sizeDial.setSliderStyle(juce::Slider::Rotary);
    dampDial.setSliderStyle(juce::Slider::Rotary);
    widthDial.setSliderStyle(juce::Slider::Rotary);
    mixDial.setSliderStyle(juce::Slider::Rotary);

    sizeDial.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    dampDial.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    widthDial.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mixDial.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);

    addAndMakeVisible (sizeDial);
    addAndMakeVisible (dampDial);
    addAndMakeVisible (widthDial);
    addAndMakeVisible (mixDial);
    addAndMakeVisible (freezeButton);

    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    sizeAttachment  = std::make_unique<Attachment>(processor.apvts, ParamIDs::size,  sizeDial);
    dampAttachment  = std::make_unique<Attachment>(processor.apvts, ParamIDs::damp,  dampDial);
    widthAttachment = std::make_unique<Attachment>(processor.apvts, ParamIDs::width, widthDial);
    mixAttachment   = std::make_unique<Attachment>(processor.apvts, ParamIDs::mix,   mixDial);
  
    setSize (defaultWidth, defaultHeight + 20);
    addAndMakeVisible(presetBar);
}

HayesReverbAudioProcessorEditor::~HayesReverbAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

void HayesReverbAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.drawImage(image, 0, 0, getWidth(), getHeight(), 0, 500, 1000, 500); 
}

void HayesReverbAudioProcessorEditor::resized()
{
    const auto scale = static_cast<float> (getWidth()) / HayesReverbAudioProcessorEditor::defaultWidth;

    auto setBoundsAndApplyScaling = [&](juce::Component* component, int x, int y, int w, int h, bool isSlider = false)
    {
        component->setBounds(static_cast<int>(x * scale), static_cast<int>(y * scale),
            static_cast<int>(w * scale), static_cast<int>(h * scale));
        if (isSlider)
            dynamic_cast<juce::Slider*>(component)->setTextBoxStyle(juce::Slider::TextBoxBelow, false, static_cast<int>(70 * scale), static_cast<int>(20 * scale));
    };
    
    customLookAndFeel.setWindowScale(scale);
    setBoundsAndApplyScaling(&presetBar, 0, 0, 500, 20);
    setBoundsAndApplyScaling(&sizeLabel, 41, 70, 70, 20);
    setBoundsAndApplyScaling(&sizeDial, 16, 95, 80, 80, true);
    setBoundsAndApplyScaling(&dampLabel, 134, 70, 70, 20);
    setBoundsAndApplyScaling(&dampDial, 114, 95, 80, 80, true);
    setBoundsAndApplyScaling(&widthLabel, 232, 70, 70, 20);
    setBoundsAndApplyScaling(&widthDial, 212, 95, 80, 80, true);
    setBoundsAndApplyScaling(&mixLabel, 335, 70, 70, 20);
    setBoundsAndApplyScaling(&mixDial, 310, 95, 80, 80, true);
    setBoundsAndApplyScaling(&freezeButton, 410, 110, 68, 32);
}
