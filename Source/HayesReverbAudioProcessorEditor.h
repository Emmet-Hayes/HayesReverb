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

    static constexpr int defaultWidth  { 500 };
    static constexpr int defaultHeight { 250 };

private:
    HayesReverbFrontPanelComponent editorContent;
    PresetBar presetBar;
    juce::Image image;


    struct SharedLnf
    {
        SharedLnf()  { juce::LookAndFeel::setDefaultLookAndFeel (&customLookAndFeel); }
        ~SharedLnf() { juce::LookAndFeel::setDefaultLookAndFeel (nullptr); }

        CustomLookAndFeel customLookAndFeel;
    };

    juce::SharedResourcePointer<SharedLnf> lnf;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HayesReverbAudioProcessorEditor)
};
