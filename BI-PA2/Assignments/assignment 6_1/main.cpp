/* author: josef dolezal */
/* git: https://github.com/josefdolezal */

#ifndef __PROGTEST__
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <algorithm>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

class CTable;

class CCell {
public:
    int m_colPos;
    int m_rowPos;
    CTable * m_table;
    
            CCell     ( void ): m_colPos(0), m_rowPos(0), m_table(nullptr), m_width(0) {}
    virtual ~CCell    ( void ) {}
    int     getHeight ( void ) const { return (int) m_data.size(); }
    int     getWidth  ( void ) const { return m_width; }
    
    virtual CCell *   clone ( void )      const = 0;
    virtual void      print ( ostream & ) const = 0;
    virtual void      print ( ostream &, int, int, int ) const = 0;
    friend  ostream & operator << ( ostream &os, const CCell &c ) { c.print( os ); return os; };
protected:
    int m_width;
    vector<string> m_data;
};

//=================================================================================================
class CEmpty : public CCell
{
public:
                     CEmpty ( void );
    virtual          ~CEmpty( void ) {}
    virtual CEmpty * clone  ( void )      const;
    virtual void     print  ( ostream & ) const;
    virtual void     print  ( ostream &, int, int, int ) const;
};
//=================================================================================================
class CText : public CCell
{
public:
    static const int         ALIGN_LEFT                    = 0;
    static const int         ALIGN_RIGHT                   = 1;
    
                   CText   ( const string &, const int );
    virtual        ~CText  ( void ) {}
            void   SetText ( const string & );
            CText* clone   ( void )      const;
    virtual void   print   ( ostream & ) const;
    virtual void   print   ( ostream &, int, int, int ) const;
private:
    int    m_align;
    vector<string> rows;
};
//=================================================================================================
class CImage : public CCell
{
public:
                     CImage  ( void );
    virtual          ~CImage ( void ) {}
            CImage & AddRow  ( const string & );
    virtual CImage * clone   ( void )      const;
    virtual void     print   ( ostream & ) const;
    virtual void     print   ( ostream &, int, int, int ) const;
    
private:
    vector<string> rows;
};
//=================================================================================================
class CTable
{
public:
             CTable       ( int, int );
             CTable       ( const CTable & );
    void     SetCell      ( int, int, const CCell & );
    CCell &  GetCell      ( int, int );
    void     updateSizeBy ( int, int, int, int ); // rows, cols, oldh, oldw
    CTable & operator =   ( const CTable & );
    
    friend ostream& operator << ( ostream &, const CTable & );
private:
    struct CRow {
    public:
        int      height;
        int      count;
        CTable * m_table;
        
        CRow  ( void ): height(0), count(0), m_table(nullptr) {}
        CRow  ( int count, CTable * );
        CRow  ( const CRow & );
        ~CRow ( void );
        
        CRow & operator = ( const CRow & );
        
        CCell & getCell        ( int );
        void    setCell        ( int, int, const CCell &, CTable * );
        void    print          ( ostream &, const vector<int> & ) const;
        void    updateHeightBy ( int, int );
        void    deepCP         ( const CRow & );
    private:
        vector<CCell *> m_cells;
        CEmpty m_dummy;
    };
    
    int    m_colsCount;
    int    m_rowsCount;
    CEmpty m_dummy;
    
    vector<CRow> m_rows;
    vector<int>  m_cellWidths;
    
    void printSeparator( ostream & ) const;
    void deepCp( const CTable & );
};
//=================================================================================================

/*
 * CEmpty CLASS DEFINITION
 ----------------------------------------------- */
CEmpty::CEmpty( void ): CCell() { }

void CEmpty::print( ostream &os ) const {
    os << "";
}

void CEmpty::print( ostream &os, int width, int height, int line ) const {
    height++; line++;
    for( int i = 0; i < width; i++ ) os << " ";
}

CEmpty* CEmpty::clone( void ) const {
    return new CEmpty(*this);
}

/*
 * CText CLASS DEFINITION
 ----------------------------------------------- */
CText::CText( const string &text, int align  ): CCell(), m_align(align) {
    SetText( text );
}

void CText::SetText( const string &text ) {
    int oldHeight = getHeight();
    int oldWidth  = getWidth();
    m_data.clear();
    istringstream iss( text );
    int i = 0;
    
    while( ! iss.eof() ) {
        i++;
        string str;
        getline( iss, str );
        if( (int) str.length() > m_width ) m_width = (int) str.length();
        m_data.push_back( str );
    }

    
    if( m_table != nullptr ) m_table->updateSizeBy( m_rowPos, m_colPos, oldHeight, oldWidth );
    
}

void CText::print( ostream &os ) const {
    for( auto i : m_data ) os << i;
}

void CText::print( ostream &os, int width, int height, int line ) const {
    height++;
    if( line >= (int) m_data.size() ) { // text ma min radek nez je radek v bunce
        for( int i = 0; i < width; i++ ) os << " ";
        return;
    }
    
    int padding = width;
    
    if( m_align == CText::ALIGN_LEFT ) { // zarovnani doleva
        os << m_data[line];
        for ( padding = (int) m_data[line].size(); padding < width; padding++ ) os << " ";
    } else { // zarovnani doprava
        for ( padding = (int) m_data[line].size(); padding < width; padding++ ) os << " ";
        os << m_data[line];
    }
    
}

CText* CText::clone( void ) const {
    return new CText(*this);
}

/*
 * CImage CLASS DEFINITION
 ----------------------------------------------- */
CImage::CImage( void ): CCell() {
    
}

CImage & CImage::AddRow( const string &row ) {
    int oldWidth  = getWidth();
    int oldHeight = getHeight();
    m_width       = (int) row.length();
    
    m_data.push_back( row );
    if( m_table != nullptr ) m_table->updateSizeBy( m_rowPos, m_colPos, oldHeight, oldWidth );
    return *this;
}

void CImage::print( ostream &os ) const {
    os << "";
}

void CImage::print( ostream &os, int width, int height, int line ) const {
    int pv = ( height - getHeight() ) / 2;
    int ph = ( width  - getWidth() )  / 2;
    
    if( line < pv || line >= ( pv + getHeight() )) { // padding nahore a prazdne radky
        for( int i = 0; i < width; i++ ) os << " ";
        return;
    }
    
    for( int i = 0; i < ph; i++ ) os << " "; // padding vlevo
    os << m_data[line-pv];
    for( int i = getWidth() + ph; i < width; i++ ) os << " ";
}

CImage* CImage::clone( void ) const {
    return new CImage( *this );
}

/*
 * CTable CLASS DEFINITION
 ----------------------------------------------- */
CTable::CTable( int rows, int cols ) {
    m_rowsCount = rows;
    m_colsCount = cols;
    
    for ( int i = 0; i < rows; i++ ) m_rows.push_back( CRow( cols, this ) );
    for ( int i = 0; i < cols; i++ ) m_cellWidths.push_back(0);
}

CTable::CTable( const CTable &o ) {
    deepCp( o );
}

CTable & CTable::operator = ( const CTable &o ) {
    if( &o == this ) return *this;
    
    deepCp( o );
    return *this;
}

void CTable::SetCell( int row, int col, const CCell &cell ) {
    if( row >= m_rowsCount || col >= m_colsCount ) return;
    m_rows[row].setCell( row, col, cell, this );
}

CCell& CTable::GetCell( int row, int col ) {
    if( row >= m_rowsCount || col >= m_colsCount ) return m_dummy;
    return m_rows[row].getCell( col );
}

ostream& operator << ( ostream &os, const CTable &table ) {
    for( int i = 0; i < table.m_rowsCount; i++ ) {
        table.printSeparator( os );
        table.m_rows[i].print( os, table.m_cellWidths );
    }
    table.printSeparator( os ); // tiskne paticku

    return os;
}

/* PRIVATE */
void CTable::printSeparator( ostream &os ) const {
    os << "+";
    for ( int i = 0; i < m_colsCount; i++ ) {
        for ( int j = 0; j < m_cellWidths[i]; j++ ) os << "-";
        os << "+";
    }
    os << endl;
}

void CTable::deepCp( const CTable &o ) {
    m_rows.clear();
    m_colsCount  = o.m_colsCount;
    m_rowsCount  = o.m_rowsCount;
    m_dummy      = o.m_dummy;
    m_rows       = o.m_rows;
    m_cellWidths = o.m_cellWidths;
    
    for ( auto i: m_rows) i.m_table = this;
}

void CTable::updateSizeBy( int row, int col, int oldHeight, int oldWidth ) {
    /* SIRKA */
    if( m_cellWidths[col] <= m_rows[row].getCell( col ).getWidth() ) // pokud se bunka rozsirila
        m_cellWidths[col] =  m_rows[row].getCell( col ).getWidth();
    else if ( oldWidth >= m_cellWidths[col] ) { // pokud puvodni sirka byla mensi nez max, nemusim hledat max
        int mw = 0;
        for( int i = 0; i < m_rowsCount; i++ )
            if( mw < m_rows[i].getCell( col ).getWidth() ) mw = m_rows[i].getCell( col ).getWidth();
        m_cellWidths[col] = mw;
    }
    /* VYSKA */
    m_rows[row].updateHeightBy( col, oldHeight );
}

CTable::CRow::CRow( int count, CTable *t ): height(0), count(count), m_table(t) {
    for ( int i = 0; i < count; i++ ) m_cells.push_back( new CEmpty() );
}

CTable::CRow::CRow( const CRow &r ) {
    deepCP( r );
}

CTable::CRow & CTable::CRow::operator = ( const CRow &r ) {
    if( this == &r ) return *this;
    
    deepCP( r );
    return *this;
}

void CTable::CRow::deepCP( const CRow &r ) {
    height  = r.height;
    count   = r.count;
    
    for ( int i = 0; i < r.count; i++ ) {
        m_cells.push_back( r.m_cells[i]->clone() );
        m_cells[i]->m_table = m_table;
    }
}

CTable::CRow::~CRow( void ) {
    for( auto i : m_cells ) delete i;
}

void CTable::CRow::setCell( int row, int col, const CCell &cell, CTable *t ) {
    if( col < 0 || col >= count || &cell == m_cells[col] ) return;
    
    int oldHeight = m_cells[col]->getHeight();
    int oldWidth  = m_cells[col]->getWidth();
    delete m_cells[col];
    
    m_cells[col]  = cell.clone();
    m_cells[col]->m_colPos = col; m_cells[col]->m_rowPos = row;
    m_cells[col]->m_table  = t;
    
    m_cells[col]->m_table->updateSizeBy( row, col, oldHeight, oldWidth ); // prepocita vysku a sirku
}

CCell & CTable::CRow::getCell( int col ) {
    if( col < 0 || col >= count ) return m_dummy;
    return *( m_cells[col] );
}

void CTable::CRow::print( ostream &os, const vector<int> &cw ) const {
    if( count < 1 ) return; // prazdna radka
    
    for( int i = 0; i < height; i++ ) { // radka
        for( int j = 0; j < count; j++ ) { // bunka
            os << "|";
            m_cells[j]->print( os, cw[j], height, i ); // tiskne i radek j bunky
        }
        if ( height > 0 )  os << "|" << endl;
    }
    
}

void CTable::CRow::updateHeightBy( int col, int oldHeight ) {
    if( height <= getCell( col ).getHeight() ) // pokud je bunka vetsi nez stavajici max
        height = getCell( col ).getHeight();
    else if ( oldHeight >= height ) { // pokud puvodni sirka byla mensi nez max, nemusim hledat max
        int mh = 0;
        for( int i = 0; i < count; i++ )
            if( mh < getCell( i ).getHeight() ) mh = getCell( i ).getHeight();
        height = mh;
    }
}


/**
 **
 ** TODO: u zmeny obsahu vyvolat update v a s, CImage celej, vlozit do CCell odkaz na table a souradnice x a y v table (bude vyvolavat update), u update dat mozna i puvodni velikost, protoze mohl zmensit nejvetsi
 **
 -------------------------------------------------------------------------------- */













void testsP( void ) {
    
    cout << sizeof(CEmpty) << endl;
    cout << sizeof(CImage) << endl;
    return;
    
    
    
    CTable a(3, 2);
    a.SetCell(0, 0, CText("sdsdsdsd", CText::ALIGN_RIGHT) );
    a.SetCell(1, 1, CText("sdsdsdsd\nsdsdsdsd\ndsdsd", CText::ALIGN_RIGHT) );
    cout << a << endl;
    
    CTable b(a);
    
    cout << b << endl;
    b.SetCell(1, 1, CText("ahoj", CText::ALIGN_RIGHT));
    b.SetCell(2,1, CImage().AddRow("assdsads").AddRow("assdsads"));
    
    cout << a << endl;
    cout << b << endl;
    
    b.SetCell(0, 0, CEmpty());
    
    a = b;
    
    cout << "-------------------------" << endl;
    cout << a << endl;
    cout << b << endl;
    
    a.SetCell(2, 0, CText("dsdsdsd", 1));
    b.SetCell(2, 1, CEmpty());
    
    cout << "-------------------------" << endl;
    cout << a << endl;
    cout << b << endl;
    
    b = a;
    
    cout << "-------------------------" << endl;
    cout << a << endl;
    cout << b << endl;
}


void testsV( void ) {
    ostringstream oss;
    CTable t0 ( 3, 2 );
    t0 . SetCell ( 0, 0, CText ( "Hello,\n"
                                "Hello Kitty", CText::ALIGN_LEFT ) );
    t0 . SetCell ( 1, 0, CText ( "Lorem ipsum dolor sit amet", CText::ALIGN_LEFT ) );
    t0 . SetCell ( 2, 0, CText ( "Bye,\n"
                                "Hello Kitty", CText::ALIGN_RIGHT ) );
    t0 . SetCell ( 1, 1, CImage ()
                  . AddRow ( "###                   " )
                  . AddRow ( "#  #                  " )
                  . AddRow ( "#  # # ##   ###    ###" )
                  . AddRow ( "###  ##    #   #  #  #" )
                  . AddRow ( "#    #     #   #  #  #" )
                  . AddRow ( "#    #     #   #  #  #" )
                  . AddRow ( "#    #      ###    ###" )
                  . AddRow ( "                     #" )
                  . AddRow ( "                   ## " )
                  . AddRow ( "                      " )
                  . AddRow ( " #    ###   ###   #   " )
                  . AddRow ( "###  #   # #     ###  " )
                  . AddRow ( " #   #####  ###   #   " )
                  . AddRow ( " #   #         #  #   " )
                  . AddRow ( "  ##  ###   ###    ## " ) );
    t0 . SetCell ( 2, 1, CEmpty () );
    oss . str ("");
    oss . clear ();
    oss << t0;
    assert ( oss . str () ==
            "+--------------------------+----------------------+\n"
            "|Hello,                    |                      |\n"
            "|Hello Kitty               |                      |\n"
            "+--------------------------+----------------------+\n"
            "|Lorem ipsum dolor sit amet|###                   |\n"
            "|                          |#  #                  |\n"
            "|                          |#  # # ##   ###    ###|\n"
            "|                          |###  ##    #   #  #  #|\n"
            "|                          |#    #     #   #  #  #|\n"
            "|                          |#    #     #   #  #  #|\n"
            "|                          |#    #      ###    ###|\n"
            "|                          |                     #|\n"
            "|                          |                   ## |\n"
            "|                          |                      |\n"
            "|                          | #    ###   ###   #   |\n"
            "|                          |###  #   # #     ###  |\n"
            "|                          | #   #####  ###   #   |\n"
            "|                          | #   #         #  #   |\n"
            "|                          |  ##  ###   ###    ## |\n"
            "+--------------------------+----------------------+\n"
            "|                      Bye,|                      |\n"
            "|               Hello Kitty|                      |\n"
            "+--------------------------+----------------------+\n" );
    t0 . SetCell ( 0, 1, t0 . GetCell ( 1, 1 ) );
    t0 . SetCell ( 2, 1, CImage ()
                  . AddRow ( "*****   *      *  *      ******* ******  *" )
                  . AddRow ( "*    *  *      *  *      *            *  *" )
                  . AddRow ( "*    *  *      *  *      *           *   *" )
                  . AddRow ( "*    *  *      *  *      *****      *    *" )
                  . AddRow ( "****    *      *  *      *         *     *" )
                  . AddRow ( "*  *    *      *  *      *        *       " )
                  . AddRow ( "*   *   *      *  *      *       *       *" )
                  . AddRow ( "*    *    *****   ****** ******* ******  *" ) );
    dynamic_cast<CText &> ( t0 . GetCell ( 1, 0 ) ) . SetText ( "Lorem ipsum dolor sit amet,\n"
                                                               "consectetur adipiscing\n"
                                                               "elit. Curabitur scelerisque\n"
                                                               "lorem vitae lectus cursus,\n"
                                                               "vitae porta ante placerat. Class aptent taciti\n"
                                                               "sociosqu ad litora\n"
                                                               "torquent per\n"
                                                               "conubia nostra,\n"
                                                               "per inceptos himenaeos.\n"
                                                               "\n"
                                                               "Donec tincidunt augue\n"
                                                               "sit amet metus\n"
                                                               "pretium volutpat.\n"
                                                               "Donec faucibus,\n"
                                                               "ante sit amet\n"
                                                               "luctus posuere,\n"
                                                               "mauris tellus" );
    oss . str ("");
    oss . clear ();
    oss << t0;
    assert ( oss . str () ==
            "+----------------------------------------------+------------------------------------------+\n"
            "|Hello,                                        |          ###                             |\n"
            "|Hello Kitty                                   |          #  #                            |\n"
            "|                                              |          #  # # ##   ###    ###          |\n"
            "|                                              |          ###  ##    #   #  #  #          |\n"
            "|                                              |          #    #     #   #  #  #          |\n"
            "|                                              |          #    #     #   #  #  #          |\n"
            "|                                              |          #    #      ###    ###          |\n"
            "|                                              |                               #          |\n"
            "|                                              |                             ##           |\n"
            "|                                              |                                          |\n"
            "|                                              |           #    ###   ###   #             |\n"
            "|                                              |          ###  #   # #     ###            |\n"
            "|                                              |           #   #####  ###   #             |\n"
            "|                                              |           #   #         #  #             |\n"
            "|                                              |            ##  ###   ###    ##           |\n"
            "+----------------------------------------------+------------------------------------------+\n"
            "|Lorem ipsum dolor sit amet,                   |                                          |\n"
            "|consectetur adipiscing                        |          ###                             |\n"
            "|elit. Curabitur scelerisque                   |          #  #                            |\n"
            "|lorem vitae lectus cursus,                    |          #  # # ##   ###    ###          |\n"
            "|vitae porta ante placerat. Class aptent taciti|          ###  ##    #   #  #  #          |\n"
            "|sociosqu ad litora                            |          #    #     #   #  #  #          |\n"
            "|torquent per                                  |          #    #     #   #  #  #          |\n"
            "|conubia nostra,                               |          #    #      ###    ###          |\n"
            "|per inceptos himenaeos.                       |                               #          |\n"
            "|                                              |                             ##           |\n"
            "|Donec tincidunt augue                         |                                          |\n"
            "|sit amet metus                                |           #    ###   ###   #             |\n"
            "|pretium volutpat.                             |          ###  #   # #     ###            |\n"
            "|Donec faucibus,                               |           #   #####  ###   #             |\n"
            "|ante sit amet                                 |           #   #         #  #             |\n"
            "|luctus posuere,                               |            ##  ###   ###    ##           |\n"
            "|mauris tellus                                 |                                          |\n"
            "+----------------------------------------------+------------------------------------------+\n"
            "|                                          Bye,|*****   *      *  *      ******* ******  *|\n"
            "|                                   Hello Kitty|*    *  *      *  *      *            *  *|\n"
            "|                                              |*    *  *      *  *      *           *   *|\n"
            "|                                              |*    *  *      *  *      *****      *    *|\n"
            "|                                              |****    *      *  *      *         *     *|\n"
            "|                                              |*  *    *      *  *      *        *       |\n"
            "|                                              |*   *   *      *  *      *       *       *|\n"
            "|                                              |*    *    *****   ****** ******* ******  *|\n"
            "+----------------------------------------------+------------------------------------------+\n" );
    CTable t1 ( t0 );
    t1 . SetCell ( 1, 0, CEmpty () );
    t1 . SetCell ( 1, 1, CEmpty () );
    oss . str ("");
    oss . clear ();
    oss << t0;
    assert ( oss . str () ==
            "+----------------------------------------------+------------------------------------------+\n"
            "|Hello,                                        |          ###                             |\n"
            "|Hello Kitty                                   |          #  #                            |\n"
            "|                                              |          #  # # ##   ###    ###          |\n"
            "|                                              |          ###  ##    #   #  #  #          |\n"
            "|                                              |          #    #     #   #  #  #          |\n"
            "|                                              |          #    #     #   #  #  #          |\n"
            "|                                              |          #    #      ###    ###          |\n"
            "|                                              |                               #          |\n"
            "|                                              |                             ##           |\n"
            "|                                              |                                          |\n"
            "|                                              |           #    ###   ###   #             |\n"
            "|                                              |          ###  #   # #     ###            |\n"
            "|                                              |           #   #####  ###   #             |\n"
            "|                                              |           #   #         #  #             |\n"
            "|                                              |            ##  ###   ###    ##           |\n"
            "+----------------------------------------------+------------------------------------------+\n"
            "|Lorem ipsum dolor sit amet,                   |                                          |\n"
            "|consectetur adipiscing                        |          ###                             |\n"
            "|elit. Curabitur scelerisque                   |          #  #                            |\n"
            "|lorem vitae lectus cursus,                    |          #  # # ##   ###    ###          |\n"
            "|vitae porta ante placerat. Class aptent taciti|          ###  ##    #   #  #  #          |\n"
            "|sociosqu ad litora                            |          #    #     #   #  #  #          |\n"
            "|torquent per                                  |          #    #     #   #  #  #          |\n"
            "|conubia nostra,                               |          #    #      ###    ###          |\n"
            "|per inceptos himenaeos.                       |                               #          |\n"
            "|                                              |                             ##           |\n"
            "|Donec tincidunt augue                         |                                          |\n"
            "|sit amet metus                                |           #    ###   ###   #             |\n"
            "|pretium volutpat.                             |          ###  #   # #     ###            |\n"
            "|Donec faucibus,                               |           #   #####  ###   #             |\n"
            "|ante sit amet                                 |           #   #         #  #             |\n"
            "|luctus posuere,                               |            ##  ###   ###    ##           |\n"
            "|mauris tellus                                 |                                          |\n"
            "+----------------------------------------------+------------------------------------------+\n"
            "|                                          Bye,|*****   *      *  *      ******* ******  *|\n"
            "|                                   Hello Kitty|*    *  *      *  *      *            *  *|\n"
            "|                                              |*    *  *      *  *      *           *   *|\n"
            "|                                              |*    *  *      *  *      *****      *    *|\n"
            "|                                              |****    *      *  *      *         *     *|\n"
            "|                                              |*  *    *      *  *      *        *       |\n"
            "|                                              |*   *   *      *  *      *       *       *|\n"
            "|                                              |*    *    *****   ****** ******* ******  *|\n"
            "+----------------------------------------------+------------------------------------------+\n" );
    oss . str ("");
    oss . clear ();
    oss << t1;
    assert ( oss . str () ==
            "+-----------+------------------------------------------+\n"
            "|Hello,     |          ###                             |\n"
            "|Hello Kitty|          #  #                            |\n"
            "|           |          #  # # ##   ###    ###          |\n"
            "|           |          ###  ##    #   #  #  #          |\n"
            "|           |          #    #     #   #  #  #          |\n"
            "|           |          #    #     #   #  #  #          |\n"
            "|           |          #    #      ###    ###          |\n"
            "|           |                               #          |\n"
            "|           |                             ##           |\n"
            "|           |                                          |\n"
            "|           |           #    ###   ###   #             |\n"
            "|           |          ###  #   # #     ###            |\n"
            "|           |           #   #####  ###   #             |\n"
            "|           |           #   #         #  #             |\n"
            "|           |            ##  ###   ###    ##           |\n"
            "+-----------+------------------------------------------+\n"
            "+-----------+------------------------------------------+\n"
            "|       Bye,|*****   *      *  *      ******* ******  *|\n"
            "|Hello Kitty|*    *  *      *  *      *            *  *|\n"
            "|           |*    *  *      *  *      *           *   *|\n"
            "|           |*    *  *      *  *      *****      *    *|\n"
            "|           |****    *      *  *      *         *     *|\n"
            "|           |*  *    *      *  *      *        *       |\n"
            "|           |*   *   *      *  *      *       *       *|\n"
            "|           |*    *    *****   ****** ******* ******  *|\n"
            "+-----------+------------------------------------------+\n" );
    t1 = t0;
    t1 . SetCell ( 0, 0, CEmpty () );
    t1 . SetCell ( 1, 1, CImage ()
                  . AddRow ( "  ********                    " )
                  . AddRow ( " **********                   " )
                  . AddRow ( "**        **                  " )
                  . AddRow ( "**             **        **   " )
                  . AddRow ( "**             **        **   " )
                  . AddRow ( "***         ********  ********" )
                  . AddRow ( "****        ********  ********" )
                  . AddRow ( "****           **        **   " )
                  . AddRow ( "****           **        **   " )
                  . AddRow ( "****      **                  " )
                  . AddRow ( " **********                   " )
                  . AddRow ( "  ********                    " ) );
    oss . str ("");
    oss . clear ();
    oss << t0;
    assert ( oss . str () ==
            "+----------------------------------------------+------------------------------------------+\n"
            "|Hello,                                        |          ###                             |\n"
            "|Hello Kitty                                   |          #  #                            |\n"
            "|                                              |          #  # # ##   ###    ###          |\n"
            "|                                              |          ###  ##    #   #  #  #          |\n"
            "|                                              |          #    #     #   #  #  #          |\n"
            "|                                              |          #    #     #   #  #  #          |\n"
            "|                                              |          #    #      ###    ###          |\n"
            "|                                              |                               #          |\n"
            "|                                              |                             ##           |\n"
            "|                                              |                                          |\n"
            "|                                              |           #    ###   ###   #             |\n"
            "|                                              |          ###  #   # #     ###            |\n"
            "|                                              |           #   #####  ###   #             |\n"
            "|                                              |           #   #         #  #             |\n"
            "|                                              |            ##  ###   ###    ##           |\n"
            "+----------------------------------------------+------------------------------------------+\n"
            "|Lorem ipsum dolor sit amet,                   |                                          |\n"
            "|consectetur adipiscing                        |          ###                             |\n"
            "|elit. Curabitur scelerisque                   |          #  #                            |\n"
            "|lorem vitae lectus cursus,                    |          #  # # ##   ###    ###          |\n"
            "|vitae porta ante placerat. Class aptent taciti|          ###  ##    #   #  #  #          |\n"
            "|sociosqu ad litora                            |          #    #     #   #  #  #          |\n"
            "|torquent per                                  |          #    #     #   #  #  #          |\n"
            "|conubia nostra,                               |          #    #      ###    ###          |\n"
            "|per inceptos himenaeos.                       |                               #          |\n"
            "|                                              |                             ##           |\n"
            "|Donec tincidunt augue                         |                                          |\n"
            "|sit amet metus                                |           #    ###   ###   #             |\n"
            "|pretium volutpat.                             |          ###  #   # #     ###            |\n"
            "|Donec faucibus,                               |           #   #####  ###   #             |\n"
            "|ante sit amet                                 |           #   #         #  #             |\n"
            "|luctus posuere,                               |            ##  ###   ###    ##           |\n"
            "|mauris tellus                                 |                                          |\n"
            "+----------------------------------------------+------------------------------------------+\n"
            "|                                          Bye,|*****   *      *  *      ******* ******  *|\n"
            "|                                   Hello Kitty|*    *  *      *  *      *            *  *|\n"
            "|                                              |*    *  *      *  *      *           *   *|\n"
            "|                                              |*    *  *      *  *      *****      *    *|\n"
            "|                                              |****    *      *  *      *         *     *|\n"
            "|                                              |*  *    *      *  *      *        *       |\n"
            "|                                              |*   *   *      *  *      *       *       *|\n"
            "|                                              |*    *    *****   ****** ******* ******  *|\n"
            "+----------------------------------------------+------------------------------------------+\n" );
    oss . str ("");
    oss . clear ();
    oss << t1;
    assert ( oss . str () ==
            "+----------------------------------------------+------------------------------------------+\n"
            "|                                              |          ###                             |\n"
            "|                                              |          #  #                            |\n"
            "|                                              |          #  # # ##   ###    ###          |\n"
            "|                                              |          ###  ##    #   #  #  #          |\n"
            "|                                              |          #    #     #   #  #  #          |\n"
            "|                                              |          #    #     #   #  #  #          |\n"
            "|                                              |          #    #      ###    ###          |\n"
            "|                                              |                               #          |\n"
            "|                                              |                             ##           |\n"
            "|                                              |                                          |\n"
            "|                                              |           #    ###   ###   #             |\n"
            "|                                              |          ###  #   # #     ###            |\n"
            "|                                              |           #   #####  ###   #             |\n"
            "|                                              |           #   #         #  #             |\n"
            "|                                              |            ##  ###   ###    ##           |\n"
            "+----------------------------------------------+------------------------------------------+\n"
            "|Lorem ipsum dolor sit amet,                   |                                          |\n"
            "|consectetur adipiscing                        |                                          |\n"
            "|elit. Curabitur scelerisque                   |        ********                          |\n"
            "|lorem vitae lectus cursus,                    |       **********                         |\n"
            "|vitae porta ante placerat. Class aptent taciti|      **        **                        |\n"
            "|sociosqu ad litora                            |      **             **        **         |\n"
            "|torquent per                                  |      **             **        **         |\n"
            "|conubia nostra,                               |      ***         ********  ********      |\n"
            "|per inceptos himenaeos.                       |      ****        ********  ********      |\n"
            "|                                              |      ****           **        **         |\n"
            "|Donec tincidunt augue                         |      ****           **        **         |\n"
            "|sit amet metus                                |      ****      **                        |\n"
            "|pretium volutpat.                             |       **********                         |\n"
            "|Donec faucibus,                               |        ********                          |\n"
            "|ante sit amet                                 |                                          |\n"
            "|luctus posuere,                               |                                          |\n"
            "|mauris tellus                                 |                                          |\n"
            "+----------------------------------------------+------------------------------------------+\n"
            "|                                          Bye,|*****   *      *  *      ******* ******  *|\n"
            "|                                   Hello Kitty|*    *  *      *  *      *            *  *|\n"
            "|                                              |*    *  *      *  *      *           *   *|\n"
            "|                                              |*    *  *      *  *      *****      *    *|\n"
            "|                                              |****    *      *  *      *         *     *|\n"
            "|                                              |*  *    *      *  *      *        *       |\n"
            "|                                              |*   *   *      *  *      *       *       *|\n"
            "|                                              |*    *    *****   ****** ******* ******  *|\n"
            "+----------------------------------------------+------------------------------------------+\n" );
}


int main ( void )
{
    testsP();
    
    return 0;
}
