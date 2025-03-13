#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "encrypt.h"
#include "utils.h"
#include <uwebsockets/App.h>

using json = nlohmann::json;

const int POLL_INTERVAL = 1000;  // 1-second polling interval

std::vector<std::string> get_active_users() {
    std::ifstream file("sessions.json");
    json sessions;
    if (!file.is_open()) return {};
    file >> sessions;

    std::vector<std::string> active_users;
    for (auto& session : sessions.items()) {
        active_users.push_back(session.key());
    }
    return active_users;
}

std::string fetch_messages(const std::string& user) {
    std::ifstream file("messages.json");
    json messages;
    if (!file.is_open()) return "[]";
    file >> messages;

    std::string user_messages = messages.contains(user) ? messages[user].dump() : "[]";
    return user_messages;
}

int main() {
    uWS::App().get("/poll", [](auto *res, auto *req) {
        std::string user = req->getQuery("user");
        std::string response = fetch_messages(user);
        res->end(response);
    }).listen(9001, [](auto *token) {
        if (token) {
            std::cout << "✅ Server running on port 9001\n";
        } else {
            std::cerr << "❌ Failed to start server.\n";
        }
    }).run();

    return 0;
}
