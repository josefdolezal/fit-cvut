# HTML tabulky I
## Zadání
Úkolem je realizovat sadu tříd, které budou implementovat tabulky podobné tabulkám v HTML.

Předpokládáme, že naše zjednodušená tabulka CTable je tvořená zadaným počtem řádků a sloupců, ty jsou vyplněné při vytváření instance. V každé buňce je buď prázdno (`CEmpty`), text (`CText`) nebo obrázek (`CImage`). Tabulka dokáže měnit obsah svých buněk a dokáže se zobrazit. Při zobrazení se tabulka velikostí přizpůsobí obsahu svých buněk (velikost se roztáhne tak, aby v žádné buňce nedošlo k ořezání).

Očekává se, že implementujete následující třídy s následujícím rozhraním:

### CEmpty

Třída reprezentuje prázdnou buňku. Jejím rozhraním je pouze implicitní konstruktor, který slouží k vytvoření instance.

### CText

Třída reprezentuje text. Text je zobrazen v příslušné buňce tabulky. Při zobrazování se zohledňují zadané konce řádků. Zobrazení lze zvolit horizontálně zarovnané vlevo nebo vpravo (align). Vertikálně je vždy text zarovnán nahoru. Rozhraní obsahuje:

* konstruktor `CText ( str, align )`
  * konstruktor inicializuje instanci třídy. Parametrem je zobrazovaný text a zarovnání (`ALIGN_LEFT` / `ALIGN_RIGHT`).
* metoda `SetText ( str )`
  * metodou lze nastavit jiný text, který má být zobrazován. Zarovnání se nemění.

### CImage

Třída reprezentuje obrázek. Obrázek je pro jednoduchost reprezentován v ASCII artu, je zadaný jako několik řádků - řetězců. Při zobrazování je obrázek umístěn do požadované buňky a je zarovnán na střed (horizontálně i vertikálně). Pokud by zarovnání na střed nebylo možné (lichý počet mezer v nějakém směru), bude obrázek posunut o jednu pozici vlevo a/nebo nahoru. Rozhraní obsahuje:

* konstruktor `CImage ()`
  * konstruktor inicializuje instanci třídy.
* metoda `AddRow ( str )`
  * metodou lze přidat další řádku obrázku. Můžete se spolehnout, že zadávané řádky mají vždy stejnou délku pro celý obrázek (tedy obrázek je vždy obdélníkový).

### CTable

třída reprezentuje tabulku. Do buněk tabulky se vkládá obsah (volno/text/obrázek). Tabulka nabízí rozhraní, které umožní manipulovat s obsahem buněk a zobrazit celou tabulku:

* `konstruktor ( rows, cols )`
  * inicializuje instanci a nastaví požadovaný počet řádek a sloupců tabulky. Takto inicializovaná tabulka bude mít všechny buňky prázdné.
* `GetCell ( row, col )`
  * metoda zpřístupní buňku v tabulce pro další operace (nastavení vlastností obsaženého textu/obrázku/... či čtení obsahu buňky.
* `SetCell ( row, col, newContent )`
  * metoda změní obsah zadané buňky tabulky na zadaný nový obsah.
* operator <<
  * umožní výpis zformátované tabulky do zadaného výstupního proudu.

## Odevzdání
Odevzdávejte zdrojový kód s implementací tříd `CTable`, `CText`, `CImage` a `CEmpty`. Třídy musejí implementovat rozhraní popsané výše. Do tříd si ale můžete doplnit další metody, které Vám implementaci zjednoduší.

Při implementaci můžete využít STL a typ c++ `string`. Základem implementace je ale dobrý návrh tříd a využití polymorfismu. Vaše řešení nebude uznáno, pokud nebude využívat polymorfismus.

## Ukázka použití
Ukázkové použití je uvedeno v souboru [_sample.cpp_](sample.cpp).