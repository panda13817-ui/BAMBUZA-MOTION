#include "PluginEditor.h"
BambuzaMotionAudioProcessorEditor::BambuzaMotionAudioProcessorEditor(BambuzaMotionAudioProcessor& p)
 : AudioProcessorEditor(&p), processor(p) {
    setSize(560, 300);
    title.setText("BAMBUZA MOTION", juce::dontSendNotification);
    title.setJustificationType(juce::Justification::centred);
    title.setFont(juce::Font(juce::FontOptions(24.0f, juce::Font::bold)));
    addAndMakeVisible(title);
    setupKnob(rate, rateLabel, "RATE"); setupKnob(width, widthLabel, "WIDTH");
    setupKnob(offset, offsetLabel, "OFFSET"); setupKnob(mix, mixLabel, "MIX");
    setupKnob(drive, driveLabel, "DRIVE");
    rateAttachment = std::make_unique<SliderAttachment>(processor.parameters, "rate", rate);
    widthAttachment = std::make_unique<SliderAttachment>(processor.parameters, "width", width);
    offsetAttachment = std::make_unique<SliderAttachment>(processor.parameters, "offset", offset);
    mixAttachment = std::make_unique<SliderAttachment>(processor.parameters, "mix", mix);
    driveAttachment = std::make_unique<SliderAttachment>(processor.parameters, "drive", drive);
}
void BambuzaMotionAudioProcessorEditor::setupKnob(juce::Slider& s, juce::Label& l, const juce::String& text) {
    s.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag); s.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    addAndMakeVisible(s); l.setText(text, juce::dontSendNotification); l.setJustificationType(juce::Justification::centred); addAndMakeVisible(l);
}
void BambuzaMotionAudioProcessorEditor::paint(juce::Graphics& g) {
    g.fillAll(juce::Colour(18, 20, 24)); g.setColour(juce::Colour(55, 60, 68)); g.drawRoundedRectangle(getLocalBounds().toFloat().reduced(8), 12.0f, 1.0f);
    g.setColour(juce::Colour(0, 190, 170)); g.fillRect(20, 58, getWidth()-40, 2);
}
void BambuzaMotionAudioProcessorEditor::resized() {
    title.setBounds(15, 12, getWidth()-30, 38);
    const int colW = (getWidth()-40)/5;
    juce::Component* sliders[] = {&rate, &width, &offset, &mix, &drive};
    juce::Component* labels[] = {&rateLabel, &widthLabel, &offsetLabel, &mixLabel, &driveLabel};
    for (int i=0;i<5;++i) { const int x=20+i*colW; labels[i]->setBounds(x, 72, colW, 24); sliders[i]->setBounds(x+5, 100, colW-10, 155); }
}