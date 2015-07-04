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

//=================================================================================================
class CEmpty 
 {
   public:
    // default constructor
 };
//=================================================================================================
class CText 
 {
   public:
    static const int         ALIGN_LEFT                    = 0;
    static const int         ALIGN_RIGHT                   = 1;
     // constructor ( text, align )
     // SetText ( newText )
 };
//=================================================================================================
class CImage 
 {
   public:
    // default constructor
    // AddRow ( row )
 };
//=================================================================================================
class CTable 
 {
   public:   
    // constructor ( rows, cols )
    // SetCell ( row, col, newContent )
    // GetCell ( row, col )
    // operator << 
 };
//=================================================================================================
int main ( void )
 {
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
   CTable t2 ( 2, 2 );
   t2 . SetCell ( 0, 0, CText ( "OOP", CText::ALIGN_LEFT ) );
   t2 . SetCell ( 0, 1, CText ( "Encapsulation", CText::ALIGN_LEFT ) );
   t2 . SetCell ( 1, 0, CText ( "Polymorphism", CText::ALIGN_LEFT ) );
   t2 . SetCell ( 1, 1, CText ( "Inheritance", CText::ALIGN_LEFT ) );
   oss . str ("");
   oss . clear ();
   oss << t2;
   assert ( oss . str () ==
        "+------------+-------------+\n"
        "|OOP         |Encapsulation|\n"
        "+------------+-------------+\n"
        "|Polymorphism|Inheritance  |\n"
        "+------------+-------------+\n" );
   t1 . SetCell ( 0, 0, t2 );
   dynamic_cast<CText &> ( t2 . GetCell ( 0, 0 ) ) . SetText ( "Object Oriented Programming" );
   oss . str ("");
   oss . clear ();
   oss << t2;
   assert ( oss . str () ==
        "+---------------------------+-------------+\n"
        "|Object Oriented Programming|Encapsulation|\n"
        "+---------------------------+-------------+\n"
        "|Polymorphism               |Inheritance  |\n"
        "+---------------------------+-------------+\n" );
   oss . str ("");
   oss . clear ();
   oss << t1;
   assert ( oss . str () ==
        "+----------------------------------------------+------------------------------------------+\n"
        "|+------------+-------------+                  |          ###                             |\n"
        "||OOP         |Encapsulation|                  |          #  #                            |\n"
        "|+------------+-------------+                  |          #  # # ##   ###    ###          |\n"
        "||Polymorphism|Inheritance  |                  |          ###  ##    #   #  #  #          |\n"
        "|+------------+-------------+                  |          #    #     #   #  #  #          |\n"
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
   t1 . SetCell ( 0, 0, t1 );
   oss . str ("");
   oss . clear ();
   oss << t1;
   assert ( oss . str () ==
        "+-------------------------------------------------------------------------------------------+------------------------------------------+\n"
        "|+----------------------------------------------+------------------------------------------+|                                          |\n"
        "||+------------+-------------+                  |          ###                             ||                                          |\n"
        "|||OOP         |Encapsulation|                  |          #  #                            ||                                          |\n"
        "||+------------+-------------+                  |          #  # # ##   ###    ###          ||                                          |\n"
        "|||Polymorphism|Inheritance  |                  |          ###  ##    #   #  #  #          ||                                          |\n"
        "||+------------+-------------+                  |          #    #     #   #  #  #          ||                                          |\n"
        "||                                              |          #    #     #   #  #  #          ||                                          |\n"
        "||                                              |          #    #      ###    ###          ||                                          |\n"
        "||                                              |                               #          ||                                          |\n"
        "||                                              |                             ##           ||                                          |\n"
        "||                                              |                                          ||                                          |\n"
        "||                                              |           #    ###   ###   #             ||                                          |\n"
        "||                                              |          ###  #   # #     ###            ||                                          |\n"
        "||                                              |           #   #####  ###   #             ||                                          |\n"
        "||                                              |           #   #         #  #             ||          ###                             |\n"
        "||                                              |            ##  ###   ###    ##           ||          #  #                            |\n"
        "|+----------------------------------------------+------------------------------------------+|          #  # # ##   ###    ###          |\n"
        "||Lorem ipsum dolor sit amet,                   |                                          ||          ###  ##    #   #  #  #          |\n"
        "||consectetur adipiscing                        |                                          ||          #    #     #   #  #  #          |\n"
        "||elit. Curabitur scelerisque                   |        ********                          ||          #    #     #   #  #  #          |\n"
        "||lorem vitae lectus cursus,                    |       **********                         ||          #    #      ###    ###          |\n"
        "||vitae porta ante placerat. Class aptent taciti|      **        **                        ||                               #          |\n"
        "||sociosqu ad litora                            |      **             **        **         ||                             ##           |\n"
        "||torquent per                                  |      **             **        **         ||                                          |\n"
        "||conubia nostra,                               |      ***         ********  ********      ||           #    ###   ###   #             |\n"
        "||per inceptos himenaeos.                       |      ****        ********  ********      ||          ###  #   # #     ###            |\n"
        "||                                              |      ****           **        **         ||           #   #####  ###   #             |\n"
        "||Donec tincidunt augue                         |      ****           **        **         ||           #   #         #  #             |\n"
        "||sit amet metus                                |      ****      **                        ||            ##  ###   ###    ##           |\n"
        "||pretium volutpat.                             |       **********                         ||                                          |\n"
        "||Donec faucibus,                               |        ********                          ||                                          |\n"
        "||ante sit amet                                 |                                          ||                                          |\n"
        "||luctus posuere,                               |                                          ||                                          |\n"
        "||mauris tellus                                 |                                          ||                                          |\n"
        "|+----------------------------------------------+------------------------------------------+|                                          |\n"
        "||                                          Bye,|*****   *      *  *      ******* ******  *||                                          |\n"
        "||                                   Hello Kitty|*    *  *      *  *      *            *  *||                                          |\n"
        "||                                              |*    *  *      *  *      *           *   *||                                          |\n"
        "||                                              |*    *  *      *  *      *****      *    *||                                          |\n"
        "||                                              |****    *      *  *      *         *     *||                                          |\n"
        "||                                              |*  *    *      *  *      *        *       ||                                          |\n"
        "||                                              |*   *   *      *  *      *       *       *||                                          |\n"
        "||                                              |*    *    *****   ****** ******* ******  *||                                          |\n"
        "|+----------------------------------------------+------------------------------------------+|                                          |\n"
        "+-------------------------------------------------------------------------------------------+------------------------------------------+\n"
        "|Lorem ipsum dolor sit amet,                                                                |                                          |\n"
        "|consectetur adipiscing                                                                     |                                          |\n"
        "|elit. Curabitur scelerisque                                                                |        ********                          |\n"
        "|lorem vitae lectus cursus,                                                                 |       **********                         |\n"
        "|vitae porta ante placerat. Class aptent taciti                                             |      **        **                        |\n"
        "|sociosqu ad litora                                                                         |      **             **        **         |\n"
        "|torquent per                                                                               |      **             **        **         |\n"
        "|conubia nostra,                                                                            |      ***         ********  ********      |\n"
        "|per inceptos himenaeos.                                                                    |      ****        ********  ********      |\n"
        "|                                                                                           |      ****           **        **         |\n"
        "|Donec tincidunt augue                                                                      |      ****           **        **         |\n"
        "|sit amet metus                                                                             |      ****      **                        |\n"
        "|pretium volutpat.                                                                          |       **********                         |\n"
        "|Donec faucibus,                                                                            |        ********                          |\n"
        "|ante sit amet                                                                              |                                          |\n"
        "|luctus posuere,                                                                            |                                          |\n"
        "|mauris tellus                                                                              |                                          |\n"
        "+-------------------------------------------------------------------------------------------+------------------------------------------+\n"
        "|                                                                                       Bye,|*****   *      *  *      ******* ******  *|\n"
        "|                                                                                Hello Kitty|*    *  *      *  *      *            *  *|\n"
        "|                                                                                           |*    *  *      *  *      *           *   *|\n"
        "|                                                                                           |*    *  *      *  *      *****      *    *|\n"
        "|                                                                                           |****    *      *  *      *         *     *|\n"
        "|                                                                                           |*  *    *      *  *      *        *       |\n"
        "|                                                                                           |*   *   *      *  *      *       *       *|\n"
        "|                                                                                           |*    *    *****   ****** ******* ******  *|\n"
        "+-------------------------------------------------------------------------------------------+------------------------------------------+\n" );
   t1 . SetCell ( 0, 0, t1 );
   oss . str ("");
   oss . clear ();
   oss << t1;
   assert ( oss . str () ==
        "+----------------------------------------------------------------------------------------------------------------------------------------+------------------------------------------+\n"
        "|+-------------------------------------------------------------------------------------------+------------------------------------------+|                                          |\n"
        "||+----------------------------------------------+------------------------------------------+|                                          ||                                          |\n"
        "|||+------------+-------------+                  |          ###                             ||                                          ||                                          |\n"
        "||||OOP         |Encapsulation|                  |          #  #                            ||                                          ||                                          |\n"
        "|||+------------+-------------+                  |          #  # # ##   ###    ###          ||                                          ||                                          |\n"
        "||||Polymorphism|Inheritance  |                  |          ###  ##    #   #  #  #          ||                                          ||                                          |\n"
        "|||+------------+-------------+                  |          #    #     #   #  #  #          ||                                          ||                                          |\n"
        "|||                                              |          #    #     #   #  #  #          ||                                          ||                                          |\n"
        "|||                                              |          #    #      ###    ###          ||                                          ||                                          |\n"
        "|||                                              |                               #          ||                                          ||                                          |\n"
        "|||                                              |                             ##           ||                                          ||                                          |\n"
        "|||                                              |                                          ||                                          ||                                          |\n"
        "|||                                              |           #    ###   ###   #             ||                                          ||                                          |\n"
        "|||                                              |          ###  #   # #     ###            ||                                          ||                                          |\n"
        "|||                                              |           #   #####  ###   #             ||                                          ||                                          |\n"
        "|||                                              |           #   #         #  #             ||          ###                             ||                                          |\n"
        "|||                                              |            ##  ###   ###    ##           ||          #  #                            ||                                          |\n"
        "||+----------------------------------------------+------------------------------------------+|          #  # # ##   ###    ###          ||                                          |\n"
        "|||Lorem ipsum dolor sit amet,                   |                                          ||          ###  ##    #   #  #  #          ||                                          |\n"
        "|||consectetur adipiscing                        |                                          ||          #    #     #   #  #  #          ||                                          |\n"
        "|||elit. Curabitur scelerisque                   |        ********                          ||          #    #     #   #  #  #          ||                                          |\n"
        "|||lorem vitae lectus cursus,                    |       **********                         ||          #    #      ###    ###          ||                                          |\n"
        "|||vitae porta ante placerat. Class aptent taciti|      **        **                        ||                               #          ||                                          |\n"
        "|||sociosqu ad litora                            |      **             **        **         ||                             ##           ||                                          |\n"
        "|||torquent per                                  |      **             **        **         ||                                          ||                                          |\n"
        "|||conubia nostra,                               |      ***         ********  ********      ||           #    ###   ###   #             ||                                          |\n"
        "|||per inceptos himenaeos.                       |      ****        ********  ********      ||          ###  #   # #     ###            ||                                          |\n"
        "|||                                              |      ****           **        **         ||           #   #####  ###   #             ||                                          |\n"
        "|||Donec tincidunt augue                         |      ****           **        **         ||           #   #         #  #             ||                                          |\n"
        "|||sit amet metus                                |      ****      **                        ||            ##  ###   ###    ##           ||          ###                             |\n"
        "|||pretium volutpat.                             |       **********                         ||                                          ||          #  #                            |\n"
        "|||Donec faucibus,                               |        ********                          ||                                          ||          #  # # ##   ###    ###          |\n"
        "|||ante sit amet                                 |                                          ||                                          ||          ###  ##    #   #  #  #          |\n"
        "|||luctus posuere,                               |                                          ||                                          ||          #    #     #   #  #  #          |\n"
        "|||mauris tellus                                 |                                          ||                                          ||          #    #     #   #  #  #          |\n"
        "||+----------------------------------------------+------------------------------------------+|                                          ||          #    #      ###    ###          |\n"
        "|||                                          Bye,|*****   *      *  *      ******* ******  *||                                          ||                               #          |\n"
        "|||                                   Hello Kitty|*    *  *      *  *      *            *  *||                                          ||                             ##           |\n"
        "|||                                              |*    *  *      *  *      *           *   *||                                          ||                                          |\n"
        "|||                                              |*    *  *      *  *      *****      *    *||                                          ||           #    ###   ###   #             |\n"
        "|||                                              |****    *      *  *      *         *     *||                                          ||          ###  #   # #     ###            |\n"
        "|||                                              |*  *    *      *  *      *        *       ||                                          ||           #   #####  ###   #             |\n"
        "|||                                              |*   *   *      *  *      *       *       *||                                          ||           #   #         #  #             |\n"
        "|||                                              |*    *    *****   ****** ******* ******  *||                                          ||            ##  ###   ###    ##           |\n"
        "||+----------------------------------------------+------------------------------------------+|                                          ||                                          |\n"
        "|+-------------------------------------------------------------------------------------------+------------------------------------------+|                                          |\n"
        "||Lorem ipsum dolor sit amet,                                                                |                                          ||                                          |\n"
        "||consectetur adipiscing                                                                     |                                          ||                                          |\n"
        "||elit. Curabitur scelerisque                                                                |        ********                          ||                                          |\n"
        "||lorem vitae lectus cursus,                                                                 |       **********                         ||                                          |\n"
        "||vitae porta ante placerat. Class aptent taciti                                             |      **        **                        ||                                          |\n"
        "||sociosqu ad litora                                                                         |      **             **        **         ||                                          |\n"
        "||torquent per                                                                               |      **             **        **         ||                                          |\n"
        "||conubia nostra,                                                                            |      ***         ********  ********      ||                                          |\n"
        "||per inceptos himenaeos.                                                                    |      ****        ********  ********      ||                                          |\n"
        "||                                                                                           |      ****           **        **         ||                                          |\n"
        "||Donec tincidunt augue                                                                      |      ****           **        **         ||                                          |\n"
        "||sit amet metus                                                                             |      ****      **                        ||                                          |\n"
        "||pretium volutpat.                                                                          |       **********                         ||                                          |\n"
        "||Donec faucibus,                                                                            |        ********                          ||                                          |\n"
        "||ante sit amet                                                                              |                                          ||                                          |\n"
        "||luctus posuere,                                                                            |                                          ||                                          |\n"
        "||mauris tellus                                                                              |                                          ||                                          |\n"
        "|+-------------------------------------------------------------------------------------------+------------------------------------------+|                                          |\n"
        "||                                                                                       Bye,|*****   *      *  *      ******* ******  *||                                          |\n"
        "||                                                                                Hello Kitty|*    *  *      *  *      *            *  *||                                          |\n"
        "||                                                                                           |*    *  *      *  *      *           *   *||                                          |\n"
        "||                                                                                           |*    *  *      *  *      *****      *    *||                                          |\n"
        "||                                                                                           |****    *      *  *      *         *     *||                                          |\n"
        "||                                                                                           |*  *    *      *  *      *        *       ||                                          |\n"
        "||                                                                                           |*   *   *      *  *      *       *       *||                                          |\n"
        "||                                                                                           |*    *    *****   ****** ******* ******  *||                                          |\n"
        "|+-------------------------------------------------------------------------------------------+------------------------------------------+|                                          |\n"
        "+----------------------------------------------------------------------------------------------------------------------------------------+------------------------------------------+\n"
        "|Lorem ipsum dolor sit amet,                                                                                                             |                                          |\n"
        "|consectetur adipiscing                                                                                                                  |                                          |\n"
        "|elit. Curabitur scelerisque                                                                                                             |        ********                          |\n"
        "|lorem vitae lectus cursus,                                                                                                              |       **********                         |\n"
        "|vitae porta ante placerat. Class aptent taciti                                                                                          |      **        **                        |\n"
        "|sociosqu ad litora                                                                                                                      |      **             **        **         |\n"
        "|torquent per                                                                                                                            |      **             **        **         |\n"
        "|conubia nostra,                                                                                                                         |      ***         ********  ********      |\n"
        "|per inceptos himenaeos.                                                                                                                 |      ****        ********  ********      |\n"
        "|                                                                                                                                        |      ****           **        **         |\n"
        "|Donec tincidunt augue                                                                                                                   |      ****           **        **         |\n"
        "|sit amet metus                                                                                                                          |      ****      **                        |\n"
        "|pretium volutpat.                                                                                                                       |       **********                         |\n"
        "|Donec faucibus,                                                                                                                         |        ********                          |\n"
        "|ante sit amet                                                                                                                           |                                          |\n"
        "|luctus posuere,                                                                                                                         |                                          |\n"
        "|mauris tellus                                                                                                                           |                                          |\n"
        "+----------------------------------------------------------------------------------------------------------------------------------------+------------------------------------------+\n"
        "|                                                                                                                                    Bye,|*****   *      *  *      ******* ******  *|\n"
        "|                                                                                                                             Hello Kitty|*    *  *      *  *      *            *  *|\n"
        "|                                                                                                                                        |*    *  *      *  *      *           *   *|\n"
        "|                                                                                                                                        |*    *  *      *  *      *****      *    *|\n"
        "|                                                                                                                                        |****    *      *  *      *         *     *|\n"
        "|                                                                                                                                        |*  *    *      *  *      *        *       |\n"
        "|                                                                                                                                        |*   *   *      *  *      *       *       *|\n"
        "|                                                                                                                                        |*    *    *****   ****** ******* ******  *|\n"
        "+----------------------------------------------------------------------------------------------------------------------------------------+------------------------------------------+\n" );
        
   return 0;
 }
