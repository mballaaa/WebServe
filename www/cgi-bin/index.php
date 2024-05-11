<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>CGI POST Request Test</title>
</head>
<body>
    <h2>CGI POST Request Test</h2>
    <form action="" method="post">
        <label for="param1">Parameter 1:</label><br>
        <input type="text" id="param1" name="param1"><br>
        <label for="param2">Parameter 2:</label><br>
        <input type="text" id="param2" name="param2"><br>
        <input type="submit" value="Submit">
    </form>
</body>
</html>

 <?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {

    // Retrieve POST data
    $param1 = $_POST['param1'];
    $param2 = $_POST['param2'];

    // Display received data
    echo "Parameter 1: " . $param1 . "<br>";
    echo "Parameter 2: " . $param2 . "<br>";
}
?> 