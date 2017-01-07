#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

class CCagePipes {
private:
    struct TLandMark {
        vector<pair<TLandMark *, int> > childs;
        vector<int>       prices;
        bool              counted;
        bool              visited;
        
        TLandMark( const int pumps = 0 ): counted(false), visited(false) {
            clear_prices( pumps );
        }
        
        void  clear_prices( const int pumps_count ) {
            for( int i = 0; i < pumps_count; ++i )
                prices.push_back(0);
        }
        
        void  add_child( TLandMark * child, const int child_price = 0 ) {
            childs.push_back( make_pair(child, child_price ) );
        }
        
        int   min_price_to( int end_num, int price ) {
            int c   = (int) prices.size();
            int min = price_to( 0, end_num, price );
            
            for( int i = 1; i < c; ++i ) {
                int cost = price_to( i, end_num, price );
                min = cost < min ? cost : min;
                
                if( min == 0 ) return min;
            }
            
            return min;
        }
        
        void  update_prices() {
            visited = true;
            
            // leaf
            if( childs.size() == 0 ) {
                counted = true;
                return;
            }
            
            int k = (int) prices.size();
            
            for( auto child : childs ) {
                // Not actualy my child
                if( (child.first)->visited ) continue;
                
                // Child prices
                if( ! (child.first)->counted ) (child.first)->update_prices();
                
                for( int to = 0; to < k; ++to )
                    prices[to] += (child.first)->min_price_to( to, (child.second) );
                
            }
            
            counted = true;
        }
        
        int   price_to( const int from, const int to, const int pipe_price ) {
            if( from < to ) return prices[from];
            
            return prices[from] + pipe_price;
        }
    };
    
    TLandMark **  marks;
    int           marks_count;
    int           pipe_types;
    
    
public:
    CCagePipes( const int marks_count, const int pipe_types ):
    marks_count(marks_count), pipe_types(pipe_types) {
        marks = new TLandMark*[marks_count];
        
        for( int i = 0; i < marks_count; ++i )
            marks[i] = NULL;
    }
    
    ~CCagePipes() {
        for( int i = 0; i < marks_count; ++i )
            delete marks[i];
        
        delete[] marks;
    }
    
    void  add_landmark( int from, int to, int price ) {
        TLandMark * parent = marks[from] == NULL ? new TLandMark( pipe_types ) : marks[from];
        TLandMark * child  = marks[to] == NULL ? new TLandMark( pipe_types ) : marks[to];
        
        parent->add_child( child, price );
        child->add_child( parent, price );
        
        marks[from] = parent;
        marks[to]   = child;
    }
    
    int   find_cheapest() {
        marks[0]->update_prices();
        return cheapest_from_root();
    }
    
    int   cheapest_from_root() {
        int min = marks[0]->prices[0];
        
        for( int i = 1; i < pipe_types; ++i ) {
            if( marks[0]->prices[i] < min ) min = marks[0]->prices[i];
            if( min == 0 ) return min;
        }
        
        return min;
    }
};

int main() {
    int marks_count, pumps_types;
    
    cin >> marks_count;
    cin >> pumps_types;
    
    CCagePipes cage( marks_count, pumps_types );
    
    for( int i = 0; i < marks_count - 1; i++ ) {
        int from, to, price;
        cin >> from;
        cin >> to;
        cin >> price;
        
        cage.add_landmark( from, to, price );
    }
    
    cout << cage.find_cheapest() << endl;
    
    return 0;
}