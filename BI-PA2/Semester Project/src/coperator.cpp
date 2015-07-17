//Author: Josef Dolezal
//dolezjo3@fit.cvut.cz


#include "coperator.h"


//! \brief Prints operator to the output stream.
//! \param os Output stream.
void COperator::display( ostream &os ) const {
    os << m_Operator;
}

//! \brief Getter for member variable.
//! \return Char representing math operator.
char COperator::type( void ) const {
    return m_Operator;
}

//! \brief Operator precence comparator.
//! \param c COperator for comparsion.
//! \return True if object itself has higher prioriry.
bool COperator::operator > ( const COperator &c ) const {
    return m_Precence > c.m_Precence;
}

//! \brief Operator precedence comparator.
//! \param c COperator for comparsion.
//! \return True if object itself has lower priority.
bool COperator::operator < ( const COperator &c ) const {
    return m_Precence < c.m_Precence;
}

//! \brief Math operator equality comparsion.
//! \param c COperator for comparsion.
//! \return True if math operators is equal.
bool COperator::operator == ( const COperator &c ) const {
    return m_Operator == c.m_Operator;
}

//! brief Math operator equality comparsion.
//! \param c COperator for comparsion.
//! \return True if math operators are different.
bool COperator::operator != ( const COperator &c ) const {
    return ! ( *this == c );
}

//! \brief Represents exception description.
//! \return Array of chars containing description.
const char * InvalidOperationException::what( void ) const noexcept {
    return "COperator: Invalid operation performed.";
}
