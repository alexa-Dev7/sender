#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <nlohmann/json.hpp>  // JSON library for handling messages

using json = nlohmann::json;
using namespace std;

// Function to read messages from JSON
json readMessages() {
    ifstream file("messages.json");
    json messages;
    if (file.is_open()) {
        file >> messages;
        file.close();
    }
    return messages;
}

int main() {
    cout << "Short Polling Server Started on Port 9001!" << endl;

    while (true) {
        json messages = readMessages();
        cout << "Checking for new messages..." << endl;

        for (const auto& msg : messages["messages"]) {
            cout << "New Message from " << msg["sender"] << ": " << msg["text"] << endl;
        }

        this_thread::sleep_for(chrono::seconds(3));  // Poll every 3 seconds
    }

    return 0;
}
