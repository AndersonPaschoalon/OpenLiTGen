#include "StochasticDistribution.h"

double StochasticDistribution::getSeed() const
{
    return this->seedVal;
}

void StochasticDistribution::setSeed(double seed)
{
    this->seedVal = seed;
}
