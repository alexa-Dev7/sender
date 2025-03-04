#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include <uwebsockets/App.h>

#define PORT 10000  // Render requires port 10000

using json = nlohmann::json;
std::vector<json> messages;

// Function to load messages from JSON file
void loadMessages() {
    std::ifstream file("messages.json");
    if (file.peek() != std::ifstream::traits_type::eof()) {
        try {
            file >> messages;
        } catch (...) {
            std::cerr << "⚠️ JSON Parse Error: Resetting messages.json\n";
            messages.clear();
        }
    }
}

// Function to save messages to JSON file
void saveMessages() {
    std::ofstream file("messages.json");
    file << messages.dump(4);
}

int main() {
    loadMessages();

    uWS::App().ws<json>("/*", {
        .open = [](auto *ws) {
            std::cout << "✅ Client Connected\n";
        },
        .message = [](auto *ws, std::string_view message, uWS::OpCode opCode) {
            try {
                json receivedMessage = json::parse(message);
                messages.push_back(receivedMessage);
                saveMessages();

                ws->send("✅ Message received!", opCode);
            } catch (...) {
                ws->send("⚠️ JSON Parse Error", opCode);
            }
        },
        .close = [](auto *ws, int code, std::string_view message) {
            std::cout << "❌ Client Disconnected\n";
        }
    }).listen(PORT, [](auto *token) {
        if (token) {
            std::cout << "🚀 Server running on port " << PORT << "\n";
        } else {
            std::cerr << "❌ Failed to start server!\n";
        }
    }).run();

    return 0;
}
