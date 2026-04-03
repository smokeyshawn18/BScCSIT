<?php
// logout.php
session_start();

// If no session existed at all, just redirect
if (!isset($_SESSION['name'])) {
    header("Location: index.php");
    exit();
}

$name       = $_SESSION['name'];
$start_time = $_SESSION['start_time'];
$end_time   = time();

// Calculate duration
$duration_sec = $end_time - $start_time;
$hours   = floor($duration_sec / 3600);
$minutes = floor(($duration_sec % 3600) / 60);
$seconds = $duration_sec % 60;

if ($hours > 0) {
    $duration_str = sprintf("%d hr %d min %d sec", $hours, $minutes, $seconds);
} elseif ($minutes > 0) {
    $duration_str = sprintf("%d min %d sec", $minutes, $seconds);
} else {
    $duration_str = sprintf("%d second%s", $seconds, $seconds !== 1 ? 's' : '');
}

$start_formatted = date("h:i:s A", $start_time);
$end_formatted   = date("h:i:s A", $end_time);

// Destroy session
session_unset();
session_destroy();
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Goodbye, <?= htmlspecialchars($name) ?></title>
 
</head>
<body>

<div class="glow"></div>

<div class="eyebrow">Session Ended</div>
<h1>Thank You,<br><?= htmlspecialchars($name) ?></h1>
<p class="sub">We hope to see you again soon.</p>

<div class="stats">
    <div class="stat">
        <span class="stat-label">Logged in at</span>
        <span class="stat-value"><?= $start_formatted ?></span>
    </div>
    <div class="stat">
        <span class="stat-label">Logged out at</span>
        <span class="stat-value"><?= $end_formatted ?></span>
    </div>
    <div class="stat highlight">
        <span class="stat-label">Duration of use</span>
        <span class="stat-value"><?= $duration_str ?></span>
    </div>
</div>

<a href="index.php" class="btn-back">&larr; Sign in again</a>

</body>
</html>
