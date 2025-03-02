#include <iostream>
#include <fstream>
#include <string>
#include <uwebsockets/App.h>

using namespace std;

#define UI_PORT 8080

string loadHTML() {
    ifstream file("index.html");
    return string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
}

int main() {
    string html = loadHTML();

    uWS::App().get("/*", [&html](auto *res, auto *req) {
        res->end(html);
    }).listen(UI_PORT, [](auto *token) {
        if (token) {
            cout << "UI running on port " << UI_PORT << endl;
        } else {
            cerr << "Failed to start UI" << endl;
        }
    }).run();
}
