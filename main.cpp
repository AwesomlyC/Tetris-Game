#include "include/raylib.h"
#include "game.h"
#include "colors.h"
#include <iostream>

double lastUpdateTime = 0.0;
// Helper function for the speed of the game to progress
// at 300 ms
bool eventTriggered(double interval){
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval){
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main(){
    const int screenWidth = 500, screenHeight = 620;
    // Creating Game Window
    InitWindow(screenWidth, screenHeight, "Tetris Game with Raylib!");

    // Setting Target FPS
    SetTargetFPS(60);
    
    // Creating the Font Object
    Font font = LoadFontEx("Fonts/monogram.ttf", 64, 0, 0);

    // Creating the Game Object
    Game game = Game();

    // Drawing on the canvas
    while (!WindowShouldClose()){
        // Plays the background music
        UpdateMusicStream(game.music);
        BeginDrawing();
        // Handle keyboard inputs from user
        game.HandleInput();

        // Speed in which the block will drop
        // 300 ms
        if (eventTriggered(0.3)){
            game.MoveBlockDown();
        }
        // Changing the background to darkBlue
        ClearBackground(darkBlue);
        // Display the "Score" Text
        DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);

        // Display the "Next Block" Text
        DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
        // Display the "Game Over" Text
        if (game.gameOver){
            DrawTextEx(font, "Game Over", {320, 450}, 38, 2, WHITE);
        }

        // Draw a rectangular box for the "Score" Text
        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);

        // Centering the score in its respective box
        char scoreText[20];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);    
        DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE); 
        // Draw a rectangular box for the "Next Block" Text
        DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);

        game.draw();
        EndDrawing();
    }


    CloseWindow();
 
    return 0;
}