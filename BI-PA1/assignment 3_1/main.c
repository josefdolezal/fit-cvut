/* author: josef dolezal */
/* git: https://github.com/josefdolezal */

#ifndef __PROGTEST__
#include <stdio.h>
#include <assert.h>
#endif /* __PROGTEST__ */

int digitalClock ( int y1, int m1, int d1, int h1, int i1,
                  int y2, int m2, int d2, int h2, int i2, long long int * consumption );

int overeniDat(int y, int m, int d, int h, int i, int prestupny);
int pocetDni(int d, int m, int p, int od);
int pocetSegmentu(int c, int nuly);
int spotrebaZaDen(int h, int m, int od);
int prestupnyRok(int y);
int pocetDniVMesici(int m, int p);

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
    long long int consumption = 0;
    
    
    assert ( digitalClock ( 2014, 10, 10, 20, 0, 2014, 10, 11, 10, 0, &consumption )   == 1	&& consumption == 1262484LL );
    assert ( digitalClock ( 2014, 10,  1, 13, 15, 2014, 10,  1, 18, 45, &consumption ) == 1 && consumption == 510384LL );
    assert ( digitalClock ( 2014, 10,  1, 13, 15, 2014, 10,  2, 11, 20, &consumption ) == 1 && consumption == 2015964LL );
    assert ( digitalClock ( 2014,  1,  1, 13, 15, 2014, 10,  5, 11, 20, &consumption ) == 1 && consumption == 605329884LL );
    assert ( digitalClock ( 2012,  1,  1, 13, 15, 2012, 10,  5, 11, 20, &consumption ) == 1 && consumption == 607515804LL );
    assert ( digitalClock ( 1900,  1,  1, 13, 15, 1900, 10,  5, 11, 20, &consumption ) == 1 && consumption == 605329884LL );
    assert ( digitalClock ( 2014, 10,  1,  0,  0, 2014, 10,  1, 12,  0, &consumption ) == 1 && consumption == 1033464LL );
    assert ( digitalClock ( 2014, 10,  1,  0, 15, 2014, 10,  1,  0, 25, &consumption ) == 1 && consumption == 15804LL );
    assert ( digitalClock ( 2014, 10,  1, 12,  0, 2014, 10,  1, 12,  0, &consumption ) == 1 && consumption == 1704LL );
    assert ( digitalClock ( 2014, 10,  1, 12,  0, 2014, 10,  1, 12,  1, &consumption ) == 1 && consumption == 3168LL );
    assert ( digitalClock ( 2014, 11,  1, 12,  0, 2014, 10,  1, 12,  0, &consumption ) == 0 );
    assert ( digitalClock ( 2014, 10, 32, 12,  0, 2014, 11, 10, 12,  0, &consumption ) == 0 );
    assert ( digitalClock ( 2100,  2, 29, 12,  0, 2100,  2, 29, 12,  0, &consumption ) == 0 );
    assert ( digitalClock ( 2400,  2, 29, 12,  0, 2400,  2, 29, 12,  0, &consumption ) == 1 && consumption == 1704LL );
    /*digitalClock ( 1916, 10, 27, 13, 37, 1917, 1, 1, 23, 59, &consumption);
    printf("%lld\n", consumption);
    digitalClock ( 1916, 10, 27, 13, 37, 2002, 5, 27, 14, 58, &consumption ); */
    
    
    assert ( digitalClock ( 1852, 1, 1, 0, 0, 1852, 1, 6, 0, 0, &consumption )      == 1	&& consumption == 10931244LL);
    assert ( digitalClock ( 1916, 10, 27, 13, 37, 2002, 5, 27, 14, 58, &consumption ) == 1	&& consumption == 68327610828LL );
    assert ( digitalClock ( 2069, 2, 19, 5, 22, 2151, 8, 24, 19, 15, &consumption )   == 1	&& consumption==65873958336LL);
    assert ( digitalClock ( 1844, 1, 1, 0, 0, 1844, 2, 20, 0, 0, &consumption )       == 1	&& consumption==109297644LL);
    assert ( digitalClock ( 2023, 8, 1, 22, 35, 2194, 11, 11, 6, 29, &consumption )   == 1	&& consumption==136747478160LL);
    assert ( digitalClock ( 1976, 6, 17, 11, 44, 2049, 11, 25, 10, 43, &consumption ) == 1	&& consumption==58635032160LL);
    assert ( digitalClock ( 2047, 10, 17, 20, 18, 2195, 5, 6, 13, 36, &consumption )  == 1  && consumption == 117802972296LL );
    assert ( digitalClock ( 1938, 2, 18, 13, 16, 2108, 1, 19, 11, 37, &consumption )  == 1  && consumption==135660233268LL);
    assert ( digitalClock ( 2074, 2, 7, 2, 29, 2197, 3, 10, 11, 0, &consumption )     == 1	&& consumption==98270965548LL);
    assert ( digitalClock ( 1910, 4, 9, 21, 10, 1921, 11, 6, 21, 30, &consumption )   == 1	&& consumption==9244287084LL);
    assert ( digitalClock ( 2074, 4, 2, 10, 36, 2108, 2, 29, 12, 32, &consumption )   == 1	&& consumption==27072790908LL);
    assert ( digitalClock ( 2044, 1, 4, 2, 19, 2122, 3, 6, 19, 26, &consumption )     == 1  && consumption == 62409550092LL );
    assert ( digitalClock ( 2005, 4, 10, 0, 15, 2005, 4, 10, 0, 0, &consumption )     == 0 );
    return 0;
}
#endif /* __PROGTEST__ */

int digitalClock ( int y1, int m1, int d1, int h1, int i1,
                  int y2, int m2, int d2, int h2, int i2, long long int * consumption )
{
    int py1       = prestupnyRok(y1);
    int py2       = prestupnyRok(y2);
    int dny       = 0;
    int dnyr2     = 0;
    int i         = 0;
    int spCelyDen = 2185920;
    long long spotreba = 0;
    
    if(overeniDat(y1, m1, d1, h1, i1, py1) == 0 || overeniDat(y2, m2, d2, h2, i2, py2) == 0 ||y1 > y2
       || ( y1 == y2 && ((m1 > m2) || ((m1 == m2) && d1 > d2)
                         || ((m1 == m2) && (d1 == d2) && (h1 > h2))
                         || ((m1 == m2) && (d1 == d2) && (h1 == h2) && (i1 > i2))))) return 0;
    
    if (y1 < y2) {
        spotreba = spotrebaZaDen(h1, i1, 0); /* spotreba do pulnoci */
        dny = pocetDni(d1, m1, py1, 0); /* pocet dni do konce roku */
        y1++;
        
        while (y1 != y2) {
            py1 = prestupnyRok(y1);
            dny += (py1 == 1) ? 366 : 365;
            y1++;
        }
        
        dny += pocetDni(d2, m2, py2, 1); /* pocet dni od zacatku roku */
        
        spotreba += (long long) spotrebaZaDen(h2, i2, 1); /* spotreba od pulnoci */
        spotreba += (long long) dny * spCelyDen;
    }
    else {
        if (m1 == m2) {
            if (d1 == d2) {
                spotreba = (long long) -(spCelyDen - spotrebaZaDen(h1, i1, 0) - spotrebaZaDen(h2, i2, 1));
            }
            else {
                dny = d2 - d1 - 1;
                
                spotreba = (long long) dny * spCelyDen;
                spotreba += spotrebaZaDen(h1, i1, 0);
                spotreba += spotrebaZaDen(h2, i2, 1);
            }
        } else {
            for (i = 1, dny = d1; i < m1; i++) dny += pocetDniVMesici(i, py1);
            for (i = 1, dnyr2 = d2; i < m2; i++) dnyr2 += pocetDniVMesici(i, py2);
            dny = dnyr2 - dny - 1;
            
            spotreba = (long long) dny * spCelyDen;
            spotreba += spotrebaZaDen(h1, i1, 0);
            spotreba += spotrebaZaDen(h2, i2, 1);
        }
        
        
        
        /*for (i = 1, dny = d1; i < m1; i++)
            dny += pocetDniVMesici(i, py1);
        for (i = 1, dnyr2 = d2; i < m2; i++) dnyr2 += pocetDniVMesici(i, py2);
        
        spotreba = ((long long) (dnyr2 * spCelyDen) + spotrebaZaDen(h2, m2, 1))
                    - ((long long) (dny * spCelyDen) + spotrebaZaDen(h1, m1, 1));*/
        
        
    }
    *consumption = spotreba;
    return 1;
}

int overeniDat(int y, int m, int d, int h, int i, int prestupny) {
    if (y < 1600 || m < 1 || m > 12 || d < 1 || d > pocetDniVMesici(m, prestupny) || h < 0 || h > 23 || i < 0 || i > 59) return 0; /* obecne */
    
    return 1;
}

int pocetDni(int d, int m, int p, int od) {
    int i   = 0;
    int dny = 0;
    
    if (od == 1) {
        for (i = 1; i < m; i++) {
            dny += pocetDniVMesici(i, p);
        }
        dny += d-1;
    } else {
        dny += pocetDniVMesici(m, p) - d;
        
        for (i = m+1; i <= 12; i++) {
            dny += pocetDniVMesici(i, p);
        }
    }
    return dny;
}

int spotrebaZaDen(int h, int m, int od) {
    int spotrebaZaMin  = 564;
    int min            = 0, hod = 0;
    int spotreba       = 0;
    
    if (od == 1) {
        for (hod = 0; hod < h; hod++) {
            for (min = 0; min < 60; min++) {
                spotreba += pocetSegmentu(hod, 0)*60 + pocetSegmentu(min, 1)*60 + spotrebaZaMin;
            }
        }
        
        for (min = 0; min <= m; min++) {
            spotreba += pocetSegmentu(h, 0)*60 + pocetSegmentu(min, 1)*60 + spotrebaZaMin;
        }
    } else {
        for (min = m; min < 60; min++) {
            spotreba += pocetSegmentu(h, 0)*60 + pocetSegmentu(min, 1)*60 + spotrebaZaMin;
        }
        
        for (hod = h+1; hod < 24; hod++) {
            for (min = 0; min < 60; min++) {
                spotreba += pocetSegmentu(hod, 0)*60 + pocetSegmentu(min, 1)*60 + spotrebaZaMin;
            }
        }
    }
    
    return spotreba;
}

int pocetSegmentu(int c, int nuly) {
    int segmenty[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
    int pocet      = 0;
    
    if(nuly == 1 || c > 9) {
        pocet = segmenty[c/10];
        pocet += segmenty[c%10];
    }
    else pocet = segmenty[c];
    
    
    return pocet;
}

int prestupnyRok(int y) {
    if (y<1600)
        return 0;
    if (y%4==0 && y%4000!=0 && (y%100!=0 || y%400==0)) return 1;
    
    return 0;
}

int pocetDniVMesici(int m, int p) {
    switch (m) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
            break;
        case 4: case 6: case 9: case 11:
            return 30;
            break;
        case 2:
            return p == 0 ? 28 : 29;
            break;
    }
    
    return 0;
}

































