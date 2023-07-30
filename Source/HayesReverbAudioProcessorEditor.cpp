#include "HayesReverbAudioProcessor.h"
#include "HayesReverbAudioProcessorEditor.h"

HayesReverbAudioProcessorEditor::HayesReverbAudioProcessorEditor (HayesReverbAudioProcessor& p, juce::UndoManager& um)
:   BaseAudioProcessorEditor { p }
,   editorContent        { p, um }
,   presetBar            { p }
{
    const auto ratio = static_cast<double> (defaultWidth) / defaultHeight;
    setResizable(false, true);
    getConstrainer()->setFixedAspectRatio (ratio);
    getConstrainer()->setSizeLimits(defaultWidth, defaultHeight, defaultWidth * 2, defaultHeight * 2);
    image = juce::ImageCache::getFromMemory(BinaryData::bg_file_jpg, BinaryData::bg_file_jpgSize);
    setSize (defaultWidth, defaultHeight + 20);
    editorContent.setSize (defaultWidth, defaultHeight);
    addAndMakeVisible(editorContent);
    presetBar.setLookAndFeel(&lnf->customLookAndFeel);
    addAndMakeVisible(presetBar);
}

void HayesReverbAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.drawImage(image, 0, 0, getWidth(), getHeight(), 0, 500, 1000, 500); 
}

void HayesReverbAudioProcessorEditor::resized()
{
    const auto factor = static_cast<float> (getWidth()) / defaultWidth;
    presetBar.setBounds(0, 0, static_cast<int>(500 * factor), static_cast<int>(20 * factor));
    editorContent.setTransform (juce::AffineTransform::scale (factor));
}
