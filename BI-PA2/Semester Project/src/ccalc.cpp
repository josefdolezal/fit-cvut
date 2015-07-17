//Author: Josef Dolezal
//dolezjo3@fit.cvut.cz


#include "ccalc.h"


//! \brief CCalc destructor clears all sources created by instances.


//! \brief Calculates math expression in infix notation.
//! \param expression String with expression.
//! \return Result of expression.
CNum CCalc::Calc( const string &expression ) {
    CParser p( expression );
    stack<CNum *> st;
    CToken *tmp = NULL;
    
    
    while ( ( tmp = p.Front() ) ) {
        COperator *co = NULL;
        if( ( co = dynamic_cast<COperator *>( tmp ) ) ) {
            if( isBracket( co->type() ) ) { delete co; throw ParenthesesMismatchException(); }
            if( st.size() < 2 ) { clear( st ); delete co; throw TooFewArgumentsException(); }
            CNum *op1 = st.top(); st.pop();
            CNum *op2 = st.top(); st.pop();
            
            st.push( new CNum( co->applyOperator( *op2, *op1 ) ) );
            
            delete co;
            delete op1;
            delete op2;
        } else st.push( dynamic_cast<CNum *>( tmp ) );
        
    }
    
    if( st.size() > 1 ) { clear( st ); throw TooMuchNumbersInQueueException(); }
    if( st.empty() ) throw NotAnExpressionException();
    
    CNum res = *st.top();
    delete st.top();
    return res;
}

//! \brief Clears stack of numbers.
//! \param st Stack of CNum pointers that will be cleared.
void CCalc::clear( stack<CNum *> &st ) {
    while( ! st.empty() ) {
        delete st.top();
        st.pop();
    }
}

//! \brief Represents exception description.
//! \return Array of chars containing exception description.
const char * TooFewArgumentsException::what( void ) const noexcept {
    return "CCalc: Too few arguments for operator";
}

//! \brief Represents exception description.
//! \return Array of chars containing exception description.
const char * TooMuchNumbersInQueueException::what( void ) const noexcept {
    return "CCalc: Too much numbers in queue.";
}

//! \brief Checks if given operator is bracket.
//! \param c Character to be checked.
//! \return True if character is right or left bracket.
bool CCalc::isBracket( char c ) const {
    return c == '(' || c == ')';
}
