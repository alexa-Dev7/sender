<?php
session_start();
if (!isset($_SESSION['user'])) {
    header("Location: login.php");
    exit();
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <link rel="stylesheet" href="assets/reset.css">
    <link rel="stylesheet" href="assets/styles.css">
    <title>Mebe Messenger</title>
</head>
<body>
    <div class="container">
        <h2>Welcome, <?= htmlspecialchars($_SESSION['user']) ?></h2>
        <div id="chat-box"></div>

        <input type="text" id="message" placeholder="Type a message...">
        <button onclick="sendMessage()">Send</button>
        <a href="logout.php">Logout</a>
    </div>

    <script>
        function fetchMessages() {
            fetch(`/poll?user=<?= $_SESSION['user'] ?>`)
                .then(response => response.json())
                .then(data => {
                    const chatBox = document.getElementById('chat-box');
                    chatBox.innerHTML = data.map(msg => `<p>${msg}</p>`).join('');
                });
        }

        setInterval(fetchMessages, 1000);

        function sendMessage() {
            const msg = document.getElementById('message').value;
            fetch('send_message.php', {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ message: msg })
            }).then(() => document.getElementById('message').value = "");
        }
    </script>
</body>
</html>
