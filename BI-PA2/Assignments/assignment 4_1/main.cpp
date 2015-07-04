/* author: josef dolezal */
/* git: https://github.com/josefdolezal */

#ifndef __PROGTEST__
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <iomanip>
using namespace std;
#endif /* __PROGTEST__ */


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

//OPRAVIT VYPIS LISTU ( ASI RETURNU )


/*
 * BEGIN ViCTOR
 ------------------------------------------------------------------ */
/* Vector Improved */
template<class T>
class victor {
public:
    victor              ( void ): m_maxI( 2 ), m_curI( 0 )
                            { m_list = new T[m_maxI]; }
    victor              ( victor const & );
    ~victor             ( void )
                            { delete[] m_list; }
    int  size           ( void ) const;
    void push_back      ( const T & );
    void pop_back       ( void );
    int  begin          ( void ) const { return 0; }
    int  end            ( void ) const { return m_curI; }
    int  lower_bound    ( const T & ) const;
    template<typename Compare>
    int  lower_bound    ( const T &,   Compare ) const;
    bool eq             ( const T &, const int ) const;
    template<typename Compare>
    bool eq             ( const T &, const int, Compare ) const; //chx
    void insert         ( const int, const T & ); //chx
    T&   back           ( void ) const;
    T&   get            ( int ) const;
    void erase          ( int );
    
    victor<T>& operator = ( victor<T> const & );
    template<class X>
    friend ostream& operator << ( ostream &, const victor<X> & );
private:
    T * m_list;
    int m_maxI;
    int m_curI;
    
    void realloc( void );
};

template<class T>
victor<T>::victor( victor<T> const &o ) {
    m_maxI = o.m_maxI;
    m_list = new T[m_maxI];
    m_curI = 0;
    
    for ( int i = 0; i < o.size(); i++ ) {
        push_back( o.get( i ) );
    }
    
}

template<class T>
victor<T>& victor<T>::operator = ( victor<T> const &o ) {
    if ( this == &o ) return *this;
    
    delete[] m_list;
    m_maxI = o.m_maxI;
    m_curI = 0;
    m_list = new T[m_maxI];
    
    for ( int i = 0; i < o.size(); i++ ) {
        push_back( o.get( i ) );
    }
    
    return *this;
}

template<class T>
int victor<T>::size( void ) const {
    return m_curI;
}

/* LOWER BOUND */
template<class T>
int victor<T>::lower_bound( const T &val ) const {
    int count = m_curI;
    int first = 0;
    int it    = 0;
    int step  = 0;
    
    while (count > 0) {
        it = first;
        step = count / 2;
        it += step;
        if ( m_list[it] < val ) {
            first = ++it;
            count -= step + 1;
        } else count = step;
    }
    return first;
}

template<class T> template<typename Compare>
int victor<T>::lower_bound( const T &val, Compare comp ) const {
    int count = m_curI;
    int first = 0;
    int it    = 0;
    int step  = 0;
    
    while (count > 0) {
        it = first;
        step = count / 2;
        it += step;
        if ( comp( m_list[it], val ) ) {
            first = ++it;
            count -= step + 1;
        } else count = step;
    }
    return first;
}

/* EQ */
template<class T> template<typename Compare>
bool victor<T>::eq( const T &val, const int it, Compare comp ) const {
    if( it < 0 || it >= m_curI ) return false;
    return comp( val, m_list[it] );
    
}

template<class T>
bool victor<T>::eq( const T &val, const int it ) const {
    if( it < 0 || it >= m_curI ) return false;
    return val == m_list[it];
}


/* INSERT */
template<class T>
void victor<T>::push_back( const T &a ) {
    if ( m_curI + 1 == m_maxI ) realloc();
    m_list[m_curI++] = a;
}

template<class T>
void victor<T>::insert( const int it, const T &val ) {
    if ( it < 0 )       { insert( 0, val ); return; }
    if ( it > m_curI )  { push_back( val ); return; }
    if ( m_curI + 1 == m_maxI ) realloc();
    
    for ( int i = m_curI++; i > it; i-- )
        m_list[i] = m_list[i-1];
    
    m_list[it] = val;
}

/* REMOVE */
template<class T>
void victor<T>::pop_back( void ) {
    if ( m_curI < 1 ) return; // empty list
    m_curI--;
}

template<class T>
void victor<T>::erase( int it ) {
    for ( int i = it; i < m_curI-1; i++ )
        m_list[i] = m_list[i+1];
    
    m_curI--;
}

/* PRIVATE */
template<class T>
void victor<T>::realloc( void ) {
    T * tmp = new T[(m_maxI*=2)]; //chx
    for ( int i = 0; i < m_curI ; i++ )
        tmp[i] = m_list[i];
    
    delete [] m_list;
    m_list = tmp;
}

/* GET */
template<class T>
T& victor<T>::back( void ) const {
    return m_curI == 0 ? m_list[m_curI] : m_list[m_curI-1];
}

template<class T>
T& victor<T>::get( int it ) const {
    return m_list[it];
}


/*
 * END ViCTOR
 ------------------------------------------------------------------ */



class CCarList
{
public:
    CCarList( void ): iter(0) {}
    CCarList( victor<Rope> &p ): plates(p), iter(0) {}
    CCarList( const CCarList &c ): plates( c.plates ), iter(0) {}
    const char *   RZ           ( void ) const;
    bool           AtEnd        ( void ) const;
    void           Next         ( void );
    
    CCarList& operator = ( const CCarList & );
    friend ostream& operator << ( ostream &, const CCarList & );
private:
    victor<Rope> plates;
    int iter;
};

class COwnerList
{
public:
    COwnerList( void ): iter(0) {}
    COwnerList( victor<Rope> &n, victor<Rope> &s ): names(n), surnames(s), iter(0) {}
    COwnerList ( const COwnerList &c ): names(c.names), surnames(c.surnames), iter(0) {}
    const char *   Name         ( void ) const;
    const char *   Surname      ( void ) const;
    bool           AtEnd        ( void ) const;
    void           Next         ( void );
    
    COwnerList& operator = ( const COwnerList & );
    friend ostream& operator << ( ostream &, COwnerList & );
private:
    victor<Rope> names;
    victor<Rope> surnames;
    int iter;
};

class CRegister
{
public:
    CRegister    ( void ) {}
    CRegister    ( CRegister& );
    
    ~CRegister    ( void );
    bool           AddCar       ( const char *    rz,
                                 const char  *    name,
                                 const char  *    surname );
    bool           DelCar       ( const char *    rz );
    bool           Transfer     ( const char *    rz,
                                 const char  *    nName,
                                 const char  *    nSurname );
    CCarList       ListCars     ( const char *    name,
                                 const char  *    surname ) const;
    int            CountCars    ( const char *    name,
                                 const char  *    surname ) const;
    COwnerList     ListOwners   ( const char *    RZ ) const;
    int            CountOwners  ( const char *    RZ ) const;

    CRegister& operator = ( const CRegister & );
    friend ostream& operator << ( ostream &, const CRegister & );
    
private:
    struct Person;
    struct CCar {
        CCar( Rope rz = "", Person *owner = NULL ): rz(rz), owner(owner) {}
        bool operator == ( const CCar & );
        
        Rope rz;
        victor<Person *> owners;
        Person *owner;
    };
    
    struct Person {
        Person( Rope name, Rope surname ): name(name), surname(surname) {}
        bool operator == ( const Person & ) const;
        bool operator < ( const Person & ) const;
        
        Rope name;
        Rope surname;
        victor<CCar *> plates;
    };
    
    victor<Person *> m_ListByNames;
    victor<CCar *> m_ListByRZ;
    
    bool contentsRZ( const Rope & ) const;
    void addPersonRZ( Person &, CCar * );
    void removePersonCar( const CCar & );
    void DelCar( CCar & );
    void deepCp( const CRegister& );
    void destruct( void );
};

/*
 * CCarList class definition
 ------------------------------------------------------------------ */
const char * CCarList::RZ( void ) const {
    return plates.get( iter );
}

bool CCarList::AtEnd( void ) const {
    return iter == plates.end();
}

void CCarList::Next( void ) {
    if ( iter < plates.size() ) iter++;
}

/* PRIVATE */
CCarList& CCarList::operator = ( const CCarList &n ) {
    if( this == &n ) return *this;
    
    plates = n.plates;
    iter   = 0;
    
    return *this;
}


/**
 * COwnerList class definition
 ------------------------------------------------------------------ */
const char * COwnerList::Name( void ) const {
    return names.get( iter );
}

const char * COwnerList::Surname( void ) const {
    return surnames.get( iter );
}

bool COwnerList::AtEnd( void ) const {
    return iter == names.end();
}

void COwnerList::Next( void ) {
    if( iter < names.size() ) iter++;
}

COwnerList& COwnerList::operator = ( const COwnerList &n ) {
    if( this == &n ) return *this;
    
    names    = n.names;
    surnames = n.surnames;
    iter     = 0;
    
    return *this;
}

/* PRIVATE */


/**
 * CRegister class definition
 ------------------------------------------------------------------ */
CRegister::CRegister( CRegister &c ) {
    deepCp( c );
}

CRegister::~CRegister( void ) {
    destruct();
}

bool CRegister::AddCar( const char * rz, const char * name, const char * surname) {
    if ( contentsRZ( rz ) ) return  false;
    
    Person *owner = new Person( name, surname );
    CCar   *car   = new CCar( rz );
    int    oIt    = m_ListByNames.lower_bound( owner, [] ( const Person *l, const Person *r ) { return *l < *r; } );
    
    if ( oIt != m_ListByNames.end() &&  m_ListByNames.eq( owner, oIt, [] ( const Person *l, const Person *r ) { return *l == *r; } ) ) { // majitel uz existuje
        car->owner = m_ListByNames.get( oIt );
        car->owners.push_back( m_ListByNames.get( oIt ) );
        addPersonRZ( *(m_ListByNames.get( oIt )), car );
        delete owner;
    } else { // novy majitel
        m_ListByNames.insert( oIt, owner );
        car->owner = owner;
        car->owners.push_back( owner );
        owner->plates.push_back( car );
    }
    
    int rIt = m_ListByRZ.lower_bound( car, [] ( const CCar *l, const CCar *r ) { return l->rz < r->rz; } );
    m_ListByRZ.insert( rIt, car );
    
    return true;
}

bool CRegister::DelCar( const char *rz ) {
    if ( ! contentsRZ( rz ) ) return false;
    
    CCar tmpCar( rz );
    int rIt = m_ListByRZ.lower_bound( &tmpCar, [] ( const CCar *l, const CCar *r ) { return l->rz < r->rz; } );
    
    CCar *del  = m_ListByRZ.get( rIt );
    DelCar( *del );
    
    delete del;
    return true;
}

bool CRegister::Transfer( const char *rz, const char *name, const char *surname ) {
    CCar tmpCar( rz );
    int cIt = m_ListByRZ.lower_bound( &tmpCar, [] ( const CCar *l, const CCar *r ) { return l->rz < r->rz; } );
    
    if( cIt != m_ListByRZ.end() && m_ListByRZ.eq( &tmpCar, cIt, [] ( const CCar *l, const CCar *r ) { return l->rz == r->rz; } ) ) { // existujici auto
        Person *owner = new Person( name, surname );
        
        if ( *(m_ListByRZ.get( cIt )->owner) == *owner ) { // stejny majitel
            delete owner;
            return false;
        }
        
        int oIt = m_ListByNames.lower_bound( owner, [] ( const Person *l, const Person *r ) { return *l < *r; } );
        removePersonCar( *(m_ListByRZ.get( cIt )) );
        
        if ( oIt != m_ListByNames.end() && m_ListByNames.eq( owner, oIt, [] ( const Person *l, const Person *r ) { return *l == *r; } ) ) { // existujici majitel
            m_ListByRZ.get( cIt )->owner = m_ListByNames.get( oIt );
            m_ListByRZ.get( cIt )->owners.push_back( m_ListByNames.get( oIt ) );
            addPersonRZ( *( m_ListByNames.get( oIt ) ), m_ListByRZ.get( cIt ) );
            delete owner;
        } else { // novy majitel
            m_ListByRZ.get( cIt )->owner = owner;
            m_ListByRZ.get( cIt )->owners.push_back( owner );
            m_ListByNames.insert( oIt, owner );
            owner->plates.push_back( m_ListByRZ.get( cIt ) );
        }
        
        return true;
    }
    return false;
}

CCarList CRegister::ListCars( const char *name, const char *surname ) const {
    Person p( name, surname );
    victor<Rope> plates;
    int it = m_ListByNames.lower_bound( &p, [] ( const Person *l, const Person *r ) { return *l < *r; } );
    
    if( it != m_ListByNames.end() && m_ListByNames.eq( &p, it, [] ( const Person *l, const Person *r ) { return *l == *r; } ) ) {
        for( int i = m_ListByNames.get( it )->plates.size() - 1; i >= 0; i-- )
            plates.push_back( m_ListByNames.get( it )->plates.get( i )->rz );
    }
    
    return CCarList( plates );
}

int CRegister::CountCars( const char *name, const char *surname ) const {
    Person p( name, surname );
    int it = m_ListByNames.lower_bound( &p, [] ( const Person *l, const Person *r ) { return *l < *r; } );
    
    return ( it != m_ListByNames.end() && m_ListByNames.eq( &p, it, [] ( const Person *l, const Person *r ) { return *l == *r; } ) ) ? (int) m_ListByNames.get( it )->plates.size() : 0;
}

COwnerList CRegister::ListOwners( const char *rz ) const {
    victor<Rope> names;
    victor<Rope> surnames;
    CCar c( rz );
    int it = m_ListByRZ.lower_bound( &c, [] ( const CCar *l, const CCar *r ) { return l->rz < r->rz; } );
    
    if ( it != m_ListByRZ.end() && m_ListByRZ.get( it )->rz == c.rz ) {
        for ( int i = m_ListByRZ.get( it )->owners.size() - 1; i >= 0; i-- ) {
            names.push_back( m_ListByRZ.get( it )->owners.get( i )->name );
            surnames.push_back( m_ListByRZ.get( it )->owners.get( i )->surname );
        }
    }
    
    return COwnerList( names, surnames );
}

int CRegister::CountOwners( const char *rz ) const {
    CCar c( rz );
    int it = m_ListByRZ.lower_bound( &c, [] ( const CCar *l, const CCar *r ) { return l->rz < r->rz; } );
    
    return ( it != m_ListByRZ.end() &&  m_ListByRZ.get( it )->rz == c.rz ) ? (int) m_ListByRZ.get( it )->owners.size() : 0;
}

ostream& operator << ( ostream &os, const CRegister &c ) {
    cout << "Persons" << endl;
    
    for ( int i = 0; i < c.m_ListByNames.size(); i++ ) cout << c.m_ListByNames.get( i )->surname << " " << c.m_ListByNames.get( i )->name << ", no. of p: " << c.m_ListByNames.get( i )->plates.size() << endl;
    
    cout << "Plates" << endl;
    
    for ( int i = 0; i < c.m_ListByRZ.size(); i++ ) cout << c.m_ListByRZ.get( i )->rz << " " << c.m_ListByRZ.get( i )->owner->surname << " " << c.m_ListByRZ.get( i )->owner->name << endl;
    
    return os;
}

/* PRIVATE */
bool CRegister::contentsRZ( const Rope &rz ) const{
    CCar tmp( rz );
    int it = m_ListByRZ.lower_bound( &tmp, [] ( const CCar *l, const CCar *r ) { return l->rz < r->rz; } );
    
    return it != m_ListByRZ.end() && m_ListByRZ.get( it )->rz == rz;
}

void CRegister::DelCar( CCar &c ) {
    removePersonCar( c );
    
    int rIt  = m_ListByRZ.lower_bound( &c, [] ( const CCar *l, const CCar *r ) { return l->rz < r->rz; } );
    if( rIt  != m_ListByRZ.end() && *( m_ListByRZ.get( rIt ) ) == c ) m_ListByRZ.erase( rIt );
}

void CRegister::addPersonRZ( Person &p, CCar *c ) {
    int it = p.plates.lower_bound( c, [] ( const CRegister::CCar *l, const CRegister::CCar *r ) { return l->rz < r->rz; } );
    p.plates.insert( it, c );
}

void CRegister::removePersonCar( const CCar &c ) {
    CCar tmp = c;
    int orIt = c.owner->plates.lower_bound( &tmp, [] ( const CCar *l, const CCar *r ) { return l->rz < r->rz; } );

    if( orIt != c.owner->plates.end() && *( c.owner->plates.get( orIt ) ) == c ) c.owner->plates.erase( orIt );
}

void CRegister::deepCp( const CRegister &c ) {
    for ( int i = 0; i < c.m_ListByNames.size(); i++ ) {
        Person *tmpOw = c.m_ListByNames.get( i );
        Person *cpOw  = new Person( tmpOw->name, tmpOw->surname );
        
        m_ListByNames.push_back( cpOw );
        
        // kazdemu uzivateli vlozi jeho auta
        for ( int j = 0; j < tmpOw->plates.size(); j++ ) {
            int itCar = m_ListByRZ.lower_bound( tmpOw->plates.get( j ), [] ( const CCar *l, const CCar *r ) { return l->rz < r->rz; } );
            
            if( itCar != m_ListByRZ.end() && *(m_ListByRZ.get( itCar )) == *(tmpOw->plates.get( j )) ) { // auto uz tam je
                //chyba ???
            } else { //auto tam jeste neni
                CCar *cpCC = new CCar( tmpOw->plates.get( j )->rz, cpOw );
                m_ListByRZ.insert( itCar, cpCC );
                cpCC->owners.push_back( cpOw );
                cpCC->owner = cpOw;
                addPersonRZ( *cpOw, cpCC );
                //int itPlate = cpOw->plates.lower_bound( cpCC, [] ( const CCar *l, const CCar *r ) { return l->rz < r->rz; } );
                //if( itPlate != )
            }
        }
    }
}

void CRegister::destruct( void ) {
    while ( m_ListByNames.begin() != m_ListByNames.end() )  { delete m_ListByNames.back(); m_ListByNames.pop_back(); }
    while ( m_ListByRZ.begin() != m_ListByRZ.end() )  { delete m_ListByRZ.back(); m_ListByRZ.pop_back(); };
}

CRegister& CRegister::operator = ( const CRegister &o ) {
    if( this == &o ) return *this;
    
    destruct();
    deepCp( o );

    return *this;
}

bool CRegister::Person::operator == ( const Person &p ) const {
    return this->name == p.name && this->surname == p.surname;
}

bool CRegister::Person::operator < ( const Person &p ) const {
    if( this->surname == p.surname ) return this->name < p.name;
    return this->surname < p.surname;
}

bool CRegister::CCar::operator == ( const CCar &c ) {
    return this->rz == c.rz;
}



#ifndef __PROGTEST__
void testsP2( void ) {
    CRegister  b0;
    b0 . AddCar ( "ABC-12-34", "John", "Smith" );
    b0 . AddCar ( "ABC-12-35", "John", "Smith" );
    b0 . AddCar ( "ABC-12-36", "John", "Smith" );
    b0 . DelCar( "ABC-12-34" );
    b0 . DelCar( "ABC-12-35" );
    
    for ( CCarList l = b0 . ListCars ( "John", "Smith" ); ! l . AtEnd (); l . Next () )
        cout << l . RZ () << endl;
}
void testsP( void ) {
    char name[50], surname[50];
    CRegister  b0;
    assert ( b0 . AddCar ( "ABC-12-34", "John", "Smith" ) == true );
    strncpy ( name, "John", sizeof ( name ) );
    strncpy ( surname, "Hacker", sizeof ( surname ) );
    assert ( b0 . AddCar ( "ABC-32-22", name, surname ) == true );
    strncpy ( name, "Peter", sizeof ( name ) );
    strncpy ( surname, "Smith", sizeof ( surname ) );
    assert ( b0 . AddCar ( "XYZ-11-22", name, surname ) == true );
    assert ( b0 . CountCars ( "John", "Hacker" ) == 1 );
    for ( CCarList l = b0 . ListCars ( "John", "Hacker" ); ! l . AtEnd (); l . Next () )
        cout << l . RZ () << endl;
}

void testsV( void ) {
    char name[50], surname[50];
    CRegister  b0;
    assert ( b0 . AddCar ( "ABC-12-34", "John", "Smith" ) == true );
    strncpy ( name, "John", sizeof ( name ) );
    strncpy ( surname, "Hacker", sizeof ( surname ) );
    assert ( b0 . AddCar ( "ABC-32-22", name, surname ) == true );
    strncpy ( name, "Peter", sizeof ( name ) );
    strncpy ( surname, "Smith", sizeof ( surname ) );
    assert ( b0 . AddCar ( "XYZ-11-22", name, surname ) == true );
    assert ( b0 . CountCars ( "John", "Hacker" ) == 1 );
    for ( CCarList l = b0 . ListCars ( "John", "Hacker" ); ! l . AtEnd (); l . Next () )
        cout << l . RZ () << endl;
    // the following license plate
    
    // ABC-32-22
    
    assert ( b0 . CountOwners ( "ABC-12-34" ) == 1 );
    for ( COwnerList l = b0 . ListOwners ( "ABC-12-34" ); ! l . AtEnd (); l . Next () )
        cout << l . Surname () << ", " << l . Name () << endl;
    // the following 1 owners in that order:
    
    // Smith, John
    
    CRegister b1 ( b0 );
    assert ( b0 . Transfer ( "XYZ-11-22", "John", "Hacker" ) == true );
    assert ( b0 . Transfer ( "XYZ-11-22", "Will", "Smith" ) == true );
    assert ( b1 . Transfer ( "XYZ-11-22", "John", "Smith" ) == true );
    assert ( b0 . CountOwners ( "XYZ-11-22" ) == 3 );
    for ( COwnerList l = b0 . ListOwners ( "XYZ-11-22" ); ! l . AtEnd (); l . Next () )
        cout << l . Surname () << ", " << l . Name () << endl;
    // the following 3 owners in that order:
    
    // Smith, Will
    // Hacker, John
    // Smith, Peter
    
    assert ( b1 . CountOwners ( "XYZ-11-22" ) == 2 );
    for ( COwnerList l = b1 . ListOwners ( "XYZ-11-22" ); ! l . AtEnd (); l . Next () )
        cout << l . Surname () << ", " << l . Name () << endl;
    // the following 2 owners in that order:
    
    // Smith, John
    // Smith, Peter
    
    b1 = b0;
    assert ( b0 . DelCar ( "XYZ-11-22" ) == true );
    assert ( b1 . DelCar ( "ABC-12-34" ) == true );
    assert ( b0 . CountCars ( "John", "Smith" ) == 1 );
    for ( CCarList l = b0 . ListCars ( "John", "Smith" ); ! l . AtEnd (); l . Next () )
        cout << l . RZ () << endl;
    // the following license plate
    
    // ABC-12-34
    
    assert ( b1 . CountCars ( "John", "Smith" ) == 0 );
    for ( CCarList l = b1 . ListCars ( "John", "Smith" ); ! l . AtEnd (); l . Next () )
        cout << l . RZ () << endl;
    // empty output
    
    
    CRegister  b2;
    assert ( b2 . AddCar ( "ABC-12-34", "John", "Smith" ) == true );
    assert ( b2 . AddCar ( "ABC-32-22", "John", "Hacker" ) == true );
    assert ( b2 . AddCar ( "XYZ-11-22", "Peter", "Smith" ) == true );
    assert ( b2 . AddCar ( "XYZ-11-22", "Jane", "Black" ) == false );
    assert ( b2 . DelCar ( "AAA-11-11" ) == false );
    assert ( b2 . DelCar ( "XYZ-11-22" ) == true );
    assert ( b2 . Transfer ( "BBB-99-99", "John", "Smith" ) == false );
    assert ( b2 . Transfer ( "ABC-12-34", "John", "Smith" ) == false );
    assert ( b2 . Transfer ( "XYZ-11-22", "John", "Smith" ) == false );
    assert ( b2 . CountCars ( "George", "White" ) == 0 );
    for ( CCarList l = b2 . ListCars ( "George", "White" ); ! l . AtEnd (); l . Next () )
        cout << l . RZ () << endl;
    // empty output
    
    assert ( b2 . CountOwners ( "AAA-AA-AA" ) == 0 );
    for ( COwnerList l = b2 . ListOwners ( "AAA-AA-AA" ); ! l . AtEnd (); l . Next () )
        cout << l . Surname () << ", " << l . Name () << endl;
    // the following 0 owners in that order:
}

void testsCopy() {
    victor<Rope> names;
    victor<Rope> surnames;
    
    names.push_back( "sdasdsad" );
    names.push_back( "sdasdsad" );
    names.push_back( "sdasdsad" );
    names.push_back( "sdasdsad" );
    names.push_back( "sdasdsad" );
    surnames.push_back( "qsdasdsad" );
    surnames.push_back( "qsdasdaad" );
    surnames.push_back( "qsdasdsad" );
    surnames.push_back( "qsdasdsad" );
    surnames.push_back( "qsdasdsad" );
    
    COwnerList b( names, surnames );
    COwnerList a;
    a = b;
}

int main ( void )
{
    testsV();
    //testsCopy();
    
    return 0;
}
#endif /* __PROGTEST__ */