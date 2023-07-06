#include "HayesReverbFrontPanelComponent.h"
#include "ParamIDs.h"
#include "GUI/CustomColours.h"

EditorContent::EditorContent (HayesReverbAudioProcessor& p, juce::UndoManager& um)
    : apvts (p.apvts), undoManager (um),
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

void EditorContent::resized()
{
    const juce::Rectangle<int> baseDialBounds { 0, 73, 80, 96 };
    sizeDial.setBounds  (baseDialBounds.withX (46));
    dampDial.setBounds  (baseDialBounds.withX (144));
    widthDial.setBounds (baseDialBounds.withX (242));
    mixDial.setBounds   (baseDialBounds.withX (340));
    freezeButton.setBounds (440, 110, 68, 32);
}

bool EditorContent::keyPressed (const juce::KeyPress& k)
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
