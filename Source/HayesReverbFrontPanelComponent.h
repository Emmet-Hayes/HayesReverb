#pragma once

#include <JuceHeader.h>
#include "HayesReverbAudioProcessor.h"
#include "../../Common/PercentSlider.h"
#include "../../Common/CustomLookAndFeel.h"
#include "GUI/FreezeButton.h"


class HayesReverbFrontPanelComponent : public juce::Component
{
public:
    HayesReverbFrontPanelComponent (HayesReverbAudioProcessor& p, juce::UndoManager& um);
    
    void resized() override;

    bool keyPressed (const juce::KeyPress& k) override;

private:
    juce::AudioProcessorValueTreeState& apvts;
    juce::UndoManager& undoManager;

    CustomLookAndFeel customLookAndFeel;

    PercentSlider sizeDial;
    PercentSlider dampDial;
    PercentSlider widthDial;
    PercentSlider mixDial;
    FreezeButton freezeButton;

    juce::Label sizeLabel, dampLabel, widthLabel, mixLabel;

    juce::ButtonParameterAttachment freezeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sizeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dampAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> widthAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HayesReverbFrontPanelComponent)
};
