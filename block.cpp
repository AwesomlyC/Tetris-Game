#include "block.h"

// Constructor
Block::Block(){
    cellSize = 30;
    rotationState = 0;
    colors = getCellColors();
    row_offset = 0;
    column_offset = 0;

}

// Draw method to display the block
void Block::draw(int offsetX, int offsetY){
    std::vector<Position> tiles = GetCellPosition();
    for (Position item: tiles){
        DrawRectangle(item.column * cellSize + offsetX, item.row * cellSize + offsetY, cellSize - 1, cellSize - 1, colors[id]);
    }

}

// To move the block via Keyboard input
void Block::move(int rows, int columns){
    row_offset += rows;
    column_offset += columns;
}

// Rotate the block by changing the Rotation State
void Block::rotate()
{
    rotationState++; 
    if (rotationState == (int)cells.size()){
        rotationState = 0;
    }
}

// Undo a rotation when it cannot occur
void Block::undo_rotate()
{
    rotationState--;
    if (rotationState < 0){
        rotationState = (int)cells.size() - 1;
    }
}

// Return the cell position of the block
std::vector<Position> Block::GetCellPosition(){
    std::vector<Position> tiles = cells[rotationState];
    std::vector<Position> movedTiles;

    for (Position item: tiles){
        Position newPos = Position(item.row + row_offset, item.column + column_offset);
        movedTiles.push_back(newPos);
    }
    return movedTiles;
}