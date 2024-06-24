#include "TgEngine.h"
#include "cpptools.h"
#include <chrono>
#include <algorithm>

TgEngine::TgEngine() : packetVector(new std::vector<PDU*>()) 
{

}


TgEngine::~TgEngine()
{
    for (PDU* pdu : *(this->packetVector)) {
        delete pdu;
    }
    delete packetVector;    

}

void TgEngine::createSamples(LitModel &model, double timeout, unsigned int seed)
{
    if (this->packetVector != nullptr) 
    {
        for (PDU* pdu : *packetVector) 
        {
            delete pdu;
        }

        delete this->packetVector;
        this->packetVector = new std::vector<PDU*>();
    }
    this->packetVector->reserve(model.nUsers * 100); // Assuming an average of 100 packets per user

    // Instantiate Random variables

    ExponentialDistribution Nsession(seed);
    Nsession.setLambda(model.lambda_Nsession);

    ExponentialDistribution Tis(seed);
    Tis.setLambda(model.lambda_Tis);    

    ExponentialDistribution Nobj(seed);
    Nobj.setLambda(model.lambda_Nobj);

    ExponentialDistribution IAobj(seed);
    IAobj.setLambda(model.lambda_IAobj);    

    ExponentialDistribution IApkt(seed);
    IApkt.setLambda(model.lambda_IApkt);

    int nUsers = model.nUsers;

    // create PDUs
    double accTime = 0;
    std::string userStr = "";
    for(int i = 0; i < nUsers; i++)
    {
        userStr = model.getNextUser();
        std::string ipStr;
        std::string portStr;
        splitString(userStr.c_str(), ':', ipStr, portStr);
        int port = std::stoi(portStr);

        // Session level. We assume each user undergoes an infinite succession of session
        // and inter-session periods. During a session, a user makes use of the network
        // resources by downloading a certain number of objects. We define two random
        // variables to characterize this level: Nsession , the session size, i.e. the number of
        // objects downloaded during a session and, Tis , the inter-session duration.
        bool sessionEnd = false;
        while (!sessionEnd)
        {
            // ceil for at least one packet
            int  nSession = std::ceil(Nsession.nextSample()); 
            // the first packet is send as the traffic starts
            double interSessionTime = 0e-9;
            for(int j = 0; j < nSession; j++)
            {
                // Object level. A session is made of one or several objects. Indeed, a session is
                // split up into a set of requests (sent by user) and responses (from the server),
                // where responses gather the session’s objects. In the case of web, objects may be
                // web pages’ main bodies (HTML skeletons) or embedded pictures [8]2 . In the case
                // of mail, objects may be servers responses to clients requests (e.g. e-mails, clients
                // accounts meta-data. . . ). In the case of P2P, objects may be files or chunks of
                // files. The description of this level requires the definition of two random variables:
                // Nobj , the object size, i.e. the number of IP packets in an object and, IAobj , the
                // objects inter-arrival times in a session.  
                accTime +=  interSessionTime;
                interSessionTime =  Tis.nextSample(); // time for the next packet to be sent
                int nPacketsInObject = std::ceil(Nobj.nextSample());
                // this will be added after the last packet of the object is pushed        
                double objectsInterArrival = IAobj.nextSample();
                for(int k = 0; k < nPacketsInObject; k++)
                {
                    if(accTime > timeout)
                    {
                        sessionEnd = true;
                        break;
                    }
                    // Packet level. Finally, each object is made of a set of packets. The arrival process
                    // of packets in an object can be described by giving the successive inter-arrival
                    // times between packets, characterized by random variables IApkt .
                    PDU* pduPtr = new PDU();


                    // pick a server
                    std::string serverStr = model.getNextServer();
                    std::string ipServerStr;
                    std::string portServerStr;
                    splitString(serverStr.c_str(), ':', ipServerStr, portServerStr);
                    int portServer = std::stoi(portServerStr);

                    // create PDU
                    pduPtr->setArrivalTime(accTime);
                    pduPtr->setIpSrc(ipStr);
                    pduPtr->setPortSrc(port);                    
                    pduPtr->setIpDst(ipServerStr);
                    pduPtr->setPortDst(portServer);
                    pduPtr->setPacketSize(1024); // TODO

                    double interArrivals = IApkt.nextSample();
                    accTime +=  interArrivals;

                    this->packetVector->push_back(pduPtr);
                }
                // delay to the next object
                accTime +=  objectsInterArrival;
                if(sessionEnd)
                {
                    break;
                }
            }
        }
    }

    // sort according to the arrival time
    std::sort(this->packetVector->begin(), this->packetVector->end(), TgEngine::comparePDUs);
}

bool TgEngine::comparePDUs(const PDU *pdu1, const PDU *pdu2)
{
    return pdu1->getArrivalTime() < pdu2->getArrivalTime();
}
