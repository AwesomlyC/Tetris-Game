#include <iostream>
#include "grid.h"
#include "colors.h"

// Constructor
Grid::Grid(){
    numRows = 20;
    numCols = 10;
    cellSize = 30;
    Initialize();
    colors = getCellColors();
}

// Initialize the grid by setting all values to 0
void Grid::Initialize(){
    for (int row = 0; row < numRows; row++){
        for (int column = 0; column < numCols; column++){
            grid[row][column] = 0;
        }
    }
}

// Print out the grid for debugging purposes
void Grid::print(){
    for (int row = 0; row < numRows; row++){
        for (int column = 0; column < numCols; column++){
            std::cout << grid[row][column] << " ";
        }
        std::cout << std::endl;
    }

}
// Draw method to display the grid
void Grid::draw(){
    for (int row = 0; row < numRows; row++){
        for (int column = 0; column < numCols; column++){
            int cellValue = grid[row][column];
            DrawRectangle(column * cellSize + 11, row * cellSize + 11, cellSize - 1, cellSize - 1 , colors[cellValue]);
        }
    }

}
// Verify if the cell is not outside of the grid
bool Grid::isCellOutside(int row, int column)
{
    if (row >= 0 && row < numRows && column >= 0 && column < numCols){
        return false;
    }
    return true;   
}
// Verify if the cell is empty
bool Grid::isCellEmpty(int row, int column)
{
    if (grid[row][column] == 0){
        return true;
    }
    return false;
}
// If there are completed row, clear it from the grid
// Return the number of completed Rows to calculate the score
int Grid::ClearFullRows()
{
    int completedRows = 0;
    // Searching from bottom up
    // As the most-bottom level is at numRows-1
    for (int row = numRows - 1; row >= 0; row--){
         if (isRowFull(row)){
            clearRow(row);
            completedRows++;
         }
         else if (completedRows > 0){
            MoveRowDown(row, completedRows);
         }
    }
    return completedRows;
}
// Verify if a row is completed
bool Grid::isRowFull(int row)
{
    for (int column = 0; column < numCols; column++){
        if (grid[row][column] == 0){
            return false;
        }
    }
    return true;
}
// Clears the row by setting its value to 0
void Grid::clearRow(int row)
{
    for (int column = 0; column < numCols; column++){
        grid[row][column] = 0;
    }
}
// If a row is cleared, move all other blocks downwards
void Grid::MoveRowDown(int row, int numRows)
{
    for (int column = 0; column < numCols; column++){
        grid[row + numRows][column] = grid[row][column];
        grid[row][column] = 0;
    }
}
