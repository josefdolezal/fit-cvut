# Anonymní zkoušky
## Zadání
Úkolem je realizovat třídu, která usnadní agendu organizace anonymizovaných testů.

Každý student ČVUT má přidělené unikátní celé číslo. Toto číslo jej jednoznačně reprezentuje, jméno a příjmení mohu mít duplicity. Každý student má kartu ČVUT (ISIC), karta má přidělený svůj identifikátor (pro jednoduchost řetězec z čísel a písmen). Jeden student může mít více karet (např. pokud kartu ztratí).

Při organizaci testu přijde student a zaregistruje se na daný test pomocí své karty. Následně je test opraven a pomocí čísla studenta je pro test vloženo jeho hodnocení. Třída dále bude poskytovat rozhraní pro zjištění výsledků a zjištění registrovaných studentů, kterým ještě nebylo vloženo hodnocení. Celé rozhraní třídy `CExam` je:

* implicitní konstruktor
* vytvoří prázdnou instanci třídy.
* metoda `Load`
  * načte ze zadaného vstupního streamu seznam studentů a jejich karet. Parametrem metody je otevřený vstupní stream. Ve streamu jsou data o studentech uložena v textové formě, každý řádek popisuje jednoho studenta. Řádek má strukturu:
    * `id_studenta`:`jméno_a_příjmení`:`identifikátor_karty`, `identifikátor_karty`, ...
  
  * Id studenta je celé kladné číslo, musí být unikátní. Jméno a příjmení je řetězec tvořený písmeny, čísly a mezerami. Může se opakovat. Identifikátory karty jsou řetězce tvořené písmeny a čísly, jsou oddělené čárkami a případně i mezerami před/za identifikátorem karty. Identifikátory karty musí být opět unikátní (přes všechny identifikátory karet).
  * Metoda Load načte tyto údaje a uloží si je do svých struktur. Pokud narazí na chybu (opakující se id studenta/karty), metoda nebude nic ukládat a vrátí `false`. Pokud je vstup bez chyb, metoda uloží přečtené údaje a vrací `true`.
* metoda `Register ( card, test )`
  * metoda zaregistruje studenta identifikovaného pomocí karty na zadaný test. Vrací `true` pro úspěch, `false` pro selhání (student se na daný test již registroval, neznámá karta).
* metoda `Assess ( student, test, res )`
  * metoda zapíše výsledek pro studenta zadaného `id` na zadaném `test`u. Vrací `true` pro úspěch, `false` pro selhání (student nebyl na daný test registrován, neznámý student, student byl již z daného testu hodnocen).
* metoda `ListTest ( test, sortBy )`
  * metoda zjistí seznam všech studentů, kteří mají ohodnocený zadaný test. Zjištěný seznam vrací jako návratovou hodnotu. Struktury `CResult` budou ve vráceném seznamu seřazené podle zadaného kritéria (viz konstanty v deklaraci třídy): `SORT_RESULT` (podle výsledku sestupně), `SORT_NAME` (podle jména studentů vzestupně), `SORT_ID` (podle ID studentů vzestupně) a `SORT_NONE` (podle pořadí ve kterém byly testy ohodnocené). Pokud samotné kritérium (počet bodů, jméno) nestačí, použije se při řazení pořadí ohodnocení testů jako druhý klíč (např. při řazení podle počtu bodů - pokud mají dva testy stejné hodnocení 50 bodů, pak bude v seznamu dříve ten, který byl dříve ohodnocen pomocí `Assess`).
* metoda `ListMissing ( test )`
  * metoda vrátí množinu se jmény studentů, kteří daný test psali (byli registrováni), ale zatím nemají `test` ohodnocený. **Vzhledem k neunikátním jménům to není příliš logické, jedná se o chybu v zadání (logické by bylo vracet množinu ID studentů).** Tento nedostatek byl nahlášen až po otevření úlohy, specifikaci by tedy nebylo fér za běhu měnit. Tedy pokud existuje více studentů stejného jména a někteří již mají `test` opravený a někteří ještě ne, pak se dané jméno ve vrácené množině nebude vyskytovat.

Při implementaci využijete připravenou strukturu `CResult` Tato struktura pouze zabaluje složky popisující jeden test jednoho studenta. Struktura je implementovaná v testovacím prostředí. Pro lokální testování je k dispozici v bloku podmíněného překladu. Ponechte deklaraci této struktury bez úprav a nechte ji v bloku podmíněného překladu. Úpravy této struktury a její případné umístění mimo blok podmíněného překladu nejspíše povedou k chybě při kompilaci na Progtestu.

Odevzdávejte zdrojový kód s implementací třídy `CExam`. Za základ implementace použijte přiložený soubor s deklarací metod a se sadou základních testů.

Při implementaci můžete/musíte využít kolekce z STL. Není ale rozumné na všechny vnitřní struktury používat kolekci `vector`.

## Ukázkové použití
Ukázkové použití je uvedeno v souboru _sample.cpp_.