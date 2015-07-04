# Registr automobilů I
## Zadání
Úkolem je realizovat třídu `CRegister`, která bude implementovat databázi automobilů.

Naše databáze bude evidovat občany a automobily, které vlastní. Občan je identifikován svým jménem a příjmením. Jména a příjmení se mohou opakovat, ale dvojice (jméno, příjmení) je v databázi unikátní. Tedy v databázi může být mnoho jmen Jan a mnoho příjmení Novak, ale Jan Novak může být v databázi v daný okamžik pouze jeden. Automobily jsou pak jednoznačně identifikované svojí registrační značkou RZ. Předpokládáme, že automobil má vždy jednoho vlastníka, jeden občan může vlastnit několik automobilů.

Veřejné rozhraní je uvedeno níže. Pro třídu `CRegister` obsahuje následující:

* Konstruktor bez parametrů. Tento konstruktor inicializuje instanci třídy tak, že vzniklá instance je zatím prázdná (neobsahuje žádné záznamy).
* Destruktor. Uvolňuje prostředky, které instance alokovala.
* Metoda `AddCar ( RZ, Name, Surname )` přidá do existující databáze další záznam. Parametry `Name` a `Surname` reprezentují jméno a příjmení občana, `RZ` je identifikace automobilu. Metoda vrací hodnotu `true`, pokud byl záznam přidán, nebo hodnotu `false`, pokud dojde k chybě a automobil přidán nebyl. Chybou je, pokud již v databázi existuje automobil se stejnou `RZ`.
* Metoda `DelCar ( RZ )` odstraní záznam z databáze. Parametrem je jednoznačná identifikace automobilu pomocí `RZ`. Pokud byl záznam skutečně odstraněn, vrátí metoda hodnotu `true`. Pokud záznam neodstraní (protože neexistoval automobil s touto identifikací), vrátí metoda hodnotu `false`.
* Metoda `Transfer ( RZ, name, surname )` provede převod zadaného automobilu (`RZ`) ze stávajícího majitele na nového majitele zadaného parametry `name` a `surname`. Pokud metoda uspěje, vrací `true`, pro neúspěch vrací `false` (neexistující automobil, chybou je i pokus o převod, kdy stávající a nový majitel je ten samý občan).
* Metoda `ListCars` vyhledá automobily, které jsou vlastněné zadaným občanem. Metoda vrátí objekt typu `CCarList`, pomocí kterého lze postupně projít nalezené záznamy (iterátor). Pokud občan zadaného jména a příjmení neexistuje, je vrácen iterátor s prázdným obsahem (0 automobilů).
* Metoda `CountCars ( name, surname )` zjistí počet automobilů, který vlastní občan se zadaným jménem a adresou. Pokud občan zadaného jména v databázi neexistuje, je vrácena `0`.
* Do třídy si budete muset přidat členské proměnné. Dále si do rozhraní můžete přidat další pomocné metody (ideálně neveřejné).

Třída `CCarList` slouží k jednorázovému procházení seznamem automobilů, které jsou vlastněné jedním občanem. V seznamu je vždy jeden automobil vybraný a v seznamu se můžeme pohybovat vpřed. Rozhraní třídy `CCarList`:

* Metoda `RZ` zjistí RZ vybraného automobilu,
* metoda `AtEnd` zjistí, zda jsme již dosáhli konce seznamu (vrátí `true`) nebo zda jsou ještě nějaké záznamy k dispozici (`false`).
* Metoda `Next` posouvá v seznamu o jednu pozici směrem ke konci.

## Rozhraní
Odevzdávejte soubor, který obsahuje implementované třídy `CRegister` a `CCarList`. Třídy musí splňovat veřejné rozhraní podle ukázky - pokud Vámi odevzdané řešení nebude obsahovat popsané rozhraní, dojde k chybě při kompilaci. Do třídy si ale můžete doplnit další metody (veřejné nebo i privátní) a členské proměnné. Odevzdávaný soubor musí obsahovat jak deklaraci třídy (popis rozhraní) tak i definice metod, konstruktoru a destruktoru. Je jedno, zda jsou metody implementované inline nebo odděleně. Odevzdávaný soubor nesmí obsahovat vkládání hlavičkových souborů a funkci main (funkce main a vkládání hlavičkových souborů může zůstat, ale pouze obalené direktivami podmíněného překladu jako v ukázce níže).

Třída je testovaná v omezeném prostředí, kde je limitovaná dostupná paměť (dostačuje k uložení seznamu) a je omezena dobou běhu. Implementace třídy `CRegister` se nemusí zabývat kopírujícím konstruktorem ani přetěžováním operátoru `=`. V této úloze ProgTest neprovádí testy této funkčnosti.

Implementace třídy musí být efektivní z hlediska nároků na čas i nároků na paměť. Jednoduché lineární řešení nestačí (pro testovací data vyžaduje čas přes 5 minut). Předpokládejte, že operace převodů, zjišťování počtů automobilů a zjišťování automobilů vlastněných zadaným občanem je častější než operace vkládaní a mazání automobilu.

Pro ukládání záznamů v databázi alokujte prostor dynamicky případně použijte kontejnery z STL. Pozor, pokud budete pole alokovat ve vlastní režii, zvolte počáteční velikost malou (např. tisíc prvků) a velikost zvětšujte/zmenšujte podle potřeby. Při zaplnění pole není vhodné alokovat nové pole větší pouze o jednu hodnotu, takový postup má obrovskou režii na kopírování obsahu. Je rozumné pole rozšiřovat s krokem řádově tisíců prvků, nebo geometrickou řadou s kvocientem ~1.5 až 2.

Pokud budete používat STL, nemusíte se starat o problémy s alokací pole. Z STL máte v této úloze k dispozici povolený kontejner `vector` (úmyslně ne `list`, `set`, `map` a další).

## Ukázka použití
Ukázkové použití je uvedeno v souboru _sample.cpp_.