//Author: Josef Dolezal
//dolezjo3@fit.cvut.cz


#include "ctoken.h"


//! \brief Prints token to output stream.
//! \param os Output to stream.
//! \param t Token to be printed.
//! \return Output stream.
ostream & operator << ( ostream &os, const CToken &t ) {
    t.display( os );
    return os;
}
