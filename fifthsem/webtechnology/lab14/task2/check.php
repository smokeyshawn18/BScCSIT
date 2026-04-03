<?php
// check.php — App 2: Age Verification Result

// Validate input
if ($_SERVER['REQUEST_METHOD'] !== 'POST'
    || empty($_POST['name'])
    || !isset($_POST['age'])) {
    header("Location: index.html");
    exit();
}

$name = htmlspecialchars(trim($_POST['name']));
$age  = (int) $_POST['age'];

$is_authorized = ($age >= 18);

// Derived display values
$status_label  = $is_authorized ? "Access Granted"   : "Access Denied";
$status_color  = $is_authorized ? "#2c5f2e"          : "#9b2335";
$status_bg     = $is_authorized ? "rgba(44,95,46,0.08)" : "rgba(155,35,53,0.08)";
$status_border = $is_authorized ? "rgba(44,95,46,0.2)"  : "rgba(155,35,53,0.2)";
$icon          = $is_authorized ? "✓" : "✕";

$message = $is_authorized
    ? "Welcome to this site"
    : "Hello {$name}, you are not authorized to visit the site";
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title><?= $status_label ?></title>
    <style>
        @import url('https://fonts.googleapis.com/css2?family=Syne:wght@400;600;700;800&family=DM+Sans:wght@300;400;500&display=swap');

        *, *::before, *::after { box-sizing: border-box; margin: 0; padding: 0; }

        body {
            background: #f5f0e8;
            color: #1a1712;
            font-family: 'DM Sans', sans-serif;
            min-height: 100vh;
            display: flex;
            align-items: center;
            justify-content: center;
            padding: 40px 16px;
            position: relative;
        }


        .btn {
            display: inline-block;
            background: transparent;
            border: 1.5px solid #ddd8ce;
            border-radius: 4px;
            color: #8a8278;
            font-family: 'Syne', sans-serif;
            font-size: 11px;
            font-weight: 600;
            letter-spacing: 0.12em;
            text-transform: uppercase;
            padding: 13px 28px;
            text-decoration: none;
            transition: border-color 0.2s, color 0.2s;
        }

    </style>
</head>
<body>

<div class="card">
    <div class="icon-ring"><?= $icon ?></div>
    <div class="badge"><?= $status_label ?></div>

    <h1><?= $is_authorized ? "Welcome!" : "Access Denied" ?></h1>

    <div class="message"><?= $message ?></div>

    <div class="meta-row">
        <div class="meta-item">
            <span class="meta-label">Name</span>
            <span class="meta-value"><?= $name ?></span>
        </div>
        <div class="meta-item">
            <span class="meta-label">Age</span>
            <span class="meta-value"><?= $age ?></span>
        </div>
        <div class="meta-item">
            <span class="meta-label">Status</span>
            <span class="meta-value" style="color:<?= $status_color ?>"><?= $is_authorized ? '18+' : 'Under 18' ?></span>
        </div>
    </div>

    <a href="index.html" class="btn">&larr; Try Again</a>
</div>

</body>
</html>
