#ifndef UTIL_H
#define UTIL_H

#include <string>

struct Host {
    std::string ip;
    int port;
    bool connectAuth;
};

#endif // UTIL_H