build: clean bisi2

bisi2:
	latexmk -pdf BI-SI2/notes/bi-si2

clean:
	latexmk -c
