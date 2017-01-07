// #import( "helix.stl" );

/**
 * Helix
 * @param d Vzdálenost středů šroubovic měřená na vodorovné rovině
 * @param o Poloměr šroubovice měřený na vodorovné rovině
 * @param h Výška šroubovice bez podstav
 * @param s Stupně rotace na milimetr výšky (znaménko určuje směr otáčení)
 * @param db Průměr podstav
 * @param hb Výška podstav
 * Model byl vyexportován s nastavením $fn=50 a výškové rozlišení je 50 µm
 * @author Miro Hrončok
 */
module helix(d=10,o=1,h=50,s=18,db=13,hb=1) {
  // spodni podstava
  cylinder(d=db, hb);
    
  // horni podstava
  translate([0,0,h+hb]) cylinder(d=db, hb);
  
  translate([0,0,hb])
    linear_extrude(height=h, twist=s*h, slices=50*h*20) {
      translate([d/2,0,0]) circle(r=o);
      translate([-d/2,0,0]) circle(r=o);
  }
  
}

helix();