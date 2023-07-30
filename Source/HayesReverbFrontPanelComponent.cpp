#include "HayesReverbFrontPanelComponent.h"
#include "ParamIDs.h"
#include "../../Common/CustomColours.h"

HayesReverbFrontPanelComponent::HayesReverbFrontPanelComponent (HayesReverbAudioProcessor& p, juce::UndoManager& um)
:   apvts (p.apvts), undoManager (um),
    sizeDial  (*apvts.getParameter (ParamIDs::size),  &um),
    dampDial  (*apvts.getParameter (ParamIDs::damp),  &um),
    widthDial (*apvts.getParameter (ParamIDs::width), &um),
    mixDial   (*apvts.getParameter (ParamIDs::mix),   &um),
    freezeAttachment (*apvts.getParameter (ParamIDs::freeze), freezeButton, &um)
{
    setWantsKeyboardFocus (true);

    addAndMakeVisible (sizeDial);
    addAndMakeVisible (dampDial);
    addAndMakeVisible (widthDial);
    addAndMakeVisible (mixDial);
    addAndMakeVisible (freezeButton);
}

void HayesReverbFrontPanelComponent::resized()
{
    const juce::Rectangle<int> baseDialBounds { 0, 73, 80, 96 };
    sizeDial.setBounds  (baseDialBounds.withX (16));
    dampDial.setBounds  (baseDialBounds.withX (114));
    widthDial.setBounds (baseDialBounds.withX (212));
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
