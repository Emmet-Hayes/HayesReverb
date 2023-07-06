#pragma once
#include <JuceHeader.h>

class HayesReverbAudioProcessor  : public juce::AudioProcessor
{
public:
    HayesReverbAudioProcessor();

    void releaseResources() override {}
    bool hasEditor() const override { return true; }
    const juce::String getName() const override { return JucePlugin_Name; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }
    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int index) override {}
    const juce::String getProgramName(int index) override { return juce::String(); }
    void changeProgramName(int index, const juce::String& newName) override {}

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    juce::AudioProcessorEditor* createEditor() override;
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState apvts;
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
