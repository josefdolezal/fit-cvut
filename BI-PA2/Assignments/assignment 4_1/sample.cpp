#ifndef __PROGTEST__
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <iomanip>
using namespace std;
#endif /* __PROGTEST__ */

class CCarList
 {
   public:
    // copy cons, op=, dtor ...
    const char   * RZ           ( void ) const;
    bool           AtEnd        ( void ) const;
    void           Next         ( void );
   private:
    // todo
 };

class COwnerList 
 {
   public:
    // copy cons, op=, dtor ...
    const char   * Name         ( void ) const;
    const char   * Surname      ( void ) const;
    bool           AtEnd        ( void ) const;
    void           Next         ( void );
   private:
    // todo
 };

class CRegister
 {
   public:
    // copy cons, op=, dtor ...
    bool           AddCar       ( const char      * rz,
                                  const char      * name,
                                  const char      * surname );
    bool           DelCar       ( const char      * rz );
    bool           Transfer     ( const char      * rz,
                                  const char      * nName,
                                  const char      * nSurname );
    CCarList       ListCars     ( const char      * name,
                                  const char      * surname ) const;
    int            CountCars    ( const char      * name,
                                  const char      * surname ) const;
    COwnerList     ListOwners   ( const char      * RZ ) const;
    int            CountOwners  ( const char      * RZ ) const;
   private:
    // todo
 };

#ifndef __PROGTEST__
int main ( void )
 {
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

  return 0;
 }
#endif /* __PROGTEST__ */