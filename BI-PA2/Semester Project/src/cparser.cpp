//Author: Josef Dolezal
//dolezjo3@fit.cvut.cz


#include "cparser.h"


//! \brief Constructor initialize new instance from String.
//! \param expression String containing math expression.
CParser::CParser( const string &expression ) {
    parse( expression );
}

//! \brief Desctructor releases all sources that object created.
CParser::~CParser( void ) {
    while( ! m_Queue.empty() ) {
        delete m_Queue.front();
        m_Queue.pop();
    }
    
    while( ! m_Ops.empty() ) {
        delete m_Ops.top();
        m_Ops.pop();
    }
}

//! \brief If Queue is not empty, returns pointer to the CToken
//! \return If Queue is not empty, returns pointer to the CToken, otherwise NULL.
CToken * CParser::Front( void ) {
    CToken *tmp = NULL;
    if( m_Queue.empty() ) return tmp;
    
    tmp = m_Queue.front();
    m_Queue.pop();
    return tmp;
}

//! \brief Prints postfix notation of infix formule.
void CParser::ShowPostfix( void ) const {
    queue<CToken *> tmp = m_Queue;
    
    while( ! tmp.empty() ) {
        cout << *tmp.front() << " ";
        tmp.pop();
    }
    
    cout << endl;
}

//! \brief Parses infix notatation to tokens.
//! \param l Expression in infix format.
void CParser::parse ( const string &l ) {
    int index = 0;
    
    while( nextToken( l, index ) );
    
    while( ! m_Ops.empty() ) {
        if( *(m_Ops.top()) == L_BRACKET ) throw ParenthesesMismatchException();
        
        m_Queue.push( m_Ops.top() );
        m_Ops.pop();
    }
}

//! \brief Extracts next token from expression.
//! \param line String with expression.
//! \param index Position of cursor in String.
//! \return True if token was successfully readed.
bool CParser::nextToken ( const string &line, int &index ) {
    string tmp;
    bool   iws = true;
    bool   op  = false;
    
    if( index >= (int) line.length() ) return false;
    
    for ( ; index < (int) line.length(); index++ ) {
        char c = line[index];
        
        if( isblank( c ) ) {
            if( iws ) continue;
            else break;
        }
        
        if( isOperator( c ) ) {
            if( tmp.length() > 0 )
                break;
            
            index++;
            op = true;
        }
        
        iws = false;
        tmp += c;
        
        if( op ) break;
    }
    
    if( ! ( tmp.length() > 0 ) ) return false;
    
    if( ! op ) m_Queue.push( new CNum( tmp ) );
    else if ( tmp[0] == L_BRACKET ) m_Ops.push( new COperator( tmp[0], operatorPrecedence( tmp[0] ) ) );
    else if( tmp[0] != R_BRACKET ){
        COperator *op = new COperator( tmp[0], operatorPrecedence( tmp[0] ) );
        
        while( ! m_Ops.empty() ) {
            if( *m_Ops.top() == L_BRACKET || *op > *m_Ops.top() ) break;
            m_Queue.push( m_Ops.top() );
            m_Ops.pop();
        }
        
        m_Ops.push( op );
    } else {
        bool m = false;
        while( ! m_Ops.empty() ) {
            COperator *tmp = m_Ops.top();
            m_Ops.pop();
            
            if( *(tmp) != L_BRACKET ) m_Queue.push( tmp );
            else {
                m = true;
                delete tmp;
                break;
            }
        }
        if( ! m ) throw ParenthesesMismatchException();
    }
    
    return true;
}

//! \brief Checks if given character contains math operator.
//! \param c Char to check.
//! \return True if character is math operator.
bool CParser::isOperator( char c ) const {
    return ( c == '+' || c == '-' || c == '*' || c == '(' || c == ')' );
}

//! \brief Checks operator precedence.
//! \param c Operator.
//! \return Integer value of precedence.
int CParser::operatorPrecedence( char c ) const {
    if( c == '+' || c == '-' ) return 1;
    if( c == '*' || c == '(' || c == ')' ) return 2;
    
    return 0;
}

//! \brief Represents exception description.
//! \return Array of chars representing dscription.
const char * ParenthesesMismatchException::what( void ) const noexcept {
    return "CParser: Mismatched parentheses in input expression.";
}

//! \brief Represents exception description.
//! \return Array of chars representing description.
const char * NotAnExpressionException::what( void ) const noexcept {
    return "CParser: Input string is not valid expression.";
}

