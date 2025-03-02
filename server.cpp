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

// Function to load messages from file
json loadMessages() {
    ifstream file(MESSAGES_FILE);
    if (!file.is_open()) return json::array();
    
    json messages;
    file >> messages;
    return messages;
}

// Function to save messages to file
void saveMessage(const string& sender, const string& message) {
    json messages = loadMessages();
    json newMessage = {{"sender", sender}, {"message", message}};
    messages.push_back(newMessage);

    ofstream file(MESSAGES_FILE);
    file << messages.dump(4);
}

// Simulated short polling function
void pollMessages() {
    json lastMessages = loadMessages();
    
    while (true) {
        this_thread::sleep_for(chrono::seconds(POLL_INTERVAL));
        json currentMessages = loadMessages();
        
        if (currentMessages != lastMessages) {
            cout << "New message received!" << endl;
            lastMessages = currentMessages;
        }
    }
}

int main() {
    cout << "Chat server running on port 10000..." << endl;
    
    thread pollingThread(pollMessages);
    pollingThread.detach();

    while (true) {
        string sender, message;
        cout << "Enter your name: ";
        getline(cin, sender);
        cout << "Enter message: ";
        getline(cin, message);

        saveMessage(sender, message);
        cout << "Message sent!" << endl;
    }

    return 0;
}
