# Obdélníky
## Zadání
Úkolem je vytvořit program, který pro čtveřici bodů v rovině rozhodne, zda tvoří obdélník.

Vstupem programu je čtveřice bodů v rovině. Každý bod je tedy zadán jako dvojice desetinných čísel - souřadnice x a y. Pořadí bodů na vstupu respektuje pořadí bodů na obvodu zadávaného obdélníku. Pokud jsou body zadané proházeně, program je vyhodnotí tak, že netvoří obdélník (viz předposlední ukázka).

Výstupem programu je rozhodnutí, zda zadané body tvoří obdélník nebo ne. Pokud body tvoří čtverec, považuje to program rovněž za obdélník (je to speciální případ obdélníku). Za výpisem (formát viz ukázka) je znak odřádkování (`\n`).

Program musí být schopen detekovat nesprávný vstup. Pokud je na vstupu nesmyslné zadání, program to zjistí, vypíše chybové hlášení a ukončí se. Formát chybového hlášení je uveden v ukázce níže. Pozor, za případným chybovým hlášením je odřádkování (`\n`). Chybová hlášení zasílejte na standardní výstup (`printf`), nezasílejte jej na chybový výstup. Za chybu je považováno:

* nečíselná hodnota souřadnice nebo
* chybějící souřadnice.

Při programování si dejte pozor na přesnou podobu výpisů. Výstup Vašeho programu kontroluje stroj, který požaduje přesnou shodu výstupů Vašeho programu s výstupy referenčními. Za chybu je považováno, pokud se výpis liší. I chybějící nebo přebývající mezera/odřádkování je považováno za chybu. Abyste tyto problémy rychle vyloučili, použijte přiložený archiv se sadou vstupních a očekávaných výstupních dat. Podívejte se na videotutoriál (edux -> výuková videa), jak testovací data použít a jak testování zautomatizovat.

Váš program bude spouštěn v omezeném testovacím prostředí. Je omezen dobou běhu (limit je vidět v logu referenčního řešení) a dále je omezena i velikost dostupné paměti (ale tato úloha by ani s jedním omezením neměla mít problém). Testovací prostředí dále zakazuje používat některé "nebezpečné funkce" -- funkce pro spouštění programu, pro práci se sítí, ... Pokud jsou tyto funkce použité, program se nespustí. Možná ve svém programu používáte volání:

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

## Ukázka práce programu
Ukázková data jsou uložena ve složce _sample_.