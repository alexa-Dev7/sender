<?php
session_start();
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $users = json_decode(file_get_contents('users.json'), true);
    $user = $_POST['username'];
    $pass = $_POST['password'];

    if (isset($users[$user]) && password_verify($pass, $users[$user])) {
        $_SESSION['user'] = $user;
        $sessions = json_decode(file_get_contents('sessions.json'), true);
        $sessions[$user] = true;
        file_put_contents('sessions.json', json_encode($sessions));
        header('Location: index.php');
        exit();
    } else {
        echo "<script>alert('Invalid username or password!'); window.location.href='login.php';</script>";
    }
}
?>

<form action="login.php" method="post">
    <input type="text" name="username" placeholder="Username" required>
    <input type="password" name="password" placeholder="Password" required>
    <button type="submit">Login</button>
</form>
