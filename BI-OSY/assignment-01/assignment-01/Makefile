CC=g++
CFLAGS=-Wall -pedantic -Wextra -g
TARGETS=run main

all: $(TARGETS)
	
run: main
	./main
main: main.cpp
	$(CC) $(CFLAGS) -o main main.cpp -lpthread -std=c++11 -g

check: main
	valgrind --leak-check=full --track-origins=yes ./main

debug: main
	gdb ./main

format: main.cpp
	clang-format-3.5 -i main.cpp 2> /dev/null

clean:
	rm -f $(TARGETS)
