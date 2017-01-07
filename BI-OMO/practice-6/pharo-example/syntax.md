## Syntaxe jazyka smalltalk
```smalltalk
"Deklarace promennych"
|s t p1 p2|
"Definice promennych"
s:='Te'.
t:='st'
Transcript show: s,t,' 1'.
"Peikazy musi koncit teckou"
1000 factorial.

"Smalltalk nema prioritu operatoru - vyhodnocuje zleva"
3+4*5. "=35"
3+(4*5). "=23"

'ah','oj' = 'ahoj'. "Porovnava hodnotu -> true"
'ah','oj' == 'ahoj'. "Porovnava identit -> dva odkazy na stejny objekt (adresy v pameti) -> false"
1+1=2. "true -> identita je primo hodnota"

"Podminky"
(3 > 4)
	ifTrue: [ Transcript show: 'Ano' ]
	ifFalse: [ Transcript show: 'Ne' ]. "Lambda vyrazy (bloky), prijemce bloku se rozhodne, zda ho vykona"

p1:=$a to: $c.
p2:=p1. "Prirazeni identity, ne hodnoty"
p2 at: 2 put: $X.
p2. "Meni i puvodni promennou"

"Kolekce"
#(1 3 9 4 6 2). "Muze obsahovat pouze literaly"
{ 1.2 . 3 . 4 . 5 . 6 }. "Vyhodnocuje se az za behu programu"
{ 1+2 . 3*6 }.
#(1 7 6 9) collect: [ :x | x+1 ]. "Spocita prvky nove kolekce podle vzorce v bloku"
#(1 10 8 6 9 2 4)
	inject: 0
	into: [ :acc :each | acc + each ]. "Scita pomoci stradace acc -> vysledek 40"

"Selekce"
#(1 3 9 4 6 2) select: [ :x | x > 5 ]. "Postupne se podminka aplikuje na vsechny prvky kolekce"
#(#jedna #dva #tri) collect: [ :x | x size ]. "Vysledek je 5 3 3"

"Logicke operace"
(1>3) & (9>2). "Plne vyhodnoceni"
(1>3) and: [9 > 2]. "Zkracene vyhodnoceni -> 9>2 se nebyhodnocuje, blok se vyhodnocuje az kdyz ho metoda vola"
```

## Cviceni 1: XOR
```smalltalk
| nand func prvni druhy treti |
nand := [ :x :y | (x & y) not ].

func := [ :x :y | | m |
	nand value: x value: y.
].

Transcript cr; show: 'x'; tab; tab; show: 'y'; tab;tab; show: 'func'; cr.
#(true false) do: [ :x |
#(true false) do: [ :y |
prvni:=(func value: x value:y).
druhy:=(func value: prvni value:y).
treti:=(func value: x value:prvni).
Transcript "sem doplňte výpis: x, y, func"
show: x; space; tab; show: y; space; tab; show: (func value: druhy value:treti);

cr
]].

```
