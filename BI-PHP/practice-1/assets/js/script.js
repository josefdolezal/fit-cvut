var s1, s2, soucet;

s1 = document.getElementById( 'txtS1' );
s2 = document.getElementById( 'txtS2' );
soucet = document.getElementById( 'txtSoucet' );

function secti () {
	soucet.value = parseFloat( s1.value ) + parseFloat( s2.value );
}