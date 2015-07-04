# Nařízení EK 244/2009
## Zadání
Úkolem je realizovat funkci (ne celý program, pouze funkci), která bude počítat spotřebu el. energie v digitálních hodinách.

Evropská unie správně chápe, že energií je potřeba šetřit, ať to stojí, co to stojí. Zatím se to týká žárovek, výbojek, vysavačů, ale dá se očekávat, že tento progresivní trend zasáhne i další energeticky náročná zařízení. Abychom náročné práci euroúředníků pomohli, poskytneme jim v této úloze analytický nástroj, kterým půjde v dlouhodobém horizontu zkoumat energetickou náročnost digitálních hodin s LED displejem.

Největší spotřebu na takových hodinách má vlastní LED displej. Pro jednoduchost předpokládejme, že displej zobrazuje čas na sedmisegmentovém displeji, kde každý segment má odběr právě 1W (watt). Displej zobrazuje čas ve formátu hodiny minuty sekundy, hodiny jsou zobrazované v rozsahu 0 až 23 bez zbytečných úvodních nul, minuty a vteřiny jsou pak zobrazené jako dvojmístná čísla. Cifry na sedmisegmentovém displeji mají standardní tvar, tedy:

```
 -         -    -         -    -    -    -    -                                                                     
| |    |    |    |  | |  |    |      |  | |  | |                                                                       
           -    -    -    -    -         -    -                                                                     
| |    |  |      |    |    |  | |    |  | |    |                                                                       
 -         -    -         -    -         -    -  
```

Naše funkce dostane parametrem dva časové údaje - počátek a konec časového intervalu. Počátek i konec je dán rokem, měsícem, dnem, hodinou a minutou. Funkce spočítá, kolik energie hodiny za tuto dobu spotřebují.

Požadovaná funkce má rozhraní:

```c
int digitalClock ( int y1, int m1, int d1, int h1, int i1,
                   int y2, int m2, int d2, int h2, int i2, 
                   long long int * consumption );
```

* y1, m1, d1, h1, i1
  * jsou vstupní parametry, které představují rok, měsíc, den, hodinu a minutu počátku intervalu,

* y2, m2, d2, h2, i2
  * jsou vstupní parametry, které představují rok, měsíc, den, hodinu a minutu konce intervalu,

* consumption
  * je výstupní parametr, do kterého funkce uloží vypočtenou spotřebu v zadaném období. Spotřebu vracejte v joulech (J). Parametr bude funkce nastavovat pouze pokud jsou zadané správné vstupní parametry. Pokud jsou zadané nesprávné vstupy, nelze hodnotu určit. V takovém případě funkce signalizuje neúspěch a ponechá tento výstupní parametr beze změn. Vypočtená hodnota zahrnuje i spotřebu v první a poslední minutě zadaného intervalu. Tedy např. pro ukázkové zadání:

```c
assert ( digitalClock ( 2400,  2, 29, 12,  0,
                      2400,  2, 29, 12,  0, &consumption ) == 1
         && consumption == 1704LL );
```
uvažujeme celkovou spotřebu od rozsvícení časového údaje 12:00:00 po zhasnutí údaje 12:00:59.

* návratová hodnota funkce

  * bude nastavena na hodnotu 1 pro úspěch (správné vstupní parametry) nebo 0 pro neúspěch (nesprávné vstupní parametry).

Pokud jsou zadané nesprávné vstupní parametry, je potřeba vrátit hodnotu 0 (neúspěch). Správné hodnoty vstupních parametrů musí splňovat:

* rok je větší roven 1600,
* měsíc je platný (1 až 12),
* den je platný (1 až počet dní v měsíci),
* hodina je platná (0 až 23),
* minuta je platná (0 až 59),
* zadaný okamžik počátku intervalu nenastane až po zadaném okamžiku konce intervalu.

Odevzdávejte zdrojový soubor, který obsahuje implementaci požadované funkce digitalClock. Do zdrojového souboru přidejte i další Vaše podpůrné funkce, které jsou z digitalClock volané. Funkce bude volaná z testovacího prostředí, je proto důležité přesně dodržet zadané rozhraní funkce. Za základ pro implementaci použijte kód z ukázky níže. V kódu chybí vyplnit funkci digitalClock (a případné další podpůrné funkce). Ukázka obsahuje testovací funkci main, uvedené hodnoty jsou použité při základním testu. Všimněte si, že vkládání hlavičkových souborů a funkce main jsou zabalené v bloku podmíněného překladu (`#ifdef`/`#endif`). Prosím, ponechte bloky podmíněného překladu i v odevzdávaném zdrojovém souboru. Podmíněný překlad Vám zjednoduší práci. Při kompilaci na Vašem počítači můžete program normálně spouštět a testovat. Při kompilaci na Progtestu funkce main a vkládání hlavičkových souborů "zmizí", tedy nebude kolidovat s hlavičkovými soubory a funkcí main testovacího prostředí.

Při výpočtu času uvažujeme Gregoriánský kalendář. Tedy měsíce mají vždy 30 nebo vždy 31 dní, výjimkou je únor, který má 28 dní (nepřestupný rok) nebo 29 dní (přestupný rok). Podle Gregoriánského kalendáře platí:

1. roky nejsou přestupné,
2. s výjimkou let dělitelných 4, které jsou přestupné,
3. s výjimkou let dělitelných 100, které nejsou přestupné,
4. s výjimkou let dělitelných 400, které jsou přestupné,
5. s výjimkou let dělitelných 4000, které nejsou přestupné.
6. Tedy roky 1901, 1902, 1903, 1905, ... jsou nepřestupné (pravidlo 1), roky 1904, 1908, ..., 1996, 2004, ... jsou přestupné (pravidlo 2), roky 1700, 1800, 1900, 2100, ... nejsou přestupné (pravidlo 3), roky 1600, 2000, 2400, ..., 3600, 4400, ... jsou přestupné (pravidlo 4) a roky 4000, 8000, ... nejsou přestupné (pravidlo 5).

Váš program bude spouštěn v omezeném testovacím prostředí. Je omezen dobou běhu (limit je vidět v logu referenčního řešení) a dále je omezena i velikost dostupné paměti. Časové limity jsou nastavené tak, aby rozumná implementace naivního algoritmu prošla všemi povinnými testy. Řešení fungující v povinných testech může získat nominálních 100% bodů. Bonusový test vyžaduje časově efektivní výpočet i pro velké intervaly (vysoké roky hodně převyšující 4000).

## Ukázka použití:
```c
#ifndef __PROGTEST__
#include <stdio.h>
#include <assert.h>
#endif /* __PROGTEST__ */

int digitalClock ( int y1, int m1, int d1, int h1, int i1,
                   int y2, int m2, int d2, int h2, int i2, long long int * consumption )
 {
   /* todo */
 }

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
 {
   long long int consumption;

   assert ( digitalClock ( 2014, 10,  1, 13, 15,
                           2014, 10,  1, 18, 45, &consumption ) == 1
            && consumption == 510384LL );
   assert ( digitalClock ( 2014, 10,  1, 13, 15,
                           2014, 10,  2, 11, 20, &consumption ) == 1
            && consumption == 2015964LL );
   assert ( digitalClock ( 2014,  1,  1, 13, 15,
                           2014, 10,  5, 11, 20, &consumption ) == 1
            && consumption == 605329884LL );
   assert ( digitalClock ( 2012,  1,  1, 13, 15,
                           2012, 10,  5, 11, 20, &consumption ) == 1
            && consumption == 607515804LL );
   assert ( digitalClock ( 1900,  1,  1, 13, 15,
                           1900, 10,  5, 11, 20, &consumption ) == 1
            && consumption == 605329884LL );
   assert ( digitalClock ( 2014, 10,  1,  0,  0,
                           2014, 10,  1, 12,  0, &consumption ) == 1
            && consumption == 1033464LL );
   assert ( digitalClock ( 2014, 10,  1,  0, 15,
                           2014, 10,  1,  0, 25, &consumption ) == 1
            && consumption == 15804LL );
   assert ( digitalClock ( 2014, 10,  1, 12,  0,
                           2014, 10,  1, 12,  0, &consumption ) == 1
            && consumption == 1704LL );
   assert ( digitalClock ( 2014, 10,  1, 12,  0,
                           2014, 10,  1, 12,  1, &consumption ) == 1
            && consumption == 3168LL );
   assert ( digitalClock ( 2014, 11,  1, 12,  0,
                           2014, 10,  1, 12,  0, &consumption ) == 0 );
   assert ( digitalClock ( 2014, 10, 32, 12,  0,
                           2014, 11, 10, 12,  0, &consumption ) == 0 );
   assert ( digitalClock ( 2100,  2, 29, 12,  0,
                           2100,  2, 29, 12,  0, &consumption ) == 0 );
   assert ( digitalClock ( 2400,  2, 29, 12,  0,
                           2400,  2, 29, 12,  0, &consumption ) == 1
            && consumption == 1704LL );
   return 0;
 }
#endif /* __PROGTEST__ */
```

## Nápověda
* Zkopírujte si ukázku a použijte ji jako základ Vašeho řešení.
* Do funkce main si můžete doplnit i další Vaše testy, případně ji můžete libovolně změnit. Důležité je zachovat podmíněný překlad.
* S pěticí hodnot (rok, měsíc, den, hodina, minuta) se špatně pracuje (například při porovnávání). Je lepší si tyto hodnoty převést na nějakou jinou reprezentaci, ideálně aby vzniklo pouze jedno číslo.
* V programu musíte mnoho výpočtů dělat 2x - pro počátek a konec intervalu. Je dobrý nápad vytvořit si pomocné funkce, které 2x zavoláte.
* V povinných testech jsou zadávané roky nepřevyšující rok 4000.
* Pro velké intervaly (bonusový test) je celková spotřeba obrovská. Rozsah datového typu int nepostačuje. Proto má funkce parametrem long long int, který již stačí. Datový typ long long int není standardní součástí C89 (byl dodán později), proto kompilátor při jeho použití generuje varování. Toto varování se potlačí přepínačem -Wno-long-long. Progtest má tento přepínač nastaven, tedy použití tohoto datového typu nezpůsobí varování.
* V ukázce je použito makro assert. Pokud je parametrem nenulová hodnota, makro nedělá nic. Pokud je parametrem nepravda (nula), makro ukončí program a vypíše řádku, kde k selhání došlo. Pokud je tedy Vaše implementace projde ukázkovými testy, program doběhne a nic nezobrazí.
* Výstupní parametr je spotřebovaná energie v joulech. Připomínáme, že 1J = 1Ws (watt-sekunda).