#include "generator.h"
#include "lintegrator.h"
#include "blocks/gain/gain.h"



Generator::Generator(std::vector<double> &states, std::vector<double> &gains, QObject *parent)
    : QObject(parent),
      integrator_1(nullptr), integrator_2(nullptr), integrator_3(nullptr),
      gain_1(nullptr), gain_2(nullptr)
{
    if (states.size() < 3 || gains.size() < 2)
        throw GeneratorException();

    InitGenerator(states[0], states[1], states[2], gains[0], gains[1]);
}

double Generator::update(double inputVal, double dt)
{
    double currState2 = this->integrator_2->getState();

    double resState2 = integrator_2->update(
                integrator_1->update(gain_1->update(currState2), dt),
                dt);

    double currState3 = integrator_3->getState();

    double resState3 = integrator_3->update(gain_2->update(currState3), dt);

    return resState2 + resState3;
}

void Generator::InitGenerator(double state1, double state2, double state3, double gain1, double gain2)
{
    integrator_1 = new LIntegrator(state1);
    integrator_2 = new LIntegrator(state2);
    integrator_3 = new LIntegrator(state3);
    gain_1 = new Gain(gain1);
    gain_2 = new Gain(gain2);
}
