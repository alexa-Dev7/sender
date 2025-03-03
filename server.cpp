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
    if (!file.is_open()) {
        // If file does not exist, create it with empty array
        ofstream newFile(MESSAGES_FILE);
        newFile << "[]";
        newFile.close();
    } else {
        // Check if file is empty
        file.seekg(0, ios::end);
        if (file.tellg() == 0) {
            ofstream newFile(MESSAGES_FILE);
            newFile << "[]";
            newFile.close();
        }
    }
}

// Function to load messages safely
json loadMessages() {
    ifstream file(MESSAGES_FILE);
    if (!file.is_open()) return json::array();
    
    json messages;
    try {
        file >> messages;
    } catch (json::parse_error& e) {
        cerr << "JSON Parse Error: " << e.what() << endl;
        return json::array(); // Return empty array on parse error
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

    // Ensure messages.json is properly initialized
    initializeMessagesFile();

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
