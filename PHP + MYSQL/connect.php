<html>
<body>

<?php

$dbname = '000'; // replace with database name
$dbuser = '000';  // replace with db user
$dbpass = 'password';  // replace with password
$dbhost = 'localhost';

$connect = @mysqli_connect($dbhost,$dbuser,$dbpass,$dbname);

if(!$connect){
	echo "Error: " . mysqli_connect_error();
	exit();
}

echo "Connection Success!<br><br>";

$value = $_GET["value"];


$query = "INSERT INTO iot_project (value) VALUES ('$value')";
$result = mysqli_query($connect,$query);

echo "Insertion Success!<br>";

?>
</body>
</html>
