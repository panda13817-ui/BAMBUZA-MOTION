#include "ModulationEngine.h"
#include <algorithm>
#include <cmath>
namespace bambuza {
float ModulationEngine::process(double sampleRate) {
    const float p = static_cast<float>(phase);
    float value = 0.0f;
    switch (shape) {
        case Shape::Sine: value = std::sin(6.28318530718f * p); break;
        case Shape::Triangle: value = 1.0f - 4.0f * std::abs(p - 0.5f); break;
        case Shape::Square: value = p < 0.5f ? 1.0f : -1.0f; break;
        case Shape::SawUp: value = 2.0f * p - 1.0f; break;
        case Shape::SawDown: value = 1.0f - 2.0f * p; break;
        case Shape::Random:
            randomState ^= randomState << 13; randomState ^= randomState >> 17; randomState ^= randomState << 5;
            value = static_cast<float>(randomState & 0xffffu) / 32767.5f - 1.0f;
            break;
    }
    phase += std::max(0.0f, rate) / std::max(1.0, sampleRate);
    phase -= std::floor(phase);
    return value;
}
}