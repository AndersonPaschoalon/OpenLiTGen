#include <vector>
#include <string>

/**
typedef struct _mod_packet
{
    double arrivalTime;
    unsigned short int pktSize;
}MOD_PACKET;


typedef struct _mod_object
{
    unsigned long userFlowId;
    long int objectId;
    std::string srcIp;
    unsigned short dstPort;
    std::vector<MOD_PACKET> pkts;
}MOD_OBJECT;


/// @brief Session object. Each user will have many sessionsof different flows
typedef struct _traffic_session
{
    long int sessionId;
    std::vector<MOD_OBJECT*> objects; 
}TRAFFIC_SESSION;
*/

typedef struct _packet_info
{
    double arrivalTime;
    unsigned short pktSize;
    unsigned long userId;
    unsigned long userFlowId;
    std::string ipSrc;
    std::string ipDst;
    std::string transportProtocol;
    int portSrc;
    int portDst; 
    bool syn;
    bool ack;
    bool fin;
    bool rst;

} PACKET_INFO;

bool comparePacketInfo(const PACKET_INFO* a, const PACKET_INFO* b);

/*
/// @brief This function iteract over a pkts list and look for packets of a given user ID and user flow ID.
/// It fills the fields srcIp and dstPort of the objLists, and uses the flags fin and rst to tell when the 
/// a object has finished. As result this funcion will produce a list of MOD_OBJECTs for a given user 
/// user flow.
/// @param pkts 
/// @param userId 
/// @param userFlowId 
/// @param objLists 
void buildObjectList(std::vector<PACKET_INFO*>& pkts, unsigned long userId, unsigned long userFlowId, std::vector<MOD_OBJECT*>& objLists);
**/
