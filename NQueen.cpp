#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <iostream>
using namespace std; 
class NQueens{
private:
    int no_queen;
    bool isSafe(int col, list<int> l_set) const   {
        int row_length = l_set.size(), counter =1;
        if(!row_length)
            return true;
        list<pair<int,int>>queens_with_Row;
        for ( auto l:l_set){
            queens_with_Row.emplace_back(row_length-counter++,l);
        }
        bool flag = true;
        for(auto l_row: queens_with_Row){
            if( l_row.second!=col && abs(l_row.second -col)!=(row_length - l_row.first)){
                continue;
                }
                else {
                    flag = false;
                    return flag;   
                }    
        } 
        return flag;  
    }

    set<list<int>> placeQueens(int k)  {
        if (k==0){
            set<list<int>> q_set;
            return q_set;
        }
        else {
            set<list<int>> q_set = placeQueens(k -1);
            set<list<int>> q_finalset;
            for(auto lset: q_set ){
                for(int col = 0 ; col <no_queen; col++ ) {
                    list<int> temp = lset;
                    if(isSafe(col, temp)) {
                            temp.emplace_front(col) ;
                            q_finalset.emplace(temp);
                    }
                }
            }
            if(q_set.empty() && k == 1){
                 for(int col = 0 ; col <no_queen; col++ ) {
                    list<int> lSubset;
                    lSubset.emplace_front(col);
                    q_finalset.emplace(lSubset);
                }
            }
            return q_finalset;
        }
        
    }
public:
    NQueens() = delete;
    NQueens(int no_queen ) {
        this->no_queen  = no_queen;
    }
    set<list<int>> solve(){
        return placeQueens(no_queen);
    }
    void show(list<int>  queens){
        queens.reverse();
        vector<string> v(queens.size());
        for( auto q: queens){
            std::ostringstream oss;
            fill(v.begin(), v.end(), "* ");
            int j = 0;
            std::for_each( v.begin(), v.end(), [&j,q](string & s)
            {
                if(j++ == q)
                    s = "X "; 
            });
            copy(v.begin(), v.end(), ostream_iterator<string>(oss, ""));
             std::cout << oss.str() << std::endl;
        }
    }
    void printCols(set<list<int>> q_set) {
        for (auto q_lst:q_set){
            for (auto elem:q_lst){
                cout <<elem <<" ";
            }
            cout <<endl;
        }
        cout <<endl <<endl;
    }
};


int main() {
    NQueens q = NQueens(8);
    set<list<int>> q_set = q.solve();
    set<list<int>> q_subset(std::next(q_set.begin(),1),std::next(q_set.begin(),5));
    //set elements are const.Cant be used as reference
    std::for_each(q_subset.begin(), q_subset.end(), [&q](list<int>  queens )
            {                                         
                q.show(queens); 
                cout <<endl;
            });
    cout<<"No of solutions :" << q_set.size() <<endl;
    //q.printCols(q_set);
}