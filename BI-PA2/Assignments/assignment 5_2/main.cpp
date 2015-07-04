/* author: josef dolezal */
/* git: https://github.com/josefdolezal */

#ifndef __PROGTEST__
#include <cassert>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <algorithm>
using namespace std;

class CResult
{
public:
    CResult ( const string & name,
             unsigned int   studentID,
             const string & test,
             int            result )
    : m_Name ( name ), m_StudentID ( studentID ),
    m_Test ( test ), m_Result ( result ) { }
    string         m_Name;
    unsigned int   m_StudentID;
    string         m_Test;
    int            m_Result;
};
#endif /* __PROGTEST__ */

/*
 * CEXAM - CLASS DECLARATION
 ---------------------------------------------------- */
class CExam
{
public:
    static const int SORT_NONE   = 0;
    static const int SORT_ID     = 1;
    static const int SORT_NAME   = 2;
    static const int SORT_RESULT = 3;
    
                   ~CExam( void );
    bool           Load        ( istream      & cardMap );
    bool           Register    ( const string & cardID,
                                const string & test );
    bool           Assess      ( unsigned int   studentID,
                                const string & test,
                                int            result );
    list<CResult>  ListTest    ( const string & test,
                                int            sortBy ) const;
    set<string>    ListMissing ( const string & test ) const;
    
private:
    struct TStudent {
        string t_Name;
        vector<string> t_Cards;
        vector<string> t_Tests;
        
        bool set( const string &, const string &, const string & );
        unsigned int ID( void ) { return t_ID; }
    private:
        unsigned int t_ID;
        
        bool checkID( const string & ) const;
        bool checkName( const string & ) const;
        bool checkCard( const string & ) const;
    };
    
    map<unsigned int, TStudent *> m_students;
    map<string, map<unsigned int, pair<bool, int> > > m_tests;
    map<string, vector<unsigned int> > m_assess;
    set<string> m_ids;
    
    bool checkUniq( unsigned int ) const;
    bool checkUniq( unsigned int, map<unsigned int, TStudent *> & ) const;
    bool checkUniqC( string & ) const;
    bool checkUniqC( string &, set<string> & ) const;
};

/*
 * CEXAM - CLASS DEFINITON
 ---------------------------------------------------- */
CExam::~CExam( void ) {
    for( auto t : m_students ) delete t.second;
}

bool CExam::Load( istream &cardMap ) {
    bool err = false;
    string line;
    string word;
    map<unsigned int, TStudent *> tmps;
    set<string> lids;
    
    vector<string> data;
    
    while ( getline( cardMap, line ) ) {
        stringstream ss ( line );
        TStudent * st = new TStudent();
        
        while( getline( ss, word, ':' ) ) {
            data.push_back( word );
            if( data.size() > 3 ) { err = true; break; }
        }
        
        if( err == true || data.size() != 3 || ! st->set( data[0], data[1], data[2] ) || ! checkUniq( st->ID() ) || ! checkUniq( st->ID(), tmps ) ) { err = true; delete st; break; }
        tmps.insert( make_pair( st->ID(), st ) );
        
        for( auto i : st->t_Cards ) {
            if( ! checkUniqC( i ) || ! checkUniqC( i, lids ) ) { err = true; break; }
        }
        
        for( auto i : st->t_Cards ) {
            lids.insert( i );
        }
        
        
        data.clear();
    }
    
    if ( err ) { for ( auto &t : tmps ) delete t.second; return false; }
    
    for ( auto t : tmps ) m_students.insert( t );
    for ( auto q : lids ) m_ids.insert( q );
    
    return true;
}

bool CExam::Register ( const string & cardID, const string & test ) {
    bool cardExists = false;
    unsigned int ID = 0;
    for( const auto &i : m_students ) // existuje karta?
        for ( const auto &j : i.second->t_Cards )
            if ( j == cardID ) {
                cardExists = true;
                ID = i.second->ID();
                break;
            }
    if( ! cardExists ) return false;
    
    auto it = m_tests.find( test );
    if( it == m_tests.end() ) { //test neexistuje
        map<unsigned int, pair<bool, int> > tmp;
        tmp.insert( make_pair( ID, make_pair( false, 0 ) ) );
        m_tests.insert( make_pair( test, tmp ) );
        m_students.find( ID )->second->t_Cards.push_back( test );
        m_assess.insert( make_pair( test, vector<unsigned int>() ) );
        return true;
    }
    
    // test existuje
    auto iit = it->second.find( ID );
    if( iit != it->second.end() ) return false; // uz je na testu
    
    // zapise test ke studentovi
    m_students.find( ID )->second->t_Cards.push_back( test );
    
    
    // zapise studenta na test
    it->second.insert( make_pair( ID, make_pair( false, 0 ) ) );
        
    return true;
}

bool CExam::Assess ( unsigned int studentID, const string & test, int result ) {
    auto sit = m_students.find( studentID );
    if( sit == m_students.end() ) return false; // student neexistuje
    
    auto tit = m_tests.find( test );
    if( tit == m_tests.end() ) return false; // test neexistuje
    
    auto sit2 = tit->second.find( studentID );
    if( sit2 == tit->second.end() || sit2->second.first == true ) return false; // student neni na existujicim testu nebo uz je ohodnocen
    
    sit2->second.first  = true; // ohodnoceni
    sit2->second.second = result;
    m_assess.find( test )->second.push_back( studentID );
    
    return true;
}

list<CResult> CExam::ListTest ( const string & test, int sortBy ) const {
    list<CResult> res;
    
    auto tit = m_tests.find( test );
    if( tit == m_tests.end() ) return res; // test neexistuje
    
    for( auto it : m_assess.find( test )->second ) { // vsichni kdo maji ohodnoceno -> razeno podle assess
        TStudent c = *(m_students.find( it )->second );
        res.push_back( CResult( c.t_Name, c.ID(), test, tit->second.find( c.ID() )->second.second ) );
    }
    
    switch ( sortBy) {
        case 0: // BY ASSESS je default
            break;
        case 1: // BY ID
            res.sort( [] ( CResult &l, CResult &r ) { return l.m_StudentID < r.m_StudentID; } );
            break;
        case 2: // BY NAME
            res.sort( [&] ( CResult &l, CResult &r ) {
                if( l.m_Name == r.m_Name ) { // tak podle assess
                    int lid   = -1;
                    int rid   = -1;
                    int index = 0;;
                    
                    for( auto it : m_assess.find( test )->second ) {
                        if( l.m_StudentID == it ) lid = index;
                        if( r.m_StudentID == it ) rid = index;
                        if( lid >= 0 && rid >= 0 ) break;
                        index++;
                    }
                    
                    return lid < rid;
                    
                }
                return l.m_Name < r.m_Name;
                
            } );
            break;
        case 3: // BY RESULT
            res.sort( [&] ( CResult &l, CResult &r ) {
                if( l.m_Result == r.m_Result ) { // tak podle assess
                    int lid   = -1;
                    int rid   = -1;
                    int index = 0;;
                    
                    for( auto it : m_assess.find( test )->second ) {
                        if( l.m_StudentID == it ) lid = index;
                        if( r.m_StudentID == it ) rid = index;
                        if( lid > 0 && rid > 0 ) break;
                        index++;
                    }
                    
                    return lid < rid;
                    
                }
                return l.m_Result > r.m_Result;
                
            } );
            break;
            
            
        default:
            return res; // neznama funkce razeni
    }
    
    return res;
}

set<string> CExam::ListMissing ( const string & test ) const {
    set<string> res;
    vector<pair<unsigned int, string> > tmp;
    
    const auto tit = m_tests.find( test );
    if( tit == m_tests.end() ) return res; // test neexistuje, prazdny set
    
    for ( auto it : tit->second ) {
        if( it.second.first == false ) // nema znamku
            tmp.push_back( make_pair( it.first, m_students.find( it.first )->second->t_Name ) );
    } // najde vsechny co nemaji znamku z testu
    
    
    for( auto uit : tmp ) {
        bool uniq = true;
        for ( auto it : tit->second ) {
            if ( uit.first == it.first ) continue; // kontrola se sebou
            if ( uit.second == m_students.find( it.first )->second->t_Name ) {
                uniq = false;
                break;
            }
        }
        
        if( uniq ) res.insert( uit.second );
    }
    
    return res;
}

bool CExam::TStudent::set( const string &id, const string &name, const string &cards ) {
    if( ! checkID( id ) || ! checkName( name ) ) return false;
    t_ID    = (unsigned int) stoul( id );
    t_Name  = name;
    
    vector<string> tmp;
    stringstream ss( cards );
    string t;
    
    while( getline( ss, t, ',' ) )  {
        for( auto it : tmp ) {
            if( it == t ) return false;
        }
        tmp.push_back( t );
    }
    
    for( int i = 0; i < (int) tmp.size(); i++ ) {
        if( tmp[i].size() < 1 ) return false;
        
        if( tmp[i][0] == ' ' ) tmp[i].erase( tmp[i].begin() );
        if( tmp[i][tmp[i].size() - 1] == ' ' ) tmp[i].erase( tmp[i].begin() + tmp[i].size() - 1 );
        if( ! checkCard( tmp[i] ) ) return false;
    }
    
    t_Cards = tmp;
    
    return true;
}

/* PRIVATE */
bool CExam::checkUniq( unsigned int id ) const {
    auto it = m_students.find( id );
    if( it != m_students.end() ) return false;
    
    return true;
}

bool CExam::checkUniq( unsigned int id, map<unsigned int, TStudent *> & mapa ) const {
    auto it = mapa.find( id );
    if( it != mapa.end() ) return false; // vraci true pro unikatni
    
    return true;
}

bool CExam::checkUniqC( string &cid ) const {
    return m_ids.find( cid ) == m_ids.end();
}

bool CExam::checkUniqC( string &cid, set<string> &ids ) const {
    return ids.find( cid ) == ids.end();
}

bool CExam::TStudent::checkID( const string &id ) const {
    if( id.size() < 1 ) return false;
    for( const auto &i : id ) if( ! isdigit( i) ) return false;
    return true;
}

bool CExam::TStudent::checkName( const string &name ) const {
    if( name.size() < 1 ) return false;
    for( const auto &i : name ) if( ! isalnum( i ) &&  ! isspace( i ) ) return false;
    return true;
}

bool CExam::TStudent::checkCard( const string &card ) const {
    if( card.size() < 1 ) return false;
    for( const auto &i : card ) if( ! isalnum( i ) ) return false;
    return true;
}






#ifndef __PROGTEST__
string toString ( const list<CResult> & l )
{
    ostringstream oss;
    for ( auto const & x : l )
        oss << x . m_Name << ":" << x . m_StudentID << ":" << x . m_Test << ":" << x . m_Result << endl;
    return oss . str ();
}
string toString ( const set<string> & s )
{
    ostringstream oss;
    for ( const auto & x : s )
        oss << x << endl;
    return oss . str ();
}


void testsV( void ) {
    istringstream iss;
    CExam         m;
    iss . clear ();
    iss . str ( "123456:Smith John:er34252456hjsd2451451, 1234151asdfe5123416, asdjklfhq3458235\n"
               "654321:Nowak Jane: 62wtsergtsdfg34\n"
               "456789:Nowak Jane: okjer834d34\n"
               "987:West Peter Thomas:sdswertcvsgncse\n" );
    assert ( m . Load ( iss ) );
    
    assert ( m . Register ( "62wtsergtsdfg34", "PA2 - #1" ) );
    assert ( m . Register ( "62wtsergtsdfg34", "PA2 - #2" ) );
    assert ( m . Register ( "er34252456hjsd2451451", "PA2 - #1" ) );
    assert ( m . Register ( "er34252456hjsd2451451", "PA2 - #3" ) );
    assert ( m . Register ( "sdswertcvsgncse", "PA2 - #1" ) );
    assert ( !m . Register ( "1234151asdfe5123416", "PA2 - #1" ) );
    assert ( !m . Register ( "aaaaaaaaaaaa", "PA2 - #1" ) );
    assert ( m . Assess ( 123456, "PA2 - #1", 50 ) );
    assert ( m . Assess ( 654321, "PA2 - #1", 30 ) );
    assert ( m . Assess ( 654321, "PA2 - #2", 40 ) );
    assert ( m . Assess ( 987, "PA2 - #1", 100 ) );
    assert ( !m . Assess ( 654321, "PA2 - #1", 35 ) );
    assert ( !m . Assess ( 654321, "PA2 - #3", 35 ) );
    assert ( !m . Assess ( 999999, "PA2 - #1", 35 ) );
    cout << toString ( m . ListTest ( "PA2 - #1", CExam::SORT_RESULT ) ) << endl;
    //return;
    assert ( toString ( m . ListTest ( "PA2 - #1", CExam::SORT_RESULT ) ) ==
            "West Peter Thomas:987:PA2 - #1:100\n"
            "Smith John:123456:PA2 - #1:50\n"
            "Nowak Jane:654321:PA2 - #1:30\n" );
    assert ( toString ( m . ListTest ( "PA2 - #1", CExam::SORT_NAME ) ) ==
            "Nowak Jane:654321:PA2 - #1:30\n"
            "Smith John:123456:PA2 - #1:50\n"
            "West Peter Thomas:987:PA2 - #1:100\n" );
    assert ( toString ( m . ListTest ( "PA2 - #1", CExam::SORT_NONE ) ) ==
            "Smith John:123456:PA2 - #1:50\n"
            "Nowak Jane:654321:PA2 - #1:30\n"
            "West Peter Thomas:987:PA2 - #1:100\n" );
    assert ( toString ( m . ListTest ( "PA2 - #1", CExam::SORT_ID ) ) ==
            "West Peter Thomas:987:PA2 - #1:100\n"
            "Smith John:123456:PA2 - #1:50\n"
            "Nowak Jane:654321:PA2 - #1:30\n" );
    assert ( toString ( m . ListMissing ( "PA2 - #3" ) ) ==
            "Smith John\n" );
    iss . clear ();
    iss . str ( "888:Watson Joe:25234sdfgwer52, 234523uio, asdf234235we, 234234234\n" );
    assert ( m . Load ( iss ) );
    
    assert ( m . Register ( "234523uio", "PA2 - #1" ) );
    assert ( m . Assess ( 888, "PA2 - #1", 75 ) );
    iss . clear ();
    iss . str ( "555:Gates Bill:ui2345234sdf\n"
               "888:Watson Joe:2345234634\n" );
    assert ( !m . Load ( iss ) ); // duplicate id 888
    
    assert ( !m . Register ( "ui2345234sdf", "PA2 - #1" ) );
    iss . clear ();
    iss . str ( "555:Gates Bill:ui2345234sdf\n"
               "666:Watson Thomas:okjer834d34\n" ); // duplicate card id okjer834d34
    //return;
    assert ( !m . Load ( iss ) );
    
    assert ( !m . Register ( "ui2345234sdf", "PA2 - #3" ) );
    iss . clear ();
    iss . str ( "555:Gates Bill:ui2345234sdf\n"
               "666:Watson Thomas:jer834d3sdf4\n" );
    assert ( m . Load ( iss ) );
    
    assert ( m . Register ( "ui2345234sdf", "PA2 - #3" ) );
    assert ( toString ( m . ListMissing ( "PA2 - #3" ) ) ==
            "Gates Bill\n"
            "Smith John\n" );

}

void testsP( void ) {
    istringstream iss;
    CExam         m;
    iss . clear ();
    iss . str ( "123456:Smith John:er34252456hjsd2451451, 1234151asdfe5123416, asdjklfhq3458235\n"
               "654321:Nowak Jane: 62wtsergtsdfg34\n"
               "456789:Nowak Jane: okjer834d34\n"
               "987:West Peter Thomas:sdswertcvsgncse\n" );
    assert ( m . Load ( iss ) );
    
    assert ( m . Register ( "62wtsergtsdfg34", "PA2 - #1" ) );
    assert ( m . Register ( "62wtsergtsdfg34", "PA2 - #2" ) );
    assert ( m . Register ( "er34252456hjsd2451451", "PA2 - #1" ) );
    assert ( m . Register ( "er34252456hjsd2451451", "PA2 - #3" ) );
    assert ( m . Register ( "sdswertcvsgncse", "PA2 - #1" ) );
    assert ( !m . Register ( "1234151asdfe5123416", "PA2 - #1" ) );
    assert ( !m . Register ( "aaaaaaaaaaaa", "PA2 - #1" ) );

}



int main ( void )
{
    testsV();
    
    return 0;
}
#endif /* __PROGTEST__ */
