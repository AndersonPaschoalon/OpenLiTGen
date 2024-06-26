#include "TgEngine.h"
#include "cpptools.h"
#include <chrono>
#include <math.h> 
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

    // Nsession: The number of objects sent during a session period
    ExponentialDistribution Nsession(seed);
    Nsession.setLambda(model.lambda_Nsession);

    // Tis: The duration of the inter-session period.
    ExponentialDistribution Tis(seed + 1); // Different seed to avoid correlation
    Tis.setLambda(model.lambda_Tis);    

    // Nobj: The number of IP packets that compose the object.
    ExponentialDistribution Nobj(seed  + 2);
    Nobj.setLambda(model.lambda_Nobj);

    // IAobj: The inter-arrival times among each object in a session.
    ExponentialDistribution IAobj(seed + 3);
    IAobj.setLambda(model.lambda_IAobj);    

    // IApkt: The inter-arrival times between packets within an object.
    ExponentialDistribution IApkt(seed + 4);
    IApkt.setLambda(model.lambda_IApkt);

    int nUsers = model.nUsers;

    // create PDUs
    // acumulated time for each user
    double accTime = 0;
    std::string userStr = "";
    for(int i = 0; i < nUsers; i++)
    {
        accTime = 0; // reset counter
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
            // pack all the objects of this session
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

                int nPacketsInObject = std::ceil(Nobj.nextSample());
                // ship all the packet of the current object
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

                    // packet ready to ship
                    this->packetVector->push_back(pduPtr);
                    
                    // inter packet time - do not add for the last packet
                    if(k < nPacketsInObject - 1)
                    {
                        double interArrivals = IApkt.nextSample();
                        accTime +=  interArrivals;
                    }

                }
                if(sessionEnd)
                {
                    break;
                }
                // delay to the next object -- do not add if it is the last
                if (j <  nSession - 1)
                {
                    accTime +=  IAobj.nextSample();
                }
            }
            // add delay to the next session -- there is no fixed number of sessions, always add.
            accTime += Tis.nextSample();
        }
    }

    // sort according to the arrival time
    // so the packets are going to be organized according arrival time.
    std::sort(this->packetVector->begin(), this->packetVector->end(), TgEngine::comparePDUs);
}

bool TgEngine::comparePDUs(const PDU *pdu1, const PDU *pdu2)
{
    return pdu1->getArrivalTime() < pdu2->getArrivalTime();
}
