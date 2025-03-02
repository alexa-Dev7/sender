#include <iostream>
#include <thread>
#include <cstdlib>

using namespace std;

void runUI() {
    int port = getenv("UI_PORT") ? stoi(getenv("UI_PORT")) : 8080;
    cout << "UI Running on Port " << port << endl;
    
    while (true) {
        cout << "UI Active..." << endl;
        this_thread::sleep_for(chrono::seconds(5));
    }
}

int main() {
    thread uiThread(runUI);
    uiThread.join();
    return 0;
}
