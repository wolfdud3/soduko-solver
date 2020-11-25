//
//  grid.h
//  SudokuProblem
//
//  Created by wolfdud3 on 19/03/2020.
//

#ifndef grid_h
#define grid_h

#include <iostream>
#include <fstream>
#include <string>

#include "Stack.h"


#endif /* grid_h */

//creating a variable type Coordinates
struct Coordinates
{
    //collumns
    int x;
    
    //rows
    int y;
    
    //used friend-function to access members inside class
    friend bool operator==(Coordinates coord1, Coordinates coord2)
    {
        return (coord1.x == coord2.y) && (coord1.x == coord2.y);
    }
    
    friend std::ostream &operator<<(std::ostream &out, const Coordinates coord)
    {
        out << "(" << coord.x << "," << coord.y << ")";
        return out;
    }
};


//creating the basic variables
struct SudokuProblem
{
    int** Sodoku;
    
    int collumn_size;
    int row_size;
    
    bool** locked;
    
    int missing_size = 0;

    //multi-level variables based on "struct Coordinates"
    Coordinates start;
    Coordinates finish;
};

struct SudokuSolver
{
    int** Sodoku;
    
    int** sudoku_solution;
    
    int step_num;
    
};


/*
 loadPuzzle
 - reads filename
 - tries to load the file
 
 if file not existing:
 - prints & exits program
 
 if file existing:
 - seperates content of file into characters
 - reads value for amount of rows
 - reads value for amount of collumns
 
 - reads and writes the values for the cells
 - locks preexisting values in cells
 - prints number of cell (incl. 0)
 
 - counts the amount of missing numbers (-> counting ia == 0) and determines first missing number
 - determines last missing number
 
 - prints amount of missing numbers
 - prints positions of first missing number and last missing number
*/
SudokuProblem* loadPuzzle(std::string filename)
{
    
    SudokuProblem* grid = new SudokuProblem();
    
    std::ifstream fs(filename);
    std::cout << filename << "\n";
    
    if(!fs)
    {
        std::cout << "no file found" << std::endl;
        return 0;
    }
    
    fs >> grid -> row_size;
    fs >> grid -> collumn_size;
    
    //test
    //std::cout << grid->row_size << std::endl;
    //std::cout << grid->collumn_size << std::endl;
    
    grid->Sodoku = new int * [grid -> row_size];
    grid->locked = new bool * [grid -> row_size];
    
    for (int i = 0; i < grid -> row_size; i++)
    {
        grid->Sodoku[i] = new int [grid->collumn_size];
        grid->locked[i] = new bool [grid -> collumn_size];
    }
    
    std::cout << "+-----------------+ \n";
    for(int i = 0; i < grid -> row_size; i++)
    {
        
        for(int j = 0; j < grid -> collumn_size; j++)
        {
            char a;
            fs >> a;
            int ia = a - '0';
            
            if(ia >= 0 && ia <= 9)
            {
                grid->Sodoku[i][j] = ia;
                
                std::cout << "|" << grid->Sodoku[i][j];
                
                grid->locked[i][j] = ia;    //whatever is not 0 is automatically true
                
                if(ia == 0)
                {
                    if(grid->missing_size == 0)
                    {
                        grid->start.x = i;
                        grid->start.y = j;
                    }
                    grid->missing_size++;
                }
            }
            else
            {
                j--;
            }
        }
        std::cout << "| \n";
    }
    std::cout << "+-----------------+ \n";
    
    
    bool found = false;
    
    for(int i = grid->row_size - 1; i >= 0 && found == false; i--)
    {
        
        for(int j = grid->collumn_size - 1; j >= 0 && found == false; j--)
        {
         
            
            if(grid->Sodoku[i][j] == 0)
            {
                grid->finish.x = i;
                grid->finish.y = j;
                
                found = true;
            }

        }
        
    }
    
    std::cout << "Number of missing numbers: " << grid->missing_size << "\n";
    std::cout << "First missing number: (" << grid->start.x << "," << grid->start.y << ") \n";
    std::cout << "Last missing number: (" << grid->finish.x << "," << grid->finish.y << ") \n";
    
    return grid;
    
}


//checks if value (int k) already exists in the collumn
bool checkCollumn(SudokuProblem* grid, int collumn, int k)
{
    for(int j = 0; j < grid->collumn_size; j++)
    {
        if(grid->Sodoku[collumn][j] == k)
        {
            return false;
        }
    }
    return true;
}

//checks if value (int k) already exists in the row
bool checkRow(SudokuProblem* grid, int row, int k)
{
    for(int i = 0; i < grid->row_size; i++)
    {
        if(grid->Sodoku[i][row] == k)
        {
            return false;
        }
    }
    return true;
}

//checks if value (int k) already exists in the 3x3 Box
bool checkSquare(SudokuProblem* grid, int x, int y , int k)
{
    int offset_x = x/3;
    int offset_y = y/3;
    
    for(int i = offset_x * 3; i < 3 + offset_x * 3; i++)
    {
        for(int j = offset_y * 3; j < 3 + offset_y * 3; j++)
        {
            if(grid->Sodoku[i][j] == k)
            {
                return false;
            }
        }
    }
    return true;
}




// returns cell position; returns -1 when nothing is found (= solved)
Coordinates find_cell(SudokuProblem* grid)
{
    Coordinates variable1;
    
    for (int i = 0; i < grid->row_size; i++)
       {
           for (int j = 0; j < grid->collumn_size; j++)
           {
               if(grid->Sodoku[i][j] == 0)
               {
                   variable1.x = i;
                   variable1.y = j;
                   
                   return variable1;
               }
           }
       }
    
    variable1.x = -1;
    variable1.y = -1;
    
    return variable1;
}

/*
 solve_Sudoku checks current cell/position, and if the next cell/position can't be solved, it will not leave the for-loop (meaning: it'll check the next k-value for current position)
 - if k reaches nine (thus no number is correct, meaning that previous number is not correct), previous position will be continuesly changed
 - if the sudoku is solved( = no zeros remaining), function returns true and exits
 
 solve_Sudoku increments int steps by 1 to count the steps made.
 
 If Sudoku is unsolvable, it will print it out and exits program
 */
int steps = 0;

bool solve_Sudoku(SudokuProblem* grid)
{
    steps++;
    
    Coordinates pos = find_cell(grid);
    
    if(pos.x == -1 && pos.y == -1)
    {
        return true;
    }
    
    for(int k = 1 ; k <= 9; k++)
    {
        if(checkCollumn(grid, pos.x, k) && checkRow(grid, pos.y, k) && checkSquare(grid, pos.x, pos.y, k))
        {
            grid->Sodoku[pos.x][pos.y] = k;
            
            /*
            position.x = pos.x;
            position.y = pos.y;
            
            moves->push(Coordinates(position));

            std::cout << "set proposed value to " << k << "\n";
            */
            
            if(solve_Sudoku(grid))      //calls itself still being in if-statement
            {
                return true;
            }
            grid->Sodoku[pos.x][pos.y] = 0;
            
        }
    }
    return false;
}

//prints solved sudoku
void print_sudoku(SudokuProblem* grid)
{
    std::cout << "\nSolution found in " << steps << " steps! \n";
    std::cout << "+-----------------+ \n";
    for (int i = 0; i < grid->row_size; i++)
            {
                for (int j = 0; j < grid->collumn_size; j++)
                {
                    std::cout << "|" << grid->Sodoku[i][j];
                }
                
                std::cout << "| \n";
            }
    std::cout << "+-----------------+ \n";
               
}
        
