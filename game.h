#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game{
    public:
        Game();
        ~Game();
        void draw();
        void HandleInput();
        void MoveBlockDown();
        bool gameOver;
        int score;
        Music music;

    private:
        Block GetRandomBlock();
        std::vector<Block> GetAllBlocks();
        void MoveBlockRight();
        void MoveBlockLeft();
        bool IsBlockOutside();
        void RotateBlock();
        void LockBlock();
        bool BlockFits();
        void ResetGame();
        void UpdateScore(int linesCleared, int movedDownPoints);
        std::vector<Block> blocks;
        Block currentBlock;
        Block nextBlock;
        Grid grid;

        Sound rotateSound;
        Sound clearSound;
};

