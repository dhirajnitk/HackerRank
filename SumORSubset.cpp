#include <iostream>
#include <vector>
#include <cmath>
using namespace std; 
#define BIT_SIZE 32
#define getBit(n,k) ({ \
    (n & (1<<k)) != 0;\
})
int bitWiseOR(vector<int> &arr)
{
    int result = 0;
    vector<int> bitFreq(BIT_SIZE);
    int n = arr.size();
    for(int i = 0;i<n;i++){
        for (int k = BIT_SIZE-1; k>=0; k--)
            bitFreq[k]+= getBit(arr[i],k);
    }
    for (int i=0; i < BIT_SIZE; ++i){
        while(bitFreq[i]){
            result+= pow(2,i)*pow(2,n-bitFreq[i]--);
        }
    }
    return result;
}
 int main()
{
    vector<int> arr= {1, 5, 6};
    
    cout << bitWiseOR(arr) <<endl;
}