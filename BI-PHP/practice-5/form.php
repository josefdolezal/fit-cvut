<?php
/**
 * File: form.php
 * Saves input from user to session
 */

// Otavira session
// Pri pouziti cookies musi byt session otevrena pred odeslanim hlavicek

ini_set( 'session.gc_maxlifetime', 4 * 60 * 60 );
session_start();

?>
<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<title>BI-PHP | Formulář</title>
</head>
<body>
	<h1>Zahájení session</h1>
	<form action="form.php" method="GET">
		<label>Jméno
			<input type="text" name="name">
		</label>
		<input type="submit" name="submit" value="Uložit">

		<a href="middle.php">Následující stránka &gt;</a>
	</form>
	
	<?php
		// Kontroluje odeslani formulare
		if( isset( $_GET['submit'] ) )
			// Uklada input do session
			$_SESSION['name'] = $_GET['name'];
	?>

</body>
</html>