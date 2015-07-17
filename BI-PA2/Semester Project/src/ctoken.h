//Author: Josef Dolezal
//dolezjo3@fit.cvut.cz


#ifndef __semestralka__ctoken__
#define __semestralka__ctoken__


#include <iostream>
#include <string>

using namespace std;

//! \brief Abstract class representing token in postfix notation.
class CToken {
public:
    //! \brief Virtual destructor.
    virtual        ~CToken  ( void ) {}
    
    //! \brief Abstract method that displays token to output stream.
    //! \param os Output stream.
    virtual void    display ( ostream &os ) const = 0;
    
    friend ostream & operator << ( ostream &, const CToken & );
private:
};

#endif /* defined(__semestralka__ctoken__) */
