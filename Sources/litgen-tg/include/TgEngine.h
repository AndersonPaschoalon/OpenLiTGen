#ifndef TG_ENGINE_H
#define TG_ENGINE_H

#include <queue>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "PDU.h"
#include "LitModel.h"

/**
 * @brief Abstract class representing a traffic generator engine.
 * 
 * This class defines the interface for a traffic generator engine. Subclasses must implement
 * the `generate` method to craft and send packets to the specified target.
 */
class TgEngine {
public:
    /**
     * @brief Constructor for the TgEngine class.
     * 
     * @param target The target for packet generation (e.g., file or network interface).
     */
    TgEngine(const std::string& target);

    /**
     * @brief Destructor for the TgEngine class.
     */
    virtual ~TgEngine();

    void samplePduQueue(LitModel& model, double timeout);

    virtual void generate() = 0;


private:
    std::string target;
    std::queue<PDU*>* packetQueue;
    double queueTimeout;
    std::mutex packetQueueMutex;       // Mutex for packet queue access
    std::condition_variable packetQueueCV; // Condition variable for packet queue synchronization


    PDU* TgEngine::consumePDU();
};

#endif // TG_ENGINE_H

