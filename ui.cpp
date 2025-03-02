#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

const string MESSAGES_FILE = "messages.json";

// Function to display chat messages
void displayMessages() {
    ifstream file(MESSAGES_FILE);
    if (!file.is_open()) {
        cout << "No messages yet." << endl;
        return;
    }
    
    json messages;
    file >> messages;

    cout << "=== Chat Messages ===" << endl;
    for (const auto& msg : messages) {
        cout << msg["sender"] << ": " << msg["message"] << endl;
    }
    cout << "=====================" << endl;
}

int main() {
    cout << "Welcome to the Chat UI!" << endl;
    displayMessages();
    return 0;
}
