#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    cout << "Content-type: text/html\n\n";
    cout << "<!DOCTYPE html>\n";
    cout << "<html lang='en'>\n";
    cout << "<head>\n";
    cout << "<meta charset='UTF-8'>\n";
    cout << "<meta name='viewport' content='width=device-width, initial-scale=1.0'>\n";
    cout << "<title>Sender</title>\n";
    cout << "<style>\n";
    cout << "body { font-family: Arial, sans-serif; background-color: #f0f2f5; margin: 0; padding: 0; }\n";
    cout << ".container { width: 100%; max-width: 600px; margin: auto; background: white; height: 100vh; display: flex; flex-direction: column; }\n";
    cout << ".header { background: #007bff; color: white; padding: 15px; text-align: center; }\n";
    cout << ".chat-window { flex: 1; overflow-y: auto; padding: 10px; }\n";
    cout << ".message { margin: 10px 0; max-width: 70%; padding: 10px; border-radius: 20px; word-wrap: break-word; }\n";
    cout << ".sent { align-self: flex-end; background: #007bff; color: white; }\n";
    cout << ".received { align-self: flex-start; background: #e0e0e0; }\n";
    cout << ".input-area { display: flex; padding: 10px; background: #f0f0f0; }\n";
    cout << ".input-area input { flex: 1; padding: 10px; border: 1px solid #ccc; border-radius: 20px; }\n";
    cout << ".input-area button { padding: 10px 20px; background: #007bff; color: white; border: none; border-radius: 20px; margin-left: 10px; }\n";
    cout << "</style>\n";
    cout << "</head>\n";
    cout << "<body>\n";
    cout << "<div class='container'>\n";
    cout << "<div class='header'>Sender</div>\n";
    cout << "<div class='chat-window' id='chatWindow'></div>\n";
    cout << "<div class='input-area'>\n";
    cout << "<input type='text' id='messageInput' placeholder='Type your message...'>\n";
    cout << "<button onclick='sendMessage()'>Send</button>\n";
    cout << "</div>\n";
    cout << "</div>\n";
    cout << "<script>\n";
    cout << "async function sendMessage() {\n";
    cout << "  let message = document.getElementById('messageInput').value;\n";
    cout << "  if (message.trim() === '') return;\n";
    cout << "  fetch('/send', { method: 'POST', body: JSON.stringify({ sender: 'User', text: message }), headers: { 'Content-Type': 'application/json' } });\n";
    cout << "  document.getElementById('messageInput').value = '';\n";
    cout << "  loadMessages();\n";
    cout << "}\n";
    cout << "async function loadMessages() {\n";
    cout << "  let response = await fetch('/messages');\n";
    cout << "  let messages = await response.json();\n";
    cout << "  let chatWindow = document.getElementById('chatWindow');\n";
    cout << "  chatWindow.innerHTML = '';\n";
    cout << "  messages.forEach(msg => {\n";
    cout << "    let div = document.createElement('div');\n";
    cout << "    div.className = msg.sender === 'User' ? 'message sent' : 'message received';\n";
    cout << "    div.innerText = msg.text;\n";
    cout << "    chatWindow.appendChild(div);\n";
    cout << "  });\n";
    cout << "}\n";
    cout << "setInterval(loadMessages, 3000);\n"; // Short polling every 3 sec
    cout << "</script>\n";
    cout << "</body>\n";
    cout << "</html>\n";
    return 0;
}
