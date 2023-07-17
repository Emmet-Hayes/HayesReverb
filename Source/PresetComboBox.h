#pragma once
#include <JuceHeader.h>
#include "HayesReverbAudioProcessor.h"

class PresetBar;

class PresetComboBox : public juce::ComboBox
{
public:
    PresetComboBox(HayesReverbAudioProcessor& p, PresetBar* bar);
    void mouseDown(const juce::MouseEvent& event) override;
    void savePreset();
    void loadPreset();
    void deletePreset();

    HayesReverbAudioProcessor& processor;
    PresetBar* presetBar;
    juce::PopupMenu saveLoadMenu;
};
