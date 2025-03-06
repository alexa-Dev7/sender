#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <ctime>
#include <thread>
#include <chrono>

using json = nlohmann::json;
using namespace std;

const string FILENAME = "messages.json";
const int POLL_INTERVAL = 3; // Short polling interval in seconds

// Struct for a message
struct Message {
    string sender;
    string text;
    string timestamp;
};

// Function to get the current timestamp
string getTimestamp() {
    time_t now = time(0);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return string(buffer);
}

// Function to save messages to JSON file
void saveMessages(vector<Message>& messages) {
    json j;
    for (const auto& msg : messages) {
        j.push_back({{"sender", msg.sender}, {"text", msg.text}, {"timestamp", msg.timestamp}});
    }
    ofstream file(FILENAME);
    file << j.dump(4);
}

// Function to load messages from JSON file
vector<Message> loadMessages() {
    vector<Message> messages;
    ifstream file(FILENAME);
    if (!file) return messages; // Return empty if file doesn't exist

    json j;
    try {
        file >> j;
        for (const auto& item : j) {
            messages.push_back({item["sender"], item["text"], item["timestamp"]});
        }
    } catch (...) {
        // Handle JSON parsing errors (e.g., empty or corrupted file)
        cout << "⚠️ JSON Parse Error: Resetting messages.json\n";
        ofstream resetFile(FILENAME);
        resetFile << "[]";
    }
    return messages;
}

// API endpoint: Get messages (Short Polling)
void getMessages() {
    while (true) {
        vector<Message> messages = loadMessages();
        system("clear"); // Clear console for fresh output
        cout << "📩 Messages:\n";
        for (const auto& msg : messages) {
            cout << "[" << msg.timestamp << "] " << msg.sender << ": " << msg.text << "\n";
        }
        cout << "📡 Waiting for new messages...\n";
        this_thread::sleep_for(chrono::seconds(POLL_INTERVAL)); // Short polling interval
    }
}

// API endpoint: Send message
void sendMessage(const string& sender, const string& text) {
    vector<Message> messages = loadMessages();
    messages.push_back({sender, text, getTimestamp()});
    saveMessages(messages);
    cout << "✅ Message sent!\n";
}

// Main function
int main() {
    cout << "🚀 Chat Server Started...\n";
    thread pollingThread(getMessages); // Start polling thread

    while (true) {
        string sender, text;
        cout << "Enter your name (or type 'exit' to quit): ";
        getline(cin, sender);
        if (sender == "exit") break;

        cout << "Enter message (or type 'exit' to quit): ";
        getline(cin, text);
        if (text == "exit") break;

        sendMessage(sender, text);
    }

    pollingThread.join();
    return 0;
}
