#include "PanEngine.h"
#include <algorithm>
#include <cmath>
namespace bambuza {
void PanEngine::processSample(float inL, float inR, float pan, float width, float& outL, float& outR) {
    constexpr float halfPi = 1.57079632679489661923f;
    const float p = std::clamp(pan, -1.0f, 1.0f);
    const float w = std::clamp(width, 0.0f, 2.0f);
    const float angle = (p + 1.0f) * 0.5f * halfPi;
    const float leftGain = std::cos(angle) * 1.41421356237f;
    const float rightGain = std::sin(angle) * 1.41421356237f;
    const float mid = 0.5f * (inL + inR);
    const float side = 0.5f * (inL - inR) * w;
    const float monoL = mid + side;
    const float monoR = mid - side;
    outL = monoL * leftGain;
    outR = monoR * rightGain;
}
}