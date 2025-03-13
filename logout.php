<?php
session_start();
session_destroy();
file_put_contents('sessions.json', json_encode([]));
header('Location: login.php');
