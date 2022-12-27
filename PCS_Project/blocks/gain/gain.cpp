#include "gain.h"
#include <iostream>

Gain::Gain(double gainValue)
{
    this->gain_value = gainValue;
}

double Gain::getGainValue() const {
    return this->gain_value;
}

double Gain::update(double input) {
	return input*(this->getGainValue());
}
