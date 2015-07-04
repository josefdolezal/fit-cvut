/* author: josef dolezal */
/* git: https://github.com/josefdolezal */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class CElement {
public:
           CElement             ( const string & );
    int    GetIntend            ( void ) const { return intend; }
    friend ostream& operator << ( ostream &, const CElement & );
private:
    string label;
    string shape;
    int    intend;
    
    void   SetLabel   ( const string & );
    void   SetShape   ( const string & );
    void   ParseInput ( const string & );
    string GetShape   ( const string & );
};

class CDiagram {
public:
           CDiagram             ( const string &n ) : name(n) {}
    void   Add                  ( const CElement & );
    friend ostream& operator << ( ostream &os, const CDiagram &d ) { d.Print( os ); return os; }
private:
    string name;
    vector<CElement> elements;
    void   Print          ( ostream & ) const;
    void   PrintRelations ( ostream & ) const;
};
/* ----------------------------------------------- */
void CDiagram::Add( const CElement &e ) {
    elements.push_back( e );
}
void CDiagram::Print( ostream &os ) const {
    os << "digraph " << name << " {" << endl;
    os << "0[label=\"/\", shape=house]" << endl; // root
    for ( int i = 0; i < (int) elements.size(); i++ ) os << i + 1 << elements[i] << endl;
    PrintRelations( os );
    os << "}";
}
void CDiagram::PrintRelations( ostream &os ) const {
    os << "0 -> 1" << endl; // root
    for( int i = 0; i < (int) elements.size(); i++ ) {
        for ( int j = i+1; j < (int) elements.size(); j++ ) {
            if( elements[i].GetIntend() + 1 == elements[j].GetIntend() )
                os << i+1 << " -> " << j+1 << endl;
            if ( elements[i].GetIntend() >= elements[j].GetIntend() ) break;
        }
    }
}
/* ----------------------------------------------- */
CElement::CElement( const string &val ): intend(0) {
    ParseInput( val );
}
void   CElement::ParseInput ( const string &r ) {
    int    i = 0;
    string tmp;
    
    for ( ; i < (int) r.length(); i++ ) if( r[i] == ' ' ) intend++; else break;
    for ( ++i; i < (int) r.length(); i++ ) if( r[i] != ' ' ) tmp += r[i]; else  { i++; break; }
    
    label = r.substr( i, r.size() - i );
    shape = GetShape( tmp );
    
    if( tmp == "attribute" ) {
        i = (int) label.find( "=" );
        if( i !=string::npos ) label.replace( i, 1, "\\n" );
    }
    if( tmp == "processing-instruction" ) {
        i = (int) label.find( " " );
        if( i !=string::npos ) label.replace( i, 1, "\\n" );
    }
}
void   CElement::SetLabel   ( const string & ) {}
void   CElement::SetShape   ( const string & ) {}
string CElement::GetShape   ( const string &k ) {
    if      ( k == "element" ) return "circle";
    else if ( k == "attribute" ) return "diamond";
    else if ( k == "text" ) return "plaintext";
    else if ( k == "entity-reference" ) return "oval";
    else if ( k == "processing-instruction" ) return "triangle";
    else if ( k == "cdata-section" ) return "trapezium";
    else if ( k == "comment" ) return "note";
    return "";
}
ostream& operator << ( ostream &os, const CElement &e ) {
    os << "[label=\"" << e.label << "\", shape=" << e.shape << "]";
    return os;
}



int main( void ) {
    CDiagram diagram("A");
    string cache;
    
    while( getline( cin, cache ) && (int) cache.length() > 0 )
        diagram.Add( CElement( cache ) );

    cout << diagram << endl;
    
    return 0;
}
