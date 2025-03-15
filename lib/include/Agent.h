#pragma once

#include <string>
#include <iostream>
#include <ctime>
#include <map>
#include <thread>
#include <ixwebsocket/IXWebSocket.h>

namespace Mms {
    enum class AgentState {
        NOT_CONNECTED,
        CONNECTED,
        AUTHENTICATED
    };

    class Agent {
    public:
        Agent(const std::string& mrn);
        ~Agent();
    
        void disconnectWebSocket();
        void cleanUp();
        bool connect(const std::string& host, int port);
        
        bool sendMessage(const std::string& message);
        AgentState getStatus() const;
    
    private:
        std::string mrn;
        AgentState state;
        std::condition_variable cv;
        ix::WebSocket webSocket;
        
        std::mutex stateMutex;
        std::condition_variable reconnectCond;
        std::atomic<bool> shutdown;
        std::thread reconnectThread;
        
        bool connectWebSocket(const std::string& host, int port);
        bool connectOverMmtp(const bool connectAuth);
        void reconnectHandler();
    };
}
