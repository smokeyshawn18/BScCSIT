<?php
echo "PHP version: " . PHP_VERSION . "\n";
echo "PDO drivers: " . implode(', ', PDO::getAvailableDrivers()) . "\n";
if (extension_loaded('pdo_mysql')) {
    echo "pdo_mysql: LOADED\n";
} else {
    echo "pdo_mysql: MISSING\n";
}
phpinfo();
?>