#pragma once
#include <vector>
#include "include/raylib.h"

class Grid{
    public:
        Grid();
        void Initialize();
        void print();
        void draw();
        bool isCellOutside(int row, int column);
        bool isCellEmpty(int row, int column);
        int ClearFullRows();
        int grid[20][10];

    private:
        bool isRowFull(int row);
        void clearRow(int row);
        void MoveRowDown(int row, int numRows);
        int numRows;
        int numCols;
        int cellSize;
        std::vector<Color> colors;
};