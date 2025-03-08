#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <uwebsockets/App.h>

using namespace std;
using json = nlohmann::json;

const string MESSAGES_FILE = "messages.json";

// Read messages from JSON
json readMessages() {
    ifstream file(MESSAGES_FILE);
    json messages;
    if (file.is_open()) {
        try {
            file >> messages;
        } catch (json::parse_error& e) {
            messages = json::array();
        }
    }
    return messages;
}

// Write messages to JSON
void writeMessages(const json& messages) {
    ofstream file(MESSAGES_FILE);
    if (file.is_open()) {
        file << messages.dump(4);
    }
}

int main() {
    uWS::App()
    .get("/messages", [](auto *res, auto *req) {
        json messages = readMessages();
        res->writeHeader("Content-Type", "application/json");
        res->end(messages.dump());
    })
    .post("/send", [](auto *res, auto *req) {
        res->onData([res](std::string_view data, bool last) {
            json received = json::parse(data);
            json messages = readMessages();

            json newMessage = {
                {"sender", received["sender"]},
                {"text", received["text"]}
            };
            messages.push_back(newMessage);
            writeMessages(messages);

            res->writeHeader("Content-Type", "application/json");
            res->end(R"({"status": "Message sent!"})");
        });
    })
    .listen(9001, [](auto *token) {
        if (token) {
            cout << "Server running on port 9001..." << endl;
        }
    })
    .run();
    
    return 0;
}
