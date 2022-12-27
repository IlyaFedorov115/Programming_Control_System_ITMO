#ifndef LINTEGRATOR_H
#define LINTEGRATOR_H

#include <QObject>

class LIntegrator : public QObject
{
    Q_OBJECT
public:
    LIntegrator(double state, QObject *parent = nullptr);
    double update(double inputVal, double dt);
    double getState();

private:
    double state_;
    double prevState_;
};

void fun();



#endif // LINTEGRATOR_H
