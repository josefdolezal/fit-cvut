// #import( "chair.stl" );

/**
 * Chair
 * Model jednoduché židle s opěradlem složeným z příček.
 * Opěradlo je pro uznání nutné dělat forcykly!
 * @param rung_number Počet příček
 * @param x seat_width Šířka čtvercového sedáku (zároveň i délka)
 * @param x seat_thickness Tloušťka sedáku
 * @param feet_width Tloušťka nohou i příček
 * @param feet_length Délka nohou židle. Musí být počítáno od spodní strany sedáku!
 * @author Marek Žehra
 */
 
module chair(
rung_number=5,
seat_width=19,
seat_thickness=2,
feet_width=2,
feet_length=15
) {
  //= Seat
  cube( [ seat_width, seat_width, seat_thickness ] );
  
  //= Chair feets
  translate( [0,0, - feet_length] )
    cube( [feet_width, feet_width, feet_length] );
  translate( [seat_width - feet_width,0, - feet_length] )
    cube( [feet_width, feet_width, feet_length] );
  translate( [seat_width - feet_width,seat_width - feet_width, - feet_length] )
    cube( [feet_width, feet_width, feet_length] );
  translate( [0,seat_width - feet_width, - feet_length] )
    cube( [feet_width, feet_width, feet_length] );
  
  //= Rungs
  for( p=[0:2:(rung_number*2) -1] ) {
    translate( [0, 0, seat_thickness + (p+1)*feet_width] ) 
      cube( [seat_width, feet_width, feet_width ] );
  }
  
  // Top rung
  cube( [feet_width, feet_width, seat_thickness + ( 2 *rung_number * feet_width ) ] );

  translate([ seat_width - feet_width, 0, 0 ])
    cube( [feet_width, feet_width, seat_thickness + ( 2 *rung_number * feet_width ) ] );
   
}

chair();