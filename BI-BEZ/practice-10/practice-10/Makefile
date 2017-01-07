CC=g++
CFLAGS=-Wall -pedantic -Wextra -g
TARGETS=main

all: $(TARGETS)

run: main
	./main

main: main.cpp
	$(CC) $(CFLAGS) -o main main.cpp -lcrypto -lssl -std=c++11

check: main
	valgrind --leak-check=full --track-origins=yes ./main

debug: main
	gdb ./main

format: main.cpp
	clang-format-3.5 -i main.cpp 2> /dev/null

clean:
	rm -f $(TARGETS)
