<?php 
/**
 * File: end.php
 * Last page displayed to user
 */

session_start();

?>
<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<title>BI-PHP | Formulář (koncová stránka)</title>
</head>
<body>
	<h1>Poslední stránka</h1>
	
	<p>
		<?php
			if( isset( $_SESSION['name'] ) ) {
				echo 'Jméno: ' . $_SESSION['name'] . '<br>' . 
				     'Session ID: ' . session_id();
			}
			else
				echo 'Jméno není nastaveno';
		?>
	</p>

	<a href="middle.php">&lt; Předchozí stránka</a>
</body>
</html>