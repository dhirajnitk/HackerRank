class FibonacciRec:
    def fib(n):
        if(n <=0):
            return 0
        elif(n==1):
            return 1
        else:
            return FibonacciRec.fib(n-1) + FibonacciRec.fib(n-2)
    def fibRec( n, prev, curr):
        if(n==0):
            return curr
        else:
            prev,curr = curr,curr+prev
            return FibonacciRec.fibRec(n-1, prev,curr)
    def fibMemo(n, memo):
        if(n<=0):
            return 0
        elif(n==1):
            return 1
        elif(not memo[n]):
            memo[n] = FibonacciRec.fibMemo(n-1, memo) + FibonacciRec.fibMemo(n-2, memo)
        return memo[n]
    def fibTail(n):
        prev, curr = 0,1
        return FibonacciRec.fibRec(n-1, prev, curr)
    def fibIterative(n):
        fibPrev,fib = 0,1
        for index in range(1,n):
            fibPrev,fib = fib,fib+fibPrev
        return fib
if __name__ == '__main__':
    print(FibonacciRec.fib(10))
    print(FibonacciRec.fibIterative(10))
    memo = [0] * 11
    print(FibonacciRec.fibMemo(10, memo))
    print(FibonacciRec.fibTail(10))


