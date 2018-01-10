build: clean bisi2 bitex biemp fiksa miadp

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

clean:
	latexmk -c
