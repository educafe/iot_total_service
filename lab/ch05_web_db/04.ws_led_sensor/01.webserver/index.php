<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8" />
	<title>Raspberry Web Server</title>
	<link rel="stylesheet" type="text/css" href="http://raspberrypi.mshome.net/rp_ws/ws_style.css">
</head>
<body>
	<header>
		<img src="https://i.vimeocdn.com/portrait/10644740_120x120.jpg" alt="rp">
		<h1><a href="http://raspberrypi.mshome.net/rp_ws/index.php?id=1">RaspberryPi Web Control</a></h1>
	</header>
	<nav>
		<ol>
		<?php
			echo file_get_contents("list.txt");
		?>
		</ol>
	</nav>
	<article>
	<?php
		if( empty($_GET['id'])==false ) {
			echo file_get_contents($_GET['id'].".txt");
		} else {
			echo file_get_contents("1.txt");
		}
	?>
	</article>
</body>
</html>
