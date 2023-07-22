#include "HayesReverbAudioProcessor.h"
#include "HayesReverbAudioProcessorEditor.h"
#include "ParamIDs.h"


HayesReverbAudioProcessor::HayesReverbAudioProcessor()
:   BaseAudioProcessor { createParameterLayout() }
{
    auto storeFloatParam = [&apvts = this->apvts](auto& param, const auto& paramID)
    {
        param = dynamic_cast<juce::AudioParameterFloat*> (apvts.getParameter (paramID));
        jassert (param != nullptr);
    };

    storeFloatParam (size,  ParamIDs::size); 
    storeFloatParam (damp,  ParamIDs::damp); 
    storeFloatParam (width, ParamIDs::width); 
    storeFloatParam (mix,   ParamIDs::mix); 

    auto storeBoolParam = [&apvts = this->apvts](auto& param, const auto& paramID)
    {
        param = dynamic_cast<juce::AudioParameterBool*> (apvts.getParameter (paramID));
        jassert (param != nullptr);
    };

    storeBoolParam (freeze, ParamIDs::freeze); 
}

juce::AudioProcessorValueTreeState::ParameterLayout HayesReverbAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    auto percentFormat = [](float value, int /*maximumStringLength*/)
    {
        if (value < 10.0f)
            return juce::String (value, 2) + " %";
        else if (value < 100.0f)
            return juce::String (value, 1) + " %";
        else
            return juce::String (value, 0) + " %";
    };

    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::size, 1 },
                                                             ParamIDs::size,
                                                             juce::NormalisableRange<float> { 0.0f, 100.0f, 0.01f, 1.0f },
                                                             50.0f,
                                                             juce::String(),
                                                             juce::AudioProcessorParameter::genericParameter,
                                                             percentFormat,
                                                             nullptr));

    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::damp, 1 },
                                                             ParamIDs::damp,
                                                             juce::NormalisableRange<float> { 0.0f, 100.0f, 0.01f, 1.0f },
                                                             50.0f,
                                                             juce::String(),
                                                             juce::AudioProcessorParameter::genericParameter,
                                                             percentFormat,
                                                             nullptr));

    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::width, 1 },
                                                             ParamIDs::width,
                                                             juce::NormalisableRange<float> { 0.0f, 100.0f, 0.01f, 1.0f },
                                                             50.0f,
                                                             juce::String(),
                                                             juce::AudioProcessorParameter::genericParameter,
                                                             percentFormat,
                                                             nullptr));

    layout.add (std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { ParamIDs::mix, 1 },
                                                             ParamIDs::mix,
                                                             juce::NormalisableRange<float> { 0.0f, 100.0f, 0.01f, 1.0f },
                                                             50.0f,
                                                             juce::String(),
                                                             juce::AudioProcessorParameter::genericParameter,
                                                             percentFormat,
                                                             nullptr));

    layout.add (std::make_unique<juce::AudioParameterBool> (juce::ParameterID { ParamIDs::freeze, 1 },
                                                            ParamIDs::freeze,
                                                            false));

    return layout;
}


void HayesReverbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;

    spec.sampleRate       = sampleRate;
    spec.maximumBlockSize = static_cast<juce::uint32> (samplesPerBlock);
    spec.numChannels      = static_cast<juce::uint32> (getTotalNumOutputChannels());

    reverb.prepare (spec);
}

void HayesReverbAudioProcessor::updateReverbParams()
{
    params.roomSize   = size->get() * 0.01f;
    params.damping    = damp->get() * 0.01f;
    params.width      = width->get() * 0.01f;
    params.wetLevel   = mix->get() * 0.01f;
    params.dryLevel   = 1.0f - mix->get() * 0.01f;
    params.freezeMode = freeze->get();
    reverb.setParameters (params);
}

void HayesReverbAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused (midiMessages);
    juce::ScopedNoDenormals noDenormals;

    updateReverbParams();

    juce::dsp::AudioBlock<float> block (buffer);
    juce::dsp::ProcessContextReplacing<float> ctx (block);
    reverb.process (ctx);
}

juce::AudioProcessorEditor* HayesReverbAudioProcessor::createEditor()
{
    return new HayesReverbAudioProcessorEditor (*this, undoManager);
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HayesReverbAudioProcessor();
}
