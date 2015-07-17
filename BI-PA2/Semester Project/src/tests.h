//Author: Josef Dolezal
//dolezjo3@fit.cvut.cz


#ifndef __semestralka__tests__
#define __semestralka__tests__

#include <stdio.h>
#include <sstream>
#include <cassert>
#include "cnum.h"
#include "coperator.h"
#include "cparser.h"
#include "ccalc.h"


//! \brief Class which tests all necesarry classes.
class Tests {
public:
    static void parserTests         ( void );
    static void cnumTests           ( void );
    static void cnumOperationsTests ( void );
    static void cnumLimits          ( void );
    static void operators           ( void );
    static void ccalcTests          ( void );
private:
};


#endif /* defined(__semestralka__tests__) */
