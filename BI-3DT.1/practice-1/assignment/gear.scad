/**
 * Parametric gear
 * Model jednoduchého ozubeného kola
 * Zuby je pro uznání nutné dělat forcykly!
 * @param gear_rad Poloměr ozubeného kola
 * @param gear_thickness Tloušťka kola
 * @param center_hole_width Šířka čtverce uprostřed kola
 * @param tooth_width Šířka jednoho zubu
 * @param tooth_prot Výstup zubu (jak moc je vystouplý zub)
 * @param tooth_count Počet zubů na ozubeném kolu po obvodu
 * @author Marek Žehra
 */

module gear(
  gear_rad=50,
  gear_thickness=10,
  center_hole_width=10,
  tooth_width=5,
  tooth_prot=5,
  tooth_count=20
) {
  //= Kolo s prostrednim vyrezem
  difference() {
    cylinder( r=gear_rad, h=gear_thickness, center=true ); 
    cube( size=[center_hole_width, center_hole_width, gear_thickness], center=true );
  }
  
  //= Cyklus pro zuby
  for( i=[0:(tooth_count-1)] ) {
    rotate( [0,0, i*360/tooth_count] ) translate( [gear_rad, 0, 0 ] ) cube( [2*tooth_prot, tooth_width, gear_thickness], center=true );
  }
}

gear();