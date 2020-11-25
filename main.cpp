//
//  main.cpp
//  SudokuProblem
//
//  Created by wolfdud3 on 19/03/2020.
//

#include <iostream>

#include "grid.h"

int main()
{
    SudokuProblem* var;
    
    var = loadPuzzle("sudoku.dat");
    
    solve_Sudoku(var);
    print_sudoku(var);
    
};





