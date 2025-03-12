<!DOCTYPE html>
<html>
<head>
    <title>iOS Style Chat</title>
    <link rel="stylesheet" href="assets/reset.css">
    <link rel="stylesheet" href="assets/styles.css">
    <meta name="apple-mobile-web-app-capable" content="yes">
    <meta name="apple-mobile-web-app-status-bar-style" content="black-translucent">
</head>
<body>
    <div class="chat-container">
        <div class="chat-header">iOS Messenger</div>
        <div id="chat-box" class="chat-box"></div>
        <input type="text" id="message" placeholder="Type a message...">
        <button onclick="sendMessage()">Send</button>
    </div>

    <script>
        async function fetchMessages() {
            const response = await fetch('messages.json');
            const data = await response.json();
            const chatBox = document.getElementById('chat-box');
            chatBox.innerHTML = data.map(msg => 
                `<div class="message ${msg.sender === 'you' ? 'sent' : 'received'}">${msg.message}</div>`
            ).join('');
            setTimeout(fetchMessages, 1000);
        }

        async function sendMessage() {
            const message = document.getElementById('message').value;
            await fetch('server.php', { method: 'POST', body: JSON.stringify({ message }) });
            document.getElementById('message').value = "";
        }

        fetchMessages();
    </script>
</body>
</html>
