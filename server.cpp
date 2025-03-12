#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "encrypt.h"
#include "utils.h"
#include <thread>
#include <chrono>

using json = nlohmann::json;

json loadMessages() {
    std::ifstream file("messages.json");
    json messages;
    file >> messages;
    return messages;
}

void saveMessages(const json &messages) {
    std::ofstream file("messages.json");
    file << messages.dump(4);
}

void handleMessage(const std::string &sender, const std::string &receiver, const std::string &message) {
    json messages = loadMessages();
    std::string encryptedMsg = encryptMessage(message);
    messages.push_back({{"sender", sender}, {"receiver", receiver}, {"message", encryptedMsg}});
    saveMessages(messages);
}

void pollMessages() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        json messages = loadMessages();
        std::cout << messages.dump(4) << std::endl;
    }
}

int main() {
    std::cout << "Server running with short polling..." << std::endl;
    pollMessages();
    return 0;
}
