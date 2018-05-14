#include <iostream>
#include <algorithm>
using namespace std;
static const int dRow = 7;
static const int dCol = 7;
static const int ROWS = 8;
static const int COLS = 8;
static void printArrays(int  grid [ROWS][COLS]  ) {
    for (int r =0 ; r <ROWS ; r++) {
        for(int c = 0; c <COLS; c++) {
            printf("%4d",grid[r][c]);
        }
        cout<<endl;
    }
 }
static int countAllPaths( bool (&grid) [ROWS][COLS], int row, int col) {
    if( (row >=ROWS || col >= COLS) || !grid[row][col])
            return 0;
        else if(row == dRow && col == dCol)
            return 1;
        else
            return countAllPaths(grid, row+1, col) + 
        countAllPaths(grid, row, col+1);
}

static int countAllPathsMemo(bool (&grid) [ROWS][COLS], int row, int col, int paths[][COLS]){
        if( (row >=ROWS || col >= COLS) || !grid[row][col])
            return 0;
        else if(row == dRow && col == dCol)
            return 1;
        else if(paths[row] [col] ==0)
            paths[row] [col] =  countAllPathsMemo(grid, row+1, col, paths) + 
        countAllPathsMemo(grid, row, col+1,paths);
        return paths[row][col];
    }

    static int countAllPathsDP(bool (&grid) [ROWS][COLS]){
        int count [ROWS][COLS] = {0};
        count[dRow][dCol] = 1;
        for (int row = ROWS-1 ; row >=0 ; row -- ){
            for (int col = COLS -1 ; col >=0 ; col -- ){
                 if((row != dRow || col!= dCol) && grid[row][col]) {
                    if (row +1 <ROWS)
                        count[row][col]+=count[row+1][col];
                    if(col+1 < COLS)
                        count[row][col]+=count[row][col+1];
                 }
            }
        }
        printArrays(count);
        return count[0][0];
    }

int main() {
    bool grid[ROWS][COLS] = {
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
        cout<<countAllPaths(grid, 0, 0) <<endl;
        int paths [ROWS][COLS] = {0};
        cout<<countAllPathsMemo(grid,0,0, paths)<<endl;
        cout<<countAllPathsDP(grid);
        return 0;
}