#Author: Josef
#dolezjo3@fit.cvut.cz

CXXFLAGS=-Wall -Wextra -pedantic -Wno-long-long -std=c++11 -O0 -ggdb
CLIBS=
CXX=g++
RM=rm -rf
OBJECTS=bin/objects/main.o bin/objects/cparser.o bin/objects/ctoken.o bin/objects/cnum.o bin/objects/coperator.o bin/objects/tests.o bin/objects/ccalc.o
DOXY=Doxyfile
BIN=./dolezjo3

all: $(OBJECTS) $(DOXY)
	make compile
	make doc

compile: $(BIN)

run: $(BIN)
	$(BIN) examples/t5

clean:
	$(RM) bin doc $(BIN)

debug: $(BIN)
	valgrind --leak-check=full --track-origins=yes $(BIN) examples/t5

doc: $(DOXY) src/*
	( cd src | doxygen $(DOXY) 1>/dev/null 2>&1 )

$(BIN): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(BIN) $(CLIBS)

bin/objects/main.o: src/main.cpp bin/objects/ccalc.o bin/objects/tests.o
	mkdir -p bin/objects
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o bin/objects/main.o $(CLIBS)

bin/objects/tests.o: src/tests.cpp bin/objects/cnum.o bin/objects/cparser.o bin/objects/coperator.o bin/objects/ccalc.o
	mkdir -p bin/objects
	$(CXX) $(CXXFLAGS) -c src/tests.cpp -o bin/objects/tests.o $(CLIBS)

bin/objects/cnum.o: src/cnum.cpp bin/objects/ctoken.o
	mkdir -p bin/objects
	$(CXX) $(CXXFLAGS) -c src/cnum.cpp -o bin/objects/cnum.o $(CLIBS)

bin/objects/ctoken.o: src/ctoken.cpp
	mkdir -p bin/objects
	$(CXX) $(CXXFLAGS) -c src/ctoken.cpp -o bin/objects/ctoken.o $(CLIBS)

bin/objects/cparser.o: src/cparser.cpp bin/objects/ctoken.o bin/objects/coperator.o bin/objects/cnum.o
	mkdir -p bin/objects
	$(CXX) $(CXXFLAGS) -c src/cparser.cpp -o bin/objects/cparser.o $(CLIBS)

bin/objects/coperator.o: src/coperator.cpp bin/objects/ctoken.o
	mkdir -p bin/objects
	$(CXX) $(CXXFLAGS) -c src/coperator.cpp -o bin/objects/coperator.o $(CLIBS)

bin/objects/ccalc.o: src/ccalc.cpp bin/objects/cparser.o
	mkdir -p bin/objects
	$(CXX) $(CXXFLAGS) -c src/ccalc.cpp -o bin/objects/ccalc.o $(CLIBS)
