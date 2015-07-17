//Author: Josef Dolezal
//dolezjo3@fit.cvut.cz


#ifndef __semestralka__coperator__
#define __semestralka__coperator__

#include "ctoken.h"


//! \brief Class represents error exception for ivalid operators.
class InvalidOperationException: public exception {
public:
    const char * what ( void ) const noexcept;
};

//! \brief Class represents math operators and their precedence.
class COperator : public CToken {
public:
                   //! \brief Creates new instance of operator.
                   //! \param op Char containing operator
                   //! \param prec Operator precendece.
                   COperator  ( char op, int prec = 1 ): m_Precence(prec), m_Operator(op) {}
    virtual       ~COperator  ( void ) {}
    virtual void   display    ( ostream &os ) const;
    virtual char   type       ( void ) const;
    virtual bool  operator >  ( const COperator & ) const;
    virtual bool  operator <  ( const COperator & ) const;
    virtual bool  operator == ( const COperator & ) const;
    virtual bool  operator != ( const COperator & ) const;
    
    template<typename T>
    T applyOperator( const T &, const T & ) const;
private:
    int  m_Precence; ///< Integer representing operator precedence
    char m_Operator; ///< Char representing math operator
};

//! \brief Applies math operator on given arguments.
//! \param a First math operand of type T
//! \param b Second math operand of type T
//! \returns New instance of type T after operator application.
template<typename T>
T COperator::applyOperator( const T &a, const T &b ) const {
    switch ( m_Operator ) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
    }
    
    throw InvalidOperationException();
    return a;
}


#endif /* defined(__semestralka__coperator__) */
