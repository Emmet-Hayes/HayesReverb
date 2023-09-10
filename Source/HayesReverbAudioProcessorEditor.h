#pragma once

#include "../../Common/BaseAudioProcessorEditor.h"
#include "../../Common/CustomLookAndFeel.h"
#include "../../Common/PresetBar.h"
#include "../../Common/PercentSlider.h"

#include "GUI/FreezeButton.h"

#include "HayesReverbAudioProcessor.h"
#include "ParamIDs.h"


class HayesReverbAudioProcessorEditor  : public BaseAudioProcessorEditor
{
public:
    HayesReverbAudioProcessorEditor (HayesReverbAudioProcessor&, 
                                      juce::UndoManager& um);
    ~HayesReverbAudioProcessorEditor();

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void addAllGUIComponents();

    CustomLookAndFeel customLookAndFeel;

    HayesReverbAudioProcessor& processor;
  
    PresetBar presetBar;
    
    juce::Image image;

    PercentSlider sizeDial, dampDial, widthDial, mixDial;
    FreezeButton freezeButton;

    juce::Label sizeLabel, dampLabel, widthLabel, mixLabel;

    juce::ButtonParameterAttachment freezeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sizeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dampAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> widthAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixAttachment;
  
    static constexpr int defaultWidth  { 500 };
    static constexpr int defaultHeight { 250 };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HayesReverbAudioProcessorEditor)
};
