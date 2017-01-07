<?php 
/**
 * File: file.php
 * Works with local files
 */

/**
 * Represents <br> html tag
 * 	
 * @return   string   Html tag
 */
function br() {
	return '<br>';
}

?>
<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<title>BI-PHP | Práce se soubory</title>
</head>
<body>
	<h1>Soubory</h1>

	<?php
		// Otevreni souboru ( r - read, w - write, a - append )
		// @ potlacuje chybovy vystup
		@$file = fopen( 'file.txt', 'r' );

		if( ! $file ) die( 'Soubor se nepodařilo otevřít.' );

		// Feof - File_ End Of File
		while( ! feof( $file ) ) {
			// Nacte 1 radek souboru
			$line = fgets( $file );

			echo $line . br();
		}

		// Uzavreni souboru
		fclose( $file );

		// Otevreni souboru pro psani (prepise existujici soubory)
		@$file = fopen( 'output.txt', 'w' );

		if( ! $file ) die( 'Soubor se nepodařilo otevřít.' );

		for( $i = 0; $i < 10; $i++ )
			// Zapisuje retezec na konec souboru
			// Alternativne fce fwrite
			fputs( $file, 'Radek: ' . $i . '\r\n' );

		fclose( $file );
	?>
	<h2>Další funkce pro práci se soubory</h2>
	<table>
		<tr>
			<td>fopen</td>
			<td>Otevírá soubor v daném módu (r, w, a)</td>
		</tr>
		<tr>
			<td>feof</td>
			<td>Označuje konec souboru</td>
		</tr>
		<tr>
			<td>fgets</td>
			<td>Čte soubor po řádku</td>
		</tr>
		<tr>
			<td>fputs/fwrite</td>
			<td>Vypisuje string do souboru</td>
		</tr>
		<tr>
			<td>fread</td>
			<td>Čte binární soubory</td>
		</tr>
		<tr>
			<td>freadfile</td>
			<td>Vypíše obsah souboru do výstupního streamu</td>
		</tr>
		<tr>
			<td>fscanf</td>
			<td>Formátované čtení</td>
		</tr>
		<tr>
			<td>fclose</td>
			<td>Uzavírá soubor</td>
		</tr>
		<tr>
			<td>file</td>
			<td>Načte soubor do pole po řádcích</td>
		</tr>
		<tr>
			<td>file_get_contents</td>
			<td>Načte soubor do stringu</td>
		</tr>
		<tr>
			<td>fgetcsv</td>
			<td>Načte sobor ve formátu csv</td>
		</tr>
		<tr>
			<td>fgetss</td>
			<td>Odstraní html tagy</td>
		</tr>
	</table>

	<h2>Práce s ukazatelem pozice v souboru</h2>
	<table>
		<tr>
			<td>fseek</td>
			<td>Nastavení pozice kurzoru</td>
		</tr>
		<tr>
			<td>ftell</td>
			<td>Zjištění pozice kurzoru</td>
		</tr>
		<tr>
			<td>frewind</td>
			<td>Nastaví ukazatel na začátek souboru</td>
		</tr>
	</table>

	<h2>Práce s názvy souborů</h2>
<pre>
	$path = '/home/user/file.txt';
</pre>
	<table>
		<tr>
			<td>dirname( $path )</td>
			<td>Název adresáře, který obsahuje daný soubor</td>
		</tr>
		<tr>
			<td>basename( $path )</td>
			<td>Ořízne na vlastní název souboru</td>
		</tr>
		<tr>
			<td>realpath( $path )</td>
			<td>Získání absolutní cesty</td>
		</tr>
	</table>

	<h2>Práce se soubory</h2>
	<table>
		<tr>
			<td>unlink</td>
			<td>Odstraní soubor</td>
		</tr>
		<tr>
			<td>rename( <i>old</i>, <i>new</i> )</td>
			<td>Přejmenování souboru</td>
		</tr>
	</table>

	<h2>Práce s adresáři</h2>
	<table>
		<tr>
			<td>mkdir</td>
			<td>Vytvoření adresáře</td>
		</tr>
		<tr>
			<td>rmdir</td>
			<td>Odstranění prázdného adresáře</td>
		</tr>
		<tr>
			<td>is_dir</td>
			<td>Je daná cesta adresář?</td>
		</tr>
		<tr>
			<td>chdir</td>
			<td>Nastavení aktulálního adresáře</td>
		</tr>
		<tr>
			<td>getcwd</td>
			<td>Vypíše pracovní adresář</td>
		</tr>
		<tr>
			<td>opendir</td>
			<td>Otevře adresář</td>
		</tr>
		<tr>
			<td>readdir</td>
			<td>Čte adresář po souborech</td>
		</tr>
		<tr>
			<td>closedir</td>
			<td>Uzavře adresář</td>
		</tr>
		<tr>
			<td>Př</td>
			<td>
<pre>
	$dir = opendir( '.' );

	while( $file = readdir( $dir ) )
		echo $file;
</pre>
			</td>
		</tr>
	</table>
</body>
</html>