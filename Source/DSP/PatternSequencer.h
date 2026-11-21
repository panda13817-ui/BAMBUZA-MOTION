#pragma once
#include <array>
#include <algorithm>
namespace bambuza {
struct PatternSequencer {
    std::array<float, 16> steps{};
    float valueAt(int index) const { return steps[static_cast<unsigned int>(index) & 15u]; }
    void setStep(int index, float value) { steps[static_cast<unsigned int>(index) & 15u] = std::clamp(value, -1.0f, 1.0f); }
};
}