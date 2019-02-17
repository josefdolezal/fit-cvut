# Řešení domácí úlohy č.1

Autor: Josef Doležal

### Konfigurace programu

Opravená konfigurace pro program se nachází v souboru `config.txt`.
Program pracuje s binární reprezentací souboru, konfigurace tedy nemá lidsky čitelný obsah.

### Postup řešení

Pro představu jak program funguje jsem ho nejprve spustil s připojeným debuggerem a sledoval jeho průchod.
Následně jsem v disassembleru IDA zkoumal význam jednotlivých funkcí a sledoval manipulaci s konfiguračním souborem.

Program nejprve načte uživatelský vstup z konzole (uživatelsé jméno), následně se pokusí otevřít konfigurační soubor (při neúspěchu program končí).
Následuje kontrola uživatelského jména (alespoň 5 znaků - 3 uživatelské + implicitní `\r\n`) a načtení souboru.
Z volání funkce `ReadFile` je patrné, že soubor musí mít alespoň 5 bytů.

Následuje série podmínek, testujících první byte souboru.
Pro zvolení slušného oslovení musí být první byte `0xA3`.

Dále se v programu nachází podmínka na kontrolu druhého bytu, ten musí být `0x90`.

Následuje částečná validace čtvrtého bytu.
Ve while cyklu se provádí kontrola na spodní čtyři bity, ty musí být rovny `0x1`.

Třetí byte lze zjistit s volání funkce obsahující `switch`.
Pomocí tohoto bytu se hledá adresa v jump table, kam má program skočit.
Na správnou adresu se dostane při volbě bytu `0x21`.

Z podmínek pro poslední byte plyne, že musí být roven `0xFB`.

Aby byl email skutečně odeslán, kontroluje se MD5 hash pro konfigurační byty.
V programu je 16 bytů hashe správné konfigurace.
Hash můžeme ovlivnit pouze horními čtyřmi bity čtvtého bytu (ostatní jsou pevně danné).
Pomocí nástroje https://cryptii.com/pipes/md5-hash jsem hashoval kombinace s hodnotami čtvrtého bytu `0x01` až `0xF1` a hash porovnával je s referenční hashí z programu.
Správná hash vyjde při využití bytu `0x11`.

Konfigurace tedy musí být `A3 90 21 11 FB` hexadecimálně.
