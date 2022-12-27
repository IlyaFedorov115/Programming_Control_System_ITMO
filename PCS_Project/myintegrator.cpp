#include "myintegrator.h"
#include <cmath>

MyIntegrator::MyIntegrator(const std::function<double(double)> fun, QObject *parent)
    : QObject(parent),
      func_(fun)
{}

double MyIntegrator::calcIntegral(double start, double end, double eps)
{
    if (eps <= 0.0) throw IntegratorException();

    double oldValue, newValue = calcInterval(start, end);
    int intervalNum = 1;

    do{
        oldValue = newValue;
        intervalNum *= 2;
        newValue = 0.0;
        double step = (end-start) / intervalNum;
        double currStart = start;
        for (int i = 0; i < intervalNum; i++){
            newValue += calcInterval(currStart, currStart+step);
            currStart += step;
        }

    } while (std::fabs(newValue-oldValue) > eps);
    return newValue;
}

double MyIntegrator::calcIntegral(double start, double end, uint n)
{
    double result = 0.0;
    double width = (end-start)/n;

    for (auto i = 0; i < n; i++){
        double x1 = start + i * (width);
        double x2 = start + (i+1)*(width);
        result += calcInterval(x1, x2);
    }

    return result;
}

double MyIntegrator::calcIntegral(Limits &limits, double dt)
{
    uint num = static_cast<uint>((limits.upper - limits.lower) / dt);
    return calcIntegral(limits.lower, limits.upper, num);
}

void MyIntegrator::setFunction(const std::function<double (double)> f)
{
   this->func_ = f;
}

/** Simpson method */

double MyIntegrator::calcInterval(double a, double b)
{
    return (b - a) * (func_(a) + 4.0 * func_((a+b)/2.0) + func_(b)) / 6.0;
}

double MyIntegrator::calcInterval(Limits &limits)
{
    return calcInterval(limits.lower, limits.upper);
}
