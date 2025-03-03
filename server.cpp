#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>
#include <thread>
#include <chrono>

using json = nlohmann::json;
using namespace std;

const string MESSAGES_FILE = "messages.json";
const int POLL_INTERVAL = 3; // Polling every 3 seconds

// Function to ensure messages.json is initialized
void initializeMessagesFile() {
    ifstream file(MESSAGES_FILE);
    if (!file.is_open() || file.peek() == ifstream::traits_type::eof()) {
        // If file does not exist or is empty, create it with an empty JSON array
        ofstream newFile(MESSAGES_FILE);
        newFile << "[]";
        newFile.close();
    }
}

// Function to safely load messages
json loadMessages() {
    ifstream file(MESSAGES_FILE);
    if (!file.is_open()) return json::array();

    json messages;
    try {
        file >> messages;
    } catch (json::parse_error&) {
        // If JSON is invalid, reset file to empty array
        cerr << "⚠️ JSON Parse Error: Resetting messages.json" << endl;
        ofstream resetFile(MESSAGES_FILE);
        resetFile << "[]";
        resetFile.close();
        return json::array();
    }
    return messages;
}

// Function to save a new message
void saveMessage(const string& sender, const string& message) {
    json messages = loadMessages();
    json newMessage = {{"sender", sender}, {"message", message}};
    messages.push_back(newMessage);

    ofstream file(MESSAGES_FILE);
    file << messages.dump(4); // Pretty print JSON
}

// Simulated short polling function (runs in a separate thread)
void pollMessages() {
    json lastMessages = loadMessages();

    while (true) {
        this_thread::sleep_for(chrono::seconds(POLL_INTERVAL));
        json currentMessages = loadMessages();

        if (currentMessages != lastMessages) {
            cout << "\n📩 New messages received!" << endl;
            lastMessages = currentMessages;
        }
    }
}

int main() {
    cout << "🚀 Chat server running on port 10000..." << endl;

    // Ensure messages.json is properly initialized
    initializeMessagesFile();

    // Start polling in a separate thread
    thread pollingThread(pollMessages);
    pollingThread.detach();

    while (true) {
        string sender, message;
        cout << "\nEnter your name (or type 'exit' to quit): ";
        getline(cin, sender);
        if (sender == "exit") break;

        cout << "Enter message (or type 'exit' to quit): ";
        getline(cin, message);
        if (message == "exit") break;

        saveMessage(sender, message);
        cout << "✅ Message sent!" << endl;
    }

    cout << "👋 Server shutting down..." << endl;
    return 0;
}
