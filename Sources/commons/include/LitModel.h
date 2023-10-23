#ifndef __LIT_MODEL_H__
#define __LIT_MODEL_H__ 1

#include <vector>
#include <string>
#include <fstream>
#include <numeric>
#include "NetworkTraffic.h"

class LitModel 
{
    public:

        enum class LoadResult
        {
            OK,
            FILE_NOT_FOUND,
            WRONG_FORMAT,
            UNKNOWN_ERROR
        };

        LitModel();
        ~LitModel();

        void calc(NetworkTraffic& net);
        bool save();
        LoadResult load(const char* fileName);

    private:

        void clear();
    
        long int nUsers;
        std::vector<std::string>* userList;
        std::vector<std::string>* serverList;
        std::string trafficName;
        std::string comment;
        double lambda_Nsession;
        double lambda_Tis;
        double lambda_Nobj;
        double lambda_IAobj;
        double lambda_IApkt;

};

#endif // #ifndef __LIT_MODEL_H__