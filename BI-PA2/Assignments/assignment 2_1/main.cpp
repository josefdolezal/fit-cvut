/* author: josef dolezal */
/* git: https://github.com/josefdolezal */

#ifndef __PROGTEST__
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>
using namespace std;
#endif /* __PROGTEST__ */

class CCarList
{
public:
    CCarList ( void ) {}
    CCarList ( vector<string> v ): plates(v) {}
    string    RZ         ( void ) const;
    bool      AtEnd      ( void ) const;
    void      Next       ( void );
    
    CCarList& operator = ( const CCarList &);
    friend ostream& operator << ( ostream &, const CCarList & );
private:
    vector<string> plates;
    
};

class CRegister
{
public:
    CRegister   ( void ) {}
    ~CRegister  ( void );
    bool      AddCar     ( const string & rz,
                          const string & name,
                          const string & surname );
    bool      DelCar     ( const string & rz );
    bool      Transfer   ( const string & rz,
                          const string & nName,
                          const string & nSurname);
    CCarList  ListCars   ( const string & name,
                          const string & surname ) const;
    int       CountCars  ( const string & name,
                          const string & surname ) const;
    
    friend ostream& operator << ( ostream&, const CRegister & );

private:
    struct Person {
        Person(string name, string surname): name(name), surname(surname) {};
        bool operator == ( const Person & ) const;
        bool operator < ( const Person & ) const;
        
        string name;
        string surname;
        vector<string> plates;
    };
    
    struct CCar {
        CCar( string rz, Person *owner = NULL ): rz(rz), owner(owner) {}
        bool operator < ( const CCar& ) const;
        bool operator == ( const CCar& ) const;
        string rz;
        Person *owner;
    };
    
    vector<Person *>  m_ListByNames;
    vector<CCar>  m_ListByRZ;
    
    bool contentsCar( const string& );
    void addPersonRZ( Person&, const string& );
    void removePersonRZ( Person&, const string& );
};

/**
 * Pro hledani podle jmena slouzi m_ListByName
 * Pro hledani podle spz slouzi m_ListByRZ
 */


/**
 * CCarList class definition
 ------------------------------------------------------------------ */
string CCarList::RZ ( void ) const {
    return plates.back();
}

bool CCarList::AtEnd( void ) const {
    return plates.rbegin() == plates.rend();
}

void CCarList::Next( void ) {
    if ( plates.size() != 0) plates.pop_back();
}

/* PRIVATE */
CCarList& CCarList::operator = ( const CCarList &n ) {
    if ( this == &n ) return *this;
    
    plates = n.plates;
    return *this;
}

ostream& operator << ( ostream &os, const CCarList &c ) {
    os << "Znacky" << endl;
    for ( auto it : c.plates ) os << it << endl;
    
    return os;
}


/**
 * CRegister class definition
 ----------------------------------------------------------------- */
CRegister::~CRegister( void ) {
    for ( auto &person : m_ListByNames )  delete person;
}


bool CRegister::AddCar ( const string & rz, const string & name, const string & surname ) {
    if ( contentsCar( rz ) ) return false;
    
    Person *owner = new Person( name, surname );
    auto oIt      = lower_bound( m_ListByNames.begin(), m_ListByNames.end(), owner, [] ( const Person *l, const Person *r ) { return *l < *r; } );
    CCar car( rz, owner );
    
    if ( oIt != m_ListByNames.end() && *(*oIt) == *owner ) { // majitel uz je v seznamu
        addPersonRZ( *(*oIt), rz );
        car.owner = (*oIt);
        delete owner;
    } else { // majitel jeste neni v seznamu
        m_ListByNames.insert( oIt, owner );
        owner->plates.push_back( rz );
    }
    
    auto cIt = lower_bound( m_ListByRZ.begin(), m_ListByRZ.end(), car );
    m_ListByRZ.insert( cIt, car );
    
    return true;
}

bool CRegister::DelCar ( const string & rz ) {
    CCar tmp( rz );
    auto it = lower_bound( m_ListByRZ.begin(), m_ListByRZ.end(), tmp );
    
    if ( it != m_ListByRZ.end() && (*it) == tmp ) { // nasel jsem znacku
        removePersonRZ( *(it->owner), rz );
        m_ListByRZ.erase( it );
        return true;
    }
    
    return false;
}

bool CRegister::Transfer( const string &rz, const string &nName, const string &nSurname ) {
    CCar tmp( rz );
    auto it = lower_bound( m_ListByRZ.begin(), m_ListByRZ.end(), tmp );
    
    if ( it != m_ListByRZ.end() && *it == tmp ) {
        Person *owner = new Person( nName, nSurname );
        
        if ( *(it->owner) == *owner ) { // stejny majitel
            delete owner;
            return false;
        }
    
        auto oIt = lower_bound( m_ListByNames.begin(), m_ListByNames.end(), owner, [] (const Person *l, const Person *r) { return *l < *r; } );
        
        removePersonRZ( *(it->owner), rz );
        
        if ( oIt != m_ListByNames.end() && *(*oIt) == *owner ) { // existujici majitel
            it->owner = (*oIt);
            addPersonRZ( *(it->owner), rz );
            delete owner;
        } else { // novy majitel jeste neni v db
            it->owner = owner;
            m_ListByNames.insert( oIt, owner );
            owner->plates.push_back( rz );
        }
        
        return true;
    }
    
    return false;
}

CCarList CRegister::ListCars( const string &name, const string &surname ) const {
    Person *tmp = new Person( name, surname );
    vector<string> res;
    auto it = lower_bound( m_ListByNames.begin(), m_ListByNames.end(), tmp, [] ( const Person *l, const Person *r ) { return *l < *r; } );
    
    if ( it != m_ListByNames.end() && *(*it) == *tmp ) res = (*it)->plates;
    
    delete tmp;
    return CCarList( res );
}

int CRegister::CountCars( const string &name, const string &surname ) const {
    Person *tmp = new Person( name, surname );
    int c = 0;
    auto it = lower_bound( m_ListByNames.begin(), m_ListByNames.end(), tmp, [] (Person *l, Person *r) { return *l < *r; } );
    
    if ( it != m_ListByNames.end() && *(*it) == *tmp )
        c = (int) (*it)->plates.size();
    
    delete tmp;
    return c;
}


/* PRIVATE */
bool CRegister::contentsCar( const string &rz ) {
    return binary_search( m_ListByRZ.begin(), m_ListByRZ.end(), CCar( rz ) );
}

void CRegister::addPersonRZ( CRegister::Person &p, const string &rz ) {
    auto it = lower_bound( p.plates.begin(), p.plates.end(), rz );
    p.plates.insert( it, rz );
}

void CRegister::removePersonRZ( CRegister::Person &p, const string &rz ) {
    auto it = lower_bound( p.plates.begin(), p.plates.end(), rz );
    if ( it != p.plates.end() && *it == rz ) p.plates.erase( it );
}

bool CRegister::Person::operator == ( const CRegister::Person & p ) const {
    return this->name == p.name && this->surname == p.surname;
}

bool CRegister::Person::operator < ( const CRegister::Person & p ) const {
    if ( this->surname == p.surname ) return this->name < p.name;
    return this->surname < p.surname;
}

bool CRegister::CCar::operator < ( const CRegister::CCar &c) const {
    return this->rz < c.rz;
}

bool CRegister::CCar::operator == ( const CRegister::CCar &c ) const {
    return this->rz == c.rz;
}

ostream& operator << ( ostream& os, const CRegister &cr ) {
    os << "Persons" << endl;
    for ( auto &t : cr.m_ListByNames ) os << (*t).surname << " " << (*t).name << endl;
    
    os << endl;
    
    os << "Plates" << endl;
    for ( auto &t : cr.m_ListByRZ ) os << t.rz << " - " << t.owner->name << " " << t.owner->surname << endl;
    
    os << endl << "Num. of plates: " << cr.m_ListByRZ.size() << ", Num. of persons: " << cr.m_ListByNames.size() << endl;
    
    return os;
}

#ifndef __PROGTEST__

/**
 * Tests, asserts, etc.
 ------------------------------------------------------------------ */

void testsV( void ) {
    CRegister b1;
    assert ( b1 . AddCar ( "ABC-12-34", "John", "Smith" ) == true );
    assert ( b1 . AddCar ( "ABC-32-22", "John", "Hacker" ) == true );
    assert ( b1 . AddCar ( "XYZ-11-22", "Peter", "Smith" ) == true );
    assert ( b1 . CountCars ( "John", "Hacker" ) == 1 );
    for ( CCarList l = b1 . ListCars ( "John", "Hacker" ); ! l . AtEnd (); l . Next () )
        cout << l . RZ () << endl;
    // the following plate
    
    // ABC-32-22
    
    assert ( b1 . Transfer ( "XYZ-11-22", "John", "Hacker" ) == true );
    assert ( b1 . AddCar ( "XYZ-99-88", "John", "Smith" ) == true );
    assert ( b1 . CountCars ( "John", "Smith" ) == 2 );
    for ( CCarList l = b1 . ListCars ( "John", "Smith" ); ! l . AtEnd (); l . Next () )
        cout << l . RZ () << endl;
    // the following 2 licence plates, in any order:
    
    // ABC-12-34
    // XYZ-99-88
    
    assert ( b1 . CountCars ( "John", "Hacker" ) == 2 );
    for ( CCarList l = b1 . ListCars ( "John", "Hacker" ); ! l . AtEnd (); l . Next () )
        cout << l . RZ () << endl;
    // the following 2 licence plates, in any order:
    
    // ABC-32-22
    // XYZ-11-22
    
    assert ( b1 . CountCars ( "Peter", "Smith" ) == 0 );
    for ( CCarList l = b1 . ListCars ( "Peter", "Smith" ); ! l . AtEnd (); l . Next () )
        cout << l . RZ () << endl;
    // empty output
    
    assert ( b1 . Transfer ( "XYZ-11-22", "Jane", "Black" ) == true );
    assert ( b1 . CountCars ( "Jane", "Black" ) == 1 );
    for ( CCarList l = b1 . ListCars ( "Jane", "Black" ); ! l . AtEnd (); l . Next () )
        cout << l . RZ () << endl;
    // the following plate
    
    // XYZ-11-22
    
    assert ( b1 . CountCars ( "John", "Smith" ) == 2 );
    for ( CCarList l = b1 . ListCars ( "John", "Smith" ); ! l . AtEnd (); l . Next () )
        cout << l . RZ () << endl;
    // the following 2 licence plates, in any order:
    
    // ABC-12-34
    // XYZ-99-88
    
    assert ( b1 . DelCar ( "XYZ-11-22" ) == true );
    assert ( b1 . CountCars ( "Jane", "Black" ) == 0 );
    for ( CCarList l = b1 . ListCars ( "Jane", "Black" ); ! l . AtEnd (); l . Next () )
        cout << l . RZ () << endl;
    // empty output
    
    assert ( b1 . AddCar ( "XYZ-11-22", "George", "White" ) == true );
    
    CRegister b2;
    assert ( b2 . AddCar ( "ABC-12-34", "John", "Smith" ) == true );
    assert ( b2 . AddCar ( "ABC-32-22", "John", "Hacker" ) == true );
    assert ( b2 . AddCar ( "XYZ-11-22", "Peter", "Smith" ) == true );
    assert ( b2 . AddCar ( "XYZ-11-22", "Jane", "Black" ) == false );
    assert ( b2 . DelCar ( "AAA-11-11" ) == false );
    assert ( b2 . Transfer ( "BBB-99-99", "John", "Smith" ) == false );
    assert ( b2 . Transfer ( "ABC-12-34", "John", "Smith" ) == false );
    assert ( b2 . CountCars ( "George", "White" ) == 0 );
    for ( CCarList l = b2 . ListCars ( "George", "White" ); ! l . AtEnd (); l . Next () )
        cout << l . RZ () << endl;
    // empty output
}


void testsP ( void ) {
    
    CRegister cr;
    
    cr.AddCar( "AA-BB-CC", "Josef", "Dolezal" );
    cr.AddCar( "AA-CC", "Josef", "Dolezal" );
    cr.AddCar( "DD", "Josef", "Dolezal" );
    cr.AddCar( "JJ", "Josef", "Dolezal" );
    
    cr.AddCar( "FF", "Jan", "Dolezal" );
    cr.Transfer( "DD", "Jan", "Dolezal" );
    
    cr.Transfer( "AA-CC", "Deda", "Libor" );
    
    cr.DelCar( "AA-BB-CC" );
    
    CCarList cjod = cr.ListCars( "Josef", "Dolezal" );
    CCarList cjad = cr.ListCars( "Jan", "Dolezal" );
    CCarList cdel = cr.ListCars( "Deda", "Libor" );
    
    
    
    cout << cr << endl;
    
    cout << cjod << endl << endl;
    cout << cjad << endl << endl;
    cout << cdel << endl << endl;
    
    
    
    
}


int main ( void )
{
    testsV();
    
    return 0;
}

#endif /* __PROGTEST__ */
