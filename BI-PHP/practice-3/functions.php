<?php
	require_once( '../debug/debug.php' );
?>
<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<title>BI-PHP | Funkce</title>
</head>
<body>
	<?php
		/**
		 * Adds two numbers
		 *
		 * @param   integer   $s1   First number
		 * @param   integer   $s2   Number added to first number
		 *
		 * @return  integer
		 */
		function add( $s1, $s2 ) {
			return $s1 + $s2;
		}

		/**
		 * Increments it's argument by one
		 *
		 * @param    integer   &$p   Reference to number
		 *
		 * @return   void
		 */
		function modify( &$p ) {
			$p++;
		}

		/**
		 * Example of function with default values for parameters
		 *
		 * @param    integer   $x   First argument
		 * @param    integer   $y   Second (optional) argument
		 * @param    integer   $z   Third (optional) argument
		 *
		 * @return   [type]         [description]
		 */
		function implicit_vals( $x, $y = 0, $z = 0 ) {
			// some code
		}

		/**
		 * Sets global variables
		 *
		 * @return   void
		 */
		function set_global_var() {
			global $i = 5; // OR
			$GLOBALS['j'] = 10;
		}

		/**
		 * Function with static variable
		 *
		 * @return   void
		 */
		function static_var() {
			// local static variable
			static $p = 0;

			$p++;
		}

		$s = add( 3, 4 );
		modify( $s );

		implicit_vals( 3 );
		implicit_vals( 3, 4 );

		set_global_var();
	?>
</body>
</html>