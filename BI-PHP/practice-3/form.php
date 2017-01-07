<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<title>BI-PHP | Formuláře</title>
	<style>
		label { display: block; margin: 5px 0 7px; }
		input[type=text] { display: block; }
		fieldset { border: 0; padding: 0; }
	</style>
</head>
<body>
	<?php
		// formular uz byl odeslan
		$form_sent = isset( $_GET['submit'] );

		if ( $form_sent ) {
			$name     = $_GET['name'];	
			$lastname = $_GET['lastname'];		
		}	
	?>
	
	<?php if( ! $form_sent ): ?>

		<form action="form.php">
			<label for="name">Jméno
				<input type="text" id="name" name="name">
			</label>

			<label for="lastname">Příjmení
				<input type="text" id="lastname" name="lastname">
			</label>
		
			<fieldset>
				<label>Muž
					<input type="radio" name="gender" value="man">
				</label>
				<label>Žena
					<input type="radio" name="gender" value="woman">
				</label>
			</fieldset>

			<input name="submit" type="submit" value="Odeslat formulář">
		</form>

	<?php else: ?>
		<div id="content">
			<p>Jméno: <?php echo $name; ?></p>
			<p>Příjmení: <?php echo $lastname; ?></p>
		</div>
	<?php endif; ?>
</body>
</html>