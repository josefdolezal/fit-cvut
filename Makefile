build: clean bisi2 bitex biemp fiksa miadp mispi fifil miaph miibe mipdb mirev

bisi2:
	latexmk -pdf BI-SI2/notes/bi-si2

bitex:
	latexmk -pdf BI-TEX/bi-tex

biemp:
	latexmk -pdf BI-EMP/project-plan/bi-emp

fiksa:
	latexmk -pdf FI-KSA/fi-ksa

miadp:
	latexmk -pdf MI-ADP/mi-adp

mispi:
	latexmk -pdf MI-SPI/mi-spi

fifil:
	latexmk -pdf FI-FIL/fi-fil

miaph:
	latexmk -pdf MI-APH/mi-aph

miibe:
	latexmk -pdf MI-IBE/mi-ibe

mipdb:
	latexmk -pdf MI-PDB/mi-pdb

mirev:
	latexmk -pdf MI-REV/notes/mi-rev

clean:
	latexmk -c
