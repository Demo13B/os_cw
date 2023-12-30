#pragma once
#include <string>

class MQ {
   private:
    char* _inputQueue;
    char* _outputQueue;
    const char* _inpQueueName;
    const char* _outpQueueName;
    int _queueSize;
    int _readIndex;
    int _writeIndex;

   public:
    MQ(std::string inputQueueName, std::string outputQueueName);
    ~MQ();

    auto recieve() -> std::string;
    auto send(std::string message) -> void;
};
