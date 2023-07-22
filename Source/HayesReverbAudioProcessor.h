#pragma once
#include <JuceHeader.h>
#include "../../Common/BaseAudioProcessor.h"

class HayesReverbAudioProcessor  : public BaseAudioProcessor
{
public:
    HayesReverbAudioProcessor();

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    juce::AudioProcessorEditor* createEditor() override;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout() override;

private:
    void updateReverbParams();
    
    juce::AudioParameterFloat* size   { nullptr };
    juce::AudioParameterFloat* damp   { nullptr };
    juce::AudioParameterFloat* width  { nullptr };
    juce::AudioParameterFloat* mix    { nullptr };
    juce::AudioParameterBool* freeze  { nullptr };

    juce::dsp::Reverb::Parameters params;
    juce::dsp::Reverb reverb;

    juce::UndoManager undoManager;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HayesReverbAudioProcessor)
};
