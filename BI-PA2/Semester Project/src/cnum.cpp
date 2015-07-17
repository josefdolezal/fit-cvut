//Author: Josef Dolezal
//dolezjo3@fit.cvut.cz


#include "cnum.h"


//! \brief Constructor initialize new instance with string.
//! \param n String representing number.
CNum::CNum( const string &n ): m_Negative(false) {
    strConstructor( n );
}

//! \brief Constructor initialize new instance with array of chars.
//! \param n Array of chars representing representing number.
CNum::CNum( const char *n ): m_Negative(false) {
    strConstructor( n );
}

//! \brief Copy Constructor initialize new instance from existing number.
//! \param o Source CNum.
CNum::CNum( const CNum &o ) {
    m_Integer  = o.m_Integer;
    m_Floating = o.m_Floating;
    m_Negative = o.m_Negative;
    
    removeLeading();
}

//! \brief Destructor clears sources created by instance.
CNum::~CNum( void ) {
    
}

//! \brief Assings source instance of CNum and rewrites current values.
//! \param o Source Cnum.
//! \return Itself with new values.
CNum & CNum::operator = ( const CNum &o ) {
    if( this == &o ) return *this;
    
    m_Integer  = o.m_Integer;
    m_Floating = o.m_Floating;
    m_Negative = o.m_Negative;
    
    removeLeading();
    
    return *this;
}

//! \brief Compares itself with another CNum instance.
//! \param o CNum to be compared with.
//! \return True if it's bigger than parameter.
bool CNum::operator > ( const CNum &o ) const {
    CNum n     = o;
    CNum m     = *this;
    bool absEq = false;
    bool negEq = false;
    
    alignStrings( n.m_Floating, m.m_Floating );
    alignStrings( n.m_Integer, m.m_Integer, false );
    
    absEq = m.m_Integer > n.m_Integer || ( m.m_Integer == n.m_Integer && m.m_Floating > n.m_Floating );
    
    if( ! m_Negative ) return o.m_Negative || absEq;
    
    negEq = n.m_Integer > m.m_Integer || ( n.m_Integer == m.m_Integer && n.m_Floating > m.m_Floating );
    
    return o.m_Negative && negEq;
}

//! \brief Compare itself with another CNum for equality.
//! \param o CNum to be compared with.
//! \return True if compared CNum is eaqul.
bool CNum::operator == ( const CNum &o ) const {
    CNum   n = o;
    CNum   m = *this;
    
    alignStrings( n.m_Floating, m.m_Floating );
    alignStrings( n.m_Integer, m.m_Integer, false );
    
    return n.m_Integer == m.m_Integer && n.m_Floating == m.m_Floating && m.m_Negative == n.m_Negative;
}

//! \brief Compare itself with another CNum for difference.
//! \param o CNum to be compared with.
//! \return True if compared CNum is different.
bool CNum::operator != ( const CNum &o ) const {
    return ! ( *this == o );
}

//! \brief Multiplies itself with another CNum.
//! \param o CNum to be multiplied with.
//! \return New instance with multiplied values.
CNum CNum::operator * ( const CNum &o ) const {
    return multiply( *this, o );
}

//! \brief Substracts CNum from itself.
//! \param o CNum to be substracted.
//! \return New instance with substracted value.
CNum CNum::operator - ( const CNum &o ) const {
    return substract( *this, o );
}

//! \brief Unary minus of CNum.
//! \return New instance with opposite sign.
CNum CNum::operator - ( void ) const {
    CNum r = *this;
    r.m_Negative = ! r.m_Negative;
    return r;
}

//! \brief Adds CNum to itself.
//! \param o CNum to be added.
//! \return New instance with addition of two CNums.
CNum CNum::operator + ( const CNum &o ) const {
    return add( *this, o );
}

//! \brief Multiplies itself with given CNum.
//! \param o CNum to be multiplied with.
//! \returns Itself multiplied by argument.
CNum & CNum::operator *= ( const CNum &o ) {
    return *this = multiply( *this, o );
}

//! \brief Substracts given CNum from itself.
//! \param o CNum to be substracted.
//! \return Itself reduced by argument.
CNum & CNum::operator -= ( const CNum &o ) {
    return ( *this = substract( *this, o ) );
}

//! \brief Adds given CNum to itself.
//! \param o CNum to be added.
//! \return itself increased by argument.
CNum & CNum::operator += ( const CNum &o ) {
    return *this = add( *this, o );
}

//! \brief Adds one CNum to another.
//! \param m CNum base for adding.
//! \param n CNum to be added to base.
//! \return New instance of CNum with value of addition of arguments.
CNum CNum::add( CNum m, CNum n ) const {
    if( ! m.m_Negative && ! n.m_Negative ) // + (+) +
        return sum( m, n );
    else if ( m.m_Negative && n.m_Negative ) // - (+) -
        return sum( m, n );
    else if ( m.m_Negative && ! n.m_Negative ) { // - (+) +
        m.m_Negative = false;
        return substract( n, m );
    }
    // else + (+) -
    
    return add( n, m );;
}

//! \brief Substracts one CNum from another.
//! \param m CNum to be substraced from.
//! \param n CNum that will be substracted.
//! \return New instance of CNum with value of first argument reduced by second.
CNum CNum::substract( CNum m, CNum n ) const {
    if( ! m.m_Negative && n.m_Negative ) { // + (-) - = + (+) +
        n.m_Negative = false;
        return add( m, n );
    } else if ( ! m.m_Negative && ! n.m_Negative ) // + (-) +
        return diff( m, n );
    else if ( m.m_Negative && ! n.m_Negative ) { // - (-) + = - (+) -
        n.m_Negative = true;
        return add( m, n );
    }
    // else - (-) - = - (+) +
    
    n.m_Negative = false;
    return add( m, n );
}

//! \brief Multiplies one CNum with another.
//! \param m CNum to be multiplied.
//! \param n CNum representing multiplier.
//! \return New instance of CNum with value of first argument multiplied by second.
CNum CNum::multiply( CNum m, CNum n ) const {
    string sum = "0";
    string padding;
    string tmp;
    
    alignStrings( m.m_Floating, n.m_Floating );
    alignStrings( m.m_Integer, n.m_Floating, false );
    
    m.m_Integer = m.m_Integer + m.m_Floating;
    n.m_Integer = n.m_Integer + n.m_Floating;
    
    for( int i = (int) n.m_Integer.length() - 1; i >= 0; i-- ) {
        int c = 0;
        tmp = strMultiply( m.m_Integer, n.m_Integer[i] );
        tmp += padding;
        padding += "0";
        
        alignStrings( tmp, sum, false );
        sum = strPlus( sum, tmp, c, false );
    }
    
    m.m_Negative = m.m_Negative != n.m_Negative;
    m.m_Integer  = sum.substr( 0, sum.length() - ( m.m_Floating.length() + n.m_Floating.length() ) );
    m.m_Floating = sum.substr( sum.length() - ( m.m_Floating.length() + n.m_Floating.length() ) );
    
    m.removeLeading();
    
    return m;
}

//! \brief Displays number to the output stream.
//! \param os Output stream.
void CNum::display( ostream &os ) const {
    os << ( m_Negative ? "-" : "" ) << m_Integer;
    if( m_Floating.length() > 0 ) os << "." << m_Floating;
}

//! \brief Parses string to the internal representation.
//! \param str String to be parsed.
void CNum::parseInput( string str ) {
    bool isInt = true;
    
    if( str.length() > 0 && str[0] == '-' ) {
        m_Negative = true;
        str = str.substr( 1 );
    }
    
    for( char c : str ) {
        if( ( ! isInt || ( isInt && c != '.' ) ) && ! isdigit( c ) ) throw BadInputFormatException();
        if( c == '.' ) { isInt = false; continue; }
        
        if( isInt ) m_Integer += c;
        else m_Floating += c;
    }
    
    if( (int) m_Floating.length() == 0 && (int) m_Integer.length() == 0 ) throw InvalidZeroLengthException();
}

//! \brief Removes leading zeros from interger and floating value.
void CNum::removeLeading( void ) {
    while( (int) m_Floating.length() > 0 && m_Floating.back() == '0' ) m_Floating.pop_back();
    while( (int) m_Integer.length() > 1 && m_Integer.front() == '0' ) m_Integer.erase( 0, 1 );
}

//! \brief Alignes two strings to the same length.
//! \param a String to be aligned.
//! \param b String to be aligned.
//! \param alignFloating Bolean indicating where to add leading zeros.
void CNum::alignStrings( string &a, string &b, bool alignFloating ) const {
    int l = (int) ( a.length() - b.length() );
    if( l == 0 ) return;
    
    string padding;
    
    for ( int i = 0; i < abs( l ); i++ ) padding += '0';

        if( l < 0 ) a = alignFloating ? a + padding : padding + a;
        else        b = alignFloating ? b + padding : padding + b;
}

//! \brief Adds one aligned String to another.
//! \param a Aligned String.
//! \param b Aligned String.
//! \param carry Carry from previous addition.
//! \param returnCarry False if carry have to be set to 0. Otherwise keeps carry value after additon.
//! \return New instance of String containing sum of two arguments.
string CNum::strPlus( const string &a, const string &b, int &carry, bool returnCarry ) const {
    string val;
    string reverse;
    int    sum = 0;
    
    for( int i = (int) a.length() - 1; i >= 0; i-- ) {
        sum = carry + ( a[i] - '0' ) + ( b[i] - '0' );
        
        carry = sum / 10;
        val  += ( sum % 10 ) + '0';
    }
    
    if( ! returnCarry && carry > 0 ) { val += carry + '0'; carry = 0; }
        
    for ( int i = (int) val.length() - 1; i >= 0 ; i-- ) reverse += val[i];
    return reverse;
}

//! \brief Substracts aligned Strings.
//! \param a Aligned String.
//! \param b Aligned String.
//! \param carry Carry from previous substraction.
//! \param returnCarry False if carry have to be set to 0. Otherwise keeps carry value after substraction.
//! \return New instance of String constaining substraction of two arguments.
string CNum::strMinus( string a, string b, int &carry, bool returnCarry ) const {
    string val;
    string reverse;
    string tmp;
    
    if( ! returnCarry && b > a ) {
        tmp = a;
        a   = b;
        b   = tmp;
    }
    
    for( int i = (int) a.length() - 1; i >= 0; i-- ) {
        int an = a[i] - '0';
        int bn = b[i] - '0' + carry;
        
        an    = bn > an ? an + 10 : an;
        val  += ( an - bn ) % 10 + '0';
        carry = an / 10;
    }
    
    if( ! returnCarry && carry > 0 ) { val += carry + '0'; carry = 0; }
    
    for ( int i = (int) val.length() - 1; i >= 0 ; i-- ) reverse += val[i];
    return reverse;
}

//! \brief Multiplies aligned String by char.
//! \param s Aligned String.
//! \param c Char that multiply given String.
//! \return New instance of String multiplied by char.
string CNum::strMultiply( string s, char c ) const {
    int    carry = 0;
    string val;
    string reverse;
    c = c - '0';
    
    for ( int i = (int) s.length() - 1; i >= 0; i-- ) {
        int mul = ( s[i] - '0' ) * c + carry;
        val += mul % 10 + '0';
        carry = mul / 10;
    }
    
    while( carry != 0 ) {
        val += carry % 10 + '0';
        carry /= 10;
    }
    
    for ( int i = (int) val.length() - 1; i >= 0 ; i-- ) reverse += val[i];
    return reverse;
}

//! \brief Creates new instance of CNum.
//! \param n String representing value of number.
void CNum::strConstructor( const string &n ) {
    parseInput( n );
    if( (int) m_Integer.length() < 1 ) m_Integer += '0';
    removeLeading();
}

//! \brief Sums absolute values of two CNums.
//! \param m CNum base for adding.
//! \param a CNum to be added to the base.
//! \return New instance of CNum.
CNum CNum::sum( CNum m, CNum a ) const {
    int carry = 0;
    
    alignStrings( m.m_Floating, a.m_Floating );
    alignStrings( m.m_Integer, a.m_Integer, false );
    
    m.m_Floating = strPlus( a.m_Floating, m.m_Floating, carry );
    m.m_Integer  = strPlus( a.m_Integer, m.m_Integer, carry, false );
    m.m_Negative = false;
    
    return m;
}

//! \brief Substract absolute values of two numbers
//! \param m CNum to be substracted from.
//! \param n CNum that will be substracted.
//! \return New instance of CNum.
CNum CNum::diff( CNum m, CNum n ) const { // m - n
    int  carry = 0;
    bool negative = n > m;
    
    if( m == n ) return "0.0";
    
    alignStrings( m.m_Floating, n.m_Floating );
    alignStrings( m.m_Integer, n.m_Integer, false );
    
    m.m_Floating = strMinus( m.m_Floating, n.m_Floating, carry );
    m.m_Integer  = strMinus( m.m_Integer, n.m_Integer, carry, false );
    m.m_Negative = negative;
    
    return m;
}

//! \brief Represents exception description.
//! \return Array of chars containing description.
const char * BadInputFormatException::what( void ) const noexcept {
    return "CNum: unexpected character in input sequence.";
}

//! \brief Represents exception description.
//! \return Array of chars containing description.
const char * InvalidZeroLengthException::what( void ) const noexcept {
    return "CNum: invalid zero length of number.";
}
