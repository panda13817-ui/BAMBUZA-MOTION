#pragma once
#include <cmath>
#include <algorithm>
namespace bambuza {
struct Saturation {
    static float process(float x, float drive, float mix) {
        const float driven = std::tanh(x * std::max(0.0f, drive));
        const float m = std::clamp(mix, 0.0f, 1.0f);
        return x * (1.0f - m) + driven * m;
    }
};
}