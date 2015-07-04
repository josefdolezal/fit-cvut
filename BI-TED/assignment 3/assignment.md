# Sazba textu
## Zadání

Pro téma podle Vašeho výběru, napište a vysázejte dokument pomocí systému LaTeX.

Proveďte následující kroky:

1. Vyberte si (nebo napište) text, který vysázíte v LaTeXu. Výběr takového textu, který Vám umožní splnit [požadavky na úspěšné odevzdání, je na Vaší zodpovědnosti](https://edux.fit.cvut.cz/courses/BI-TED/seminars/01/start#ulohasazba_textu).
2. Napište zdrojovou formu dokumentu pro zpracování systémem LaTeX.

Nezapomeňte si dokument vygenerovaný LaTeXem a zkontrolujte podle [osnovy hodnocení na EDUXu](http://edux.fit.cvut.cz/courses/BI-TED/tutorials/01/start#uloha_-_sazba_textu) počet bodů, které (pravděpodobně) dostanete. **Je důležité zkontrolovat si, zda Váš dokument splňuje všechny požadavky uvedené na EDUXu, neboť úspěšné odevzdání a ohodnocení je nutnou podmínkou k zápočtu.**

Odevzdejte ZIP archiv obsahující zdrojové soubory LaTeXu a další soubory (např. obrázky) potřebné k vygenerování Vašeho dokumentu pomocí pdfLaTeXu. Bez schopnosti vygenerovat dokument pouze z toho, co odevzdáte, nebude Vaše řešení akceptováno. Neodevzdávejte nic, co není k vygenerování dokumentu potřeba (např. už vygenerovaný dokument ve formátu PDF). Odevzdaný archiv nesmí obsahovat žádný adresář, hlavní zdrojový soubor musí být pojmenovaný text.tex. Hlášení o chybě testovacího subsystému zpravidla znamená, že Váš archiv nesplňuje pokyny (např. obsahuje adresář). Chyba při kompilaci může znamenat, že na Progtestu chybí některý balíček, který používáte (v tom případě pošlete mail *xxx*).

Nepoužívejte balíček svg a jeho příkaz `includesvg`. Inkscape není na Progtestu nainstalovaný. Místo toho použijte Inkscape (nebo jiný software) přímo k převodu obrázku ve formátu SVG do formátu PDF.

## Hodnocení

Odevzdejte zde na Progtest ZIP archiv, jak je popsaný výše. Pro toto odevzdání platí termíny. Pozdní odevzdání je penalizováno zpočátku ztrátou 30 % bodů, tato penalizace se však postupně zvyšuje s přibližujícím se koncem období pro pozdní odevzdání.

Při odevzdání na Progtest nejsou prováděné žádné důkladné kontroly (tedy úspěšné odeslání na Progtest neznamená správnost ani nárok na zápočet). Body jsou udělené až na základě osobní diskuse (obhajoby) s cvičícím. Pro osobní obhajobu také platí termín (pouze v rámci zápočtového termínu, na který jste v KOS přihlášeni). Pozor – jak odevzdání přes Progtest (v rámci vlastního termínu), tak osobní obhajoba (v rámci zápočtového termínu v KOS) jsou (obojí) podmínkou pro zisk bodů za tuto úlohu.

Odevzdání na Progtest proveďte až ve chvíli, kdy je Vaše práce hotová (a nebudete na ní nic měnit). **Na odevzdání máte jediný pokus.** Po ohodnocení Vaší práce body není možnost, jak svůj bodový výsledek změnit nebo opravit.

### Význam chybových hlášení Progtestu

* Selhání testovacího subsystému
  * problém s odevzdaným souborem (soubor není ZIP archiv, obsahuje adresář, neobsahuje soubor text.tex v kořenovém adresáři atd.)
* Chyba při základní kompilaci
  * pdflatex s Vaším kódem skončil s chybou (použití balíčku, který není na Progtestu, chybějící obrázek apod.)
* Nesprávný výstup
  * odevzdaná práce neprošla některým ze základních testů (z názvu testu lze vyčíst, co je špatně)