#include "ExponentialDistribution.h"

ExponentialDistribution::ExponentialDistribution() : ExponentialDistribution(0) 
{
}

ExponentialDistribution::ExponentialDistribution(unsigned int seed) : lambda(0.0), modelWasCreated(false)
{
    if (seed != 0)
    {
        std::seed_seq seq{int(seed), int(seed*seed), int(seed*seed*seed)};
        this->gen = std::mt19937(seq);
    }
    else
    {
        std::random_device rd;
        this->gen = std::mt19937(rd());
    }

}

void ExponentialDistribution::fit(const std::vector<double> &samples)
{
    this->modelWasCreated = true;

    if (samples.empty()) 
    {
        // Handle the case when no samples are provided
        this->lambda = 0.0;
        this->distribution = std::exponential_distribution<double>(this->lambda);
        return;
    }

    double sum = 0.0;
    for (double sample : samples) 
    {
        sum += sample;
    }

    this->lambda = static_cast<double>(samples.size()) / sum;
    this->distribution = std::exponential_distribution<double>(this->lambda);
}

double ExponentialDistribution::getLambda() const
{
    return this->lambda;
}

void ExponentialDistribution::setLambda(double lambdaVal)
{
    this->lambda = lambdaVal;
    this->distribution = std::exponential_distribution<double>(this->lambda);
    this->modelWasCreated = true;

}

double ExponentialDistribution::nextSample()
{
    if(this->modelWasCreated == true)
    {
        return this->distribution(this->gen);
    }

    std::fprintf(stderr, "Error: ExponentialDistribution::fit() or ExponentialDistribution::setLambda() must be called first.\n");
    // printf("ExponentialDistribution::fit() or  ExponentialDistribution::setLambda() must be called first.\n");
    return 0.0;
}


