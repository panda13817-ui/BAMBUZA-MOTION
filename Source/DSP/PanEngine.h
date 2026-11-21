#pragma once
namespace bambuza {
struct PanEngine {
    static void processSample(float inL, float inR, float pan, float width, float& outL, float& outR);
};
}