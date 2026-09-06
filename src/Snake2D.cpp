/*******************************************************************************************
*
* Nokia's Snake Game - By RayLib.
* Created By - Mahmoud.
********************************************************************************************/

#include "raylib.h"
#include <deque>
#include <ctime>
#include <iostream>
#include <string>

// Text Game Structure
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
struct Text
{
    std::string content;
    int x;
    int y;
    int size;
    Color color;

    int scoreValue = 0;

    void UpdateScore(int points)
    {
        scoreValue += points;
        content = "Score : " + std::to_string(scoreValue);
    }

    void Draw()
    {
        DrawText(content.c_str(), x, y, size, color);
    }
};

int main() {
    // 1. Initialization
    //-------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 800;
    const int cellSize = 25; // The "Grid" size

    InitWindow(screenWidth, screenHeight, "Snake Game - Classic");
    SetTargetFPS(12);

    // 2. Apple Variables
    //-------------------------------------------------------------------
    srand(static_cast<unsigned int>(time(0)));
    Rectangle apple = {
        static_cast<float>(rand() % (screenWidth / cellSize)) * cellSize,
        static_cast<float>(rand() % (screenHeight / cellSize)) * cellSize,
        static_cast<float>(cellSize),
        static_cast<float>(cellSize)
    };

    // 3. Snake Variables
    //-------------------------------------------------------------------
    std::deque<Vector2> body = { Vector2{400, 400}, Vector2{375, 400}, Vector2{350, 400} };
    Vector2 direction = { static_cast<float>(cellSize), 0 }; // Starting movement: Right
    bool gameOver = false;

    // 4. Score TEXT 
    // ------------------------------------------------------------------
    Text scoreText = { "Score : 0", 15, 15, 20, WHITE };
    int currentScore = 0;

    // 5. Level 
    // -----------------------------------------------------------------
    unsigned int FrameSpeed = 12;

    // Main Game Loop
    //-------------------------------------------------------------------
    while (!WindowShouldClose()) {

        if (!gameOver) {
            // A. Update Direction (Input)
            //-----------------------------------------------------------
            if (IsKeyPressed(KEY_UP) && direction.y == 0)    direction = { 0, -static_cast<float>(cellSize) };
            if (IsKeyPressed(KEY_DOWN) && direction.y == 0)  direction = { 0, static_cast<float>(cellSize) };
            if (IsKeyPressed(KEY_LEFT) && direction.x == 0)  direction = { -static_cast<float>(cellSize), 0 };
            if (IsKeyPressed(KEY_RIGHT) && direction.x == 0) direction = { static_cast<float>(cellSize), 0 };

            // B. Movement Logic
            //-----------------------------------------------------------
            Vector2 nextHeadPos = { body[0].x + direction.x, body[0].y + direction.y };

            // Wall Collision Check
            if (nextHeadPos.x < 0 || nextHeadPos.x >= screenWidth ||
                nextHeadPos.y < 0 || nextHeadPos.y >= screenHeight) {
                gameOver = true;
            }

            // Self-Collision Check
            for (const auto& segment : body) {
                if (nextHeadPos.x == segment.x && nextHeadPos.y == segment.y) {
                    gameOver = true;
                }
            }

            if (!gameOver) {
                body.push_front(nextHeadPos); // Add new head

                // Apple Collision Check
                if (CheckCollisionRecs(Rectangle{ body[0].x, body[0].y, static_cast<float>(cellSize), static_cast<float>(cellSize) }, apple)) {
                    apple.x = static_cast<float>(rand() % (screenWidth / cellSize)) * cellSize;
                    apple.y = static_cast<float>(rand() % (screenHeight / cellSize)) * cellSize;

                    currentScore++;
                    scoreText.content = "Score : " + std::to_string(currentScore);

                    if (currentScore > 0 && currentScore % 5 == 0) {
                        FrameSpeed += 2;
                        SetTargetFPS(FrameSpeed);
                    }
                }
                else {
                    body.pop_back(); // Remove tail to move forward
                }
            }
        }
        else {
            // Restart game if R is pressed
            if (IsKeyPressed(KEY_R)) {
                body = { Vector2{400, 400}, Vector2{375, 400}, Vector2{350, 400} };
                direction = { static_cast<float>(cellSize), 0 };
                FrameSpeed = 12;
                SetTargetFPS(FrameSpeed);
                currentScore = 0;
                scoreText.content = "Score : 0";
                gameOver = false;
            }
        }

        // Drawing
        //---------------------------------------------------------------
        BeginDrawing();
        ClearBackground(DARKGREEN);

        if (!gameOver) {
            DrawRectangleRec(apple, RED);
            scoreText.Draw();

            for (size_t i = 0; i < body.size(); i++) {
                Color color = (i == 0) ? LIME : GREEN;
                DrawRectangle(static_cast<int>(body[i].x), static_cast<int>(body[i].y), cellSize - 1, cellSize - 1, color);
            }
        }
        else {
            DrawText("GAME OVER", screenWidth / 2 - 100, screenHeight / 2 - 20, 40, RED);
            DrawText("Press 'R' to Restart", screenWidth / 2 - 110, screenHeight / 2 + 30, 20, RAYWHITE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}