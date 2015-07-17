//Author: Josef Dolezal
//dolezjo3@fit.cvut.cz


#ifndef __semestralka__cnum__
#define __semestralka__cnum__

#include <string>
#include <ctype.h>
#include "ctoken.h"


using namespace std;

//! \brief Class represents error exception for numbers with zero lenght.
class InvalidZeroLengthException: public exception {
public:
    virtual const char * what() const noexcept;
};

//! \brief Class represents error exeption for bad input format.
class BadInputFormatException: public exception {
public:
    const char * what() const noexcept;
};

//! \brief Class represents number with endless precision.
class CNum : public CToken{
public:
                    CNum  ( const string & );
                    CNum  ( const char * );
                    CNum  ( const CNum & );
    virtual        ~CNum  ( void );
    
    CNum & operator =     ( const CNum & );
    bool   operator >     ( const CNum & ) const;
    bool   operator ==    ( const CNum & ) const;
    bool   operator !=    ( const CNum & ) const;
    CNum   operator *     ( const CNum & ) const;
    CNum   operator -     ( const CNum & ) const;
    CNum   operator -     ( void )         const;
    CNum   operator +     ( const CNum & ) const;
    CNum & operator *=    ( const CNum & );
    CNum & operator -=    ( const CNum & );
    CNum & operator +=    ( const CNum & );
    
    virtual void   display   ( ostream & ) const;
private:
    string m_Integer;   ///< String with integer value.
    string m_Floating;  ///< String with floating point number value.
    bool   m_Negative;  ///< Boolean value representing number sign.
    
    void   parseInput     ( string );
    string strPlus        ( const string &, const string &, int &, bool = true ) const;
    string strMinus       ( string, string, int &, bool = true ) const;
    string strMultiply    ( string, char ) const;
    
    void   strConstructor ( const string & );
    void   alignStrings   ( string &, string &, bool = true ) const;
    void   removeLeading  ( void );
    CNum   sum            ( CNum, CNum ) const;
    CNum   diff           ( CNum, CNum ) const;
    CNum   substract      ( CNum, CNum ) const;
    CNum   multiply       ( CNum, CNum ) const;
    CNum   add            ( CNum, CNum ) const;
};

#endif /* defined(__semestralka__cnum__) */
