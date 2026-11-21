#pragma once
#include <JuceHeader.h>
#include "../DSP/ModulationEngine.h"
#include "../DSP/EnvelopeFollower.h"
class BambuzaMotionAudioProcessor : public juce::AudioProcessor {
public:
    BambuzaMotionAudioProcessor();
    ~BambuzaMotionAudioProcessor() override = default;
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override {}
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }
    const juce::String getName() const override { return "Bambuza Motion"; }
    bool acceptsMidi() const override { return true; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }
    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const juce::String getProgramName(int) override { return {}; }
    void changeProgramName(int, const juce::String&) override {}
    void getStateInformation(juce::MemoryBlock&) override;
    void setStateInformation(const void*, int) override;
    juce::AudioProcessorValueTreeState parameters;
private:
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    bambuza::ModulationEngine lfo;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BambuzaMotionAudioProcessor)
};