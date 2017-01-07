module thorn(
  data = []
) {
  /* Spike height */
  top_height = pow( data[1], 1/3 );
  /* Body height */
  body_height = data[1] - top_height;

  /* Crystal body */
  cylinder( r1 = data[2]/3, r2 = data[2], h = body_height, $fn = data[3] );
  /* Crystal top */
  translate( [0,0, body_height] )
    cylinder( r1 = data[2], r2 = 0, h = top_height, $fn = data[3] );
}

module crystal(
  thorns=[]
) {
  for( thorn = thorns ) {
    /* Rotation axes */
    axes = thorn[0];

    rotate( [axes[0], axes[1], axes[2]] )
      thorn( thorn );
  }
}

module random_crystal(
  nthorns = 350,
  rot = [-90,100],
  height = [20,40],
  circumr = [2,4.5],
  seg = [3,10]
) {
  for( i = [ 0 : nthorns - 1 ] ) {
    r_rot     = rands( rot[0], rot[1], 3 );
    r_height  = rands( height[0], height[1], 1 )[0];
    r_circumr = rands( circumr[0], circumr[1], 1 )[0];
    r_seg     = round( rands( seg[0], seg[1], 1)[0] );
    options   = [ r_rot, r_height, r_circumr, r_seg ];

    rotate( r_rot )
      thorn( options );
  }
}
