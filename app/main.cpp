#include <iostream>
#include "Agent.h"

int main()
{
    Mms::Agent agent
    {
        "Sam",
        std::time(nullptr),
        "Delivering cargos",
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor"
                " incididunt ut labore et dolore magna aliqua.\nUt enim ad minim veniam, quis nostrud"
                " exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat."
    };

    agent.print(std::cout);

    return 0;
}
