#include "game.h"
#include <random>

// Constructor
Game::Game(){
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
    // Create the audio device
    InitAudioDevice();
    // Set the background music
    music = LoadMusicStream("Sounds/music.mp3");
    PlayMusicStream(music);
    // Set the rotate sound
    rotateSound = LoadSound("Sounds/rotate.mp3");
    // Set the clear row sound
    clearSound = LoadSound("Sounds/clear.mp3");
}
// Destructor
Game::~Game(){
    UnloadMusicStream(music);
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    CloseAudioDevice();
}
// Choose a random block that has not been chosen before
// If all blocks have been chosen, refill the container and repeat the process
Block Game::GetRandomBlock(){
    if (blocks.empty()){
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

// Generate all types of blocks
std::vector<Block> Game::GetAllBlocks(){
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}
// Draw method to display the game information
void Game::draw(){
    grid.draw();
    currentBlock.draw(11,11);
    // Centering certain blocks
    switch (nextBlock.id){
        // IBlock
        case 3:
            nextBlock.draw(255, 290);
            break;
        // OBlock
        case 4:
            nextBlock.draw(255, 280);
            break;
        // All other blocks
        default:
            nextBlock.draw(270, 270);
    }
}
// Handle all keyboard inputs
// i.e. left, right, down, up
void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();
    if (gameOver && keyPressed){
        gameOver = false;
        ResetGame();
    }
    switch (keyPressed){
        case (KEY_LEFT):
            MoveBlockLeft();
            break;
        case (KEY_RIGHT):
            MoveBlockRight();
            break;
        case (KEY_DOWN):
            MoveBlockDown();
            UpdateScore(0, 1);
            break;
        case (KEY_UP):
            RotateBlock();
            break;
    }
}
// When the user press the left arrow key,
// move the block to the left
void Game::MoveBlockLeft(){
    if (!gameOver){
        currentBlock.move(0, -1);
        if (IsBlockOutside() || !BlockFits()){
            currentBlock.move(0, 1);
        }
    }
}
// When the user press the right arrow key,
// move the block to the right
void Game::MoveBlockRight(){
    if (!gameOver){
        currentBlock.move(0,1);
        if (IsBlockOutside() || !BlockFits()){
            currentBlock.move(0, -1);
        }
    }
}
// When the user press the down arrow key,
// move the block to the down
void Game::MoveBlockDown(){
    if (!gameOver){
        currentBlock.move(1,0);
        if (IsBlockOutside() || !BlockFits()){
            currentBlock.move(-1,0);
            LockBlock();
        }
    }
}
// Verify if the block is not outside the grid
bool Game::IsBlockOutside()
{
    std::vector<Position> tiles = currentBlock.GetCellPosition();
    for (Position item: tiles){
        if (grid.isCellOutside(item.row, item.column)){
            return true; 
        }
    }
    return false;
}
// When the user press the up arrow key,
// rotate the block
void Game::RotateBlock()
{
    if (!gameOver){
        currentBlock.rotate();
        if (IsBlockOutside() || !BlockFits()){
            currentBlock.undo_rotate();
        }
        else{
            PlaySound(rotateSound);
        }
    }
}
// Lock the block when it touch the bottom of the grid or another block
void Game::LockBlock()
{
    std::vector<Position> tiles = currentBlock.GetCellPosition();

    for (Position item: tiles){
        grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;
    if (!BlockFits()){
        gameOver = true;
    }
    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearFullRows();
    if (rowsCleared > 0){
        PlaySound(clearSound);
        UpdateScore(rowsCleared, 0);
    }
}
// Verify the block can fit in a particular area
bool Game::BlockFits()
{
    std::vector<Position> tiles = currentBlock.GetCellPosition();
    for (Position item: tiles){
        if (grid.isCellEmpty(item.row, item.column) == false){
            return false;
        }
    }
    return true;
}

// Reset the game
void Game::ResetGame()
{
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
}

// Update the score whenever the user press the down arrow key
// or clear a row
void Game::UpdateScore(int linesCleared, int movedDownPoints)
{
    switch(linesCleared)
    {
        case 1:
            score += 100;
            break;
        case 2:
            score += 300;
            break;
        case 3:
            score += 500;
            break;
        case 4:
            score += 1000;
            break;
        default:
            break;
    }
    score += movedDownPoints;

}