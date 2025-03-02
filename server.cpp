#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <nlohmann/json.hpp>  
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

using json = nlohmann::json;
using namespace std;

json readMessages() {
    ifstream file("messages.json");
    json messages;
    if (file.is_open()) {
        file >> messages;
        file.close();
    }
    return messages;
}

void startServer(int port) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        cerr << "Socket creation failed!" << endl;
        exit(EXIT_FAILURE);
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        cerr << "Binding failed!" << endl;
        exit(EXIT_FAILURE);
    }

    listen(server_fd, 3);
    cout << "Server listening on port " << port << endl;

    while (true) {
        json messages = readMessages();
        cout << "Checking for new messages..." << endl;

        for (const auto& msg : messages["messages"]) {
            cout << "New Message from " << msg["sender"] << ": " << msg["text"] << endl;
        }

        this_thread::sleep_for(chrono::seconds(3));
    }
}

int main() {
    int port = getenv("PORT") ? stoi(getenv("PORT")) : 10000;  // Default to 10000
    startServer(port);
    return 0;
}
