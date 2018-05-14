#include <iostream>
#include <algorithm>
using namespace std;
static int fib(int n) {
    if(n <=0)
            return 0;
        else if(n==1)
            return 1;
        else
            return fib(n-1) + fib(n-2);
}

static int fibMemo(int n,int * memo) {
    if(n <=0)
            return 0;
        else if(n==1)
            return 1;
        else if(!memo[n]){
            memo[n] = fibMemo(n-1,memo) + fibMemo(n-2,memo);
        }
        return memo[n];
}
static long long fibRec(int n, long long & prev, long long & next) {
    if(n==0)
        return next;
    else {
        long long old = next;
        next += prev;
        prev = old;
        fibRec(n-1, prev, next);
    }
}
static long long fibTail(int n){
    long long prev = 0, next = 1;
    //Fib0, Fib1 are calculated so we  need to calculated n-1 times on tail
    return fibRec(n-1, prev, next);
}
static int fibIterative(int n) {
    int fibPrev =0;
    int fib=1;
    int index =1;
    //n-1 times more
    while(index++<n){
        int temp = fib;
        fib +=fibPrev;
        fibPrev = temp;
    }
    return fib;
}


int main(){
    cout<<fib(10)<<endl;
    cout<<fibIterative(10)<<endl;
    cout<<fibTail(10)<<endl;
    int memo[11] = {0};
    cout<<fibMemo(10,memo)<<endl;
    return 0;
}