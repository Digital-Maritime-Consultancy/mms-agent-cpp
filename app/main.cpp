#include <iostream>
#include "Agent.h"

int main()
{
    Mms::Agent agent("mrn");
    if (agent.connect("localhost", 3000)) {
        std::cout << "Successfully connected." << std::endl;
    } else {
        std::cout << "Failed to connect." << std::endl;
    }
    std::cout << "Status: " << static_cast<int>(agent.getStatus()) << std::endl;
    return 0;
}
