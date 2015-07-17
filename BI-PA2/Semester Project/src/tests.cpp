//Author: Josef Dolezal
//dolezjo3@fit.cvut.cz


#include "tests.h"


//! \brief Tests CParser class.
void Tests::parserTests( void ) {
    cout << "CParser Tests" << endl;
    CParser p( "2 * 0.5" );
    p.ShowPostfix();
    
    
    
    //cout << o.applyOperator( 2, 2 ) << endl;
    
    
    cout << "  -> OK" << endl;
}

//! \brief Tests CNum class.
void Tests::cnumTests( void ) {
    cout << "CNum Format Tests" << endl;
    ostringstream oss;
    
    CNum c1 = "1.1";
    assert( c1 == "1.1" );
    assert( c1 != "-1.1" );
    
    try {
        CNum c2 = "..";
    } catch ( exception &e ) {
        oss << e.what();
    }
    assert( oss.str() == "CNum: unexpected character in input sequence." );
    oss.str( "" ); oss.clear();
    
    try {
        CNum c2 = ".";
    } catch ( exception &e ) {
        oss << e.what();
    }
    assert( oss.str() == "CNum: invalid zero length of number." );
    oss.str( "" ); oss.clear();
    
    try {
        CNum c2 = "2121.a";
    } catch ( exception &e ) {
        oss << e.what();
    }
    assert( oss.str() == "CNum: unexpected character in input sequence." );
    oss.str( "" ); oss.clear();
    
    try {
        CNum c2 = "2121a.232";
    } catch ( exception &e ) {
        oss << e.what();
    }
    assert( oss.str() == "CNum: unexpected character in input sequence." );
    oss.str( "" ); oss.clear();
    
    assert( CNum( ".25" ) == "0.25" );
    
    CNum c4 = "25";
    assert( c4 == "25.0" );
    
    string t = "5";
    c4 += t;
    assert( c4 == "30.0" );
    
    assert( CNum( "-7" ) == "-7.0" );
    assert( - CNum( "-7" ) == "7" );
    
    
    

    cout << "  -> OK" << endl;
}

//! \brief Tests math operation with CNum.
void Tests::cnumOperationsTests( void ) {
    ostringstream oss;
    cout << "CNum Operations Tests" << endl;
    CNum a = "2.0999";
    CNum b = "0.099";
    a += b;
    
    oss << a;
    assert( oss.str() == "2.1989");
    
    assert( CNum( "10" ) > CNum( "9" ) );
    assert( CNum( "10" ) > CNum( "-10" ) );
    assert( CNum( "-4" ) > CNum( "-5" ) );
    assert( ( CNum( "-5" ) > CNum( "-4" ) ) == false );
    assert( ( CNum( "-5" ) > CNum( "4" ) ) == false );
    
    a += "1.99";
    assert( a == "4.1889");
    
    CNum c( "928.359284611" );
    c += "9245.724133891246";
    assert( c == "10174.083418502246" );
    
    CNum t1 = "83";
    CNum t2 = "-9";
    CNum t3 = "-12";
    CNum t4 = "68";
    
    assert( ( t1 + t4 ) == "151" );
    assert( ( t1 + t2 ) == "74" );
    assert( ( t1 - t4 ) == "15" );
    assert( ( t1 - t2 ) == "92" );
    assert( ( t2 + t1 ) == "74" );
    assert( ( t2 + t3 ) == "-21" );
    assert( ( t2 - t1 ) == "-92" );
    assert( ( t2 - t3 ) == "3" );
    
    assert( ( CNum( "2" ) * CNum( "2" ) ) == "4" );
    assert( ( CNum( "-2" ) * CNum( "-2" ) ) == "4" );
    assert( ( CNum( "2" ) * CNum( "-2" ) ) == "-4" );
    assert( ( CNum( "-2" ) * CNum( "2" ) ) == "-4" );
    
    assert( ( CNum( "102.9999" ) * CNum( "2.387" ) ) == "245.86076130" );
    
    cout << "  -> OK" << endl;
}

//! \brief Tests CNum limits.
void Tests::cnumLimits( void ) {
    ostringstream oss;
    cout << "CNum Limits Tests" << endl;
    
    CNum a = "340282366920938463463374607431768211456";
    assert( ( a += "44" ) == "340282366920938463463374607431768211500" );
    
    CNum b = "65535";
    
    cout << "  -> OK" << endl;
}

//! \brief Tests math operators.
void Tests::operators( void ) {
    cout << "COperator Tests" << endl;
    
    assert( COperator( '+', 1 ) < COperator( '*', 2 ) );
    assert( COperator( '(' ) == '(' );
    
    cout << "  -> OK" << endl;
}

//! \brief Tests Expressions
void Tests::ccalcTests( void ) {
    ostringstream oss;
    CCalc c;
    
    try {
        c.Calc( "((" );
    } catch ( exception &ex ) {
        
    }
    
    
}

