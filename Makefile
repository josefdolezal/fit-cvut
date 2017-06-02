build: clean bisi2 bitex biemp

bisi2:
	latexmk -pdf BI-SI2/notes/bi-si2

bitex:
	latexmk -pdf BI-TEX/bi-tex

biemp:
	latexmk -pdf BI-EMP/project-plan/bi-emp

clean:
	latexmk -c
