#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <ctime>
#include <string>

using namespace std;
using json = nlohmann::json;

const string MESSAGES_FILE = "messages.json";

// Function to read messages from JSON
json readMessages() {
    ifstream file(MESSAGES_FILE);
    json messages;
    if (file.is_open()) {
        try {
            file >> messages;
        } catch (json::parse_error& e) {
            messages = json::array(); // Reset on error
        }
    }
    return messages;
}

// Function to write messages to JSON
void writeMessages(const json& messages) {
    ofstream file(MESSAGES_FILE);
    if (file.is_open()) {
        file << messages.dump(4);
    }
}

// Handle GET /messages (returns stored messages)
void handleMessagesRequest() {
    json messages = readMessages();
    cout << "Content-Type: application/json\n\n";
    cout << messages.dump();
}

// Handle POST /send (adds a new message)
void handleSendMessage() {
    string sender, message;
    cout << "Enter your name: ";
    getline(cin, sender);
    cout << "Enter your message: ";
    getline(cin, message);

    json messages = readMessages();
    json newMessage = {
        {"sender", sender},
        {"text", message},
        {"timestamp", time(0)}
    };
    messages.push_back(newMessage);
    writeMessages(messages);
    
    cout << "Message sent!\n";
}

int main() {
    cout << "Server running on port 9001...\n";
    string command;
    
    while (true) {
        cout << "Enter command (messages/send): ";
        cin >> command;
        if (command == "messages") {
            handleMessagesRequest();
        } else if (command == "send") {
            handleSendMessage();
        }
    }
    
    return 0;
}
