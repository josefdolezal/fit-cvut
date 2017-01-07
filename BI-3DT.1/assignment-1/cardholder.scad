module card_block(
  size=[0, 0, 0],
  radius=1,
  height=1
 ) {
  linear_extrude( height=height ) {
    if( radius > 0 ) {
      hull() {
        for( i=[0:1], j=[0:1] ) {
          translate( [i*size[1], j*size[2], 0] )
            circle( r=radius );
        }
      }
    // Bleh :-(
    } else {
      square( size=[size[1], size[2]] );
    }
  }
}

module cardholder(
  size=[85, 54, 1],
  thickness=3,
  spacing=1,
  cards=4,
  delta=25,
  visibility=0.3
 ) {
  // Upravit deltu a dodelat rotate, vymyslet prirazeni a rozdelit do modulu
  if( len(size) > 1 && size[0] > 0 && size[1] > 0 && cards > 0 ) {
    // Osetreni vstupu
    size       = len(size) == 2 ? [size[0], size[1], 0] : size;
    thickness  = thickness < 0 ? 0 : thickness;
    spacing    = spacing < 0 ? 0 : spacing;
    visibility = visibility > 1 ? 1 : ( visibility < 0 ? 0 : visibility );

    // Otoceni kolem Y pro delta < 0
    rotation = delta < 0 ? 180 : 0;
    delta    = delta < 0 ? -delta : delta;

    // Vyska vyrezu
    notch_height       = (1-visibility) * size[0] + spacing;
    // Vyska jednoho slotu na kartu
    compartment_height = notch_height + thickness;
    // Hloubka slotu
    compartment_deep   = 2*thickness + 2*spacing + size[2];
    // Sirka zdi (po ose Y)
    wall_thickness     = size[2] + thickness + 2*spacing;
    // Posun slotu po ose x
    shift_x            = spacing + thickness + size[1]/2;
    // Posun slotu po ose y
    shift_y            = (cards * size[2] + (cards + 1) * thickness + 2*cards * spacing)/2;

    rotate([0, 0, rotation]) {
      translate([thickness + spacing - shift_x, thickness + spacing - shift_y, 0])
        difference() {
          for( k=[0:cards-1] ) {
            translate( [0, k * (compartment_deep - thickness), 0] )
              // Vnejsi rozmer
              card_block( height=compartment_height + k*delta, size=size, radius=thickness + spacing);

            // Zarovnani bocnic
            if(k>0)
              translate([ -spacing - thickness, (k-1)*wall_thickness, 0]) cube([ 2*(thickness + spacing) + size[1], wall_thickness, compartment_height + (k-1)*delta]);
          }

          // Vyrez pro kartu
          for( k=[0:cards-1] )
            translate( [0, k * (compartment_deep - thickness), thickness + k*delta] )
              card_block( height=notch_height, size=size, radius=spacing );
        }
    }
  }
}