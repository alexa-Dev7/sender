#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>
#include <chrono>
#include <thread>
#include <cstdlib> // For getenv()

using json = nlohmann::json;
using namespace std;

void loadMessages() {
    ifstream file("messages.json");
    json messages;

    if (file.peek() == ifstream::traits_type::eof()) {
        messages = json::array();
    } else {
        file >> messages;
    }

    system("clear");
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

int main() {
    // Get the port from Render environment variable
    const char* port = getenv("PORT");
    if (!port) port = "8080"; // Fallback if PORT isn't provided

    cout << "✅ Server started on port " << port << ", short polling every 1 second...\n";

    while (true) {
        loadMessages();
        this_thread::sleep_for(chrono::seconds(1));
    }

    return 0;
}
