import java.util.*;
public class CountPaths{
    final static int dRow = 7;
    final static int dCol = 7;
    public static int countAllPaths(boolean [][] grid, int row, int col){
        if( (row >=grid.length || col >= grid[0].length) || !grid[row][col])
            return 0;
        else if(row == dRow && col == dCol)
            return 1;
        else
            return countAllPaths(grid, row+1, col) + 
        countAllPaths(grid, row, col+1);
    }

    public static int countAllPathsMemo(boolean [][] grid, int row, int col, int [][] paths){
        if( (row >=grid.length || col >= grid[0].length) || !grid[row][col])
            return 0;
        else if(row == dRow && col == dCol)
            return 1;
        else if(paths[row] [col] ==0)
            paths[row] [col] =  countAllPathsMemo(grid, row+1, col, paths) + 
        countAllPathsMemo(grid, row, col+1,paths);
        return paths[row][col];
    }

    public static int countAllPathsDP(boolean [][] grid){
        int nRows = grid.length;
        int nCols = grid[0].length;
        int [][] count = new int [nRows][nCols];
        count[dRow][dCol] = 1;
        for (int row = nRows -1 ; row >=0 ; row -- ){
            for (int col = nCols -1 ; col >=0 ; col -- ){
                 if((row != dRow || col!= dCol) && grid[row][col]) {
                    if (row +1 <nRows)
                        count[row][col]+=count[row+1][col];
                    if(col+1 < nCols)
                        count[row][col]+=count[row][col+1];
                 }
            }
        }
        for (int[] row: count)
            System.out.println(Arrays.toString(row));
        return count[0][0];
    }
    public static void main(String [] args){
        boolean[][] grid = {
            {
                true,true,true,true,true,true,true,true,
            },
            {
               true,true,false,true,true,true,false,true,   
            },
            {
               true,true,true,true,false,true,true,true   
            },
            {
               false,true,false,true,true,false,true,true   
            },
            {
               true,true,false,true,true,true,true,true   
            },
            {
               true,true,true,false,false,true,false,true   
            },
            {
               true,false,true,true,true,false,true,true   
            },

            {
               true,true,true,true,true,true,true,true   
            }
        };
     System.out.println(countAllPaths(grid, 0, 0));
     int [][] paths = new int[8][8];
     System.out.println(countAllPathsMemo(grid, 0, 0,paths));
     System.out.println(countAllPathsDP(grid));
    }
}