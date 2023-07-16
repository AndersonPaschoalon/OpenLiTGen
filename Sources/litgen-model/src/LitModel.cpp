#include "LitModel.h"

void LitModel::calc(NetworkTraffic &net)
{
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