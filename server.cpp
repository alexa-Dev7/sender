#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>
#include <chrono>
#include <thread>

using json = nlohmann::json;
using namespace std;

void loadMessages() {
    ifstream file("messages.json");
    json messages;

    // Check if file is empty or broken
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
    cout << "✅ Server started, short polling every 1 second...\n";

    while (true) {
        loadMessages();
        this_thread::sleep_for(chrono::seconds(1));
    }

    return 0;
}
