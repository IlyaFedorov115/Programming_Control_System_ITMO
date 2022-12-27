#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>
#include <vector>

class LIntegrator;
class Gain;

class GeneratorException{};

class Generator : public QObject
{
    Q_OBJECT
public:
    Generator(std::vector<double>& states, std::vector<double>& gains, QObject *parent = nullptr);
    double update(double inputVal, double dt);

private:
    void InitGenerator(double state1, double state2, double state3, double gain1, double gain2);
    LIntegrator* integrator_1;
    LIntegrator* integrator_2;
    LIntegrator* integrator_3;

    Gain* gain_1;
    Gain* gain_2;
};

#endif // GENERATOR_H
