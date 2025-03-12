#include <fmt/format.h>
#include <fmt/chrono.h>
#include "Agent.h"
#include <uwebsockets/App.h>
#include <iostream>
#include <google/protobuf/util/message_differencer.h>
#include "mmtp.pb.h"

void testProtobuf() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    //*
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
    //*/
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

void Mms::Agent::print(std::ostream& output) const
{
    //useUWebSockets();
    testProtobuf();
    output << fmt::format("\"{}\" by {} on {:%Y-%m-%d}\n\n", title, author, fmt::localtime(date))
           << fmt::format("{}", body);
}