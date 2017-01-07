<?php session_start(); ?>
<!DOCTYPE html>
<html>
<head>
	<title></title>
</head>
<body><?php var_dump( $_GET ); ?>
	<form action="" method="get">
		<input type="checkbox" name="test[]" value="ds">
		<input type="checkbox" name="test[]" value="aaaaa">

		<input type="submit">
	</form>
</body>
</html>