#include <vector>
#include <iostream>
#include <climits>
#include <random>
#include <algorithm>
#include <chrono>
using namespace std;
 // obtain a time-based seed:
std::mt19937 rng;
std::random_device rd;
int findUniformMax(int *arr, int n){
    vector<int>v;
    int MAX = INT_MIN;
    for (int i =0; i <n;i++) {
        if(arr[i] >=MAX){
            MAX = arr[i];
            if(v.size() && arr[v[0]] < MAX)
                v.clear();
            v.emplace_back(i);
        }
    }
    //rng.seed(rd());
    rng.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0,v.size()-1); 
    return v[dist(rng)];
}

int main() {
    
    int arr[] = { 1,3, 6 ,4, 8, 7, 8, 8, 8, 8, 8, 5};
    cout <<findUniformMax(arr, sizeof(arr)/sizeof(arr[0]));

}