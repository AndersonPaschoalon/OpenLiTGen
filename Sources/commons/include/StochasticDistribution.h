#ifndef STOCHASTIC_DISTRIBUTION_H
#define STOCHASTIC_DISTRIBUTION_H 1

#include <vector>

class StochasticDistribution 
{
    public:
        virtual ~StochasticDistribution() {}

        // Fit the distribution to the provided samples
        virtual void fit(const std::vector<double>& samples) = 0;

        // Generate nSamples samples following the distribution
        virtual void gen(int nSamples, std::vector<double>& samples) = 0;

        // Get the seed value for generating samples
        virtual double getSeed() const;

        // Set the seed value for generating samples
        virtual void setSeed(double seed);

    private: 

        double seedVal;

};

#endif // STOCHASTIC_DISTRIBUTION_H
