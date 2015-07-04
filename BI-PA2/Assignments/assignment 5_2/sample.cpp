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

class CExam
 {
   public:
    static const int SORT_NONE   = 0;
    static const int SORT_ID     = 1;
    static const int SORT_NAME   = 2;
    static const int SORT_RESULT = 3;

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
    // todo
 };

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
int main ( void )
 {
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

   return 0;
 }
#endif /* __PROGTEST__ */
