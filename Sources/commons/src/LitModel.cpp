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
    this->userCounter = 0;
    this->serverCounter = 0;

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

    printf("\nParameters:");
    printf("\ntrafficName:%s", this->trafficName.c_str());
    printf("\nComment:%s", this->comment.c_str());
    printf("\nnUsers:%ld", this->nUsers);
    printf("\nlambda_Nsession:%f", this->lambda_Nsession);
    printf("\nlambda_Tis:%f", this->lambda_Tis);
    printf("\nlambda_Nobj:%f", this->lambda_Nobj);
    printf("\nlambda_IAobj:%f", this->lambda_IAobj);
    printf("\nlambda_IApkt:%f\n", this->lambda_IApkt);


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

LitModel::LoadResult LitModel::load(const char *fileName)
{
    this->clear();

    std::ifstream file(fileName);
    if (!file.is_open())
    {
        return LoadResult::FILE_NOT_FOUND;
    }

    std::string line;
    while (std::getline(file, line))
    {
        // Split the line into key and value
        size_t delimiterPos = line.find('=');
        if (delimiterPos == std::string::npos)
        {
            file.close();
            clear();
            printf("Wrong file format: No value was found for the key <%s>\n", line.c_str());
            return LoadResult::WRONG_FORMAT;
        }

        std::string key = line.substr(0, delimiterPos);
        std::string value = line.substr(delimiterPos + 1);

        // Handle different keys
        if (key == "nUsers")
        {
            this->nUsers = std::stol(value);
        }
        else if (key == "trafficName")
        {
            this->trafficName = value;
        }
        else if (key == "comment")
        {
            this->comment = value;
        }
        else if (key == "lambda_Nsession")
        {
            this->lambda_Nsession = std::stod(value);
        }
        else if (key == "lambda_Tis")
        {
            this->lambda_Tis = std::stod(value);
        }
        else if (key == "lambda_Nobj")
        {
            this->lambda_Nobj = std::stod(value);
        }
        else if (key == "lambda_IAobj")
        {
            this->lambda_IAobj = std::stod(value);
        }
        else if (key == "lambda_IApkt")
        {
            this->lambda_IApkt = std::stod(value);
        }
        else if (key == "userList")
        {
            this->userList = new std::vector<std::string>();
            VectorUtils::toVec(value.c_str(), *(this->userList), ',');
        }
        else if (key == "serverList")
        {
            this->serverList = new std::vector<std::string>();
            VectorUtils::toVec(value.c_str(), *(this->serverList), ',');
        }
    }

    // Check if all required members have been loaded
    if (this->nUsers == -1 || 
        this->trafficName.empty() || 
        this->comment.empty() ||
        this->lambda_Nsession == -1 || 
        this->lambda_Tis == -1 || 
        this->lambda_Nobj == -1 ||
        this->lambda_IAobj == -1 || 
        this->lambda_IApkt == -1 || 
        this->userList->empty() || 
        this->serverList->empty())
    {
        file.close();
        this->clear();
        return LoadResult::WRONG_FORMAT;
    }

    file.close();
    return LoadResult::OK;
}

std::string LitModel::getNextUser()
{
    if (this->userList->empty()) 
    {
        return "";
    }
    std::string nextUser = this->userList->at(this->userCounter);
    this->userCounter = (this->userCounter + 1) % this->userList->size();
    return nextUser;
}

std::string LitModel::getNextServer()
{
    if (this->serverList->empty()) 
    {
        return "";
    }
    std::string nextServer = this->serverList->at(this->serverCounter);
    this->serverCounter = (this->serverCounter + 1) % this->serverList->size();
    return nextServer;
}

void LitModel::clear()
{
    // Clear existing data
    this->nUsers = -1;
    this->userList->clear();
    this->serverList->clear();
    this->trafficName.clear();
    this->comment.clear();
    this->lambda_Nsession = -1;
    this->lambda_Tis = -1;
    this->lambda_Nobj = -1;
    this->lambda_IAobj = -1;
    this->lambda_IApkt = -1;    
}
