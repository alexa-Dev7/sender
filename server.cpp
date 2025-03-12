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
    file >> messages;

    system("clear");
    cout << "🔥 Chat Room 🔥\n\n";

    for (auto& msg : messages) {
        cout << msg["user"] << ": " << msg["text"] << endl;
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
