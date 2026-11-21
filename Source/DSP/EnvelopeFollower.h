#pragma once
#include <algorithm>
#include <cmath>

namespace bambuza {
class EnvelopeFollower {
public:
    void prepare(double sampleRate) {
        const auto sr = std::max(1.0, sampleRate);
        attackCoeff = std::exp(-1.0 / (0.010 * sr));
        releaseCoeff = std::exp(-1.0 / (0.100 * sr));
        envelope = 0.0f;
    }
    float process(float input) {
        const float x = std::abs(input);
        const float c = x > envelope ? attackCoeff : releaseCoeff;
        envelope = (1.0f - c) * x + c * envelope;
        return envelope;
    }
    void reset() { envelope = 0.0f; }
private:
    float envelope = 0.0f;
    float attackCoeff = 0.0f;
    float releaseCoeff = 0.0f;
};
}