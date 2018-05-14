#include <bits/stdc++.h>

using namespace std;
/*
 * Complete the function below.
 */
string findNumber(vector < int > arr, int k) {
    auto it = std::find(arr.begin(),arr.end(),k);
    if(it!= arr.end())
        return "YES";
    else
        return "NO";

}

int main() {
    ofstream fout(getenv("OUTPUT_PATH"));
    string res;
    
    int _arr_size = 0;
    cin >> _arr_size;
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
    vector<int> _arr;
    int _arr_item;
    for(int _arr_i=0; _arr_i<_arr_size; _arr_i++) {
        cin >> _arr_item;
        cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
        _arr.push_back(_arr_item);
    }
    
    int _k;
    cin >> _k;
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    
    res = findNumber(_arr, _k);
    fout << res << endl;
    
    fout.close();
    return 0;
}
