<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<title>BI-PHP | Cykly</title>
</head>
<body>
	<?php 
		for( $i = 0; $i < 10; $i++ ) {
			break;
			// cislo urcuje z kolika cyklu se vyskoci
			// break 3;
		}

		/**
		 * Pole
		 */
		$arr  = array( 't1', 't2', 't3' ); // implicitni indexy
		$arr2 = $arr;
		$arr2[0] = 'test'; // pole nejsou referencni typy

		var_dump( $arr );
		var_dump( $arr2 );

		foreach ( $arr as $val )
			$val = $val . '_x'; // nemeni puvodni hodnoty
	
		foreach ( $arr as &$val )
			$val = $val . '_x'; // meni puvodni hodnoty

		include 'file.php';
		// @include potlacuje warningy a chyby

		require 'file.php'; // pri chybe padne php

		include_once 'file.php'; // vlozi linkovany soubor pouze jednou
		require_once 'file.php';
	?>
</body>
</html>