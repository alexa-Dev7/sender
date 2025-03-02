#include <iostream>
#include <uwebsockets/App.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <vector>

using namespace std;
using json = nlohmann::json;

#define SERVER_PORT 10000

vector<string> messages;

// Load messages from JSON
void loadMessages() {
    ifstream file("messages.json");
    if (file) {
        json j;
        file >> j;
        messages = j["messages"].get<vector<string>>();
    }
}

// Save messages to JSON
void saveMessages() {
    ofstream file("messages.json");
    json j;
    j["messages"] = messages;
    file << j.dump(4);
}

int main() {
    loadMessages();

    uWS::App().ws<"/*">([](auto *ws, auto *req) {
        ws->send("Connected to WebSocket server");
    }).listen(SERVER_PORT, [](auto *token) {
        if (token) {
            cout << "Server running on port " << SERVER_PORT << endl;
        } else {
            cerr << "Failed to start server" << endl;
        }
    }).run();

    saveMessages();
}
