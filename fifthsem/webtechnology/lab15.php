<!DOCTYPE html>
<html>
<head>
    <title>Form to DB</title>
</head>
<body>

<?php
$name = "";
$phone = "";
$gender = "";

if ($_POST) {
    $host = 'localhost';
    $dbname = 'college';
    $username = 'root';
    $password = 'letsgocitY@mysql47';

    try {
        $pdo = new PDO("mysql:host=$host;dbname=$dbname", $username, $password);
        $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

        $name = $_POST['text'];
        $phone = $_POST['select'];
        $gender = $_POST['radio'];

        $stmt = $pdo->prepare("INSERT INTO form_data (text_input, select_choice, radio_choice) VALUES (?, ?, ?)");
        $stmt->execute([$name, $phone, $gender]);

        echo "<p>✅ Data saved successfully!</p>";

        echo "<h3>Submitted Data:</h3>";
        echo "Name: " . htmlspecialchars($name) . "<br>";
        echo "Phone: " . htmlspecialchars($phone) . "<br>";
        echo "Gender: " . htmlspecialchars($gender) . "<br>";

    } catch (PDOException $e) {
        echo "<p>Error: " . $e->getMessage() . "</p>";
    }
}
?>

<form method="POST">
    <h2>User Information Form</h2>

    <label>Name:
        <input type="text" name="text" value="<?php echo htmlspecialchars($name); ?>" required>
    </label><br><br>

    <label>Which phone do you have:</label><br>
    <select name="select" required>
        <option value="option1" <?php if($phone == "option1") echo "selected"; ?>>Redmi</option>
        <option value="option2" <?php if($phone == "option2") echo "selected"; ?>>Samsung</option>
        <option value="option3" <?php if($phone == "option3") echo "selected"; ?>>iPhone</option>
        <option value="option4" <?php if($phone == "option4") echo "selected"; ?>>OnePlus</option>
    </select><br><br>

    <label>Gender:</label><br>
    <input type="radio" name="radio" value="male" 
        <?php if($gender == "male") echo "checked"; ?> required> Male

    <input type="radio" name="radio" value="female" 
        <?php if($gender == "female") echo "checked"; ?>> Female<br><br>

    <input type="submit" value="Submit">
</form>

</body>
</html>