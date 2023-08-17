#ifndef __LIT_MODEL_H__
#define __LIT_MODEL_H__ 1

#include <vector>
#include <string>
#include <fstream>
#include <numeric>
#include "NetworkTraffic.h"

class LitModel 
{
    private:
        long int nUsers;
        std::vector<std::string>* userList;
        std::vector<std::string>* serverList;
        std::string trafficName;
        std::string comment;
        long int lambda_Nsession;
        long int lambda_Tis;
        long int lambda_Nobj;
        long int lambda_IAobj;
        long int lambda_IApkt;


    public:
        LitModel();
        ~LitModel();

        void calc(NetworkTraffic& net);
        bool save();
};

#endif // #ifndef __LIT_MODEL_H__