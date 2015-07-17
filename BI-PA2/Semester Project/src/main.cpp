//Author: Josef Dolezal
//dolezjo3@fit.cvut.cz

/*! \mainpage
 \section Introduction
 I made this program as semestral project in 6/2015.
 
 This program parses math expressions and calculates them in infinite precision.
 
 \section Compilation
 You can compile the program by makefile using <code>make compile</code>.
 */

#include <iostream>
#include <fstream>
#include <string>
#include "ccalc.h"
#include "tests.h"


int main( int argc, char const *argv[] ) {
    
    CCalc t;
    
    try {
        cout << t.Calc( "3 + (3-2))" ) << endl;
    } catch (exception &ex) {
        cout << ex.what() << endl;
    }
    
    return 0;
    
    if( argc < 2 ) {
        cout << "Calculator: undefined filename." << endl;
        return 1;
    }
    
    ifstream fs( argv[1], ios::in );
    
    
    if ( fs.fail() ) {
        cout << "Calculator: cannot read input file." << endl;
        return 1;
    }
    
    try {
        string s;
        getline( fs, s );
        CCalc g;
        
        cout << g.Calc( s ) << endl;
    } catch ( exception &ex ) {
        cout << ex.what() << endl;
    }
    
    return 0;
}



//! \brief Runs tests from Tests class.
void runTests( void ) {
    Tests::parserTests();
    Tests::cnumTests();
    Tests::cnumOperationsTests();
    Tests::cnumLimits();
    Tests::operators();
}
