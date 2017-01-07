#ifndef __PROGTEST__
#include <sstream>
#include <iostream>
#include <assert.h>

using namespace std;

class NotFoundException {
  public:
    NotFoundException() {}
    ostream& print( ostream & os ) const { os << "Value not found"; return os; }
    friend ostream& operator<<(ostream& os, const NotFoundException& e ) { return e.print( os ); }
};

class CValue {
  public:
    CValue( void ): value(0) { }

    CValue( const CValue &i ): value(i.value) { }

    CValue( const int & i ): value( i ) { };

    ~CValue( void ) { }

    CValue& operator = ( const CValue &i ) {
      if( this == &i ) return *this;

      value = i.value;
      return *this;
    }

    bool operator == ( const CValue &i ) const { return value == i.value; }
    bool operator != ( const CValue &i ) const { return value != i.value; }
    bool operator <  ( const CValue &i ) const { return value < i.value;  }
    bool operator >  ( const CValue &i ) const { return value > i.value;  }
    bool operator >= ( const CValue &i ) const { return value >= i.value; }
    bool operator <= ( const CValue &i ) const { return value <= i.value; }

    friend ostream & operator << ( ostream & os, const CValue & val ) {
      os << val.value;
      return os;
    }
  private:
    int value;
};

class CKey {
  public:
    CKey( void ): key(0) { }

    CKey( const CKey &i ) { key = i.key; }

    CKey( const int & i ): key( i ) { }

    ~CKey( void ) { }

    CKey& operator = ( const CKey &i ) {
      if( this == &i ) return *this;

      key = i.key;
      return *this;
    }

    bool operator == ( const CKey &i ) const { return key == i.key; }
    bool operator != ( const CKey &i ) const { return key != i.key; }
    bool operator <  ( const CKey &i ) const { return key < i.key;  }
    bool operator >  ( const CKey &i ) const { return key > i.key;  }
    bool operator >= ( const CKey &i ) const { return key >= i.key; }
    bool operator <= ( const CKey &i ) const { return key <= i.key; }

    friend ostream & operator << ( ostream & os, const CKey & key ) {
      os << key.key;
      return os;
    }

  private:
    int key;
};
#endif /* __PROGTEST__ */



class CNode {
  public:
    CNode( void ): left(NULL), right(NULL), parent(NULL), color('R') { }

    CNode( const CKey &key, const CValue &value, const char &color = 'R' ): left(NULL), right(NULL), parent(NULL), color(color), key(key), value(value) { }

    char   getColor  ( void ) const { return color;  }
    CNode* getParent ( void ) const { return parent; }
    CNode* getLeft   ( void ) const { return left;   }
    CNode* getRight  ( void ) const { return right;  }
    CKey   getKey    ( void ) const { return key;    }
    CValue getValue  ( void ) const { return value;  }

    void setKey    ( const CKey & k )    { key = k;    }
    void setValue  ( const CValue & cv ) { value = cv; }
    void setParent ( CNode * p )         { parent = p; }
    void setLeft   ( CNode * l )         { left = l;   }
    void setRight  ( CNode * r )         { right = r;  }
    void setColor  ( const char & c )    { color = c;  }

    bool leftIsBlack( void ) const {
      return left == NULL || left->getColor() == 'B';
    }

    bool rightIsBlack( void ) const {
      return right == NULL || right->getColor() == 'B';
    }

    CNode& operator = ( const CNode & i );

    bool operator == ( const CNode & i ) const { return key == i.key; }
    bool operator != ( const CNode & i ) const { return key != i.key; }
    bool operator <  ( const CNode & i ) const { return key < i.key;  }
    bool operator >  ( const CNode & i ) const { return key > i.key;  }
    bool operator >= ( const CNode & i ) const { return key >= i.key; }
    bool operator <= ( const CNode & i ) const { return key <= i.key; }

    bool isLeaf( void ) const {
      return left == NULL && right == NULL;
    }

    void removeChild( CNode * c ) {
      if( left == c ) left = NULL;
      if( right == c ) right = NULL;
    }

    ~CNode( void ) {
      if( right )
        delete right;
      if( left )
        delete left;
    }

#ifndef __PROGTEST__
    friend ostream & operator << ( ostream & os, const CNode & t ) {
      os << " " << t.color << "(" << t.key << ", " << t.value << ") ";

      if( t.left != NULL ) os << *(t.left); else os << " null ";
      if( t.right != NULL ) os << *(t.right); else os << " null ";

      return os;
    }
#endif /* __PROGTEST__ */

  private:
    CNode  * left;
    CNode  * right;
    CNode  * parent;
    char     color;
    CKey     key;
    CValue   value;
};

class CTable {
  public:
    CTable(): root(NULL) {}
    ~CTable() { if( root != NULL ) delete root; }

    bool insert( const CKey& key, const CValue& val ) {
      if( ! root ) {
        root = new CNode( key, val, 'B' );
        return true;
      }

      CNode * parent  = NULL;
      CNode * current = root;
      CNode * n_node  = new CNode( key, val );

      while( current ) {
        parent = current;

        if ( *n_node == *current ) {
          current->setValue( n_node->getValue() );
          delete n_node;
          return false;
        } else if ( *n_node < *current ) // its left child
          current = current->getLeft();
        else
          current = current->getRight();
      }

      if( *n_node < *parent )
        parent->setLeft( n_node );
      else
        parent->setRight( n_node );

      n_node->setParent( parent );

      // Balance tree
      case1( n_node );

      return true;
    }

    bool remove( const CKey& key ) {
      CNode * target = findElement( key );

      if( target == NULL ) return false;

      removeElement( target );
      return true;
    }

    CValue search( const CKey& key ) const {
      CNode * tmp = findElement( key );

      if( tmp == NULL ) throw NotFoundException();

      return tmp->getValue();
    }

    bool isElem( const CKey& key ) const {
      CNode * tmp = findElement( key );

      return tmp != NULL;
    }

    CNode * getRoot( void ) const { return root; }

#ifndef __PROGTEST__
    void inorder( void ) const {
      if( root ) cout << *root;
    }

    friend ostream & operator << ( ostream & os, const CTable & t ) {
      if( t.root )
        os << *(t.root);
      else os << "kde nic tu nic";

      return os;
    }
#endif /* __PROGTEST__ */

  private:
    CNode * root;

    CNode * getGrandParentOf( const CNode * i ) const {
      if( i != NULL && i->getParent() != NULL )
        return i->getParent()->getParent();
      else return NULL;
    }

    CNode * getUncleOf( const CNode * i ) const {
      CNode * gp = getGrandParentOf( i );

      if( gp == NULL ) return NULL;

      if( i->getParent() == gp->getLeft() ) return gp->getRight();

      return gp->getLeft();
    }

    CNode * getSiblingOf( const CNode * c ) const {
      if( c == NULL || c->getParent() == NULL ) return NULL;

      if( c->getParent()->getRight() == c ) return c->getParent()->getLeft();

      return c->getParent()->getRight();
    }

    CNode * findElement( const CKey & k ) const {
      CNode s( k, CValue() );
      CNode * tmp = root;

      while( tmp ) {
        if( s == *tmp ) break;
        else if( s < *tmp ) tmp = tmp->getLeft();
        else if( s > *tmp ) tmp = tmp->getRight();
      }

      return tmp;
    }

    void removeElement( CNode * target ) {
      CNode * p = NULL;
      CNode * s = NULL;

      if( target->isLeaf() ) { // Leaf
        p = target->getParent();
        s = getSiblingOf( target );

        if( p != NULL ) p->removeChild( target );
        else root = NULL;

        if( target->getColor() == 'B' ) dCase1( s );

        delete target;
      } else if( target->getLeft() == NULL && target->getRight() != NULL ) { // Only right child
        p = target->getParent();
        s = getSiblingOf( target );
        CNode * r = target->getRight();

        r->setParent( p );

        if( p != NULL )
          if( p->getRight() == target ) p->setRight( r );
          else p->setLeft( r );
        else root = r;

        target->setRight( NULL );

        if( r->isLeaf() && r->getColor() == 'R' ) {
          r->setColor( 'B' );
          delete target;
          return;
        }

        if( target->getColor() == 'B' ) dCase1( s );
        delete target;
      } else if( target->getRight() == NULL && target->getLeft() != NULL ) { // Only left child
        p = target->getParent();
        s = getSiblingOf( target );
        CNode * l = target->getLeft();

        l->setParent( p );

        if( p != NULL )
          if( p->getRight() == target ) p->setRight( l );
          else p->setLeft( l);
        else root = l;

        target->setLeft( NULL );

        if( l->isLeaf() && l->getColor() == 'R' ) {
          l->setColor( 'B' );
          delete target;
          return;
        }

        if( target->getColor() == 'B' ) dCase1( s );
        delete target;
      } else { // Two childs
        CNode * p = findPredecessor( target );

        target->setKey( p->getKey() );
        target->setValue( p->getValue() );

        removeElement( p );
      }
    }

    void rotateLeft( CNode * i ) {
      CNode * tmp = i->getRight();

      i->setRight( tmp->getLeft() );

      if( i->getRight() != NULL ) i->getRight()->setParent( i );

      tmp->setParent( i->getParent() );

      if( i->getParent() == NULL ) root = tmp;
      else if ( i == i->getParent()->getLeft() ) i->getParent()->setLeft( tmp );
      else i->getParent()->setRight( tmp );

      tmp->setLeft( i );
      i->setParent( tmp );
    }

    void rotateRight( CNode * i ) {
      CNode * tmp = i->getLeft();

      i->setLeft( tmp->getRight() );

      if( tmp->getRight() != NULL ) tmp->getRight()->setParent( i );

      tmp->setParent( i->getParent() );

      if( tmp->getParent() == NULL ) root = tmp;
      else if( i == i->getParent()->getLeft() ) i->getParent()->setLeft( tmp );
      else i->getParent()->setRight( tmp );

      tmp->setRight( i );
      i->setParent( tmp );
    }

    void case1( CNode * i ) {
      if( i->getParent() == NULL ) i->setColor( 'B' ); // root
      else {
        i->setColor( 'R' );
        case2( i );
      }
    }

    void case2( CNode * i ) {
      if ( i->getParent()->getColor() != 'B' ) case3( i );
    }

    void case3( CNode * i ) {
      CNode * uncle = getUncleOf( i );

      if( uncle != NULL && uncle->getColor() == 'R' ) {
        i->getParent()->setColor( 'B' );
        uncle->setColor( 'B' );

        CNode * gp = getGrandParentOf( i );
        if( gp != root ) gp->setColor( 'R' );

        case1( gp );
      } else case4( i );
    }

    void case4( CNode * i ) {
      CNode * gp = getGrandParentOf( i );

      if( i == i->getParent()->getRight() && i->getParent() == gp->getLeft() ) {
        rotateLeft( i->getParent() );
        i = i->getLeft();
      } else {
        if ( i == i->getParent()->getLeft() && i->getParent() == gp->getRight() ) {
          rotateRight( i->getParent() );
          i = i->getRight();
        }
      }

      case5( i );
    }

    void case5( CNode * i ) {
      CNode * gp = getGrandParentOf( i );

      i->getParent()->setColor( 'B' );
      gp->setColor( 'R' );

      if( i == i->getParent()->getLeft() && i->getParent() == gp->getLeft() ) {
        rotateRight( gp );
      } else if( i == i->getParent()->getRight() && i->getParent() == gp->getRight() )
        rotateLeft( gp );
    }

    void dCase1( CNode * s ) {
      if( s != NULL && s->getParent() != NULL ) {
        if( s->getColor() == 'R' ) {
          CNode * p = s->getParent();
          if( p->getRight() == s ) { // S is right child
            rotateLeft( p );
            s->setColor( 'B' );
            s->getLeft()->setColor( 'R' );
            s = p->getRight();
          }
          else { // S is left child
            rotateRight( p );
            s->setColor( 'B' );
            s->getRight()->setColor( 'R' );
            s = p->getLeft();
          }
        }

        dCase2( s );
      }
    }

    void dCase2( CNode * s ) {
      if( s->getParent() == NULL ) return;

      if( s->getColor() == 'B' && s->rightIsBlack() && s->leftIsBlack() ) {
        s->setColor( 'R' );
        if( s->getParent()->getColor() == 'R' ) {
          s->getParent()->setColor( 'B' );
          return;
        }

        dCase1( getSiblingOf( s->getParent() ) );
      } else dCase3( s );
    }

    void dCase3( CNode * s ) {
      CNode * p = s->getParent();
      if( p == NULL ) return;

      if( s->getColor() == 'B' ) {
        if( p->getRight() == s && s->getRight() != NULL && s->getRight()->getColor() == 'R' ) { // S is right child
          rotateLeft( p );
          char t = s->getColor();
          s->setColor( p->getColor() );
          p->setColor( t );

          if( s->getRight() != NULL ) s->getRight()->setColor( 'B' );
          return;
        } else if ( p->getLeft() == s && s->getLeft() != NULL && s->getLeft()->getColor() == 'R' ) { // S is left child
          rotateRight( p );
          char t = s->getColor();
          s->setColor( p->getColor() );
          p->setColor( t );

          if( s->getLeft() != NULL ) s->getLeft()->setColor( 'B' );
          return;
        }
      }

      dCase4( s );
    }

    void dCase4( CNode * s ) {
      if( s->getParent() == NULL ) return;
      if( s->getColor() == 'B' ) {
        if( s->getParent()->getRight() && s->rightIsBlack() && s->getLeft() != NULL && s->getLeft()->getColor() == 'R' ) { // S is right child
          CNode * l = s->getLeft();
          rotateRight( s );
          char t = s->getColor();
          s->setColor( l->getColor() );
          l->setColor( t );

          dCase3( l );
        } else if( s->getParent()->getLeft() && s->leftIsBlack() && s->getRight() != NULL && s->getRight()->getColor() == 'R' ) { // S is left child
          CNode * r = s->getRight();
          rotateLeft( s );
          char t = s->getColor();
          s->setColor( r->getColor() );
          r->setColor( t );

          dCase3( r );
        }
      }
    }

    CNode * findPredecessor( const CNode * v ) const {
      CNode * ret = v->getLeft();

      if( ret == NULL ) v->getParent();

      while( ret != NULL )
        if( ret->getRight() != NULL ) ret = ret->getRight();
        else break;

      return ret;
    }
};

#ifndef __PROGTEST__
void tests() {
  ostringstream oss;
  CTable t;

  oss.str( "" );
  oss.clear();

  t.insert( 20, 20 );
  t.insert( 8, 8 );
  t.insert( 40, 40 );
  t.insert( 7, 7 );
  t.insert( 9, 9 );
  t.insert( 21, 21 );
  t.insert( 41, 41 );
  t.insert( 6, 6 );
  t.insert( 5, 5 );

  CTable t2;

  t2.insert( 10, 20 );
  t2.insert( 85, 20 );
  t2.insert( 15, 20 );
  t2.insert( 70, 20 );
  t2.insert( 20, 20 );
  t2.insert( 60, 20 );
  t2.insert( 30, 20 );
  t2.insert( 50, 20 );
  t2.insert( 65, 20 );
  t2.insert( 80, 20 );
  t2.insert( 90, 20 );
  t2.insert( 40, 20 );
  t2.insert( 5, 20 );
  t2.insert( 55, 20 );

  oss.str( "" );
  oss.clear();

  oss << t2;
  assert( oss.str() == " [30] -> *20* (B)  [15] -> *20* (B)  [10] -> *20* (B)  [5] -> *20* (R)  null  null  null  [20] -> *20* (B)  null  null  [70] -> *20* (B)  [60] -> *20* (R)  [50] -> *20* (B)  [40] -> *20* (R)  null  null  [55] -> *20* (R)  null  null  [65] -> *20* (B)  null  null  [85] -> *20* (B)  [80] -> *20* (R)  null  null  [90] -> *20* (R)  null  null " );

  t2.remove( 90 );
  oss.str( "" );
  oss.clear();

  oss << t2;
  assert( oss.str() == " [30] -> *20* (B)  [15] -> *20* (B)  [10] -> *20* (B)  [5] -> *20* (R)  null  null  null  [20] -> *20* (B)  null  null  [70] -> *20* (B)  [60] -> *20* (R)  [50] -> *20* (B)  [40] -> *20* (R)  null  null  [55] -> *20* (R)  null  null  [65] -> *20* (B)  null  null  [85] -> *20* (B)  [80] -> *20* (R)  null  null  null " );

  t2.remove( 85 );
  oss.str( "" );
  oss.clear();

  oss << t2;
  //assert( oss.str() == " [30] -> *20* (B)  [15] -> *20* (B)  [10] -> *20* (B)  [5] -> *20* (R)  null  null  null  [20] -> *20* (B)  null  null  [70] -> *20* (B)  [60] -> *20* (R)  [50] -> *20* (B)  [40] -> *20* (R)  null  null  [55] -> *20* (R)  null  null  [65] -> *20* (B)  null  null  [80] -> *20* (R)  null  null " );

}

void remove( void ) {
  CTable t;
  CTable t2;
  ostringstream oss;

  oss.str( "" );
  oss.clear();

  t.insert( 20, 20 );
  t.insert( 40, 20 );
  t.insert( 30, 20 );
  t.insert( 50, 20 );

  t.remove( 40 );
  oss << t;
  assert( oss.str() == " B(30, 20)  B(20, 20)  null  null  B(50, 20)  null  null " );

  t2.insert( 10, 20 );
  t2.insert( 85, 20 );
  t2.insert( 15, 20 );
  t2.insert( 70, 20 );
  t2.insert( 20, 20 );
  t2.insert( 60, 20 );
  t2.insert( 30, 20 );
  t2.insert( 50, 20 );
  t2.insert( 65, 20 );
  t2.insert( 80, 20 );
  t2.insert( 90, 20 );
  t2.insert( 40, 20 );
  t2.insert( 5, 20 );
  t2.insert( 55, 20 );

  assert( t2.remove( 90 ) == true );
  t2.remove( 85 );
  t2.remove( 30 );
  t2.remove( 20 );
  t2.remove( 70 );
  t2.remove( 15 );
  t2.remove( 65 );
  t2.remove( 80 );
  t2.remove( 5 );
  assert( t2.remove( 10 ) == true );
  t2.remove( 40 );
  t2.remove( 60 );
  t2.remove( 55 );
  t2.remove( 50 );

  try {
    assert( t2.search( 23 ) == false );
    cout <<  "1";
  } catch ( NotFoundException e ) { }

  assert( t2.getRoot() == NULL );
  assert( t2.isElem( 23 ) == false );
}

void loader( void ) {
  CTable t;

  int key;
  while( cin >> key )
    t.insert( key, 20 );

  cout << t;
}

int main( void ) {
  //tests();
  //loader();
  remove();
  return 0;
}

#endif /* __PROGTEST__ */
