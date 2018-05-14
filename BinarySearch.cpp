#include <iostream>
#include <algorithm>
using namespace std;
template <typename T> class BinarySearch{
public:
    bool binarySearchRecursive(T array [], T x, int N);
    bool binarySearchRecursive(T array [], T x,int left, int right);
    bool binarySearchIterative(T array [], T x,int N);
    int  binarySearchIterativeFastRight(T array [], T x,int N);
    int  binarySearchIterativeFastLeft(T array [], T x,int N);
};

template <typename T> bool BinarySearch<T>::binarySearchRecursive(T array[], T x, int N){
    
    return binarySearchRecursive(array,x, 0, N -1);
}
template <typename T> bool BinarySearch<T>::binarySearchRecursive(T array[], T x, int left, int right){
    if (left > right)
            return false;
        else{
            int mid = left + (right - left)/2;
            if(array[mid] == x)
                return true;
            else if(array[mid] <x)
                return binarySearchRecursive(array,x, mid +1, right);
            else 
                return binarySearchRecursive(array,x, left, mid-1);

        }
}
template <typename T> bool BinarySearch<T>::binarySearchIterative(T array[], T x, int N){
        int left = 0;
        int right = N-1;
        while(left <= right) {
            int mid = left + (right - left)/2;
            if(array[mid] == x)
                return true;
            else if(array[mid]<x)
                 left = mid + 1;
            else 
                 right = mid -1;
         }
         return false;
}
template <typename T> int  BinarySearch<T>::binarySearchIterativeFastLeft(T array[], T x, int N){
        int left = -1;
        int right = N-1;
        while(right - left >1) {
            int mid = left + (right - left)/2;
            if(array[mid] >=x)
                right = mid;
            else
                left = mid;
         }
         return right;
}
template <typename T> int BinarySearch<T>::binarySearchIterativeFastRight(T array[], T x, int N){
        int left = 0;
        int right = N;
        while(right - left >1) {
            int mid = left + (right - left)/2;
            if(array[mid] <=x)
                left = mid;
            else
                right = mid;
         }
         return left;
}

int main() {
    int arr []  = { 1, 3, 5, 7, 9, 10, 10 ,10 ,10, 11, 13};
    BinarySearch<int> bSearch;
    int x = 7;
    cout <<bSearch.binarySearchRecursive(arr, x, sizeof(arr)/sizeof(arr[0])) <<endl;
    cout <<bSearch.binarySearchIterative(arr, x,sizeof(arr)/sizeof(arr[0])) <<endl;
    x = 10;
    cout <<bSearch.binarySearchIterativeFastRight(arr, x,sizeof(arr)/sizeof(arr[0])) <<endl;
    cout <<bSearch.binarySearchIterativeFastLeft(arr, x,sizeof(arr)/sizeof(arr[0])) <<endl;
}