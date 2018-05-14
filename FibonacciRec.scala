import scala.annotation.tailrec
object Fibonacci extends App{
     private def fib(n:Int):Int ={
        if (n <= 0)
            0
        else if (n == 1)
            1
        else
            fib(n-1) + fib(n-2)
     }
     def fibTail(x:Int):BigInt = {
        @tailrec
        def fib(x:Int, prev:BigInt = 0, next:BigInt =1) : BigInt = x match{
            case 0 =>prev
            case 1 => next
            case _ => fib(x-1, next, (next + prev))
        }
        fib(x)
     }
     def fibIterative(n:Int):BigInt = {
        var (fibPrev,fib,index) = (0,1,1)
        //Need n-1 times more
        for( index <- 2 to n){
            var temp = fib
            fib+= fibPrev
            fibPrev = temp
        }
        fib
     }
     def fibMemo(n:Int, memo:Array[Int]):Int={
        if(n<=0)
            return 0
        else if(n==1)
            return 1
        else if(memo(n)==0){
            memo(n)= fibMemo(n-1,memo) + fibMemo(n-2, memo)
        }
        memo(n)
     }
     
     println(fib(10))
     println(fibIterative(10))
     println(fibTail(10))
     val memo = new Array[Int](11)
     println(fibMemo(10,memo))
}