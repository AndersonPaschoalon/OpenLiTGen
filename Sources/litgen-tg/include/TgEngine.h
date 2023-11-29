#ifndef TG_ENGINE_H
#define TG_ENGINE_H

#include <queue>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "ExponentialDistribution.h"
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
    TgEngine();
 
    /**
     * @brief Destructor for the TgEngine class.
     */
    virtual ~TgEngine();

    void createSamples(LitModel& model, double timeout, unsigned int seed = 0);

    virtual void generate(const char* target) = 0;


    static bool comparePDUs(const PDU* pdu1, const PDU* pdu2);

private:
    std::vector<PDU*>* packetVector;


    // PDU* TgEngine::consumePDU();
};

#endif // TG_ENGINE_H

