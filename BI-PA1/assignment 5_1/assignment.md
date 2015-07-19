# Docházkový systém
## Zadání
Úkolem je realizovat program, který bude vyhodnocovat docházkový systém.

Předpokládejme docházkový systém, který kontroluje příchody a odchody pracovníků ze zaměstnání. Každý pracovník je vybaven svoji kartou identifikovanou unikátním číslem. Karta po přiložení na snímač umožní vstup na pracoviště nebo odchod z pracoviště. Snímačů je u vchodu více, projít lze libovolným z nich. Každý snímač vytváří protokol (log) o kartách použitých pro příchod/odchod. V logu je uveden čas, číslo karty a směr (dovnitř/ven). Program dostane na vstup logy z těchto snímačů a vyhodnotí je.

Vstupem programu jsou logy ze snímačů. Log obsahuje záznamy dvou typů:

```
+ h:m:s id
- h:m:s id
```

Oba záznamy obsahují hodinu, minutu a sekundu použití snímače a identifikátor karty. Pokud je prvním znakem +, pracovník vchází dovnitř. Znak - naopak znamená odchod pracovníka pryč. Záznamy v logu jsou uspořádané vzestupně, navíc žádný časový údaj se v logu jednoho snímače neopakuje (projít snímačem trvá nejméně 1s).

Snímačů může být instalováno více, náš program dostane na vstup všechny logy. Obecně má vstup tvar:

```
log_snimace_1
#
log_snimace_2
#
...
#
log_snimace_N
```

Logy jednotlivých snímačů obsahují záznamy zmíněné výše. Log snímače může být i prázdný (nikdo jím ten den neprošel).

Program nejprve zkontroluje správnost vstupů. Pokud je log správně, program vypíše pracovníka (pracovníky) dne, tedy ty pracovníky, kteří v daný den odpracovali nejdelší směnu. Pracovníky program vypíše oddělené čárkami (viz ukázka), v pořadí dle rostoucího čísla karty. Zároveň program vypíše i délku této nejdelší směny.

Program musí správně ošetřovat vstupy. Pokud jsou vstupy neplatné, program to musí detekovat, vypsat chybové hlášení a ukončit se. Za chybu je považováno:

* nesprávný záznam v logu (nemá formát + H:M:S ID ani - H:M:S ID),
* nečíselný časový údaj, čas mimo rozmezí 0:00:00 až 23:59:59,
* nečíselný údaj čísla karty, číslo karty mimo rozmezí 1 až 100000,
* log je prázdný (nikdo ten den nepřišel ani neodešel),
* log snímače nesplňuje podmínku striktně rostoucí časové posloupnosti,
* pracovník uvnitř znovu přichází, pracovník venku odchází,
* pracovník uvnitř zůstává po 23:59:59,
* ten samý pracovník je v ten samý okamžik zpracováván více snímači.

Program je spouštěn v omezeném prostředí. Je omezen dobou běhu i dostupnou pamětí. Pro úspěšné zvládnutí je potřeba realizovat řešení, které nebude zbytečně plýtvat pamětí a nebude zbytečně plýtvat časem.

## Ukázka práce programu
Ukázková data jsou uložena ve složce [_sample_](sample).

## Nápověda
* Pro zpracování vstupu se hodí funkce `scanf` s formátem `"%c"` a `" %c"`. Zjistěte si, jaký je v nich rozdíl.
* Další užitečnou funkcí může být funkce `ungetc()`.
