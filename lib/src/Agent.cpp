#include <fmt/format.h>
#include <fmt/chrono.h>
#include "Agent.h"
#include <iostream>
#include <google/protobuf/util/message_differencer.h>
#include <string>
#include "mmtp.pb.h"

using namespace Mms;

Agent::Agent(std::string mrn, bool useReconnectToken)
    : mrn_(std::move(mrn)), state_(AgentState::NOT_CONNECTED), 
      shutdown_(false), useReconnectToken_(useReconnectToken) {}

void Agent::clean_up() {
    shutdown_ = true;
}

Agent::~Agent() {
    clean_up();
}

bool Agent::connect(std::string host, int port) {

}


/*
void Agent::CleanUp() {
    shutdown_ = true;
}

bool Agent::Connect(std::string host, int port) {
    try {
        boost::asio::ip::tcp::resolver resolver(ioContext_);
        auto endpoints = resolver.resolve(host, std::to_string(port));
        boost::asio::connect(ws_.next_layer().next_layer(), endpoints.begin(), endpoints.end());

        ws_.next_layer().handshake(boost::asio::ssl::stream_base::client);
        ws_.handshake(host, "/");
        state_ = AgentState::CONNECTED;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Connection error: " << e.what() << std::endl;
        return false;
    }
}

bool Agent::SendMessage(std::string recipient, const std::vector<uint8_t>& data) {
    std::lock_guard<std::mutex> lock(queueMutex_);
    outgoingMessages_.push(data);
    queueCondition_.notify_one();
    return true;
}

bool Agent::ReceiveMessage() {
    try {
        boost::beast::flat_buffer buffer;
        ws_.read(buffer);
        std::cout << "Received message: " << boost::beast::buffers_to_string(buffer.data()) << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Receive error: " << e.what() << std::endl;
        return false;
    }
}

void Agent::Disconnect() {
    if (state_ == AgentState::CONNECTED || state_ == AgentState::AUTHENTICATED) {
        ws_.close(boost::beast::websocket::close_code::normal);
        state_ = AgentState::NOT_CONNECTED;
    }
}

void Agent::MessageHandler() {
    while (!shutdown_) {
        std::unique_lock<std::mutex> lock(queueMutex_);
        queueCondition_.wait(lock, [this] { return !outgoingMessages_.empty() || shutdown_; });

        if (shutdown_) break;

        auto message = std::move(outgoingMessages_.front());
        outgoingMessages_.pop();
        lock.unlock();

        try {
            ws_.write(boost::asio::buffer(message));
        } catch (const std::exception& e) {
            std::cerr << "Send error: " << e.what() << std::endl;
        }
    }
}

void Agent::TryConnectEdgeRouter() {
    while (!shutdown_) {
        if (state_ != AgentState::AUTHENTICATED) {
            std::this_thread::sleep_for(std::chrono::seconds(5));
            if (!Connect("edgerouter.example.com", 443)) {
                continue;
            }
            std::cout << "Connected to edge router." << std::endl;
        }
    }
}

void testProtobuf() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    MmtpMessage message;
    message.set_uuid("123e4567-e89b-12d3-a456-426614174000");

    std::string serialized;
    message.SerializeToString(&serialized);

    MmtpMessage message2;
    message2.ParseFromString(serialized);

    google::protobuf::util::MessageDifferencer differencer;
    if (differencer.Compare(message, message2)) {
        std::cout << "Protobuf message is the same after serialization and deserialization" << std::endl;
    } else {
        std::cout << "Protobuf message is different after serialization and deserialization" << std::endl;
    }
}

void useUWebSockets() {
    uWS::App().get("/*", [](auto *res, auto *req) {
        res->end("Hello, world!");
    }).listen(3000, [](auto *token) {
        if (token) {
            std::cout << "Server listening on port 3000" << std::endl;
        }
    }).run();
}



// ...existing code...

void Mms::Agent::clean_up()
{
    //useUWebSockets();
    testProtobuf();
    output << fmt::format("\"{}\" by {} on {:%Y-%m-%d}\n\n", title, author, fmt::localtime(date))
           << fmt::format("{}", body);
}

*/