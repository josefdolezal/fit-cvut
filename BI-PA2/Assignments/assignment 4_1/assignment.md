# Registr automobilů III
## Zadání
Úkolem je rozšířit třídu `CRegister` z předešlé úlohy tak, aby správně kopírovala obsah objektů při použití kopírujícího konstruktoru a operátoru `=`.

Naše databáze bude evidovat občany a automobily, které vlastní. Občan je identifikován svým jménem a příjmením. Jména a příjmení se mohou opakovat, ale dvojice (jméno, příjmení) je v databázi unikátní. Tedy v databázi může být mnoho jmen Jan a mnoho příjmení Novak, ale Jan Novak může být v databázi v daný okamžik pouze jeden. Automobily jsou pak jednoznačně identifikované svojí registrační značkou RZ. Předpokládáme, že automobil má vždy jednoho vlastníka, jeden občan může vlastnit několik automobilů.

Z důvodů zálohování chceme mít možnost vytvářet kopie existujícího instance `CRegister`. Kopie budou vznikat jednak kopírujícím konstruktorem a dále i operátorem `=`. Vzniklé kopie musí být nezávislé objekty, tedy operace s jedním z nich nemůže ovlivnit obsah druhého. Na druhou stranu se dá počítat s tím, že změn mezi kopiemi nebude mnoho, tedy některá data mohou kopie sdílet v zájmu šetření místa.

Veřejné rozhraní je uvedeno níže. Pro třídu `CRegister` obsahuje následující:

* Konstruktor bez parametrů. Tento konstruktor inicializuje instanci třídy tak, že vzniklá instance je zatím prázdná (neobsahuje žádné záznamy).
* Destruktor. Uvolňuje prostředky, které instance alokovala.
* Kopírující konstruktor a operátor `=` bude správně kopírovat obsah objektu.
* Metoda `AddCar ( RZ, Name, Surname )` přidá do existující databáze další záznam. Parametry Name a Surname reprezentují jméno a příjmení občana, `RZ` je identifikace automobilu. Metoda vrací hodnotu `true`, pokud byl záznam přidán, nebo hodnotu `false`, pokud dojde k chybě a automobil přidán nebyl. Chybou je, pokud již v databázi existuje automobil se stejnou `RZ`.
* Metoda `DelCar ( RZ )` odstraní záznam z databáze. Parametrem je jednoznačná identifikace automobilu pomocí `RZ`. Pokud byl záznam skutečně odstraněn, vrátí metoda hodnotu `true`. Pokud záznam neodstraní (protože neexistoval automobil s touto identifikací), vrátí metoda hodnotu `false`.
* Metoda `Transfer ( RZ, name, surname )` provede převod zadaného automobilu (`RZ`) ze stávajícího majitele na nového majitele zadaného parametry `name` a `surname`. Pokud metoda uspěje, vrací `true`, pro neúspěch vrací `false` (neexistující automobil, chybou je i pokus o převod, kdy stávající a nový majitel je ten samý občan).
* Metoda `ListCars` vyhledá automobily, které jsou vlastněné zadaným občanem. Metoda vrátí objekt typu `CCarList`, pomocí kterého lze postupně projít nalezené záznamy (iterátor). Pokud občan zadaného jména a příjmení neexistuje, je vrácen iterátor s prázdným obsahem (0 automobilů).
* Metoda `CountCars ( name, surname )` zjistí počet automobilů, který vlastní občan se zadaným jménem a adresou. Pokud občan zadaného jména v databázi neexistuje, je vrácena `0`.
* Metoda `ListOwners ( RZ )` vyhledá osoby, které vlastnily (vlastní) zadaný automobil. Metoda vrátí objekt typu `COwnerList`, pomocí kterého lze postupně projít nalezené záznamy (iterátor). Pokud zadaný automobil neexistuje, je vrácen iterátor s prázdným obsahem (0 osob).
* Metoda `CountOwners ( RZ )` zjistí počet majitelů v historii vlastnictví zadaného automobilu. Pokud zadaný automobil v databázi neexistuje, je vrácena `0`.
* Do třídy si budete muset přidat členské proměnné. Dále si do rozhraní můžete přidat další pomocné metody (ideálně neveřejné).

Třída `CCarList` slouží k jednorázovému procházení seznamem automobilů, které jsou vlastněné jedním občanem. V seznamu je vždy jeden automobil vybraný a v seznamu se můžeme pohybovat vpřed. Rozhraní třídy `CCarList`:

* Metoda `RZ` zjistí `RZ` vybraného automobilu,
* metoda `AtEnd` zjistí, zda jsme již dosáhli konce seznamu (vrátí `true`) nebo zda jsou ještě nějaké záznamy k dispozici (`false`).
* Metoda `Next` posouvá v seznamu o jednu pozici směrem ke konci.

Třída `COwnerList` slouží k jednorázovému procházení seznamem vlastníků, kteří vlastnili/vlastní zadaný automobil. V seznamu je vždy jeden vlastník aktuální a v seznamu se můžeme pohybovat vpřed. První v pořadí musí být aktuální vlastník, při procházení se pak pohybujeme směrem zpět do historie. Rozhraní třídy `COwnerList`:

* Metoda `Name` zjistí jméno vybraného vlastníka,
* Metoda `Surname` zjistí příjmení vybraného vlastníka,
* metoda `AtEnd` zjistí, zda jsme již dosáhli konce seznamu (vrátí `true`) nebo zda jsou ještě nějaké záznamy k dispozici (`false`).
* Metoda Next posouvá v seznamu o jednu pozici směrem ke konci (zpět v historii).

## Odevzdání
Odevzdávejte soubor, který obsahuje implementované třídy `CRegister`, `CCarList` a `COwnerList`. Třídy musí splňovat veřejné rozhraní podle ukázky - pokud Vámi odevzdané řešení nebude obsahovat popsané rozhraní, dojde k chybě při kompilaci. Do třídy si ale můžete doplnit další metody (veřejné nebo i privátní) a členské proměnné. Odevzdávaný soubor musí obsahovat jak deklaraci třídy (popis rozhraní) tak i definice metod, konstruktoru a destruktoru. Je jedno, zda jsou metody implementované inline nebo odděleně. Odevzdávaný soubor nesmí obsahovat vkládání hlavičkových souborů a funkci main (funkce main a vkládání hlavičkových souborů může zůstat, ale pouze obalené direktivami podmíněného překladu jako v ukázce níže).

Třída je testovaná v omezeném prostředí, kde je limitovaná dostupná paměť (dostačuje k uložení seznamu) a je omezena dobou běhu. Pro řešení zcela záměrně nemáte k dispozici STL ani `std::string`. Úloha má procvičit pochopení hluboké a mělké kopie. S využitím STL by tento cíl nebyl naplněn.

Hodnocení je rozděleno mezi povinné, nepovinné a bonusové testy. Pro zvládnutí povinných testů stačí implementace základní verze kopírování obsahu. Pro zvládnutí dalších testů je potřeba využít techniky copy-on-write, aby vznikající kopie zabíraly rozumný objem paměti.

## Ukázka použití
Ukázkové použití je uvedeno v souboru _sample.cpp_.