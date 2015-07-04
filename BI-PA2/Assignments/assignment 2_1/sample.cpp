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
    string    RZ         ( void ) const;
    bool      AtEnd      ( void ) const;
    void      Next       ( void );
   private:
    // todo
 };

class CRegister
 {
   public:
              CRegister  ( void );
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
   private:
    // todo
 };

#ifndef __PROGTEST__
int main ( void )
 {
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

  return 0;
 }
#endif /* __PROGTEST__ */