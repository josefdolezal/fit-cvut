/* author: josef dolezal */
/* git: https://github.com/josefdolezal */

#include <iostream>
#include <vector>

using namespace std;

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



struct CCar {
    CCar( string rz = "", unsigned int vin = 0 ): rz(rz), vin(vin) {}
    bool operator == ( const CCar & );
    bool operator < ( const CCar &c ) { return this->rz < c.rz; }
    
    string rz;
    unsigned int vin;
    
    friend ostream& operator << ( ostream &os, CCar &c ) {
        os << "{ RZ: " << c.rz << ", VIN:" << c.vin << " }";
        return os;
    }
};




void test_ccarh();
void test_ccar();
void test_int();

int main( void ) {
    
    test_ccar();
    
    victor<CCar *> a;
    
    for ( int i = 0; i < 10; i++)
        a.push_back( new CCar( "a", 99 ) );
    
    while( a.begin() != a.end() ) {
        delete a.back();
        a.pop_back();
    }
    
    return 0;
}

void test_ccar() {
    victor<CCar> a;
    
    a.push_back( CCar( "a", 99 ) );
    a.push_back( CCar( "c", 99 ) );
    CCar c( "b", 99 );
    
    a.insert( a.lower_bound( c, [] ( const CCar &l, const CCar &r ) { return l.rz < r.rz; } ), c );
    
    //cout << a << endl;
}

void test_ccarh() {
    victor<CCar *> a;
    CCar *cc = new CCar( "tst",  90 );
    CCar *dd = new CCar( "zzz",  90 );
    CCar *ff = new CCar( "aaa", 100 );
    
    a.push_back( cc );
    a.push_back( dd );
    
    a.insert( a.lower_bound( ff, [] ( const CCar *l, const CCar *r ) { return l->rz < r->rz; } ), ff);
    
    while ( a.begin() != a.end() ) {
        cout << * ( a.back() ) << endl;
        a.pop_back();
    }
    
    //cout << a << endl;
    return;
}

void test_int() {
    victor<int> a;
    
    for ( int i = 0; i < 85; i++ ) {
        a.push_back( i );
    }
    
    //cout << a << endl;
    
    cout << a.lower_bound( 101 ) << endl;
    cout << a.lower_bound( 200, [] ( const int &l, const int &r ) { return l < r; } ) << endl;
    cout << a.eq( 84, 84, [] ( const int &l, const int &r ) { return l == r; } ) << endl;
    
    a.insert( a.lower_bound( 10 ), 10);
    
    //cout << a << endl;
    
    
    while ( a.begin() != a.end() ) {
        a.pop_back();
    }
    
    
    //cout << a << endl;
}
