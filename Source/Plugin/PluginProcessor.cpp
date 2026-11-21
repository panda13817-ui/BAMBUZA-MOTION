#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "../DSP/PanEngine.h"
#include "../DSP/Saturation.h"
BambuzaMotionAudioProcessor::BambuzaMotionAudioProcessor()
 : AudioProcessor(BusesProperties().withInput("Input", juce::AudioChannelSet::stereo(), true)
                  .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
   parameters(*this, nullptr, "PARAMETERS", createParameterLayout()) {}
juce::AudioProcessorValueTreeState::ParameterLayout BambuzaMotionAudioProcessor::createParameterLayout() {
    juce::AudioProcessorValueTreeState::ParameterLayout p;
    p.add(std::make_unique<juce::AudioParameterFloat>("rate", "Rate", juce::NormalisableRange<float>(0.05f, 10.0f, 0.001f), 1.0f));
    p.add(std::make_unique<juce::AudioParameterFloat>("width", "Width", juce::NormalisableRange<float>(0.0f, 2.0f, 0.001f), 1.0f));
    p.add(std::make_unique<juce::AudioParameterFloat>("offset", "Offset", juce::NormalisableRange<float>(-1.0f, 1.0f, 0.001f), 0.0f));
    p.add(std::make_unique<juce::AudioParameterFloat>("mix", "Mix", juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 1.0f));
    p.add(std::make_unique<juce::AudioParameterFloat>("drive", "Drive", juce::NormalisableRange<float>(1.0f, 8.0f, 0.001f), 1.0f));
    return p;
}
void BambuzaMotionAudioProcessor::prepareToPlay(double sr, int) { lfo.reset(); }
bool BambuzaMotionAudioProcessor::isBusesLayoutSupported(const BusesLayout& l) const {
    return l.getMainInputChannelSet() == juce::AudioChannelSet::stereo()
        && l.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}
void BambuzaMotionAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&) {
    juce::ScopedNoDenormals noDenormals;
    const auto rate = parameters.getRawParameterValue("rate")->load();
    const auto width = parameters.getRawParameterValue("width")->load();
    const auto offset = parameters.getRawParameterValue("offset")->load();
    const auto mix = parameters.getRawParameterValue("mix")->load();
    const auto drive = parameters.getRawParameterValue("drive")->load();
    auto* left = buffer.getWritePointer(0);
    auto* right = buffer.getWritePointer(1);
    for (int i = 0; i < buffer.getNumSamples(); ++i) {
        lfo.setRate(rate);
        const float modulation = lfo.process(getSampleRate());
        const float pan = juce::jlimit(-1.0f, 1.0f, offset + modulation * 0.5f);
        float wetL, wetR;
        bambuza::PanEngine::processSample(left[i], right[i], pan, width, wetL, wetR);
        wetL = bambuza::Saturation::process(wetL, drive, 0.0f);
        wetR = bambuza::Saturation::process(wetR, drive, 0.0f);
        left[i] = left[i] * (1.0f - mix) + wetL * mix;
        right[i] = right[i] * (1.0f - mix) + wetR * mix;
    }
}
juce::AudioProcessorEditor* BambuzaMotionAudioProcessor::createEditor() { return new BambuzaMotionAudioProcessorEditor(*this); }
void BambuzaMotionAudioProcessor::getStateInformation(juce::MemoryBlock& dest) {
    auto state = parameters.copyState(); std::unique_ptr<juce::XmlElement> xml(state.createXml()); copyXmlToBinary(*xml, dest);
}
void BambuzaMotionAudioProcessor::setStateInformation(const void* data, int size) {
    std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data, size));
    if (xml && xml->hasTagName(parameters.state.getType())) parameters.replaceState(juce::ValueTree::fromXml(*xml));
}
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() { return new BambuzaMotionAudioProcessor(); }