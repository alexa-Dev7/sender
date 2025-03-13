#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <bcrypt.h>  // For password hashing

using json = nlohmann::json;
using namespace std;

// 🛠️ Hash a password with bcrypt
string hashPassword(const string& password) {
    char salt[BCRYPT_HASHSIZE];
    char hash[BCRYPT_HASHSIZE];

    if (bcrypt_gensalt(12, salt) != 0 || bcrypt_hashpw(password.c_str(), salt, hash) != 0) {
        cerr << "❌ Error hashing password!\n";
        return "";
    }
    return string(hash);
}

// 🔒 Check if a password matches the stored hash
bool verifyPassword(const string& password, const string& hash) {
    return bcrypt_checkpw(password.c_str(), hash.c_str()) == 0;
}

// 🔥 Load and display messages
void loadMessages() {
    ifstream file("messages.json");
    json messages;

    if (file.peek() == ifstream::traits_type::eof()) {
        messages = json::array();
    } else {
        file >> messages;
    }

    cout << "🔥 Chat Room 🔥\n\n";

    if (messages.empty()) {
        cout << "No messages yet. Start the conversation!\n";
    } else {
        for (auto& msg : messages) {
            if (msg.contains("user") && msg.contains("text")) {
                cout << msg["user"] << ": " << msg["text"] << endl;
            }
        }
    }
}

// 🚀 Main server setup — with port binding for Render
int main() {
    const char* portEnv = getenv("PORT");
    int port = portEnv ? stoi(portEnv) : 8080;

    cout << "✅ Server started on port " << port << ", short polling every 1 second...\n";

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        cerr << "❌ Error: Failed to create socket.\n";
        return 1;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        cerr << "❌ Error: Failed to bind to port " << port << ".\n";
        return 1;
    }

    if (listen(server_fd, 10) < 0) {
        cerr << "❌ Error: Failed to listen on port " << port << ".\n";
        return 1;
    }

    cout << "🚀 Server is live and waiting for connections!\n";

    while (true) {
        loadMessages();
        this_thread::sleep_for(chrono::seconds(1));
    }

    close(server_fd);
    return 0;
}
