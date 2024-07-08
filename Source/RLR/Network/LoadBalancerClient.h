#pragma once

#include <string>
#include <mutex>
#include <condition_variable>
#include "Sockets.h"

class LoadBalancerClient
{
public:
    LoadBalancerClient(const std::string& host, int port);
    std::string RequestServer(int32 userSeq);

private:
    void Connect();
    void SendRequest(int32 userSeq);
    void OnRecv(const uint8* buffer, int32 len);

    std::string host;
    int port;
    std::string mainServerAddress;
    std::string monsterServerAddress;
    int mainServerPort;
    int monsterServerPort;
    bool responseReceived;
    std::mutex mutex;
    std::condition_variable cv;
};
