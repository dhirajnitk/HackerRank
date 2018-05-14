class CountPaths:
    dRow = 7
    dCol = 7
    @classmethod
    def countAllPaths(cls,grid,row ,col):
        if(row>=len(grid) or col >= len(grid[0]) or ( not grid[row][col])):
            return 0
        elif(row == cls.dRow and col == cls.dCol):
            return 1
        else:
            return cls.countAllPaths(grid, row+1, col) + cls.countAllPaths(grid, row, col+1)
if __name__ == '__main__':
    grid = [[True,True,True,True,True,True,True,True ],
                    [True,True,False,True,True,True,False,True  ],
                    [True,True,True,True,False,True,True,True],
                    [False,True,False,True,True,False,True,True],
                    [True,True,False,True,True,True,True,True ],
                    [True,True,True,False,False,True,False,True ],
                    [True,False,True,True,True,False,True,True],
                    [True,True,True,True,True,True,True,True]]
    print(CountPaths.countAllPaths(grid,0,0))