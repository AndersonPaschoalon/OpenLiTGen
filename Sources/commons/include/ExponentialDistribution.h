#ifndef EXPONENTIAL_DISTRIBUTION_H
#define EXPONENTIAL_DISTRIBUTION_H 1

#include <random>
#include "StochasticDistribution.h"


class ExponentialDistribution : public StochasticDistribution
{
    private:
        double lambda; // Rate parameter
        std::mt19937 gen;
        std::exponential_distribution<double> distribution;
        bool modelWasCreated;


    public:

        ExponentialDistribution();

        ExponentialDistribution (unsigned int seed);

        /// @brief Fit the distribution to the provided samples
        /// @param samples 
        void fit(const std::vector<double>& samples) override;

        /// @brief Get the rate parameter (lambda)
        /// @return 
        double getLambda() const;

        void setLambda(double lambdaVal);

        /// @brief 
        /// @return 
        double nextSample() override;

};

#endif // EXPONENTIAL_DISTRIBUTION_H
