<?php
// index.php - Login Page
session_start();

// If already logged in, redirect to hello page
if (isset($_SESSION['name'])) {
    header("Location: hello.php");
    exit();
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Login</title>

</head>
<body>
    <div class="card">
        <div class="eyebrow">Welcome</div>
        <h1>Sign In</h1>
        <p class="subtitle">Enter your name to continue</p>

        <form method="POST" action="hello.php">
            <div class="field">
                <label for="name">Your Name</label>
                <input
                    type="text"
                    id="name"
                    name="name"
                    placeholder="e.g. Ramesh Thapa"
                    required
                    autocomplete="off"
                >
            </div>
            <button type="submit">Enter &rarr;</button>
        </form>

        <hr class="divider">
        <p class="note">Your session start time will be recorded<br>and shown on the next page.</p>
    </div>
</body>
</html>
