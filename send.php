<?php
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $user = htmlspecialchars($_POST['user']);
    $text = htmlspecialchars($_POST['text']);

    $messages = json_decode(file_get_contents('messages.json'), true);
    $messages[] = ["user" => $user, "text" => $text];

    file_put_contents('messages.json', json_encode($messages, JSON_PRETTY_PRINT));
    header("Location: index.php");
}
?>
