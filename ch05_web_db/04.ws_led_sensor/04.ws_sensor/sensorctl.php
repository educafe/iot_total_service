<?php
	echo "start sensor processing..";
	echo "<br>";
	$sensor_val= $_GET['sensor'];
	echo $sensor_val;
	echo "<br>";

	$conn = mysqli_connect("localhost", "root", root);
	mysqli_select_db($conn, "mydb1");
	echo "connect ok!";
	echo "<br>";

	$sql = 'select * from dht11 order by created desc limit 1';
	$rst = mysqli_query($conn, $sql);
	$row = mysqli_fetch_assoc($rst);
	echo '<h2>'.$row['temperature_humidity'].'</h2>';
	echo $row['created'];
	echo "<br>";

	echo "end sensor processing..";

	//header('Location: http://raspberrypi.mshome.net/rp_ws/index.php?id=4');
?>
