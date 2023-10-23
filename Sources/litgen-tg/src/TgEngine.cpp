#include "TgEngine.h"
#include <chrono>

TgEngine::TgEngine(const std::string& target) : target(target) 
{
}

TgEngine::~TgEngine() {}

void TgEngine::samplePduQueue(LitModel &model, double timeout)
{
}

PDU* TgEngine::consumePDU() 
{
    auto startTime = std::chrono::steady_clock::now();
    PDU* pdu = nullptr;

    while (!pdu) 
    {
        std::unique_lock<std::mutex> lock(packetQueueMutex);

        if (!packetQueue->empty()) {
            pdu = packetQueue->front();
            packetQueue->pop();
        } 
        else 
        {
            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime).count();
            if (elapsed >= queueTimeout * 1000) {
                break; // Timeout reached
            }
            // Wait for a new PDU to be added to the queue or timeout
            packetQueueCV.wait_for(lock, std::chrono::milliseconds(100));
        }
    }

    return pdu;
}


/**
 

void TgEngine::generate(std::queue<PDU*>* ptrPacketQueue, double timeout) {
    while (true) {
        // Check if the queue is empty
        if (ptrPacketQueue->empty()) {
            // Sleep for the specified timeout
            std::this_thread::sleep_for(std::chrono::duration<double>(timeout));
            if (ptrPacketQueue->empty()) {
                // Queue is still empty, stop generating
                break;
            }
        }

        // Get the front packet from the queue
        PDU* packet = ptrPacketQueue->front();
        ptrPacketQueue->pop();

        // Craft and send the packet to the target (implementation dependent)
        // ...
    }
}


 * **/

