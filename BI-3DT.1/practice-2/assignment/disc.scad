//#import( "disc.stl" );

/**
 * Disc
 * Modul parametrického disku k robotovi. Jedná se o kolo s gumovou pneumatikou o kruhovém průřezu.
 * @param radius Poloměr disku
 * @param height Výška disku
 * @param r_hole Poloměr díry uprostřed kola
 * @param reduce_offset Odsazení odlehčujících děr od stran kola
 * @param reduce_num Počet odlehčujících děr
 * @author Marek Žehra
 */
 
module wheel (
  radius=50,
  height=10,
  r_hole=2,
  reduce_offset=5,
  reduce_num=2
) {
    difference() {
        difference() {
            cylinder(r=radius, h=height, center=true);
            cylinder(r=r_hole, h=height,center=true);
            rotate_extrude() {
            translate([radius, 0, 0]) circle(d=height);
            }
        }
        for(i=[0:reduce_num-1]) {
            rotate([0,0,360/max(3,reduce_num)*i])
        translate([radius-(radius/3)-reduce_offset,0,0]) cylinder( d=(radius/2.5)/max(3,reduce_num)*5, h=height, center=true );
        }
    }
}

wheel();