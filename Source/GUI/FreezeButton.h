#pragma once

#include "JuceHeader.h"
#include "../../Common/CustomColours.h"

class FreezeButton  : public juce::Button
{
public:
    FreezeButton();

    void paint (juce::Graphics& g) override;
    void resized () override;

    void paintButton (juce::Graphics& g, 
                      bool shouldDrawButtonAsHighlighted,
                      bool shouldDrawButtonAsDown) override;
    void mouseDown(const juce::MouseEvent& e) override;
    void mouseUp(const juce::MouseEvent& e) override;

private:
    juce::Path freezeIconPath;
    juce::Rectangle<float> freezeIconBounds;
    juce::Colour freezeColour { CustomColours::midGrey };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FreezeButton)
};
