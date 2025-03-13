<?php
session_start();
$data = json_decode(file_get_contents('php://input'), true);
$message = htmlspecialchars($data['message']);
$user = $_SESSION['user'];

$messages = json_decode(file_get_contents('messages.json'), true);
$messages[$user][] = $message;

file_put_contents('messages.json', json_encode($messages));
