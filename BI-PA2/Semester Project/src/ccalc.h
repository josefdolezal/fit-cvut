//Author: Josef Dolezal
//dolezjo3@fit.cvut.cz


#ifndef __semestralka__ccalc__
#define __semestralka__ccalc__

#include <stack>
#include "cparser.h"


//! \brief Class represents too much numbers exception.
class TooMuchNumbersInQueueException: public exception {
public:
    const char * what( void ) const noexcept;
};

//! \brief Class represents too few arguments for operator exception/
class TooFewArgumentsException: public exception {
public:
    const char * what( void ) const noexcept;
};

//! \brief Class calculates math expression in infinite precision.
class CCalc {
public:
               // ~CCalc ( void );
    CNum  Calc  ( const string & );
private:
    void  clear     ( stack<CNum *> & );
    bool  isBracket ( char ) const;
};


#endif /* defined(__semestralka__ccalc__) */
