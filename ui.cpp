#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Function to display chat messages
void displayChat() {
    std::ifstream file("messages.json");
    if (!file) {
        std::cerr << "❌ Error loading chat history!\n";
        return;
    }

    json messages;
    file >> messages;

    std::cout << "\n📨 Chat Messages:\n";
    for (const auto &msg : messages) {
        std::cout << "👤 " << msg["user"] << ": " << msg["message"] << "\n";
    }
}

// Function to send a message
void sendMessage(const std::string &username, const std::string &message) {
    std::ofstream file("messages.json", std::ios::app);
    if (!file) {
        std::cerr << "❌ Error opening messages.json!\n";
        return;
    }

    json newMessage = {{"user", username}, {"message", message}};
    file << newMessage.dump() << std::endl;

    std::cout << "✅ Message sent!\n";
}

int main() {
    std::string username;
    std::cout << "Enter your name: ";
    std::getline(std::cin, username);

    while (true) {
        std::string message;
        std::cout << "Enter message (or type 'exit' to quit): ";
        std::getline(std::cin, message);

        if (message == "exit") break;

        sendMessage(username, message);
        displayChat();
    }

    return 0;
}
