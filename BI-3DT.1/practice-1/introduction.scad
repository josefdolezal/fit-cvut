//= Objekty s % jsou pouze v nahledu
//= Objekty s # pouzivaji normalne
//= Pri definic promenne na vice mistech plati jeji posledni definice


//= Vykresli kvadr 25x10x5 vycentrovanou na vsech osach
// cube([25,10,5], center=true);

//= Koule o polomeru vycentrovana na vsech osach
// sphere(5);

//= Vykresluje kuzel (spodni polomer, vrchni polomer, vyska)
// cylinder( r1=13, r2=0, h=20 );

//= Kostka o hrane 150, vycentrovana
// cube( 150, center=true);

//= Posunuje kouli po ose x o 200 jednotek
// translate( [-200, 0, 0] )
    // sphere( 100 );

//= Zrcadleni podle osy y
// mirror([0,1,0])
    //= Zmena rozmeru (na vsech osach na max 12 jednotek, na osach y a z proporcialne)
    // resize([12,12,12], auto=[0,1,1])
      //= Rotace vuci ose x
      // rotate([45,0,0])
        //= Rotace (45 stupnu, na ose z) - alternativni zapis
        // rotate( 45, [0,0,1])
          //= Skalovani vzhledem k osam, alternativne: scale( 0.5 )
          // scale( [1,1,2] )
            //= Koule o polomeru 100 jednotek
            // sphere( 100 );

//= Sjednoceni vice objektu v jeden
//= alternativne difference (prvni - druhy) nebo intersection (prunik)              
union() {
  // cube(150, center=true);
  // sphere( 100 );
}

//= Cyklus pro prvky {5, 4, 8}
for( i=[5, 4, 8]) {
  echo (i);
}

//= Cyklus od 5 do 8 (vcetne)
for( i=[5:8]) {
  echo (i);
}

//= Cyklus od 5 do 8 vcetne s krokem 0.5
for( i=[5:0.5:8]) {
  echo (i);
}

//= Definovani noveho modulu s 2 parametry
module sisojd( size = 12, amount = 4 ) {
  intersection_for(n = [1 : amount] ) {
    rotate([0,0,n*(360/amount)]) translate([size/4, 0,0])
      sphere(d=size);
  }
}

module mirror_and_keep(v=[1,0,0]) {
  //= Funkce zrcadli objekt na ktery je aplikovana
  mirror(v) child();
  
  //= Vykresli znovu objekt na ktery je aplikovana (bez transformaci vyse)
  child();
}

mirror_and_keep() cube(50);

sisojd();