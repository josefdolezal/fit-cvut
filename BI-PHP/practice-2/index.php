<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<title>BI-PHP |</title>
</head>
<body>
	<?php 
		function br() { echo "<br>"; }

		$name = "John";

		echo $name; br();

		// gettype vraci typ promenne
		echo gettype( $name );

		$e = FALSE || TRUE; // $e = ( FALSE || TRUE );
		$e = FALSE or TRUE; // ( $e = FALSE ) || TRUE; 
	?>
</body>
</html>