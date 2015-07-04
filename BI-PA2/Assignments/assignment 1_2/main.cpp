/* author: josef dolezal */
/* git: https://github.com/josefdolezal */

#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <stdint.h>
#include <bitset>
using namespace std;
#endif /* __PROGTEST__ */

//
// Reader

class Reader {
private:
    char *content;
    int *fibs;
    int index, len, fibBits;
    unsigned char fibCache;
    bool error;
    const string filename;
    
    bool getNextByte ( int& );
    bool utfSecByte ( const int & ) const;
    bool cacheByte ( void );
    void fibSequence( void );
    void readFile();
    
public:
    Reader(const char * &);
    ~Reader();
    bool utfGetNext( unsigned int& );
    bool fibGetNext( unsigned int& );
    bool fail( void ) const { return error; };
};

    Reader::Reader( const char * &file ): index(0), len(0), fibBits(0), error(false), filename(file) {
        fibs  = new int[29];
        fibSequence();
        readFile();
    }

    void Reader::readFile() {
        ifstream fs( filename, ios::binary | ios::in );
        
        if ( fs.fail() ) {
            error = true;
            fs.close();
            content = new char[1];
            return;
        }
        
        fs.seekg ( 0, fs.end );
        len = (int) fs.tellg();
        fs.seekg ( 0, fs.beg );
        
        len = len <= 0 ? 1 : len;
        
        content = new char[len];
        if ( ! fs.read ( content, len ) ) {
            error = true;
        }
        
        fs.close();
        
    }

    void Reader::fibSequence() {
        fibs[0] = 1;
        fibs[1] = 2;
        
        for ( int i = 2; i < 29; i++ ) {
            fibs[i] = fibs[i-1] + fibs[i-2];
        }
    }

    bool Reader::utfSecByte( const int &index ) const {
        return ( index < len && (unsigned char) content[index] > 127 && (unsigned char) content[index] < 192 );
    }

    bool Reader::utfGetNext( unsigned int &dec ) {
        if ( error || index == len ) return false;
        
        unsigned int tmp = (unsigned char) content[index];
        
        if ( tmp < 128 ) { dec = tmp; index++; return true; }
        else if ( tmp < 192 )  { error = true; return false; }
        else if ( tmp < 224 ) {
            if ( utfSecByte( index + 1 ) ) {
                dec = (tmp - 192) << 6 | ( (unsigned char) content[index+1] - 128 );
                
                index += 2;
                return true;
            }
        }
        else if ( tmp < 240 ) {
            if ( utfSecByte( index + 1 ) && utfSecByte( index + 2 ) ) {
                dec = (tmp - 224) << 12 | ( (unsigned char) content[index+1] - 128 ) << 6 |
                    ( (unsigned char) content[index+2] - 128 );
                
                index += 3;
                return true;
            }
        }
        else if ( tmp < 248 ) {
            if ( utfSecByte( index + 1 ) && utfSecByte( index + 2) && utfSecByte( index + 3 ) ) {
                
                dec = (tmp - 240) << 18 | ( (unsigned char) content[index+1] - 128 ) << 12 |
                    ( (unsigned char) content[index+2] - 128 ) << 6 | ( (unsigned char) content[index+3] - 128 );
                
                index += 4;
                return true;
            }
        }
        
        error = true;
        return false;
    }

    bool Reader::fibGetNext( unsigned int &res ) {
        if ( error || ( index == len && fibBits == 0 ) ) return false;
        
        unsigned int tmp = 0;
        int i = 0;
        bool one = false;
        
        if ( ! cacheByte() )
            return false;
    
        while ( cacheByte() ) {
            if ( tmp > 0x10ffff + 1) { error = true; return false; }
            
            char f = ( fibCache >> ( 8 - fibBits ) ) & 0x1;
            fibBits--;
        
            if ( f == 1 ) {
                if ( one ) break;
                
                tmp += fibs[i];
                one = true;
            } else one = false;
            
            if ( i > 28) {
                error = true;
                return false;
            }
            
            i++;
        }
        
        if ( tmp == 0) return false;
        
        if ( res > 0x10ffff ) {
            error = true;
            return false;
        }
        
        res = tmp-1;
        return true;
    }

    bool Reader::cacheByte() {
        if ( fibBits == 0 ) {
            if ( index == len ) {
                return false;
            }
            
            fibCache = content[index++];
            fibBits  = 8;
            
        }
        
        return true;
    }

    Reader::~Reader() {
        delete[] content;
        delete[] fibs;
    }

//
// Encoder


class Encoder {
private:
    unsigned int *fibs;
    string fibBytes;
    unsigned char fibCache;
    int fibBits;
    bool error;
    
    unsigned char utfMaskByte( const int & ) const;
    void fibSequence( void );
    void fibSaveCache( void );
    
public:
    Encoder( void );
    ~Encoder( void );
    bool toUtf( const int&, string& );
    bool toFib( const int& );
    bool fibFlush( string& );
    bool fail( void ) const { return error; };
};

    Encoder::Encoder(): fibBytes(""), fibBits(0), error(false) {
        fibs  = new unsigned int[29];
        fibSequence();
    }

    bool Encoder::toUtf( const int &decn, string &enc ) {
        
        if ( decn <= 0x7f ) { enc += (unsigned char) decn; return true; }
        else if ( decn >= 0x80 && decn <= 0x7ff ) {
            enc += (unsigned char) ( ( decn >> 6 ) | 0xc0 );
            enc += utfMaskByte( decn );
        } else if ( decn >= 0x800 && decn <= 0xffff ) {
            enc += (unsigned char) ( ( decn >> 12 ) | 0xe0 );
            enc += utfMaskByte( decn >> 6 );
            enc += utfMaskByte( decn );
        } else if( decn >= 0x10000 && decn <= 0x10ffff ) {
            enc += (unsigned char) ( ( decn >> 18 ) | 0xf0 );
            enc += utfMaskByte( decn >> 12 );
            enc += utfMaskByte( decn >> 6 );
            enc += utfMaskByte( decn );
        } else {
            error = true;
            return false;
        }
        
        return true;
    }

    bool Encoder::toFib( const int &decn ) {
        if ( decn > 0x10ffff ) {
            error = true;
            return false;
        }
        
        unsigned int a = decn + 1;
        unsigned int numCache = 1;
        int bits              = 1;
        bool printZero        = false;
        
        for ( int i = 28 ; i >= 0 ; i-- ) {
            if ( fibs[i] <= a ) {
                a = a % fibs[i];
                printZero = true;
                numCache  = ( numCache << 1 ) | 1;
                bits++;
                
                if ( i-- != 0 ) {
                    numCache = numCache << 1;
                    bits++;
                }
            } else if ( printZero )  { numCache = numCache << 1; bits++; }//fibBits++;
        }
        
        for ( int i = 0; i < bits; i++ ) {
            fibSaveCache();
            fibCache = fibCache |  ( ( numCache & 1 ) << fibBits );
            fibBits++;
            numCache = numCache >> 1;
        }

        return true;
    }

    bool Encoder::fibFlush( string &result ) {
        if ( error ) return false;
        
        fibBits = 8;
        fibSaveCache();
        result  = fibBytes;
        
        return true;
    }

    void Encoder::fibSaveCache() {
        if ( fibBits == 8 ) {
            fibBytes += fibCache;
            fibCache = fibCache & 0;
            fibBits  = 0;
        }
    }

    unsigned char Encoder::utfMaskByte( const int &c) const {
        return (unsigned char) ( (c & 0x3f) | 0x80 );
    }

    void Encoder::fibSequence() {
        fibs[0] = 1;
        fibs[1] = 2;
        
        for ( int i = 2; i < 29; i++ ) {
            fibs[i] = fibs[i-1] + fibs[i-2];
        }
    }

    Encoder::~Encoder() {
        delete[] fibs;
    }


bool Utf8ToFibonacci ( const char * inFile, const char * outFile )
{
    Encoder enc;
    Reader utf( inFile );
    string result = "";
    unsigned int tmp = 0;
    ofstream os ( outFile, ios::binary | ios::out );
    
    while ( ! os.fail() && utf.utfGetNext( tmp ) ) {
        enc.toFib( tmp );
    }
    
    enc.fibFlush( result );
    
    if ( os.fail() || utf.fail() ) { os.close(); return false; }
    
    for ( int i = 0; i < (int) result.length(); i++ ) {
        os.write(&result[i], 1);
        if ( os. fail() )  { os.close(); return false; }
    }
    
    os.close();
    
    return true;
}

bool FibonacciToUtf8 ( const char * inFile, const char * outFile )
{
    Encoder enc;
    Reader fib( inFile );
    string result = "";
    unsigned int tmp = 0;
    ofstream os( outFile, ios::binary | ios::out );
    
    while ( ! os.fail() && fib.fibGetNext( tmp ) ) {
        enc.toUtf( tmp, result );
    }
    
    if ( fib.fail() || os.fail() ) { os.close(); return false; }
    
    for ( int i = 0; i < (int) result.length(); i++ ) {
        os.write(&result[i], 1);
        if ( os. fail() )  { os.close(); return false; }
    }
    
    os.close();
    
    return true;
}

#ifndef __PROGTEST__
int main ( )
{
//    int a = 1, b = 2, c = 3, d = 2;
//    
//    
//    while ( c <= 0x10ffff ) {
//        cout << c << endl;
//        a = b;
//        b = c;
//        c = a + b;
//        d++;
//        
//    }
//    
//    cout << d << endl;
//    const char *inFile  = "toUtf/test_4.fib";
//    const char *outFile = "test";
//    
//    if ( ! FibonacciToUtf8( inFile, outFile ) ) {
//        cout << "chyba" << endl;
//    } else cout << "ok" << endl;
    
//    Encoder enc;
//    string fibcode = "";
//    
//    enc.toFib( 0 );
//    enc.toFib( 5 );
//    enc.toFib( 10 );
//    
//    if ( ! enc.fibFlush( fibcode ) ) {
//        cout << "dsdsd";
//    }
//    
//    cout << fibcode.length() << endl;
//    
//    bitset<8> bs1(fibcode[0]);
//    bitset<8> bs2(fibcode[1]);
//    
//    cout << bs1 << " " << bs2 << endl;
    
    
//    unsigned int a = 2;
//    Encoder enc;
//    string test = "";
//
//    const char * inFile = "test_0.fib";
//    
//    ofstream os( "test", ios::binary | ios::out );
//    Reader fib( inFile );
//    
//    while ( fib.fibGetNext( a ) ) {
//        enc.toUtf( a, test );
//    }
//    
//    for ( int i = 0; i < (int) test.length(); i++ )
//        os.write(&test[i], 1);
//    
//    if ( fib.fail() ) {
//        cout << "chyba" << endl;
//        return 1;
//    }
//    
//    os.close();
//    
//    
//    
//    return 0;
//    
//    enc.toFib(a, test);
//    
//    
//
//    
//    if( enc.toUtf( 20049, test ) )
//        for ( int i = 0; i < (int) test.length(); i++ )
//            os.write(&test[i], 1);
//    else
//        cout << "chyba" << endl;
//    
//    os.close();
//    
//    Reader  utfR( "test" );
//    
//    utfR.utfGetNext( a );
//    
//    cout << a << endl;

    return 0;
}
#endif /* __PROGTEST__ */
