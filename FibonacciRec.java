import java.util.*;
public class FibonacciRec{
    public static Long fibRec(int n, long  prev, long  next) {
            if(n==0)
                return (Long)next;
            else {
                long old = next;
                next += prev;
                prev = old;
                 //Fib0, Fib1 are calculated so we  need to calculated n-1 times on tail
                return fibRec(n-1, prev, next);
            }
    }
    static int fibMemo(int n,int [] memo) {
        if(n <=0)
            return 0;
        else if(n==1)
            return 1;
        else if(memo[n]==0){
            memo[n] = fibMemo(n-1,memo) + fibMemo(n-2,memo);
        }
        return memo[n];
  }
    public static Long fibTail(int n) {
         long prev = 0L;
         Long next = 1L;
         return fibRec(n-1, prev, next);
    }
    public static Long fib(int n) {
        if(n <=0)
            return 0L;
        else if(n==1)
            return 1L;
        else
            return fib(n-1) + fib(n-2);
    }
    public static Long  fibIteraive(int n){
        Long fibPrev =0L;
        Long fib=1L;
        int index =1;
        while(index++<n){
            Long temp = fib;
            fib +=fibPrev;
            fibPrev = temp;
        }
        return fib;
    }
    public static void main(String[] args){
        System.out.println(fib(10));
        System.out.println(fibIteraive(10));
        int [] memo = new int [11];
        System.out.println(fibMemo(10,memo));
        System.out.println(fibTail(10));
    }
}