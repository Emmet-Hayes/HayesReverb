#pragma once

#include <JuceHeader.h>
#include "HayesReverbAudioProcessor.h"
#include "HayesReverbFrontPanelComponent.h"
#include "GUI/CustomLookAndFeel.h"

class HayesReverbAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    HayesReverbAudioProcessorEditor (HayesReverbAudioProcessor&, 
                                      juce::UndoManager& um);

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    EditorContent editorContent;

    juce::Image image;
    const int defaultWidth  { 500 };
    const int defaultHeight { 250 };

    struct SharedLnf
    {
        SharedLnf()  { juce::LookAndFeel::setDefaultLookAndFeel (&customLookAndFeel); }
        ~SharedLnf() { juce::LookAndFeel::setDefaultLookAndFeel (nullptr); }

        EditorLnf customLookAndFeel;
    };

    juce::SharedResourcePointer<SharedLnf> lnf;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HayesReverbAudioProcessorEditor)
};
