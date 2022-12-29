#ifndef CONTROLMODEL_H
#define CONTROLMODEL_H

#include <QVector>
#include <QPair>

class LIntegrator;
class Gain;

class ControlModelError{};

class ControlModel
{
public:
    ControlModel(QVector<double>& states, QVector<QPair<double, double>>& gains, QPair<double, double>& sigGain);
    double update(double inputVal, double dt);

private:
    QVector<LIntegrator*> integrators_;
    QVector<QPair<Gain*,Gain*>> gains_;
    QPair<Gain*,Gain*> inputSignalGain_;
};

#endif // CONTROLMODEL_H
