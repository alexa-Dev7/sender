#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <chrono>
#include <thread>
#include <vector>
#include <mutex>
#include <ctime>

using json = nlohmann::json;
using namespace std;

mutex fileMutex;
const string MESSAGES_FILE = "messages.json";

// Function to read messages from JSON
json readMessages() {
    lock_guard<mutex> lock(fileMutex);
    ifstream file(MESSAGES_FILE);
    json messages;
    
    if (file.is_open()) {
        try {
            file >> messages;
        } catch (json::parse_error& e) {
            messages = json::array(); // Reset on error
        }
    } else {
        messages = json::array();
    }
    
    return messages;
}

// Function to write messages to JSON
void writeMessages(const json& messages) {
    lock_guard<mutex> lock(fileMutex);
    ofstream file(MESSAGES_FILE);
    
    if (file.is_open()) {
        file << messages.dump(4);
    }
}

// Function to handle sending messages
void sendMessage(const string& sender, const string& message) {
    json messages = readMessages();
    json newMessage = {
        {"sender", sender},
        {"message", message},
        {"timestamp", time(0)}
    };
    
    messages.push_back(newMessage);
    writeMessages(messages);
}

// Function to get latest messages
json getMessages() {
    return readMessages();
}

int main() {
    cout << "Server running on port 9001..." << endl;
    while (true) {
        // Simulate API loop (use short polling every 3 seconds)
        this_thread::sleep_for(chrono::seconds(3));
    }
    return 0;
}
