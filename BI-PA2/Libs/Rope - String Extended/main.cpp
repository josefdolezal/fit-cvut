/* author: josef dolezal */
/* git: https://github.com/josefdolezal */

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>

using namespace std;

/*
 * BEGIN ROPE
 ------------------------------------------------------------------ */
class Rope {
public:
    ~Rope( void ) { delete[] m_data; }
    Rope( const Rope & ); //x
    Rope( const char * = "" ); //x
    
    Rope&  operator =  ( const char * ); //x
    Rope&  operator =  ( const Rope & ); //x
    bool   operator <  ( const Rope & ) const; //x
    bool   operator >  ( const Rope & ) const; //x
    bool   operator == ( const Rope & ) const; //x
    operator const char *();
    friend ostream& operator << ( ostream &, Rope & );
private:
    char* m_data;
    int   m_maxL;
    int   m_len;
    
    void allocWithStr( const char * ); //x
};

bool Rope::operator <  ( const Rope &r ) const {
    return strcmp( m_data, r.m_data ) < 0;
}
bool Rope::operator >  ( const Rope &r ) const {
    return strcmp( m_data, r.m_data ) > 0;
}
bool Rope::operator == ( const Rope &r ) const {
    return strcmp( m_data, r.m_data ) == 0;
}

Rope::operator const char *() {
    return m_data;
}

ostream& operator << ( ostream &os, Rope &r ) {
    os << r.m_data;
    return os;
}

Rope& Rope::operator = ( const char * str ) {
    delete[] m_data;
    allocWithStr( str );
    
    return *this;
}

Rope& Rope::operator = ( const Rope &r ) {
    if( this == &r ) return *this;
    delete[] m_data;
    allocWithStr( r.m_data );
    return *this;
}

Rope::Rope( const char * str ) {
    allocWithStr( str );
}

Rope::Rope( const Rope &r ) {
    allocWithStr( r.m_data );
}

/* PRIVATE */
void Rope::allocWithStr( const char *str ) {
    m_len  = (int) strlen( str );
    m_maxL = m_len + 1;
    m_data = new char[m_maxL];
    strncpy( m_data, str, m_maxL );
}
/*
 * END ROPE
 ------------------------------------------------------------------ */

