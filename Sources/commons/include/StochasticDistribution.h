#ifndef STOCHASTIC_DISTRIBUTION_H
#define STOCHASTIC_DISTRIBUTION_H 1

#include <vector>

class StochasticDistribution 
{
    public:
    
        // Fit the distribution to the provided samples
        virtual void fit(const std::vector<double>& samples) = 0;

        // Retuns a single sample.
        virtual double nextSample() = 0;

    private: 


};

#endif // STOCHASTIC_DISTRIBUTION_H
