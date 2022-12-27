#include "lintegrator.h"

LIntegrator::LIntegrator(double state, QObject *parent)
    : QObject(parent), state_(state), prevState_(0.0)
{}

double LIntegrator::update(double inputVal, double dt)
{
    this->state_ = state_ + (prevState_ + inputVal) * dt / 2.0; // y[k-1] + (u[k] + u[k+1]) * dt/2
    prevState_ = inputVal;
    return state_;
}

double LIntegrator::getState()
{
    return state_;
}



