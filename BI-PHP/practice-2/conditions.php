<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<title>BI-PHP | Podmínky</title>
</head>
<body>
	<?php 
		$pohlavi = 'muz';

		if( $pohlavi == 'muz' ) : ?>
			<p>Dobrý den pane</p>
		<?php else : ?>
			<p>Dobrý den paní</p>
		<?php endif;
	?>
</body>
</html>