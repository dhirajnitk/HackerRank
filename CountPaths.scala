import java.util._
import scala.annotation.tailrec
object CountPaths extends App{
    private val dRow = 7
    private val dCol = 7
    private def countAllPaths(grid: Array[Array[Boolean]], row: Int, col: Int) :Int = {
        if(row >= grid.length || col >= grid(0).length || !grid(row)(col))
            0
        else if(row ==dRow && col == dCol)
            1
        else
            countAllPaths(grid, row+1, col) + countAllPaths(grid, row, col+1)

    }

    private def countAllPathsMemo(grid: Array[Array[Boolean]], row: Int, col: Int, paths: Array[Array[Int]]):Int ={
        if( (row >=grid.length || col >= grid(0).length) || !grid(row)(col))
             return 0
        else if(row == dRow && col == dCol)
             return 1
        else if(paths(row)(col) ==0) {
            paths(row) (col) =  countAllPathsMemo(grid, row+1, col, paths) + countAllPathsMemo(grid, row, col+1,paths)
        }
        paths(row)(col) 
    }

    private def countAllPathsDP(grid: Array[Array[Boolean]]) :Int = {
        val nRows  = grid.length
        val nCols = grid(0).length
        val count = Array.ofDim[Int](nRows,nCols)
        count(dRow)(dCol) = 1
        for ( row <- nRows -1  to 0 by -1 ){
            for (col <- nCols -1  to 0 by -1 ){
                 if((row != dRow || col!= dCol) && grid(row)(col)) {
                    if(row +1<nRows)
                        count(row)(col)+=count(row+1)(col)
                    if(col+1 < nCols)
                        count(row)(col)+=count(row)(col+1)
                 }
            }
        }
        for (row <- count)
            System.out.println(Arrays.toString(row));
        return count(0)(0)
    }
    val grid = Array(
             Array(true,true,true,true,true,true,true,true,
            ),
            
            Array(true,true,false,true,true,true,false,true,   
            ),
            
            Array(true,true,true,true,false,true,true,true   
            ),
            Array(
               false,true,false,true,true,false,true,true   
            ),
            Array(
               true,true,false,true,true,true,true,true   
            ),
            Array(
               true,true,true,false,false,true,false,true   
            ),
            Array(
               true,false,true,true,true,false,true,true   
            ),

            Array(
               true,true,true,true,true,true,true,true   
            ))
            println(countAllPaths(grid, 0, 0))
            val paths = Array.ofDim[Int](8,8)
            println(countAllPathsMemo(grid, 0, 0,paths))
            println(countAllPathsDP(grid))
}