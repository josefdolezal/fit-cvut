<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<title>BI-PHP | Syntaxe PHP</title>
	<link rel="stylesheet" href="assets/css/style.css">
</head>
<body>
	<div id="lecture">
		<article class="block">
			<header>
				<h1>Komentráře</h1>
			</header>
			<div class="content">
				<pre class="code">
					
				</pre>
				<pre class="output"></pre>
			</div>
		</article>
	</div>
	
	<?php
        // identifikatory zacinaji $
        $i = 1;
        $i = "abc";
        
        //echo - vypis dat do vystupu
        echo "Ahoj!<br>";
        
        $name = "Franta";
        echo "Jmenuje se $name<br>";
        echo "Jmenuje se " . $name . "<br>";
        
        $i = 2; $j = 3;
        echo "$i * $j<br>";
        echo "Soucin: ".($i * $j)."<br>";
        
        //retezce s apostrofy nevkladaji hodnoty promennych
        
        $cena = 2.5;
        printf("Cena = %5.2f", $cena);
        
        //test existence promennych - isset - existuje vraci 1, neexistuje nevraci nic
        echo "Je nastaveno: ==".isset($jmeno)."==<br>";
        echo "Je nastaveno: ==".isset($jmeno2)."==<br>";
        echo "Je nastaveno: ".(isset($jmeno2)?"ano":"ne")."<br>";
        
        //lze zrusit promennou pomoci unset
        unset($jmeno);
        echo "Je nastaveno: ".(isset($jmeno)?"ano":"ne")."<br>";
        
        $jmeno = "Venca";
        echo "Je prazdne: ".(empty($jmeno)?"ano":"ne")."<br>";
        
        echo (3 + "4")."<br>"; //automaticka konverze + secte
        
        $i = (int)"123";
        $i = (int)"123ABC";           
        echo"$i <br>";
        
        $i = (int)"AB1C" //0
        
        //definice konstanty
        //define("PI", 3.141592);
        #delka = 2 * PI * 10;
	?>
</body>
</html>