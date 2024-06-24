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

        /**
         * @brief Creates samples based on the given LitModel.
         * 
         * @param model The LitModel used to generate traffic samples.
         * @param timeout The maximum time to generate samples.
         * @param seed Optional seed for random number generation.
         */
        void createSamples(LitModel& model, double timeout, unsigned int seed = 0);

        /**
         * @brief Pure virtual method to generate traffic.
         * 
         * Subclasses must implement this method to generate traffic to the specified target.
         * 
         * @param target The target for packet generation (e.g., file or network interface).
         */
        virtual void generate(const char* target) = 0;

        /**
         * @brief Comparator function for sorting PDUs.
         * 
         * @param pdu1 First PDU to compare.
         * @param pdu2 Second PDU to compare.
         * @return True if pdu1 arrival timer is smaller than than pdu2 (came before), false otherwise.
         */
        static bool comparePDUs(const PDU* pdu1, const PDU* pdu2);

    protected:
        std::vector<PDU*>* packetVector;

};

#endif // TG_ENGINE_H

