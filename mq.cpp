#include "mq.hpp"
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string>

MQ::MQ(std::string inputQueueName, std::string outputQueueName) {
    _inpQueueName = inputQueueName.c_str();
    _outpQueueName = outputQueueName.c_str();
    _readIndex = 0;
    _writeIndex = 0;

    int memoryd = shm_open(inputQueueName.c_str(), O_RDWR | O_CREAT, 0666);
    ftruncate(memoryd, 1024);
    _inputQueue = (char*)mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, memoryd, 0);

    memoryd = shm_open(outputQueueName.c_str(), O_RDWR | O_CREAT, 0666);
    ftruncate(memoryd, 1024);
    _outputQueue = (char*)mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, memoryd, 0);
}

MQ::~MQ() {
    munmap(_inputQueue, 1024);
    munmap(_outputQueue, 1024);
    shm_unlink(_inpQueueName);
    shm_unlink(_outpQueueName);
}

auto MQ::recieve() -> std::string {
    std::string answer = "";
    char c = _inputQueue[_readIndex];

    while (c != '\0') {
        answer += c;
        _readIndex = (_readIndex + 1) % 1024;
        c = _inputQueue[_readIndex];
    }
    _readIndex = (_readIndex + 1) % 1024;

    return answer;
}

auto MQ::send(std::string message) -> void {
    for (size_t i = 0; i != message.length(); ++i) {
        char c = message[i];
        _outputQueue[_writeIndex] = c;
        _writeIndex = (_writeIndex + 1) % 1024;
    }
    _outputQueue[_writeIndex] = '\0';
    _writeIndex = (_writeIndex + 1) % 1024;
}