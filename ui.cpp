#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

// Function to send a message
void sendMessage(const string& sender, const string& text) {
    ifstream file("messages.json");
    json messages;

    if (file.is_open()) {
        file >> messages;
        file.close();
    }

    messages["messages"].push_back({{"sender", sender}, {"text", text}});

    ofstream outFile("messages.json");
    outFile << messages.dump(4);  // Save with indentation
    outFile.close();
}

int main() {
    cout << "Simple UI Started!" << endl;
    string sender, text;

    while (true) {
        cout << "Enter sender name: ";
        getline(cin, sender);

        cout << "Enter message: ";
        getline(cin, text);

        sendMessage(sender, text);
        cout << "Message sent!" << endl;
    }

    return 0;
}
