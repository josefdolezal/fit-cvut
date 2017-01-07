// intersection() {
    // circle(25);
    // square(45, center=true);
// }

//linear_extrude(height=6, twist=360, slices=1000) //polygon([[0,0], [0,1], [1,0]]);

// sphere(5, $fn=100);

// $fn - pocet hran
// $fa - pocet hran relativne

module rec(cr=5, ch=50, bc=3, angle=60) {
    cylinder(r=cr, h=ch);
    translate([0,0,ch]) {
        sphere(r=cr)
        for(i=[0:bc-1]) {
            rotate([0,0,(360/bc)*i])
                rotate([angle,0,0])
                    cylinder(r=cr, h=ch);
        }
    }
}

rec();