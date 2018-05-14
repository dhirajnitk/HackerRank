import java.io.PrintWriter

object Solution {
   

    def findNumber(arr: Array[Int], k: Int): String = {
        if(arr.contains(k))
            "YES"
        else
        "NO"
    }

def main(args: Array[String]) {
        val fw = new PrintWriter(sys.env("OUTPUT_PATH"));

        val _arr_size = scala.io.StdIn.readInt
        val _arr = Array.ofDim[Int](_arr_size)
        
        for (_arr_i <- 0 until _arr_size)
        	_arr(_arr_i) = scala.io.StdIn.readInt
        
        
        val _k = scala.io.StdIn.readInt
        
        val res = findNumber(_arr, _k)
        fw.println(res)
        
        fw.close();
    }
}
 
