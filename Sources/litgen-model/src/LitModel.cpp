#include "LitModel.h"

double LitModel::exponentialLambda(const std::vector<double> &interArrivals)
{
    if (interArrivals.empty()) 
    {
        // If the input vector is empty, return 0 (undefined lambda for an empty sample)
        return 0.0;
    }

    // Calculate the sample mean of inter-arrival times
    double meanInterArrival = std::accumulate(interArrivals.begin(), interArrivals.end(), 0.0) / interArrivals.size();

    // Calculate the lambda parameter (rate parameter) as the reciprocal of the sample mean
    double lambda = 1.0 / meanInterArrival;

    return lambda;
}

void LitModel::calc(NetworkTraffic &net)
{
    int numberOfUsers;
    std::vector<std::string> userList;
    std::vector<double> interSessionTimes;
    std::vector<int> nObjectsPersection;
    std::vector<double> interObjectTimes;
    std::vector<int> npacketsPerObject;
    std::vector<std::string> serverList;
    std::vector<double> interPacketTimes;
    std::vector<short> packetSizes;

    net.queryUsersData(numberOfUsers, userList);
    net.querySessionsData(interSessionTimes, nObjectsPersection);
    net.queryObjectData(interObjectTimes, npacketsPerObject, serverList);
    net.queryPacketData(interPacketTimes, packetSizes);

    this->comment = net.getDescription();
    this->trafficName = net.getName();
    this->userList = userList;
    this->serverList = serverList;
    this->nUsers = numberOfUsers;


}

bool LitModel::save()
{
    std::string filename = trafficName + ".lit";
    std::ofstream file(filename);

    if (!file.is_open()) {
        return false;  // Failed to open file
    }

    // Write the private variables as key-value pairs
    file << "nUsers=" << nUsers << '\n';

    file << "userList=";
    for (const auto& user : userList) {
        file << user << ",";
    }
    file.seekp(-1, std::ios_base::cur);  // Remove the trailing comma
    file << '\n';

    file << "serverList=";
    for (const auto& server : serverList) {
        file << server << ",";
    }
    file.seekp(-1, std::ios_base::cur);  // Remove the trailing comma
    file << '\n';

    file << "trafficName=" << trafficName << '\n';
    file << "comment=" << comment << '\n';
    file << "lambda_Nsession=" << lambda_Nsession << '\n';
    file << "lambda_Tis=" << lambda_Tis << '\n';
    file << "lambda_Nobj=" << lambda_Nobj << '\n';
    file << "lambda_IAobj=" << lambda_IAobj << '\n';
    file << "lambda_IApkt=" << lambda_IApkt << '\n';

    file.close();
    return true;    
}