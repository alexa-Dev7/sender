#include <uwebsockets/App.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>  // For getenv()
#include <nlohmann/json.hpp>
#include <bcrypt/BCrypt.hpp>

using json = nlohmann::json;

std::vector<std::pair<std::string, std::string>> users;

void loadUsers() {
    std::ifstream file("users.json");
    if (file.is_open()) {
        json data;
        file >> data;
        for (auto &user : data) {
            users.push_back({user["username"], user["password"]});
        }
    }
}

bool authenticateUser(const std::string &username, const std::string &password) {
    for (auto &user : users) {
        if (user.first == username && BCrypt::validatePassword(password, user.second)) {
            return true;
        }
    }
    return false;
}

int main() {
    loadUsers();

    // Get Render-assigned port (default to 9001 if not set)
    int port = getenv("PORT") ? std::stoi(getenv("PORT")) : 9001;

    uWS::App().ws<json>("/*", {
        .message = [](auto *ws, std::string_view message, uWS::OpCode opCode) {
            std::cout << "Received: " << message << std::endl;
            ws->send(message, opCode);
        }
    }).listen(port, [port](auto *token) {
        if (token) {
            std::cout << "Server started on port " << port << std::endl;
        }
    }).run();

    return 0;
}
