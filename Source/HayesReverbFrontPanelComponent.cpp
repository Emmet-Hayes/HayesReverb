#include "HayesReverbFrontPanelComponent.h"
#include "ParamIDs.h"
#include "../../Common/CustomColours.h"

HayesReverbFrontPanelComponent::HayesReverbFrontPanelComponent (HayesReverbAudioProcessor& p, juce::UndoManager& um)
:   apvts (p.apvts), undoManager (um),
    freezeAttachment (*apvts.getParameter (ParamIDs::freeze), freezeButton, &um)
{
    setWantsKeyboardFocus (true);
    setLookAndFeel(&customLookAndFeel);

    sizeLabel.setText("Size", juce::dontSendNotification);
    dampLabel.setText("Damp", juce::dontSendNotification);
    widthLabel.setText("Width", juce::dontSendNotification);
    mixLabel.setText("Mix", juce::dontSendNotification);
    
    addAndMakeVisible(sizeLabel);
    addAndMakeVisible(dampLabel);
    addAndMakeVisible(widthLabel);
    addAndMakeVisible(mixLabel);

    sizeDial.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    dampDial.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    widthDial.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    mixDial.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);

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

    sizeAttachment  = std::make_unique<Attachment>(apvts, ParamIDs::size,  sizeDial);
    dampAttachment  = std::make_unique<Attachment>(apvts, ParamIDs::damp,  dampDial);
    widthAttachment = std::make_unique<Attachment>(apvts, ParamIDs::width, widthDial);
    mixAttachment   = std::make_unique<Attachment>(apvts, ParamIDs::mix,   mixDial);
}

void HayesReverbFrontPanelComponent::resized()
{
    const juce::Rectangle<int> baseDialBounds { 0, 95, 80, 80 };
    sizeLabel.setBounds(baseDialBounds.withX(41).withY(50));
    sizeDial.setBounds  (baseDialBounds.withX (16));
    dampLabel.setBounds(baseDialBounds.withX(134).withY(50));
    dampDial.setBounds  (baseDialBounds.withX (114));
    widthLabel.setBounds(baseDialBounds.withX(232).withY(50));
    widthDial.setBounds (baseDialBounds.withX (212));
    mixLabel.setBounds(baseDialBounds.withX(335).withY(50));
    mixDial.setBounds   (baseDialBounds.withX (310));
    freezeButton.setBounds (410, 110, 68, 32);
}

bool HayesReverbFrontPanelComponent::keyPressed (const juce::KeyPress& k)
{
    const auto cmdZ = juce::KeyPress ('z', juce::ModifierKeys::commandModifier, 0);

    if (k == cmdZ && undoManager.canUndo())
    {
        undoManager.undo();
        return true;
    }

    const auto cmdShiftZ = juce::KeyPress ('z', juce::ModifierKeys::commandModifier 
                                                | juce::ModifierKeys::shiftModifier, 0);
    
    if (k == cmdShiftZ && undoManager.canRedo())
    {
        undoManager.redo();
        return true;
    }

    return false;
}
