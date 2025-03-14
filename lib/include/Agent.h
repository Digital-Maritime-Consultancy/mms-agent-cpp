#pragma once

#include <string>
#include <iostream>
#include <ctime>
#include <map>
#include <thread>
#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocket.h>
#include <ixwebsocket/IXUserAgent.h>

namespace Mms {
    enum class AgentState {
        NOT_CONNECTED,
        CONNECTED,
        AUTHENTICATED
    };

    class Agent {
        public:
            Agent(std::string mrn, bool use_reconnect_token);
            ~Agent();
        
            void clean_up();
            void try_connect_edge_router();
            bool connect(std::string host, int port);
            bool send_message(std::string recipient, const std::vector<uint8_t>& data);
            bool receive_message();
            void disconnect();
        
        private:
            std::string mrn_;
            std::string host_;
            int port_;
            AgentState state_;
           
            std::mutex mutex;
            std::condition_variable cv;

            std::shared_ptr<ix::WebSocket> ws;
            std::queue<std::string> messageQueue;
            std::thread eventLoopThread;

            std::queue<std::vector<uint8_t>> outgoingMessages_;
            std::mutex queueMutex_;
            std::condition_variable queueCondition_;
            
            bool shutdown_;
            bool useReconnectToken_;
            std::map<std::string, std::chrono::system_clock::time_point> recentNotifies_;
        
            void MessageHandler();
            void ConnectionHandler();
    };
}
