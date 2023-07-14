
#ifndef __SESSION_H__
#define __SESSION_H__

#include <vector>
#include "PacketInfo.h"
#include "Object.h"
#include <unordered_map>

class Session {
private:
    std::vector<Object> objects;

public:

    void populateSession(const std::vector<PACKET_INFO *> &pkts);
    std::vector<Object> getObjects() const;
    void setObjects(const std::vector<Object>& objects);
};

#endif // __SESSION_H__