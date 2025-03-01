#include <uwebsockets/App.h>
#include <iostream>
#include <unordered_map>

struct UserSession {
    std::string username;
};

std::unordered_map<std::string, UserSession> activeUsers;

int main() {
    uWS::App().ws<UserSession>("/*", {
        .open = [](auto* ws) {
            UserSession* session = ws->getUserData();
            session->username = "User" + std::to_string(rand() % 1000);
            activeUsers[session->username] = *session;
            std::cout << "New connection: " << session->username << std::endl;
        },
        .message = [](auto* ws, std::string_view message, uWS::OpCode opCode) {
            std::cout << "Received: " << message << std::endl;
            ws->send(message, opCode);
        },
        .close = [](auto* ws, int code, std::string_view message) {
            UserSession* session = ws->getUserData();
            activeUsers.erase(session->username);
            std::cout << "Disconnected: " << session->username << std::endl;
        }
    }).listen(9001, [](auto* token) {
        if (token) {
            std::cout << "WebSocket server started on port 9001" << std::endl;
        }
    }).run();

    return 0;
}
