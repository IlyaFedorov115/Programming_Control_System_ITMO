#ifndef GAIN_H
#define GAIN_H

#include <inttypes.h>

class Gain
{
public:
    Gain(double gain_value);
    double getGainValue() const;
    double update(double input);

private:
    double gain_value;
};

#endif // GAIN_H
