<?php
	echo "start led processing..";
	echo "<br>";
	$buff= $_GET['led']."\n";
	$led_val= $_GET['led'];
	//echo $buff;
	echo $led_val;
	echo "<br>";

	for($i=0; $i<10; $i++) {
		$fname = "/var/www/html/rp_ws/ledstate";
		$fp = fopen($fname, "w");
		if($fp) break;
	}
	if($fp) {
		echo "open ok!!";
		echo "<br>";
		echo $led_val;
		echo "<br>";
		fwrite($fp, $led_val);
		fclose($fp);
	} else {
		echo "Could not open file($fname)..<br>";
	}
	echo "end led processing..";

	//header('Location: http://169.254.32.10/rp_ws/index.php?id=2');
?>
