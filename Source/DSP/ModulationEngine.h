#pragma once
namespace bambuza {
class ModulationEngine {
public:
    enum class Shape { Sine, Triangle, Square, SawUp, SawDown, Random };
    void setRate(float hz) { rate = hz; }
    void setShape(Shape s) { shape = s; }
    void reset() { phase = 0.0; }
    float process(double sampleRate);
private:
    double phase = 0.0;
    float rate = 1.0f;
    Shape shape = Shape::Sine;
    unsigned int randomState = 0x1234567u;
};
}