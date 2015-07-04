/* author: josef dolezal */
/* git: https://github.com/josefdolezal */

#include <iostream>

using namespace std;

#ifndef __PROGTEST__
#include <cstdio>
#include <ctime>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;
#endif /* __PROGTEST__ */

class InvalidDateException {};

//=================================================================================================
// date_format manipulator - a dummy implementation. Keep this code unless you implement your
// own working manipulator.
ios_base & dummy_date_format_manipulator ( ios_base & x )
{
    return x;
}

ios_base & ( * ( date_format ( const char * fmt ) ) ) ( ios_base & x )
{
    return dummy_date_format_manipulator;
}
//=================================================================================================
/**
 * CDate class declaration
 * ----------------------------------------------------------------------- */
class CDate
{
public:
    // constructor ( y,m,d )
    // operator + int
    // operator - int
    // operator - CDate
    // operators ++, --, both prefix and postfix
    // operators ==, !=, <=, <, >=, >
    // operators << and >>
    
    CDate( int y, int m, int d ) {
        if ( ! validDate( y, m, d ) ) throw InvalidDateException();
        setTime( y, m, d );
    }
    CDate( const CDate &c ): m_timest( c.m_timest ) {}
    
    CDate&  operator + ( int ); //done
    CDate&  operator - ( int ); //done
    int     operator - ( const CDate & ) const; //done
    CDate& operator ++(); // pre done
    CDate  operator ++( int ); //done
    CDate& operator --(); //done
    CDate  operator --( int ); //done
    CDate& operator = ( const CDate & ); //done
    bool operator == ( const CDate& ) const; //done
    bool operator != ( const CDate& ) const; //done
    bool operator <= ( const CDate& ) const; //done
    bool operator <  ( const CDate& ) const; //done
    bool operator >= ( const CDate& ) const; //done
    bool operator >  ( const CDate& ) const; //done
    
    friend ostream& operator << ( ostream &os, CDate& );
    friend istream& operator >> ( istream &is, CDate& );
private:
    time_t m_timest;
    static const int DAYSEC = 86400;
    
    void setTime( int, int ,int );
    bool validDate( int, int, int ) const;
    int daysInMonth( int, bool ) const;
    bool isLeapYear( int ) const;
    

};

/**
 * CDate class definition
 * ----------------------------------------------------------------------- */
CDate& CDate::operator + ( int days ) {
    m_timest += DAYSEC * days;
    
    return *this;
}

CDate& CDate::operator - ( int days ) {
    return *this + (-days);
}

int CDate::operator - ( const CDate &d ) const {
    return difftime( m_timest, d.m_timest ) / DAYSEC;
}

CDate& CDate::operator ++ () {
    m_timest  += DAYSEC;
    return *this;
}

CDate CDate::operator ++ ( int ) {
    CDate tmp = *this;
    this->m_timest += DAYSEC;
    return tmp;
}

CDate& CDate::operator -- () {
    m_timest  -= DAYSEC;
    return *this;
}

CDate CDate::operator -- ( int ) {
    CDate tmp = *this;
    this->m_timest -= DAYSEC;
    return tmp;
}

CDate& CDate::operator = ( const CDate &d ) {
    if ( this == &d) return *this;
    
    this->m_timest = d.m_timest;
    return *this;
}

bool CDate::operator == ( const CDate &d ) const {
    return d.m_timest == this->m_timest;
}

bool CDate::operator != ( const CDate &d ) const {
    return ! ( *this == d );
}

bool CDate::operator <= ( const CDate &d ) const {
    return m_timest <= d.m_timest;
}

bool CDate::operator < ( const CDate &d ) const {
    return ! ( *this >= d);
}

bool CDate::operator >= ( const CDate &d ) const {
    return m_timest >= d.m_timest;
}

bool CDate::operator > ( const CDate &d ) const {
    return ! ( *this <= d);
}

/* PRIVATE */
void CDate::setTime( int y, int m, int d ) {
    m_timest = time( NULL );
    struct tm timest = *localtime( &m_timest );
    
    timest.tm_year = y - 1900;
    timest.tm_mon  = m - 1;
    timest.tm_mday = d;
    timest.tm_sec = 1; timest.tm_min = 1; timest.tm_hour = 1;
    
    m_timest = mktime( &timest );
}

bool CDate::validDate( int y, int m, int d ) const {
    bool leapy = isLeapYear( y );
    return ! ( y < 1600 || m < 1 || m > 12 || d < 1 || d > daysInMonth( m, leapy ) );
}

int CDate::daysInMonth( int month, bool leapy) const {
    switch ( month ) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
            break;
        case 4: case 6: case 9: case 11:
            return 30;
            break;
        case 2:
            return leapy == 0 ? 28 : 29;
            break;
    }
    
    return 0;
}

bool CDate::isLeapYear( int y ) const {
    if ( y < 1600 || ( y % 4 == 0 && y % 4000 != 0 && ( y % 100 != 0 || y % 400 == 0 ) ) )
        return true;
    
    return false;
}

ostream& operator << ( ostream &os, CDate &d ) {
    struct tm timest = *localtime( &d.m_timest );
    os << timest.tm_year + 1900 << '-' << setfill( '0' ) << setw( 2 ) << timest.tm_mon + 1 << '-' << setw( 2 ) << timest.tm_mday;
    return os;
}

istream& operator >> ( istream &is, CDate &c ) {
    char m1, m2;
    int y, m, d;
    
    is >> y >> m1 >> m >> m2 >> d;
    if ( ! c.validDate( y, m, d ) || m1 != '-' || m2 != '-' ) {
        is.setstate( ios::failbit );
        return is;
    }
    
    c.setTime( y, m, d );
    
    return is;
}
