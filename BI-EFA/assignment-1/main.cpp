#include <iostream>
#include <cstdlib>

using namespace std;

struct SHours {
    int       start;
    long long price;
    int       end;
    SHours *  next;
    
    SHours( const int day = 0, const int to = 0, const long long pr = 0, SHours * next = NULL ):
    start( day ), price( pr ), end( to ), next( next ) {}
    
    long long get_price() {
        //cout << ( end - start + 1 ) * price << endl;
        return ( end - start + 1 ) * price;
    }
    
    bool operator <  ( const SHours & s ) const {
        return start < s.start;
    }
    
    ~SHours() {
        if( next )
            delete next;
    }
};

void you_will_die_at( int day ) {
    cout << "You will die at day " << day << endl;
}

ostream & operator << ( ostream & os, const SHours & sh ) {
    os << "<" << sh.start << "," << sh.end << ":" << sh.price << ">";
    
    return os;
}

SHours ** load_working_days( const int count, const int max ) {
    SHours **w_days = new SHours*[count];
    
    for( int i = 0; i < count; i ++ ) {
        int start = 0, price = 0, e = 0;
        
        cin >> start;
        cin >> price;
        cin >> e;
        e += start;
        e = e > max ? max : e;
        w_days[i] = new SHours( start, e, price );
    }
    
    qsort(w_days, count, sizeof(SHours*), [](const void* a, const void* b) {
        //SHours arg1 = *static_cast<const SHours*>(a);
        SHours *arg1 = *((SHours**)a);
        SHours *arg2 = *((SHours**)b);
        
        return (*arg2 < *arg1) - (*arg1 < *arg2);
        return 0;
    } );
    // sort( w_days, w_days + count );
    return w_days;
}

SHours * split_interval( SHours * ver_pos, SHours * new_val ) {
    if( ver_pos->price > new_val->price ) {
        
        // Paste it to the middle
        if( new_val->start > ver_pos->start && new_val->start <= ver_pos->end ) {
            SHours *splitted = new SHours( new_val->start, ver_pos->end,
                                          ver_pos->price, ver_pos->next);
            
            ver_pos->end  = new_val->start - 1;
            ver_pos->next = splitted;
            ver_pos = splitted;
            
            // recursion -> paste new to the begin
            return split_interval( ver_pos, new_val );
            //return ver_pos;
            
            // Paste it to the beign
        } else if( new_val->start == ver_pos->start ) {
            // new interval is longer
            if( new_val->end > ver_pos->end ) {
                ver_pos->price = new_val->price;
                new_val->start = ver_pos->end + 1;
                
                // paste to end
                return split_interval( ver_pos, new_val );
                //return ver_pos;
            }
            
            int end = ver_pos->end;
            long long price = ver_pos->price;
            
            ver_pos->end = new_val->end;
            ver_pos->price = new_val->price;
            
            // new interval was shorter
            if( ver_pos->end < end ) {
                new_val->start = ver_pos->end + 1;
                new_val->end   = end;
                new_val->price = price;
                new_val->next  = ver_pos->next;
                ver_pos->next = new_val;
            } else {
                delete new_val;
            }
            return ver_pos;
        }
    } else {
        if( ver_pos->end < new_val->end ) {
            if( new_val->start <= ver_pos->end + 1 )
                new_val->start = ver_pos->end + 1;
            
            if( ver_pos->next ) {
                return split_interval( ver_pos->next, new_val );
            }
        } else {
            delete new_val;
            return ver_pos;
        }
    }
    
    // Paste it to the end
    SHours * n = ver_pos->next;
    if( n ) {
        // inserting too big
        if( new_val->start >= n->start )
            return split_interval( n, new_val );
        else {
            int end = new_val->end;
            new_val->end = n->start - 1;
            new_val->next = n;
            ver_pos->next = new_val;
            
            if( new_val->end < end ) {
                SHours * t = new SHours( n->start, end, new_val->price );
                split_interval( n, t );
                return new_val;
            }
        }
    } // make it end of list
    else  {
        ver_pos->next = new_val;
        
        if( ver_pos->end + 1 < new_val->start ) {
            you_will_die_at( ver_pos->end + 1 );
            return NULL;
        }
        ver_pos->next = new_val;
        return ver_pos;
    }
    return ver_pos;
}

void debug( SHours * st, int sz ) {
    for( int i = 0; i < sz; i++ )
        cout << st[i] << endl;
}

void print_linked( SHours * l ) {
    cout << *l;
    
    if( l->next ) {
        cout << " -> ";
        print_linked( l->next );
    }
}

int main() {
    int ill_days = 0,
        days_count = 0;
    
    long long current_price = 0;
    long long sum = 0;
    
    SHours * range_list   = NULL,
    * verified_pos = NULL;
    SHours ** w_days       = NULL;
    
    cin >> ill_days;
    cin >> days_count;
    
    w_days = load_working_days( days_count, ill_days );
    
    for( int i = 0; i < days_count; ++i ) {
        SHours * curr = w_days[i];
        SHours * n_ver = NULL;
        
        if( ! verified_pos ) {
            verified_pos = range_list = curr;
            current_price = curr->price;
            
            if( verified_pos->start != 1 ) {
                you_will_die_at( 1 );
                delete[] w_days;
                delete verified_pos;
                
                return 0;
            }
            
            continue;
        }
        
        current_price += curr->price;
        curr->price    = current_price;
        
        n_ver = split_interval( verified_pos, curr );
        
        if( ! n_ver ) {
            //debug(w_days, days_count);
            //print_linked( range_list );
            delete[] w_days;
            delete range_list;
            //delete curr;
            return 0;
        }
        
        while( n_ver != verified_pos ) {
            sum += verified_pos->get_price();
            verified_pos = verified_pos->next;
        }
        //if( n_ver != verified_pos ) {
            //sum += verified_pos->get_price();
          //  verified_pos = n_ver;
        //}
    }
    
    //verified_pos = range_list;
    while( verified_pos ) {
        sum += verified_pos->get_price();
        
        if( ! verified_pos->next && verified_pos->end != ill_days) {
            you_will_die_at( verified_pos->end + 1 );
            delete range_list;
            delete[] w_days;
            return 0;
        }
        
        verified_pos = verified_pos->next;
    }
    
    // print_linked( range_list );
    cout << sum << endl;
    
    delete range_list;
    delete[] w_days;
    return 0;
}
