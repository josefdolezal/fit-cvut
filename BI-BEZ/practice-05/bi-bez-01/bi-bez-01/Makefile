CC=gcc
CFLAGS=-Wall -pedantic 
TARGETS=main

all: $(TARGETS)

main: main.cpp
	$(CC) $(CFLAGS) -o main main.cpp -lcrypto -lssl

run: main
	./main

clean:
	rm -f $(TARGETS)
