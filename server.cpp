#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <cstdlib>  // For getenv()
#include <nlohmann/json.hpp>  

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
    // Load environment variables
    int port = getenv("SERVER_PORT") ? stoi(getenv("SERVER_PORT")) : 9001;
    int pollInterval = getenv("POLL_INTERVAL") ? stoi(getenv("POLL_INTERVAL")) : 3;

    cout << "Short Polling Server Started on Port " << port << "!" << endl;

    while (true) {
        json messages = readMessages();
        cout << "Checking for new messages..." << endl;

        for (const auto& msg : messages["messages"]) {
            cout << "New Message from " << msg["sender"] << ": " << msg["text"] << endl;
        }

        this_thread::sleep_for(chrono::seconds(pollInterval));  // Use env variable for interval
    }

    return 0;
}
