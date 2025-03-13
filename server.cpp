#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <nlohmann/json.hpp>
#include <openssl/sha.h>  // SHA256 for password hashing
#include <unistd.h>        // Short polling

// SHA256 hashing function
std::string hashPassword(const std::string& password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)password.c_str(), password.length(), hash);

    std::ostringstream oss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        oss << std::hex << (int)hash[i];
    }
    return oss.str();
}

// Load user data
nlohmann::json loadUsers() {
    std::ifstream file("users.json");
    nlohmann::json users;
    if (file) file >> users;
    return users;
}

// Authenticate user
bool authenticateUser(const std::string &username, const std::string &password) {
    auto users = loadUsers();
    return users.contains(username) && users[username]["password"] == hashPassword(password);
}

// Load and save messages
nlohmann::json loadMessages() {
    std::ifstream file("messages.json");
    nlohmann::json messages;
    if (file) file >> messages;
    return messages;
}

void saveMessage(const std::string& user, const std::string& msg) {
    nlohmann::json messages = loadMessages();
    messages.push_back({{"user", user}, {"message", msg}, {"time", std::time(0)}});
    std::ofstream file("messages.json");
    file << messages.dump(4);
}

// Short polling chat room
void chatRoom() {
    std::cout << "✅ Server running on port 8080, polling every second...\n";
    while (true) {
        auto messages = loadMessages();
        std::cout << "🔥 Chat Room 🔥\n";
        if (!messages.empty()) {
            for (const auto &msg : messages) {
                std::cout << msg["user"] << ": " << msg["message"] << "\n";
            }
        } else {
            std::cout << "No messages yet. Start chatting!\n";
        }
        sleep(1);
    }
}

int main() {
    std::string username, password;

    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    if (authenticateUser(username, password)) {
        std::cout << "✅ Login successful!\n";
        chatRoom();
    } else {
        std::cout << "❌ Invalid username or password!\n";
    }

    return 0;
}
