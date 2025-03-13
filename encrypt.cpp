#include "encrypt.h"
#include <string>

std::string encrypt(const std::string& data) {
    return "ENCRYPTED(" + data + ")";
}

std::string decrypt(const std::string& data) {
    return data.substr(10, data.size() - 11);
}
