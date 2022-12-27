#ifndef MYINTEGRATOR_H
#define MYINTEGRATOR_H

#include <QObject>
#include <functional>

struct Limits {
    double lower;
    double upper;

    Limits(double a = 0, double b = 0)
        : lower{a}, upper{b}
    {
        if (b < a){
            lower = b;
            upper = a;
        }
    }
};


class IntegratorException {};


// const std::function<double (double)> &f
class MyIntegrator : public QObject
{
    Q_OBJECT
public:
    MyIntegrator(const std::function<double(double)>, QObject *parent = nullptr);
    double calcIntegral(double start, double end, double eps); // with given error
    double calcIntegral(double start, double end, uint n);      // num of intervals
    double calcIntegral(Limits& limits, double dt);  // with size of step

    void setFunction(const std::function<double(double)>);

private:
    std::function<double(double)> func_;
    double calcInterval(double a, double b);
    double calcInterval(Limits& limits);
};

#endif // MYINTEGRATOR_H
