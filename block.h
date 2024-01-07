#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"

class Block{
    public:
        Block();
        int id;
        std::map<int, std::vector<Position>> cells;
        void draw(int offsetX, int offsetY);
        void move(int rows, int columns);
        void rotate();
        void undo_rotate();
        std::vector<Position> GetCellPosition();

    private:
        int cellSize;
        int rotationState;
        std::vector<Color> colors;
        int row_offset;
        int column_offset;

};