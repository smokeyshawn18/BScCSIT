<!DOCTYPE html>
<html>
<head>
    <title>PHP Lab Programs</title>
</head>
<body>

<h2>1. Sum of Digits</h2>
<form method="post">
    Enter Number: <input type="number" name="digitsNum">
    <button type="submit" name="sumBtn">Calculate</button>
</form>

<h2>2. Palindrome Check</h2>
<form method="post">
    Enter Number: <input type="number" name="palNum">
    <button type="submit" name="palBtn">Check</button>
</form>

<h2>3. Date and Time</h2>
<form method="post">
    <button type="submit" name="timeBtn">Show Date/Time</button>
</form>

<hr>

<?php
function sumOfDigits($num) {
    $sum = 0;
    while ($num > 0) {
        $sum += $num % 10;
        $num = intval($num / 10);
    }
    return $sum;
}

function isPalindrome($num) {
    $original = $num;
    $reverse = 0;
    while ($num > 0) {
        $reverse = $reverse * 10 + $num % 10;
        $num = intval($num / 10);
    }
    return $original == $reverse;
}

// Handle Sum
if (isset($_POST['sumBtn'])) {
    $num = $_POST['digitsNum'];
    echo "<p><b>Sum of digits of $num = " . sumOfDigits($num) . "</b></p>";
}

// Handle Palindrome
if (isset($_POST['palBtn'])) {
    $num = $_POST['palNum'];
    $result = isPalindrome($num) ? "PALINDROME" : "NOT PALINDROME";
    echo "<p><b>$num is $result</b></p>";
}

// Handle Date/Time
if (isset($_POST['timeBtn'])) {
    echo "<p><b>Date:</b> " . date("Y-m-d H:i:s") . "</p>";
    echo "<p><b>Formatted:</b> " . date("d M Y, l") . "</p>";
}
?>

</body>
</html>