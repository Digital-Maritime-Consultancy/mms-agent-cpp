#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <sstream>
#include "Agent.h"
#include "mmtp.pb.h"
#include <google/protobuf/util/message_differencer.h>

using namespace std;

TEST_CASE("MmtpMessage serialization and deserialization") {
    // Create an MmtpMessage
    MmtpMessage message;
    message.set_uuid("123e4567-e89b-12d3-a456-426614174000");
    message.set_msgtype(MsgType::PROTOCOL_MESSAGE);

    // Create a ProtocolMessage and set it in the MmtpMessage
    ProtocolMessage* protocolMessage = new ProtocolMessage();
    protocolMessage->set_protocolmsgtype(ProtocolMessageType::SUBSCRIBE_MESSAGE);
    message.set_allocated_protocolmessage(protocolMessage);

    // Serialize the message to a string
    std::string serialized;
    message.SerializeToString(&serialized);

    // Deserialize the message from the string
    MmtpMessage deserializedMessage;
    deserializedMessage.ParseFromString(serialized);

    // Compare the original and deserialized messages
    google::protobuf::util::MessageDifferencer differencer;
    REQUIRE(differencer.Compare(message, deserializedMessage));
}

int main(int argc, char* argv[])
{
    return Catch::Session().run(argc, argv);
}