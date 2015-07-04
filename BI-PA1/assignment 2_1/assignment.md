# MHD
## Zadání
Úkolem je realizovat program, který pomůže optimalizovat hledání návaznosti MHD.

Jistě všichni známe problémy, když musíme přestupovat na jiný spoj MHD. Přijedeme na přestupní zastávku a zjistíme, že požadovaný navazující spoj odjel před pár minutami. Jak by byla krásná opačná situace, tedy přijet na přestupní zastávku, kde by navazující spoj odjížděl za pár minut. Náš program dokáže optimalizovat takové přestupy, tedy bude hledat, kdy se vyplatí vyrazit, abychom přestup zvládli bez zbytečného čekání.

Ve zjednodušeném výpočtu uvažujeme, že přijíždíme spojem #1. Tento spoj má pravidelné intervaly (zadané jako počet hodin a minut). Na přestupní stanici chceme odjet spojem #2, který má rovněž daný svůj interval (hodiny a minuty). Pro jednoduchost předpokládáme, že tento interval je stále stejný (spoje jezdí stejně často ve dne i v noci, zcela přesně ve svém intervalu). Předpokládejme, že spojem #1 přijedeme na přestupní stanici, kde zjistíme, že požadovaný spoj #2 odjel před zadaným počtem hodin a minut. Program z těchto údajů spočte, za jak dlouho nastane optimální situace pro přestup, tedy kdy bude spoj #2 odjíždět právě 1 minutu po příjezdu spoje #1.

Vstupem programu jsou tři časové údaje. Každý se sestává z hodin (celé číslo), dvojtečky a minut (celé číslo). Tyto časy udávají interval spoje #1, interval spoje #2 a dobu od odjezdu spoje #2.

Výstup programu se liší podle zadaných vstupů:

* zobrazí se časový údaj (hodiny a minuty), který udává za jak dlouho nastane optimální situace pro přestup, tedy kdy bude spoj #2 odjíždět přesně 1 minutu po příjezdu spoje #1,
* zobrazí se informace, že právě nyní je optimální situace pro přestup, tedy spoj #2 bude odjíždět za 1 minutu,
* zobrazí se informace, že pro zadané hodnoty vstupů nebude nikdy spoj #2 odjíždět 1 minutu po příjezdu spoje #1.

Formát výstupu pro každou variantu je uveden v ukázkovém běhu níže. Pozor, za každým řádkem výstupu je odřádkování (`\n`).

Program musí být schopen detekovat nesprávný vstup. Pokud je na vstupu nesmyslné zadání, program to zjistí, vypíše chybové hlášení a ukončí se. Formát chybového hlášení je uveden v ukázce níže. Pozor, za případným chybovým hlášením je odřádkování (`\n`). Chybová hlášení zasílejte na standardní výstup (`printf`), nezasílejte jej na chybový výstup. Za chybu je považováno:

* nečíselná nebo záporná hodnota hodin či minut,
* počet minut převyšující 59,
* nulový interval spoje,
* nesmyslná kombinace intervalu a odjezdu spoje #2.

Při programování si dejte pozor na přesnou podobu výpisů. Výstup Vašeho programu kontroluje stroj, který požaduje přesnou shodu výstupů Vašeho programu s výstupy referenčními. Za chybu je považováno, pokud se výpis liší. I chybějící nebo přebývající mezera/odřádkování je považováno za chybu. Abyste tyto problémy rychle vyloučili, použijte přiložený archiv se sadou vstupních a očekávaných výstupních dat. Podívejte se na videotutoriál (edux -> výuková videa), jak testovací data použít a jak testování zautomatizovat.

Váš program bude spouštěn v omezeném testovacím prostředí. Je omezen dobou běhu (limit je vidět v logu referenčního řešení) a dále je omezena i velikost dostupné paměti (ale tato úloha by ani s jedním omezením neměla mít ve standardních testech problém). Testovací prostředí dále zakazuje používat některé "nebezpečné funkce" -- funkce pro spouštění programu, pro práci se sítí, ... Pokud jsou tyto funkce použité, program se nespustí. Možná ve svém programu používáte volání:

```c
int main ( int argc, char * argv [] )
{
 
  ...
     
  system ( "pause" ); /* aby se nezavrelo okno programu */
  return 0;
}
```

Toto nebude v testovacím prostředí fungovat - je zakázáno spouštění jiného programu. (I pokud by se program spustil, byl by odmítnut. Nebyl by totiž nikdo, kdo by pauzu "odmáčkl", program by čekal věčně a překročil by tak maximální dobu běhu.) Pokud tedy chcete zachovat pauzu pro testování na Vašem počítači a zároveň chcete mít jistotu, že program poběží správně, použijte následující trik:

```c
int main ( int argc, char * argv [] )
{
 
  ...

#ifndef __PROGTEST__
  system ( "pause" ); /* toto progtest "nevidi" */
#endif /* __PROGTEST__ */
  return 0;
}
```

Hodnocení této úlohy má část povinnou a část bonusovou. V povinné části se testují rozumné hodnoty, vstupů, pro řešení postačuje naivní algoritmus. Bonusová část je nepovinná, jejím zvládnutím lze získat body navíc. V bonusovém testu jsou na vstupu zadávané velké intervaly, pro výpočet v časovém limitu je potřeba použít efektivnější algoritmus.

## Ukázka práce programu
Ukázková data jsou uložena ve složce _sample_.

## Poznámky
* V povinné části jsou zadávané hodnoty malé, pro implementaci postačuje datový typ `int`. V bonusové části datový typ `int` nestačí, je potřeba použít datový typ `long long` případně `int64_t` z hlavičkového souboru stdint.h. Kompilátor při použití typu `long long` hlásí varování, toto varování je při testování vypnuté, tedy datový typ lze použít bez penalizací.
* Pro zobrazení proměnné typu long long se používá konverze `%lld`.
* Při řešení bonusové části je potřeba zkontrolovat, že během výpočtu nedochází k překročení rozsahu typu long long. Zadané velikosti intervalu spojů nepřekročí rozsah datového typu `int`. Některé algoritmy/implementace ale při výpočtu vytvářejí mezivýsledky, které by mohly překročit rozsah typu `long long`. Pokud by tomu tak bylo, je potřeba algoritmus upravit (např. lze prohodit pořadí některých operací, případně operace rozepsat).
* Bonusová úloha - **SPOILER:** pokud si chcete bonusovou úlohu vyřešit samostatně, nečtěte dále. Program lze realizovat bez časově náročného cyklu. Referenční řešení používá rozšířený Euklidův algoritmus.