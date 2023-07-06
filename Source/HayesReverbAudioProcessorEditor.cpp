#include "HayesReverbAudioProcessor.h"
#include "HayesReverbAudioProcessorEditor.h"

HayesReverbAudioProcessorEditor::HayesReverbAudioProcessorEditor (HayesReverbAudioProcessor& p, juce::UndoManager& um)
:   AudioProcessorEditor (&p)
,   editorContent (p, um)
{
    const auto ratio = static_cast<double> (defaultWidth) / defaultHeight;
    setResizable (false, true);
    getConstrainer()->setFixedAspectRatio (ratio);
    getConstrainer()->setSizeLimits (defaultWidth, defaultHeight, defaultWidth * 2, defaultHeight * 2);
    setSize (defaultWidth, defaultHeight);
    editorContent.setSize (defaultWidth, defaultHeight);
    addAndMakeVisible (editorContent);
}

void HayesReverbAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colour { 0xff0e5e0e }); // dark forest green
}

void HayesReverbAudioProcessorEditor::resized()
{
    const auto factor = static_cast<float> (getWidth()) / defaultWidth;
    editorContent.setTransform (juce::AffineTransform::scale (factor));
}
