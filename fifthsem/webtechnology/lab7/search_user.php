<?php
$xmlFile = 'users.xml';

// Read user_id from URL (GET)
$userId = $_GET['user_id'] ?? '';

if ($userId !== '') {
    $doc = new DOMDocument();

    if (!$doc->load($xmlFile)) {
        echo "<p>Error loading XML file.</p>";
        exit;
    }

    $users = $doc->getElementsByTagName('user');
    $found = false;

    foreach ($users as $user) {
        if ($user->getAttribute('id') == $userId) {
            $name   = $user->getElementsByTagName('name')->item(0)->nodeValue;
            $email  = $user->getElementsByTagName('email')->item(0)->nodeValue;
            $age    = $user->getElementsByTagName('age')->item(0)->nodeValue;
            $city   = $user->getElementsByTagName('city')->item(0)->nodeValue;

            echo "<h2>User Details (ID: $userId)</h2>";
            echo "<ul>";
            echo "<li>Name: $name</li>";
            echo "<li>Email: $email</li>";
            echo "<li>Age: $age</li>";
            echo "<li>City: $city</li>";
            echo "</ul>";
            $found = true;
            break;
        }
    }

    if (!$found) {
        echo "<h3>User with ID = $userId not found.</h3>";
    }
}
?>

<h2>Enter User ID</h2>
<form method="GET">
    <label>User ID:
        <input type="number" name="user_id" value="<?= htmlspecialchars($userId) ?>"
               min="1" max="10" required>
    </label>
    <button type="submit">Search</button>
</form>