#include "HayesReverbFrontPanelComponent.h"
#include "HayesReverbAudioProcessorEditor.h"
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

    sizeAttachment  = std::make_unique<Attachment>(apvts, ParamIDs::size,  sizeDial);
    dampAttachment  = std::make_unique<Attachment>(apvts, ParamIDs::damp,  dampDial);
    widthAttachment = std::make_unique<Attachment>(apvts, ParamIDs::width, widthDial);
    mixAttachment   = std::make_unique<Attachment>(apvts, ParamIDs::mix,   mixDial);
}

void HayesReverbFrontPanelComponent::resized()
{
    const auto scale = static_cast<float> (getWidth()) / HayesReverbAudioProcessorEditor::defaultWidth;

    auto setBoundsAndApplyScaling = [&](juce::Component* component, int x, int y, int w, int h, bool isSlider = false)
    {
        component->setBounds(static_cast<int>(x * scale), static_cast<int>(y * scale),
            static_cast<int>(w * scale), static_cast<int>(h * scale));
        if (isSlider)
            dynamic_cast<juce::Slider*>(component)->setTextBoxStyle(juce::Slider::TextBoxBelow, false, static_cast<int>(70 * scale), static_cast<int>(20 * scale));
    };
    
    setBoundsAndApplyScaling(&sizeLabel, 41, 60, 70, 20);
    setBoundsAndApplyScaling(&sizeDial, 16, 95, 80, 80, true);
    setBoundsAndApplyScaling(&dampLabel, 134, 60, 70, 20);
    setBoundsAndApplyScaling(&dampDial, 114, 95, 80, 80, true);
    setBoundsAndApplyScaling(&widthLabel, 232, 60, 70, 20);
    setBoundsAndApplyScaling(&widthDial, 212, 95, 80, 80, true);
    setBoundsAndApplyScaling(&mixLabel, 335, 60, 70, 20);
    setBoundsAndApplyScaling(&mixDial, 310, 95, 80, 80, true);
    setBoundsAndApplyScaling(&freezeButton, 410, 110, 68, 32);
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
