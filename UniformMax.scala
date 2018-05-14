import java.util.Arrays
import scala.collection.mutable.ArrayBuffer
import scala.util.Random
object UniformMax extends App{
    def findUniformMax(arr: Array[Int]):Int = {
        var v = ArrayBuffer[Int]()
        var MAX = Integer.MIN_VALUE
        for (i <- 0 to arr.length -1){
            if(arr(i) >=MAX){
                MAX = arr(i);
            if(!v.isEmpty && arr(v(0)) < MAX)
                v.clear();
            v+=i
            }
        }
        val r = new Random()
        val index = Math.abs(r.nextInt() %(v.size-1))
        v(index)
    }
    def findUniformMaxFold(arr: Array[Int]):Int = {
        var v = ArrayBuffer[Int]()
        var MAX = Integer.MIN_VALUE
        /*
        def op(v: ArrayBuffer[Int], cur: (Int, Int)) = {
            if(cur._1 >=MAX) {
                MAX = cur._1
                if(!v.isEmpty && arr(v(0)) < MAX)
                    v.clear();
                v+=cur._2
            }
            v
        }
        */
        arr.toList.zipWithIndex.foldLeft(v){
            (v,cur) =>
                if(cur._1 >=MAX) {
                    MAX = cur._1
                    if(!v.isEmpty && arr(v(0)) < MAX)
                        v.clear();
                    v+=cur._2
                }
                v
        }
        val r = new Random()
        val index = Math.abs(r.nextInt() %(v.size-1))
        v(index)
    }
    val arr:Array[Int] = Array(1,3, 6 ,4, 8, 7, 8, 8, 8, 8, 8, 5)
    println(Arrays.toString(arr))
    println(findUniformMaxFold(arr))
    
}