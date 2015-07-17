//Author: Josef Dolezal
//dolezjo3@fit.cvut.cz


#ifndef __semestralka__parser__
#define __semestralka__parser__

#include <string>
#include <stack>
#include <queue>
#include <ctype.h>
#include "ctoken.h"
#include "coperator.h"
#include "cnum.h"


using namespace std;

//! \brief Class represents parentheses missmatch.
class ParenthesesMismatchException: public exception {
public:
    const char * what( void ) const noexcept;
};

//! \brief Class represents not expression input.
class NotAnExpressionException: public exception {
public:
    const char * what( void ) const noexcept;
};

//! \brief Class math expression from infix to postfix annotation.
class CParser {
public:
    static const char L_BRACKET = '('; ///< Constant containing left bracket.
    static const char R_BRACKET = ')'; ///< Constant containing right bracket.
    
              CParser     ( const string & );
             ~CParser     ( void );
    void      ShowPostfix ( void ) const;
    CToken *  Front       ( void );

    
private:
    queue<CToken *>       m_Queue; ///< Queue of tokens
    stack<COperator *>    m_Ops;   ///< Stack of operators
    
    void parse              ( const string & );
    bool nextToken          ( const string &, int & );
    bool isOperator         ( char ) const;
    int  operatorPrecedence ( char ) const;
};


#endif /* defined(__semestralka__parser__) */
