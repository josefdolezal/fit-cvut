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
    string         RZ           ( void ) const;
    unsigned int   VIN          ( void ) const;
    bool           AtEnd        ( void ) const;
    void           Next         ( void );
   private:
    // todo
 };

class COwnerList 
 {
   public:
    string         Name         ( void ) const;
    string         Surname      ( void ) const;
    bool           AtEnd        ( void ) const;
    void           Next         ( void );
   private:
    // todo
 };

class CRegister
 {
   public:
                   CRegister    ( void );
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
   private:
    // todo
 };

#ifndef __PROGTEST__
int main ( void )
 {
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



  return 0;
 }
#endif /* __PROGTEST__ */