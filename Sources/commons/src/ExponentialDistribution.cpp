#include "ExponentialDistribution.h"
#include <random>

ExponentialDistribution::ExponentialDistribution() : lambda(0.0)
{
}

void ExponentialDistribution::fit(const std::vector<double> &samples)
{
    if (samples.empty()) 
    {
        // Handle the case when no samples are provided
        this->lambda = 0.0;
        return;
    }

    double sum = 0.0;
    for (double sample : samples) 
    {
        sum += sample;
    }

    this->lambda = static_cast<double>(samples.size()) / sum;
}

double ExponentialDistribution::getLambda() const
{
    return this->lambda;
}

void ExponentialDistribution::gen(int nSamples, std::vector<double> &samples)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::exponential_distribution<double> distribution(this->lambda);

    samples.clear();
    samples.reserve(nSamples);
    for (int i = 0; i < nSamples; ++i) 
    {
        samples.push_back(distribution(gen));
    }    
}
