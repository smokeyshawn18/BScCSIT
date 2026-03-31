<!DOCTYPE html>
<html>
<head>
    <title>PHP Lab Programs</title>
    <!-- <style>
        body { font-family: Arial; margin: 40px; background: #f4f4f4; }
        .container { max-width: 700px; margin: auto; background: white; padding: 30px; border-radius: 10px; box-shadow: 0 4px 10px rgba(0,0,0,0.1); }
        h2 { color: #333; border-bottom: 2px solid #007bff; padding-bottom: 10px; }
        .program { margin: 25px 0; padding: 20px; background: #f8f9fa; border-radius: 8px; border-left: 4px solid #007bff; }
        input, button { padding: 10px; margin: 5px; border-radius: 5px; border: 1px solid #ddd; }
        button { background: #007bff; color: white; cursor: pointer; }
        button:hover { background: #0056b3; }
        .result { background: #d4edda; padding: 15px; margin-top: 10px; border-radius: 5px; font-weight: bold; }
    </style> -->
</head>
<body>
    <div class="container">
        <h1>🔥 PHP Programming Lab Demo</h1>
        
        <!-- 1. Sum of Digits -->
        <div class="program">
            <h2>1. Sum of Individual Digits</h2>
            Enter Number: <input type="number" id="digitsNum" placeholder="e.g. 12345">
            <button onclick="sumDigits()">Calculate Sum</button>
            <div id="digitsResult"></div>
        </div>
        
        <!-- 2. Palindrome Check -->
        <div class="program">
            <h2>2. Palindrome Check</h2>
            Enter Number: <input type="number" id="palindromeNum" placeholder="e.g. 121">
            <button onclick="checkPalindrome()">Check</button>
            <div id="palindromeResult"></div>
        </div>
        
        <!-- 3. Date Time Delay -->
        <div class="program">
            <h2>3. Current Date, Time & Delay</h2>
            <button onclick="showDateTime()">Show Date/Time</button>
            <div id="datetimeResult"></div>
        </div>
    </div>

    <?php
    // PHP Functions
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
    ?>

    <script>
        // JavaScript calls to PHP via AJAX simulation (for demo)
        function sumDigits() {
            const num = document.getElementById('digitsNum').value;
            if (!num) {
                document.getElementById('digitsResult').innerHTML = '<span style="color:red;">Enter number!</span>';
                return;
            }
            
            // Pure JS implementation (same logic as PHP)
            let sum = 0, n = parseInt(num);
            while (n > 0) {
                sum += n % 10;
                n = Math.floor(n / 10);
            }
            document.getElementById('digitsResult').innerHTML = 
                `<div class="result">Sum of digits of ${num} = ${sum}</div>`;
        }
        
        function checkPalindrome() {
            const num = document.getElementById('palindromeNum').value;
            if (!num) {
                document.getElementById('palindromeResult').innerHTML = '<span style="color:red;">Enter number!</span>';
                return;
            }
            
            // Pure JS implementation (same logic as PHP)
            const original = parseInt(num);
            let reverse = 0, n = original;
            while (n > 0) {
                reverse = reverse * 10 + n % 10;
                n = Math.floor(n / 10);
            }
            
            const result = original === reverse ? 'PALINDROME' : 'NOT PALINDROME';
            document.getElementById('palindromeResult').innerHTML = 
                `<div class="result">${num} is ${result}</div>`;
        }
        
        function showDateTime() {
            // PHP Date/Time
            const phpDate = '<?php echo date("Y-m-d H:i:s"); ?>';
            const phpFormatted = '<?php echo date("d M Y, l"); ?>';
            
            // JavaScript Date/Time + Delay demo
            const now = new Date();
            const jsDate = now.toLocaleString();
            
            document.getElementById('datetimeResult').innerHTML = `
                <div class="result">
                    <strong>PHP Date:</strong> ${phpDate}<br>
                    <strong>PHP Formatted:</strong> ${phpFormatted}<br>
                    <strong>JavaScript:</strong> ${jsDate}<br>
                    <em>Demo shows PHP server time vs client time</em>
                </div>
            `;
        }
    </script>
</body>
</html>