<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<title>BI-PHP | Pokročilé Formuláře</title>
	<style>
		label { display: block; margin: 5px 0 7px; }
		input[type=text],
		input[type=submit],
		select { display: block; }
		fieldset { border: 0; padding: 0; margin-top: 10px; }
	</style>
</head>
<body>
	<?php
		include '../debug/debug.php';

		// formular uz byl odeslan
		$form_sent = isset( $_GET['submit'] );

		function selected( $element, $name, $attr = 'selected' ) {
			if( isset( $_GET[$element] ) && in_array( $name, $_GET[$element] ) )
				echo $attr . '="' . $$attr . '"';
		}

		if ( $form_sent ) {
			$name     = $_GET['name'];	
			$lastname = $_GET['lastname'];		
		}

		// if( $form_sent ) pre_dump( $_GET, TRUE );
	?>
		<form action="form-advanced.php">
			<fieldset>Zařízení
				<label>DVD
					<input type="checkbox" name="devices[]" value="dvd" <?php selected( 'devices', 'dvd', 'checked' ); ?>>
				</label>
				<label>Monitor
					<input type="checkbox" name="devices[]" value="lcd" <?php selected( 'devices', 'lcd', 'checked' ); ?>>
				</label>
				<label>Tiskárna
					<input type="checkbox" name="devices[]" value="printer" <?php selected( 'devices', 'printer', 'checked' ); ?>>
				</label>
			</fieldset>

			<fieldset>Velikost paměti
				<label>1 GB
					<input type="radio" name="ram" value="1">
				</label>
				<label>4 GB
					<input type="radio" name="ram" value="4">
				</label>
				<label>8 GB
					<input type="radio" name="ram" value="8">
				</label>
			</fieldset>
			
			<!-- Volba vice moznosti je pomoci atributu multiple="multiple" -->
			<select name="language[]" multiple="multiple">
				<!-- Vyber pomoci selected="selected" -->
				<option value="php" <?php selected( 'language', 'php' ); ?>>PHP</option>
				<option value="c" <?php selected( 'language', 'c' ); ?>>C</option>
				<option value="cpp" <?php selected( 'language', 'cpp' ); ?>>C++</option>
			</select>

			<select name="components">
				<option value="hdd">HDD</option>
				<option value="hdd">SSD</option>
			</select>

			<input type="submit" name="submit" value="Odeslat">
			<input type="image" name="awesome" src="assets/img/adventure-time.png">
			
		</form>

		<?php
			if( $_GET['awesome_x'] < 139 )
				echo 'Finn is awesome!';
			else if( $_GET['awesome_y'] > 71 )
				echo 'Jake rulez!';
		?>
</body>
</html>