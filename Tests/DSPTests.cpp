#include "DSP/PanEngine.h"
#include "DSP/ModulationEngine.h"
#include "DSP/EnvelopeFollower.h"
#include "DSP/Saturation.h"
#include <cassert>
#include <cmath>
int main() {
    float l=0.0f, r=0.0f;
    bambuza::PanEngine::processSample(1.0f, 1.0f, 0.0f, 1.0f, l, r);
    assert(std::isfinite(l) && std::isfinite(r));
    bambuza::ModulationEngine lfo;
    lfo.setRate(1.0f);
    const auto v = lfo.process(48000.0);
    assert(std::isfinite(v));
    bambuza::EnvelopeFollower env;
    env.prepare(48000.0);
    assert(env.process(1.0f) >= 0.0f);
    assert(std::isfinite(bambuza::Saturation::process(0.5f, 2.0f, 1.0f)));
    return 0;
}