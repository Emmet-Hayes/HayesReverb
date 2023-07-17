#include "FreezeButton.h"

FreezeButton::FreezeButton() : juce::Button(juce::String{})
{
    setOpaque(true);
    setWantsKeyboardFocus(true);
    setClickingTogglesState(true);
    onClick = [&]()
    {
        freezeColour = getToggleState() ? CustomColours::blue : CustomColours::midGrey;
    };

    auto svg = juce::Drawable::createFromImageData(BinaryData::FreezeIcon_svg,
        BinaryData::FreezeIcon_svgSize);
    jassert(svg != nullptr);

    if (svg != nullptr)
        freezeIconPath = svg->getOutlineAsPath();
}

void FreezeButton::resized()
{
    freezeIconBounds = getLocalBounds().toFloat().reduced(6.0f);
    freezeIconPath.applyTransform(freezeIconPath.getTransformToScaleToFit(freezeIconBounds, true));
}

void FreezeButton::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(freezeColour);

    juce::Path transformedPath = freezeIconPath;
    if (isMouseButtonDown())
    {
        const auto centre = freezeIconBounds.getCentre();
        const auto trans = juce::AffineTransform::scale(0.95f, 0.95f, centre.x, centre.y);
        transformedPath.applyTransform(trans);
    }

    g.fillPath(transformedPath);
}

void FreezeButton::paintButton(juce::Graphics& g,
    bool shouldDrawButtonAsHighlighted,
    bool shouldDrawButtonAsDown)
{
    juce::ignoreUnused(g, shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);
}

void FreezeButton::mouseDown (const juce::MouseEvent& e)
{
    juce::Button::mouseDown (e);

    const auto centre = freezeIconBounds.getCentre();
    const auto trans  = juce::AffineTransform::scale (0.95f, 0.95f, centre.x, centre.y);
    freezeIconPath.applyTransform (trans);
}

void FreezeButton::mouseUp (const juce::MouseEvent& e)
{
    juce::Button::mouseUp (e);

    const auto trans = freezeIconPath.getTransformToScaleToFit (freezeIconBounds, true);
    freezeIconPath.applyTransform (trans);
}
