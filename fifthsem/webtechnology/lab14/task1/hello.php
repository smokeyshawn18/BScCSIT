<?php
// hello.php
session_start();

// Handle form submission from index.php
if ($_SERVER['REQUEST_METHOD'] === 'POST' && !empty($_POST['name'])) {
    $_SESSION['name'] = htmlspecialchars(trim($_POST['name']));
    $_SESSION['start_time'] = time();
}

// If no session, redirect to login
if (!isset($_SESSION['name'])) {
    header("Location: index.php");
    exit();
}

$name       = $_SESSION['name'];
$start_time = $_SESSION['start_time'];
$formatted  = date("h:i:s A", $start_time);   // e.g. 09:45:12 AM
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Hello, <?= $name ?></title>

</head>
<body>

<header>
    <div class="brand">Portal</div>
    <div class="header-right">
        <div class="start-time">
            <span class="label">Session started</span>
            <span class="time"><?= $formatted ?></span>
        </div>
        <a href="logout.php" class="btn-logout">Logout &rarr;</a>
    </div>
</header>

<main>
    <div class="glow"></div>
    <div class="eyebrow">You're in</div>
    <h1>
        <span class="greeting">Hello,&nbsp;</span><br>
        <span class="name-text"><?= $name ?></span>
    </h1>
    <p class="tagline">Your session is active and running.</p>

    <div class="info-card">
        <span class="ic-label">Session started at</span>
        <span class="ic-value"><?= $formatted ?></span>
    </div>

    <div id="live-clock">Current time: <span id="clock-val"></span></div>
</main>

<script>
    function pad(n){ return String(n).padStart(2,'0'); }
    function tick(){
        const now = new Date();
        let h = now.getHours(), m = now.getMinutes(), s = now.getSeconds();
        const ampm = h >= 12 ? 'PM' : 'AM';
        h = h % 12 || 12;
        document.getElementById('clock-val').textContent =
            pad(h) + ':' + pad(m) + ':' + pad(s) + ' ' + ampm;
    }
    tick();
    setInterval(tick, 1000);
</script>

</body>
</html>
