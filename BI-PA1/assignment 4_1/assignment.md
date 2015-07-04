## Zadání
Úkolem je realizovat program, který vypočte počet různých trojúhelníků, který lze sestavit ze stavebnice **Merkur**.

Stavebnice Merkur obsahuje díly - nosníky - různé délky. Z trojice takových dílů se dá s použitím tří šroubků sestavit trojúhelník. Předpokládejme, že máme stavebnici, ve které známe s počet nosníků a jejich délky. Úkolem je zjistit, kolik typově různých trojúhelníků lze z takové stavebnice sestavit.

Vstupem našeho programu je zadání délek nosníků, které jsou ve stavebnici obsažené. Pokud je nosníků zadané délky ve stavebnici více, je daná délka nosníku na vstupu zadána několikrát. Zadávání délek nosníků končí s koncem vstupu (EOF je aktivní). Délka vstupu je omezena na maximálně 10000 nosníků.

Výstupem programu je počet různých trojúhelníků, který lze ze stavebnice sestavit. Přesněji, kolika různými způsoby lze vybrat trojici nosníků a sestavit z nich trojúhelník. Do výsledného počtu chceme zahrnout pouze navzájem různé trojúhelníky. Například trojúhelníky o délce stran 3 - 4 - 5 a 5 - 3 - 4 považujeme za identické.

Program musí být schopen detekovat nesprávný vstup. Pokud je na vstupu nesmyslné zadání, program to zjistí, vypíše chybové hlášení a ukončí se. Formát chybového hlášení je uveden v ukázce níže. Pozor, za případným chybovým hlášením je odřádkování (`\n`). Chybová hlášení zasílejte na standardní výstup (`printf`), nezasílejte jej na chybový výstup. Za chybu je považováno:

* nečíselná, záporná nebo nulová délka nosníku,
* počet nosníků na vstupu menší než 3,
* počet nosníků na vstupu větší než 10000.

Váš program bude spouštěn v omezeném testovacím prostředí. Je omezen dobou běhu (limit je vidět v logu referenčního řešení) a dále je omezena i velikost dostupné paměti (ale tato úloha by s omezením velikosti paměti neměla mít problém). V testu práce s pamětí se kontroluje, zda Váš program nezasahuje do paměti mimo alokovaný prostor (např. mimo meze alokovaných polí).

Hodnocení této úlohy má část povinnou a část bonusovou. V povinné části se testují malé objemy vstupů, pro řešení postačuje naivní algoritmus. Bonusová část je nepovinná, jejím zvládnutím lze získat body navíc. V bonusovém testu jsou na vstupu zadávané větší počty nosníků, pro výpočet v časovém limitu je potřeba použít efektivnější algoritmus.

## Ukázka práce programu
Ukázková data jsou uložena ve složce [_sample_](sample).

## Poznámky
* V povinné části jsou zadávané hodnoty malé, pro implementaci postačuje datový typ `int`. Pokud chcete uspět i v bonusové části, datový typ `int` nestačí. Je potřeba použít datový typ `long long` případně `int64_t` z hlavičkového souboru `stdint.h`. Kompilátor při použití typu `long long` hlásí varování, toto varování je při testování vypnuté, tedy datový typ `long long` lze použít bez penalizací.
* Pro zobrazení hodnoty typu `long long` se používá konverze `%lld`.
* Nosníky ve stavebnici Merkur jsou perforované, šroubky lze umístit do mnoha děr, tedy z celkové délky nosníku lze využít i kratší úseky. V této úloze ale uvažujeme pouze plnou délku nosníku.