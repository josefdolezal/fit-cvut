<?php
/**
 * Dumps information about a variable (var_dump wrapper)
 *
 * @param    mixed     $var   Variable to be dumped
 * @param    boolean   $die   Whether php should end execution
 *
 * @return   void
 */
function pre_dump( $var, $die = FALSE ) {
	echo '<pre>';
		var_dump( $var );
	echo '</pre>';

	if( $die ) die();
}

/**
 * Prints human-readable information about a variable (print_r wrapper)
 *
 * @param    mixed     $array   Variable to be printed
 * @param    boolean   $die     Whether php eshoud end execution
 *
 * @return   void
 */
function pre_arr( $array, $die = FALSE ) {
	echo '<pre>';
		print_r( $array );
	echo '</pre>';

	if( $die ) die();
}

?>