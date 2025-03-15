#include <fmt/format.h>
#include <fmt/chrono.h>
#include "Agent.h"
#include <iostream>
#include <google/protobuf/util/message_differencer.h>
#include <string>
#include <condition_variable>
#include <future>
#include "mmtp.pb.h"

using namespace Mms;

Agent::Agent(const std::string& mrn)
    : mrn(mrn), state(AgentState::NOT_CONNECTED), shutdown(false), cv() {
}

bool Agent::connect(const std::string& host, int port) {
    std::cout << "Attempt connect" << std::endl;
    if (!connectWebSocket(host, port)) {
        return false;
    }
    bool connectAuth = false;
    connectOverMmtp(connectAuth);
    return false;
}

Agent::~Agent() {
    shutdown = true;
    reconnectCond.notify_all();
    if (reconnectThread.joinable()) {
        reconnectThread.join();
    }
    disconnectWebSocket();
}

bool Agent::connectWebSocket(const std::string& host, int port) {
    webSocket.setUrl("ws://" + host + ":" + std::to_string(port));
    std::promise<bool> promise;
    std::future<bool> future = promise.get_future();

    webSocket.setOnMessageCallback([this, &promise](const ix::WebSocketMessagePtr& msg)
        {
            if (msg->type == ix::WebSocketMessageType::Open)
            {
                std::cout << "Connection established" << std::endl;
                promise.set_value(true);
            }
            else if (msg->type == ix::WebSocketMessageType::Error)
            {
                std::cout << "Connection error: " << msg->errorInfo.reason << std::endl;
                promise.set_value(false);
            } else if (msg->type == ix::WebSocketMessageType::Message) {
                std::cout << "Received message: " << msg->str << std::endl;
            }
        }
    );

    webSocket.start();

    std::cout << "Waiting for connection..." << std::endl;
    
    return future.get();
}

bool Agent::connectOverMmtp(const bool connectAuth) {
    MmtpMessage connectMessage;
    connectMessage.set_uuid("123e4567-e89b-12d3-a456-426614174000");
    connectMessage.set_msgtype(MsgType::PROTOCOL_MESSAGE);

}

void Agent::disconnectWebSocket() {
    std::lock_guard<std::mutex> lock(stateMutex);
    webSocket.stop();
    state = AgentState::NOT_CONNECTED;
}

bool Agent::sendMessage(const std::string& message) {
    if (state != AgentState::AUTHENTICATED) {
        std::cerr << "Cannot send message when not authenticated" << std::endl;
        return false;
    }
    webSocket.send(message);
    return true;
}

AgentState Agent::getStatus() const {
    //std::lock_guard<std::mutex> lock(stateMutex);
    return state;
}

void Agent::cleanUp() {
    shutdown = true;
    reconnectCond.notify_all();
}

void Agent::reconnectHandler() {
    while (!shutdown) {
        std::unique_lock<std::mutex> lock(stateMutex);
        reconnectCond.wait_for(lock, std::chrono::seconds(5));

        if (shutdown) break;
        if (state == AgentState::NOT_CONNECTED) {
            connectWebSocket();
        }
    }
}
