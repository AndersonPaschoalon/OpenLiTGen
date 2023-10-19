#ifndef EXPONENTIAL_DISTRIBUTION_H
#define EXPONENTIAL_DISTRIBUTION_H 1

#include "StochasticDistribution.h"

class ExponentialDistribution : public StochasticDistribution
{
    private:
        double lambda; // Rate parameter

    public:
    
        ExponentialDistribution();

        // Fit the distribution to the provided samples
        void fit(const std::vector<double>& samples) override;

        // Get the rate parameter (lambda)
        double getLambda() const;

        // Generate nSamples samples following the distribution
        void gen(int nSamples, std::vector<double>& samples) override;
};

#endif // EXPONENTIAL_DISTRIBUTION_H
