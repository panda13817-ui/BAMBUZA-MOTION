#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
class BambuzaMotionAudioProcessorEditor : public juce::AudioProcessorEditor {
public:
    explicit BambuzaMotionAudioProcessorEditor(BambuzaMotionAudioProcessor&);
    void paint(juce::Graphics&) override;
    void resized() override;
private:
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    BambuzaMotionAudioProcessor& processor;
    juce::Slider rate, width, offset, mix, drive;
    juce::Label title, rateLabel, widthLabel, offsetLabel, mixLabel, driveLabel;
    std::unique_ptr<SliderAttachment> rateAttachment, widthAttachment, offsetAttachment, mixAttachment, driveAttachment;
    void setupKnob(juce::Slider&, juce::Label&, const juce::String&);
};