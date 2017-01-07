<?php
	require_once( '../debug/debug.php' );
?>
<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<title>BI-PHP | Pole</title>
</head>
<body>
	<?php
		// Definice pole
		$arr = array( 1, 2, 3 );

		// Doplnuje pole na *5* prvku hodnotou *0*
		// Funkce vraci nove pole
		$new_arr = array_pad( $arr, 5, 0 );

		// Vytvori pole velikosti *10* a vyplni ho hvezdickami
		$new_arr = array_fill( 0, 10, "*" )

		$names = array( 'Jan', 'Tom', 'Mike' );
		pre_dump( in_array( 'Jan', $names ) );

		// Vraci index nalezeneho prvku nebo FALSE
		pre_dump( array_search( 'Tom', $names ) );

		// Vraci pole klicu
		pre_dump( array_keys( $names ) );

		// Vypise prvek na kterem je kurzor v poli
		// Pohyb v poli pomoci next, prev, reset, end
		current( $names );

		// Pocet prvku v poli
		count( $names );

		// Prirazuje klice k poli bez klicu
		$new_arr = array_combine( array( 'A', 'B', 'C' ), $names );

		$mixed_indexes = array( 'color' => 'red', 10, 40 );
		pre_dump( $mixed_indexes );

		$mixed_indexes_2 = array( 'z', 'y', 'color' => 'green', 'shape' => 'rectangle' );
		pre_dump( $mixed_indexes_2 );

		// Sklada dve pole do jednoho
		// Duplicitni indexy si nechaji hodnotu prvniho pole
		pre_dump( array_merge( $mixed_indexes, $mixed_indexes_2 ) );

		// Tridi pole - upravuje aktualni pole
		sort( $names );

		// Pouziva pri trideni uzivatelske funkce
		usort( $names, function( $str1, $str2 ) {
			return strcmp( $str1, $str2 );
		} );
	?>
</body>
</html>