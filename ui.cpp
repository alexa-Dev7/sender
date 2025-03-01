#include "sciter-x.h"
#include "sciter-x-window.hpp"

class MessengerUI : public sciter::window {
public:
    MessengerUI() : window(SW_MAIN | SW_RESIZEABLE) {}
};

int main() {
    MessengerUI ui;
    ui.load_html(R"(
        <window>
            <div style='background: #0084FF; color: white; padding: 10px; font-size: 20px;'>Messenger</div>
            <div id='chatbox' style='height: 400px; overflow-y: auto; padding: 10px;'></div>
            <input id='message' style='width: 80%;' />
            <button id='send' style='width: 18%;'>Send</button>
        </window>
    )", nullptr);
    ui.run();
    return 0;
}
