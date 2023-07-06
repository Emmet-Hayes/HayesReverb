#pragma once

#include <JuceHeader.h>
#include "HayesReverbAudioProcessor.h"
#include "GUI/Dial.h"
#include "GUI/FreezeButton.h"


class EditorContent  : public juce::Component
{
public:
    EditorContent (HayesReverbAudioProcessor& p, juce::UndoManager& um);
    
    void resized() override;

    bool keyPressed (const juce::KeyPress& k) override;

private:
    juce::AudioProcessorValueTreeState& apvts;
    juce::UndoManager& undoManager;
    
    Dial sizeDial;
    Dial dampDial;
    Dial widthDial;
    Dial mixDial;

    FreezeButton freezeButton;

    juce::ButtonParameterAttachment freezeAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EditorContent)
};
