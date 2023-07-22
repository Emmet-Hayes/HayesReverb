#pragma once

#include <JuceHeader.h>
#include "HayesReverbAudioProcessor.h"
#include "HayesReverbFrontPanelComponent.h"
#include "../../Common/BaseAudioProcessorEditor.h"
#include "../../Common/CustomLookAndFeel.h"
#include "../../Common/PresetBar.h"

class HayesReverbAudioProcessorEditor  : public BaseAudioProcessorEditor
{
public:
    HayesReverbAudioProcessorEditor (HayesReverbAudioProcessor&, 
                                      juce::UndoManager& um);

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    HayesReverbFrontPanelComponent editorContent;
    PresetBar presetBar;
    juce::Image image;
    const int defaultWidth  { 500 };
    const int defaultHeight { 250 };

    struct SharedLnf
    {
        SharedLnf()  { juce::LookAndFeel::setDefaultLookAndFeel (&customLookAndFeel); }
        ~SharedLnf() { juce::LookAndFeel::setDefaultLookAndFeel (nullptr); }

        CustomLookAndFeel customLookAndFeel;
    };

    juce::SharedResourcePointer<SharedLnf> lnf;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HayesReverbAudioProcessorEditor)
};
