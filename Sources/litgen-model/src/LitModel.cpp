#include "LitModel.h"
#include "ExponentialDistribution.h"


LitModel::LitModel()
{
    this->lambda_IAobj = 0;
    this->lambda_IApkt = 0;
    this->lambda_Nobj = 0;
    this->lambda_Nsession = 0;
    this->lambda_Tis = 0;
    this->nUsers = 0;
    this->comment = "";
    this->trafficName = "";
    this->serverList = nullptr;
    this->userList = nullptr;
}

LitModel::~LitModel()
{
    if (this->serverList != nullptr)
    {
        delete this->serverList;
        this->serverList = nullptr;
    }
    if (this->userList != nullptr)
    {
        delete this->userList;
        this->userList = nullptr;
    }
}

void LitModel::calc(NetworkTraffic &net)
{
    int numberOfUsers;
    std::vector<std::string>* userList = new std::vector<std::string>();

    std::vector<double>* interSessionTimes = new std::vector<double>();
    std::vector<int>* nObjectsPersection = new std::vector<int>();

    std::vector<double>* interObjectTimes = new std::vector<double>();
    std::vector<int>* npacketsPerObject = new std::vector<int>();
    std::vector<std::string>* serverList = new std::vector<std::string>();

    std::vector<double>* interPacketTimes = new std::vector<double>();
    std::vector<short>* packetSizes = new std::vector<short>();

    net.queryUsersData(numberOfUsers, *userList, true);
    net.querySessionsData(*interSessionTimes, *nObjectsPersection);
    net.queryObjectData(*interObjectTimes, *npacketsPerObject, *serverList, true);
    net.queryPacketData(*interPacketTimes, *packetSizes);

    std::vector<double> doublenObjectsPersection;
    std::vector<double> doublenpacketsPerObject;
    doublenObjectsPersection.reserve(nObjectsPersection->size()); 
    doublenpacketsPerObject.reserve(npacketsPerObject->size()); 

    std::transform(nObjectsPersection->begin(), nObjectsPersection->end(), std::back_inserter(doublenObjectsPersection), [](short value) {
        return static_cast<double>(value);
    });
    std::transform(npacketsPerObject->begin(), npacketsPerObject->end(), std::back_inserter(doublenpacketsPerObject), [](short value) {
        return static_cast<double>(value);
    });

    this->comment = net.getDescription();
    this->trafficName = net.getName();
    this->nUsers = numberOfUsers;
    this->userList = userList;
    this->serverList = serverList;

    ExponentialDistribution Tis = ExponentialDistribution();
    ExponentialDistribution Nsession = ExponentialDistribution();
    ExponentialDistribution IAobj = ExponentialDistribution();
    ExponentialDistribution Nobj = ExponentialDistribution();
    ExponentialDistribution IApkt = ExponentialDistribution();

    Tis.fit(*interSessionTimes);
    Nsession.fit(doublenObjectsPersection);

    IAobj.fit(*interObjectTimes);
    Nobj.fit(doublenpacketsPerObject);

    IApkt.fit(*interPacketTimes);

    this->lambda_Tis = Tis.getLambda();
    this->lambda_Nsession = Nsession.getLambda();

    this->lambda_IAobj = IAobj.getLambda();
    this->lambda_Nobj = Nobj.getLambda();

    this->lambda_IApkt = IApkt.getLambda();


    // free allocated memoty

    delete interSessionTimes;
    delete nObjectsPersection;

    delete interObjectTimes; 
    delete npacketsPerObject;

    delete interPacketTimes; 
    delete packetSizes; 

    interSessionTimes = nullptr;
    nObjectsPersection = nullptr;

    interObjectTimes = nullptr; 
    npacketsPerObject = nullptr;

    interPacketTimes = nullptr; 
    packetSizes = nullptr; 




}

bool LitModel::save()
{
    std::string filename = this->trafficName + ".lit";
    std::ofstream file(filename);

    if (!file.is_open()) {
        return false;  // Failed to open file
    }

    // Write the private variables as key-value pairs
    file << "nUsers=" << this->nUsers << '\n';
    file << "trafficName=" << this->trafficName << '\n';
    file << "comment=" << this->comment << '\n';
    file << "lambda_Nsession=" << this->lambda_Nsession << '\n';
    file << "lambda_Tis=" << this->lambda_Tis << '\n';
    file << "lambda_Nobj=" << this->lambda_Nobj << '\n';
    file << "lambda_IAobj=" << this->lambda_IAobj << '\n';
    file << "lambda_IApkt=" << this->lambda_IApkt << '\n';

    file << "userList=";
    if (this->userList != nullptr)
    {
        for (const auto& user : *(this->userList)) 
        {
            file << user << ",";
        }
        file.seekp(-1, std::ios_base::cur);  // Remove the trailing comma
    }
    file << '\n';

    file << "serverList=";
    if (this->serverList != nullptr)
    {
        for (const auto& server : (*this->serverList)) 
        {
            file << server << ",";
        }
        file.seekp(-1, std::ios_base::cur);  // Remove the trailing comma        
    }
    file << '\n';

    file.close();

    return true;    
}