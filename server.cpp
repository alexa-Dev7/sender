#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <unistd.h>
#include <ctime>

using json = nlohmann::json;
using namespace std;

struct Message {
    string sender;
    string text;
    time_t timestamp;
};

// Function to load messages from JSON file
vector<Message> loadMessages() {
    vector<Message> messages;
    ifstream file("messages.json");
    if (file) {
        json j;
        file >> j;
        for (const auto& item : j) {
            messages.push_back({item["sender"], item["text"], item["timestamp"]});
        }
    }
    return messages;
}

// Function to save messages to JSON file
void saveMessage(const Message& msg) {
    vector<Message> messages = loadMessages();
    messages.push_back(msg);

    json j = json::array();
    for (const auto& m : messages) {
        j.push_back({{"sender", m.sender}, {"text", m.text}, {"timestamp", m.timestamp}});
    }

    ofstream file("messages.json");
    file << j.dump(4);
}

// Function to simulate HTTP requests
void handleRequest() {
    string command;
    while (true) {
        cout << "Enter command (messages/send): ";
        cin >> command;

        if (command == "messages") {
            vector<Message> messages = loadMessages();
            for (const auto& msg : messages) {
                cout << msg.sender << ": " << msg.text << " (" << msg.timestamp << ")\n";
            }
        } else if (command == "send") {
            string sender, text;
            cout << "Enter sender name: ";
            cin >> sender;
            cout << "Enter message: ";
            cin.ignore();
            getline(cin, text);

            Message msg = {sender, text, time(nullptr)};
            saveMessage(msg);
            cout << "Message sent successfully!\n";
        }

        // Short polling: refresh every 3 seconds
        sleep(3);
    }
}

int main() {
    cout << "Starting short polling server...\n";
    handleRequest();
    return 0;
}
