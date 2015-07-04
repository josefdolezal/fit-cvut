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
    CCarList( void ) {}
    CCarList( vector<string> p, vector<unsigned int> v ): plates(p), vins(v) {}
    string         RZ           ( void ) const;
    unsigned int   VIN          ( void ) const;
    bool           AtEnd        ( void ) const;
    void           Next         ( void );
    
    CCarList& operator = ( const CCarList & );
    friend ostream& operator << ( ostream &, const CCarList & );
private:
    vector<string> plates;
    vector<unsigned int> vins;
};

class COwnerList
{
public:
    COwnerList( void ) {}
    COwnerList( vector<string> n, vector<string> s ): names(n), surnames(s) {}
    string         Name         ( void ) const;
    string         Surname      ( void ) const;
    bool           AtEnd        ( void ) const;
    void           Next         ( void );
    
    COwnerList& operator = ( const COwnerList & );
    friend ostream& operator << ( ostream &, COwnerList & );
private:
    vector<string> names;
    vector<string> surnames;
};

class CRegister
{
public:
    CRegister    ( void ) {}
    ~CRegister    ( void );
    bool           AddCar       ( const string    & rz,
                                 unsigned int      vin,
                                 const string    & name,
                                 const string    & surname );
    bool           DelCar       ( const string    & rz );
    bool           DelCar       ( unsigned int      vin );
    bool           Transfer     ( const string    & rz,
                                 const string    & nName,
                                 const string    & nSurname );
    bool           Transfer     ( unsigned int      vin,
                                 const string    & nName,
                                 const string    & nSurname );
    CCarList       ListCars     ( const string    & name,
                                 const string    & surname ) const;
    int            CountCars    ( const string    & name,
                                 const string    & surname ) const;
    COwnerList     ListOwners   ( const string    & RZ ) const;
    int            CountOwners  ( const string    & RZ ) const;
    COwnerList     ListOwners   ( unsigned int      vin ) const;
    int            CountOwners  ( unsigned int      vin ) const;
    
    
    friend ostream& operator << ( ostream &, const CRegister & );

private:
    struct Person;
    struct CCar {
        CCar( string rz = "", unsigned int vin = 0, Person *owner = NULL ): rz(rz), vin(vin), owner(owner) {}
        bool operator == ( const CCar & );
        
        string rz;
        unsigned int vin;
        vector<Person *> owners;
        Person *owner;
    };
    
    struct Person {
        Person( string name, string surname ): name(name), surname(surname) {}
        bool operator == ( const Person & ) const;
        bool operator < ( const Person & ) const;
        
        string name;
        string surname;
        vector<CCar *> plates;
        vector<CCar *> vins;
    };
    
    vector<Person *> m_ListByNames;
    vector<CCar *> m_ListByRZ;
    vector<CCar *> m_ListByVin;
    
    bool contentsRZ( const string & ) const;
    bool contentsVin( unsigned int ) const;
    void addPersonRZ( Person &, CCar * );
    void addPersonVin( Person &, CCar *);
    void removePersonCar( const CCar & );
    void DelCar( CCar & );
};

/*
 * CCarList class definition
 ------------------------------------------------------------------ */
string CCarList::RZ( void ) const {
    return plates.back();
}

unsigned int CCarList::VIN( void ) const {
    return vins.back();
}

bool CCarList::AtEnd( void ) const {
    return vins.rbegin() == vins.rend();
}

void CCarList::Next( void ) {
    if ( plates.size() != 0 ) {
        plates.pop_back();
        vins.pop_back();
    }
}

/* PRIVATE */
CCarList& CCarList::operator = ( const CCarList &n ) {
    if( this == &n ) return *this;
    
    plates = n.plates;
    vins   = n.vins;
    
    return *this;
}


/**
 * COwnerList class definition
 ------------------------------------------------------------------ */
string COwnerList::Name( void ) const {
    return names.back();
}

string COwnerList::Surname( void ) const {
    return surnames.back();
}

bool COwnerList::AtEnd( void ) const {
    return names.rend() == names.rbegin();
}

void COwnerList::Next( void ) {
    if( names.size() != 0 ) {
        names.pop_back();
        surnames.pop_back();
    }
}

COwnerList& COwnerList::operator = ( const COwnerList &n ) {
    if( this == &n ) return *this;
    
    names = n.names;
    surnames = n.surnames;
    
    return *this;
}

/* PRIVATE */


/**
 * CRegister class definition
 ------------------------------------------------------------------ */
CRegister::~CRegister( void ) {
    for ( auto &n : m_ListByNames ) delete n;
    for ( auto &r : m_ListByRZ ) delete r;
}

bool CRegister::AddCar( const string &rz, unsigned int vin, const string &name, const string &surname) {
    if ( contentsRZ( rz ) || contentsVin( vin ) ) return  false;
    
    Person *owner = new Person( name, surname );
    CCar   *car   = new CCar( rz, vin );
    auto   oIt    = lower_bound( m_ListByNames.begin(), m_ListByNames.end(), owner, [] ( const Person *l, const Person *r ) { return *l < *r; } );
    
    if ( oIt != m_ListByNames.end() && *(*oIt) == *owner ) { // majitel uz existuje
        car->owner = *oIt;
        car->owners.push_back( *oIt );
        addPersonRZ( *(*oIt), car );
        addPersonVin( *(*oIt), car );
        delete owner;
    } else { // novy majitel
        m_ListByNames.insert( oIt, owner );
        car->owner = owner;
        car->owners.push_back( owner );
        owner->plates.push_back( car );
        owner->vins.push_back( car );
    }
    
    auto rIt = lower_bound( m_ListByRZ.begin(), m_ListByRZ.end(), car, [] ( const CCar *l, const CCar *r ) { return l->rz < r->rz; } );
    m_ListByRZ.insert( rIt, car );
    
    auto vIt = lower_bound( m_ListByVin.begin(), m_ListByVin.end(), car, [] ( const CCar *l, const CCar *r) { return l->vin < r->vin; } );
    m_ListByVin.insert( vIt, car );
    
    return true;
}

bool CRegister::DelCar( const string &rz ) {
    if ( ! contentsRZ( rz ) ) return false;
    
    CCar tmpCar( rz );
    auto rIt = lower_bound( m_ListByRZ.begin(), m_ListByRZ.end(), &tmpCar, [] ( const CCar *l, const CCar *r ) { return l->rz < r->rz; } );
    
    CCar *del  = (*rIt);
    tmpCar.vin = del->vin;
    DelCar( *del );
    
    delete del;
    return true;
}

bool CRegister::DelCar( unsigned int vin ) {
    if ( ! contentsVin( vin ) ) return false;
    
    CCar tmpCar( "", vin );
    auto vIt     = lower_bound( m_ListByVin.begin(), m_ListByVin.end(), &tmpCar, [] ( const CCar *l, const CCar *r ) { return l->vin < r->vin; } );
    
    return DelCar( (*vIt)->rz );
}

bool CRegister::Transfer( const string &rz, const string &name, const string &surname ) {
    CCar tmpCar( rz );
    auto cIt = lower_bound( m_ListByRZ.begin(), m_ListByRZ.end(), &tmpCar, [] ( const CCar *l, const CCar *r ) { return l->rz < r->rz; } );
    
    if( cIt != m_ListByRZ.end() && (**cIt).rz == tmpCar.rz ) { // existujici auto
        Person *owner = new Person( name, surname );
        
        if ( *((*cIt)->owner) == *owner ) { // stejny majitel
            delete owner;
            return false;
        }

        auto oIt = lower_bound( m_ListByNames.begin(), m_ListByNames.end(), owner, [] ( const Person *l, const Person *r ) { return *l < *r; } );
        removePersonCar( **cIt );
        
        if ( oIt != m_ListByNames.end() && **oIt == *owner ) { // existujici majitel
            (*cIt)->owner = *oIt;
            (*cIt)->owners.push_back( *oIt );
            addPersonRZ( **oIt, *cIt);
            addPersonVin( **oIt, *cIt);
            delete owner;
        } else { // novy majitel
            (*cIt)->owner = owner;
            (*cIt)->owners.push_back( owner );
            m_ListByNames.insert( oIt, owner );
            owner->plates.push_back( *cIt );
            owner->vins.push_back( *cIt );
        }
        
        return true;
    }
    return false;
}

bool CRegister::Transfer( unsigned int vin, const string &name, const string &surname ) {
    if ( ! contentsVin( vin) ) return false;
    
    CCar tmp( "", vin );
    auto it = lower_bound(m_ListByVin.begin(), m_ListByVin.end(), &tmp, [] ( const CCar *l, const CCar *r) { return l->vin < r->vin; } );
    
    return Transfer( (*it)->rz, name, surname );
}

CCarList CRegister::ListCars( const string &name, const string &surname ) const {
    Person p( name, surname );
    vector<string> plates;
    vector<unsigned int> vins;
    auto it = lower_bound( m_ListByNames.begin(), m_ListByNames.end(), &p, [] ( const Person *l, const Person *r ) { return *l < *r; } );
    
    if( it != m_ListByNames.end() && **it == p ) {
        for( auto &c : (*it)->vins ) {
            plates.push_back( c->rz );
            vins.push_back( c->vin );
        }
    }
    
    return CCarList( plates, vins );
}

int CRegister::CountCars( const string &name, const string &surname ) const {
    Person p( name, surname );
    auto it = lower_bound( m_ListByNames.begin(), m_ListByNames.end(), &p, [] ( const Person *l, const Person *r ) { return *l < *r; } );
    
    return ( it != m_ListByNames.end() && **it == p ) ? (int) (*it)->plates.size() : 0;
}

COwnerList CRegister::ListOwners( const string &rz ) const {
    vector<string> names;
    vector<string> surnames;
    CCar c( rz );
    auto it = lower_bound( m_ListByRZ.begin(), m_ListByRZ.end(), &c, [] ( const CCar *l, const CCar *r ) { return l->rz < r->rz; } );
    
    if ( it != m_ListByRZ.end() && (*it)->rz == c.rz ) {
        for ( auto &o : (*it)->owners ) {
            names.push_back( o->name );
            surnames.push_back( o->surname );
        }
    }
    
    return COwnerList( names, surnames );
}

int CRegister::CountOwners( const string &rz ) const {
    CCar c( rz );
    auto it = lower_bound( m_ListByRZ.begin(), m_ListByRZ.end(), &c, [] ( const CCar *l, const CCar *r ) { return l->rz < r->rz; } );
    return ( it != m_ListByRZ.end() && (*it)->rz == c.rz ) ? (int) (*it)->owners.size() : 0;
}

COwnerList CRegister::ListOwners( unsigned int vin ) const {
    vector<string> names;
    vector<string> surnames;
    CCar c( "", vin );
    auto it = lower_bound( m_ListByVin.begin(), m_ListByVin.end(), &c, [] ( const CCar *l, const CCar *r ) { return l->vin < r->vin; } );
    
    if ( it != m_ListByVin.end() && (*it)->vin == c.vin ) {
        for ( auto &o : (*it)->owners ) {
            names.push_back( o->name );
            surnames.push_back( o->surname );
        }
    }
    
    return COwnerList( names, surnames );
}

int CRegister::CountOwners( unsigned int vin ) const {
    CCar c( "", vin );
    auto it = lower_bound( m_ListByVin.begin(), m_ListByVin.end(), &c, [] ( const CCar *l, const CCar *r ) { return l->vin < r->vin; } );
    return ( it != m_ListByVin.end() && (*it)->vin == c.vin ) ? (int) (*it)->owners.size() : 0;
}

ostream& operator << ( ostream &os, const CRegister &c ) {
    cout << "Persons" << endl;
    
    for ( auto &p : c.m_ListByNames ) cout << p->surname << " " << p->name << ", no. of p: " << p->plates.size() << ", v: " << p->vins.size() << endl;
    
    cout << "Plates" << endl;
    
    for ( auto &p : c.m_ListByRZ ) cout << p->rz << " " << p->owner->surname << " " << p->owner->name << endl;
    
    return os;
}

/* PRIVATE */
bool CRegister::contentsRZ( const string &rz ) const{
    CCar tmp( rz );
    return binary_search( m_ListByRZ.begin(), m_ListByRZ.end(), &tmp, [] ( const CCar *l, const CCar *r ) { return l->rz < r->rz; } );
}

bool CRegister::contentsVin( unsigned int vin ) const {
    CCar tmp( "", vin );
    return binary_search( m_ListByVin.begin(), m_ListByVin.end(), &tmp, [] ( const CCar *l, const CCar *r ) { return l->vin < r->vin; } );
}

void CRegister::DelCar( CCar &c ) {
    removePersonCar( c );
    
    auto rIt  = lower_bound( m_ListByRZ.begin(), m_ListByRZ.end(), &c, [] ( const CCar *l, const CCar *r ) { return l->rz < r->rz; } );
    auto vIt  = lower_bound( m_ListByVin.begin(), m_ListByVin.end(), &c, [] ( const CCar *l, const CCar *r ) { return l->vin < r->vin; } );
    
    if( rIt  != m_ListByRZ.end() && **rIt == c )  m_ListByRZ.erase( rIt );
    if( vIt  != m_ListByVin.end() && **vIt == c ) m_ListByVin.erase( vIt );
}


void CRegister::addPersonRZ( Person &p, CCar *c ) {
    auto it = lower_bound( p.plates.begin(), p.plates.end(), c, [] ( const CRegister::CCar *l, const CRegister::CCar *r ) { return l->rz < r->rz; } );
    p.plates.insert( it, c );
}

void CRegister::addPersonVin( Person &p, CCar *c ) {
    auto it = lower_bound( p.vins.begin(), p.vins.end(), c, [] ( const CRegister::CCar *l, CRegister::CCar *r ) { return l->vin < r->vin; } );
    p.vins.insert( it, c );
}

void CRegister::removePersonCar( const CCar &c ) {
    auto orIt = lower_bound( c.owner->plates.begin(), c.owner->plates.end(), &c, [] ( const CCar *l, const CCar *r ) { return l->rz < r->rz; } );
    auto ovIt = lower_bound( c.owner->vins.begin(), c.owner->vins.end(), &c, [] ( const CCar *l, const CCar *r ) {
        return l->vin < r->vin; } );
    
    if( orIt != c.owner->plates.end() && **orIt == c ) c.owner->plates.erase( orIt );
    if( ovIt != c.owner->vins.end() && **ovIt == c ) c.owner->vins.erase( ovIt );
}

bool CRegister::Person::operator == ( const Person &p ) const {
    return this->name == p.name && this->surname == p.surname;
}

bool CRegister::Person::operator < ( const Person &p ) const {
    if( this->surname == p.surname ) return this->name < p.name;
    return this->surname < p.surname;
}

bool CRegister::CCar::operator == ( const CCar &c ) {
    return this->rz == c.rz && this->vin == c.vin;
}



#ifndef __PROGTEST__

void testsN( void ) {
    CRegister b1;
    assert ( b1 . AddCar ( "ABC-12-34", 1000, "John", "Smith" ) == true );
    assert ( b1 . AddCar ( "ABC-32-22", 2000, "John", "Hacker" ) == true );
    assert ( b1 . AddCar ( "XYZ-11-22", 10, "Peter", "Smith" ) == true );
    assert ( b1 . CountCars ( "John", "Hacker" ) == 1 );
    for ( CCarList l = b1 . ListCars ( "John", "Hacker" ); ! l . AtEnd (); l . Next () )
        cout << l . RZ () << ", " << l . VIN () << endl;
}

void testsP( void ) {
    CRegister b1;
    assert ( b1 . AddCar ( "ABC-12-34", 1000, "John", "Smith" )  == true );
    assert ( b1 . AddCar ( "ABC-32-22", 2000, "John", "Hacker" ) == true );
    assert ( b1 . AddCar ( "ABC-33-22", 2001, "John", "Hacker" ) == true );
    assert ( b1 . AddCar ( "XYZ-11-22", 10, "Peter", "Smith" )   == true );
    assert ( b1 . AddCar ( "XYZ-11-22", 10, "Peter", "Smith" )   == false );
    
    CCarList l = b1 . ListCars ( "John", "Hacker" );
    
    assert( b1.CountOwners( "ABC-12-34" ) == 1 );
    assert( b1.CountOwners( 1000 ) == 1 );
    
    assert( b1.DelCar( "ABC-12-34" ) == true );
    assert( b1.DelCar( 2000 ) == true );
    assert( b1.DelCar( "ABC-12-34" ) == false );
    assert( b1.DelCar( 2000 ) == false );
    
    assert( b1.Transfer( "neexistujici", "Jan", "Dolezal" ) == false );
    assert( b1.Transfer( 12341234, "Jan", "Dolezal" ) == false );
    assert( b1.Transfer( 2000, "Jan", "Dolezal" ) == false );
    assert( b1.Transfer( "ABC-12-34", "Jan", "Dolezal" ) == false);
    
    assert( b1.Transfer( "XYZ-11-22", "John", "Hacker" ) == true );
    assert( b1.Transfer( "ABC-33-22", "Josef", "Dolezal" ) == true );
    
    assert( b1.CountOwners( "XYZ-11-22" ) == 2 );
    assert( b1.CountOwners( 10 ) == 2 );
    assert( b1.CountOwners( "ABC-33-22" ) == 2 );
    assert( b1.CountOwners( 2001 ) == 2 );
    
    assert( b1.CountCars( "Josef", "Dolezal" ) == 1);
    assert( b1.CountCars( "Deda", "Libor" ) == 0 );
    assert( b1.CountCars( "Peter", "Smith" ) == 0 );
    
    assert( b1.Transfer( "ABC-33-22", "Deda", "Libor" ) == true );
    assert( b1.CountCars( "Deda", "Libor" ) == 1);
    assert( b1.CountOwners( "ABC-33-22" ) == 3 );
    assert( b1.CountOwners( 2001 ) == 3 );
    
    
    
    cout << b1 << endl;
}

void testsV( void ) {
    CRegister b1;
    assert ( b1 . AddCar ( "ABC-12-34", 1000, "John", "Smith" ) == true );
    assert ( b1 . AddCar ( "ABC-32-22", 2000, "John", "Hacker" ) == true );
    assert ( b1 . AddCar ( "XYZ-11-22", 10, "Peter", "Smith" ) == true );
    assert ( b1 . CountCars ( "John", "Hacker" ) == 1 );
    for ( CCarList l = b1 . ListCars ( "John", "Hacker" ); ! l . AtEnd (); l . Next () )
        cout << l . RZ () << ", " << l . VIN () << endl;
    // the following license plate + VIN
    
    // ABC-32-22, 2000
    
    assert ( b1 . CountOwners ( "ABC-12-34" ) == 1 );
    for ( COwnerList l = b1 . ListOwners ( "ABC-12-34" ); ! l . AtEnd (); l . Next () )
        cout << l . Surname () << ", " << l . Name () << endl;
    // the following 1 owners in that order:
    
    // Smith, John
    
    assert ( b1 . CountOwners ( 10 ) == 1 );
    for ( COwnerList l = b1 . ListOwners ( 10 ); ! l . AtEnd (); l . Next () )
        cout << l . Surname () << ", " << l . Name () << endl;
    // the following 1 owners in that order:
    
    // Smith, Peter
    
    assert ( b1 . Transfer ( "XYZ-11-22", "John", "Hacker" ) == true );
    assert ( b1 . Transfer ( 10, "Will", "Smith" ) == true );
    assert ( b1 . Transfer ( "XYZ-11-22", "John", "Hacker" ) == true );
    assert ( b1 . AddCar ( "XYZ-99-88", 20, "John", "Smith" ) == true );
    assert ( b1 . CountCars ( "John", "Smith" ) == 2 );
    for ( CCarList l = b1 . ListCars ( "John", "Smith" ); ! l . AtEnd (); l . Next () )
        cout << l . RZ () << ", " << l . VIN () << endl;
    // the following 2 license plates + VINs, in any order:
    
    // ABC-12-34, 1000
    // XYZ-99-88, 20
    
    assert ( b1 . CountCars ( "John", "Hacker" ) == 2 );
    for ( CCarList l = b1 . ListCars ( "John", "Hacker" ); ! l . AtEnd (); l . Next () )
        cout << l . RZ () << ", " << l . VIN () << endl;
    // the following 2 license plates + VINs, in any order:
    
    // ABC-32-22, 2000
    // XYZ-11-22, 10
    
    assert ( b1 . CountCars ( "Peter", "Smith" ) == 0 );
    for ( CCarList l = b1 . ListCars ( "Peter", "Smith" ); ! l . AtEnd (); l . Next () )
        cout << l . RZ () << ", " << l . VIN () << endl;
    // empty output
    
    assert ( b1 . CountOwners ( 10 ) == 4 );
    for ( COwnerList l = b1 . ListOwners ( 10 ); ! l . AtEnd (); l . Next () )
        cout << l . Surname () << ", " << l . Name () << endl;
    // the following 4 owners in that order:
    
    // Hacker, John
    // Smith, Will
    // Hacker, John
    // Smith, Peter
    
    assert ( b1 . CountOwners ( "XYZ-11-22" ) == 4 );
    for ( COwnerList l = b1 . ListOwners ( "XYZ-11-22" ); ! l . AtEnd (); l . Next () )
        cout << l . Surname () << ", " << l . Name () << endl;
    // the following 4 owners in that order:
    
    // Hacker, John
    // Smith, Will
    // Hacker, John
    // Smith, Peter
    
    assert ( b1 . Transfer ( "XYZ-11-22", "Jane", "Black" ) == true );
    assert ( b1 . CountCars ( "Jane", "Black" ) == 1 );
    for ( CCarList l = b1 . ListCars ( "Jane", "Black" ); ! l . AtEnd (); l . Next () )
        cout << l . RZ () << ", " << l . VIN () << endl;
    // the following license plate + VIN
    
    // XYZ-11-22, 10
    
    assert ( b1 . CountCars ( "John", "Smith" ) == 2 );
    for ( CCarList l = b1 . ListCars ( "John", "Smith" ); ! l . AtEnd (); l . Next () )
        cout << l . RZ () << ", " << l . VIN () << endl;
    // the following 2 license plates + VINs, in any order:
    
    // ABC-12-34, 1000
    // XYZ-99-88, 20
    
    assert ( b1 . CountOwners ( 10 ) == 5 );
    for ( COwnerList l = b1 . ListOwners ( 10 ); ! l . AtEnd (); l . Next () )
        cout << l . Surname () << ", " << l . Name () << endl;
    // the following 5 owners in that order:
    
    // Black, Jane
    // Hacker, John
    // Smith, Will
    // Hacker, John
    // Smith, Peter
    
    assert ( b1 . CountOwners ( "XYZ-11-22" ) == 5 );
    for ( COwnerList l = b1 . ListOwners ( "XYZ-11-22" ); ! l . AtEnd (); l . Next () )
        cout << l . Surname () << ", " << l . Name () << endl;
    // the following 5 owners in that order:
    
    // Black, Jane
    // Hacker, John
    // Smith, Will
    // Hacker, John
    // Smith, Peter
    
    assert ( b1 . DelCar ( "XYZ-11-22" ) == true );
    assert ( b1 . DelCar ( 1000 ) == true );
    assert ( b1 . CountCars ( "Jane", "Black" ) == 0 );
    for ( CCarList l = b1 . ListCars ( "Jane", "Black" ); ! l . AtEnd (); l . Next () )
        cout << l . RZ () << ", " << l . VIN () << endl;
    // empty output
    
    assert ( b1 . AddCar ( "XYZ-11-22", 30, "George", "White" ) == true );
    assert ( b1 . CountOwners ( 30 ) == 1 );
    for ( COwnerList l = b1 . ListOwners ( 30 ); ! l . AtEnd (); l . Next () )
        cout << l . Surname () << ", " << l . Name () << endl;
    // the following 1 owners in that order:
    
    // White, George
    
    assert ( b1 . CountOwners ( "XYZ-11-22" ) == 1 );
    for ( COwnerList l = b1 . ListOwners ( "XYZ-11-22" ); ! l . AtEnd (); l . Next () )
        cout << l . Surname () << ", " << l . Name () << endl;
    // the following 1 owners in that order:
    
    // White, George
    
    
    CRegister b2;
    assert ( b2 . AddCar ( "ABC-12-34", 10, "John", "Smith" ) == true );
    assert ( b2 . AddCar ( "ABC-32-22", 20, "John", "Hacker" ) == true );
    assert ( b2 . AddCar ( "XYZ-11-22", 30, "Peter", "Smith" ) == true );
    assert ( b2 . AddCar ( "XYZ-11-22", 30, "Jane", "Black" ) == false );
    assert ( b2 . AddCar ( "XYZ-11-22", 50, "Jane", "Black" ) == false );
    assert ( b2 . AddCar ( "ZZZ-11-22", 30, "Jane", "Black" ) == false );
    assert ( b2 . DelCar ( "AAA-11-11" ) == false );
    assert ( b2 . DelCar ( 9999 ) == false );
    assert ( b2 . DelCar ( "ABC-32-22" ) == true );
    assert ( b2 . DelCar ( 20 ) == false );
    assert ( b2 . DelCar ( 30 ) == true );
    assert ( b2 . DelCar ( "XYZ-11-22" ) == false );
    assert ( b2 . Transfer ( "BBB-99-99", "John", "Smith" ) == false );
    assert ( b2 . Transfer ( "ABC-12-34", "John", "Smith" ) == false );
    assert ( b2 . Transfer ( 9999, "John", "Smith" ) == false );
    assert ( b2 . Transfer ( 10, "John", "Smith" ) == false );
    assert ( b2 . CountCars ( "George", "White" ) == 0 );
    for ( CCarList l = b2 . ListCars ( "George", "White" ); ! l . AtEnd (); l . Next () )
        cout << l . RZ () << ", " << l . VIN () << endl;
    // empty output
    
    assert ( b2 . CountOwners ( "AAA-AA-AA" ) == 0 );
    for ( COwnerList l = b2 . ListOwners ( "AAA-AA-AA" ); ! l . AtEnd (); l . Next () )
        cout << l . Surname () << ", " << l . Name () << endl;
    // the following 0 owners in that order:
    
    
    assert ( b2 . CountOwners ( 9999 ) == 0 );
    for ( COwnerList l = b2 . ListOwners ( 9999 ); ! l . AtEnd (); l . Next () )
        cout << l . Surname () << ", " << l . Name () << endl;
    // the following 0 owners in that order:
}

int main ( void )
{
    testsP();
    return 0;
}
#endif /* __PROGTEST__ */