<?php
// Get the QUERY_STRING value
$queryString = isset($_SERVER['QUERY_STRING']) ? $_SERVER['QUERY_STRING'] : '';

// Get the REMOTE_ADDR value
$remoteAddr = isset($_SERVER['REMOTE_ADDR']) ? $_SERVER['REMOTE_ADDR'] : '';

// Get the REQUEST_METHOD value
$requestMethod = isset($_SERVER['REQUEST_METHOD']) ? $_SERVER['REQUEST_METHOD'] : '';

echo "QUERY_STRING: " . $queryString . "<br>";
echo "REMOTE_ADDR: " . $remoteAddr . "<br>";
echo "REQUEST_METHOD: " . $requestMethod . "<br>";
?>

