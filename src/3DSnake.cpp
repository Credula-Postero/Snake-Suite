#include "raylib.h"
#include <string>
#include <deque>
#include <ctime>
#include <cstdlib>

struct GameText
{
    std::string text;
    int textX;
    int textY;
    int textSize;
    Color textColor;

    void Draw() const
    {
        DrawText(text.c_str(), textX, textY, textSize, textColor);
    }
};

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "3D Snake Game");

    int currentFPS = 12;
    SetTargetFPS(currentFPS);

    srand(static_cast<unsigned int>(time(nullptr)));

    GameText scoreText = { "Eaten Apples : 0", 15, 15, 20, WHITE };
    int currentScore = 0;

    GameText gameOverText = { "Game Over", (screenWidth / 4) + 150, (screenHeight / 2) - 75, 35, RED };
    GameText restartText = { "To Restart Again, Press Space", (screenWidth / 4) + 100, (screenHeight / 2) - 35, 20, WHITE };

    Camera3D camera = { 0 };
    camera.position = Vector3{ 10.0f, 20.0f, 20.0f };
    camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    std::deque<Vector3> snakeBody = {
        Vector3{  0.0f, 0.0f, 0.0f },
        Vector3{ -1.0f, 0.0f, 0.0f },
        Vector3{ -2.0f, 0.0f, 0.0f }
    };

    Vector3 direction = { 1.0f, 0.0f, 0.0f };
    const float appleRadius = 0.4f;

    Vector3 applePosition = {
        static_cast<float>(rand() % 14 - 7),
        0.0f,
        static_cast<float>(rand() % 14 - 7)
    };

    bool gameover = false;

    while (!WindowShouldClose())
    {
        if (!gameover)
        {
            if (IsKeyDown(KEY_UP) && direction.z == 0.0f) direction = Vector3{ 0.0f, 0.0f, -1.0f };
            if (IsKeyDown(KEY_DOWN) && direction.z == 0.0f) direction = Vector3{ 0.0f, 0.0f,  1.0f };
            if (IsKeyDown(KEY_RIGHT) && direction.x == 0.0f) direction = Vector3{ 1.0f, 0.0f,  0.0f };
            if (IsKeyDown(KEY_LEFT) && direction.x == 0.0f) direction = Vector3{ -1.0f, 0.0f,  0.0f };

            Vector3 nextHead = Vector3{ snakeBody[0].x + direction.x, 0.0f, snakeBody[0].z + direction.z };
            snakeBody.push_front(nextHead);

            if (snakeBody[0].x == applePosition.x && snakeBody[0].z == applePosition.z)
            {
                applePosition = Vector3{
                    static_cast<float>(rand() % 14 - 7),
                    0.0f,
                    static_cast<float>(rand() % 14 - 7)
                };

                currentScore++;
                scoreText.text = "Eaten Apples : " + std::to_string(currentScore);

                if (currentScore % 5 == 0)
                {
                    currentFPS += 1;
                    SetTargetFPS(currentFPS);
                }
            }
            else
            {
                snakeBody.pop_back();
            }

            if (snakeBody[0].x > 9.0f || snakeBody[0].x < -9.0f ||
                snakeBody[0].z > 9.0f || snakeBody[0].z < -9.0f)
            {
                gameover = true;
            }

            for (size_t i = 1; i < snakeBody.size(); ++i)
            {
                if (snakeBody[0].x == snakeBody[i].x && snakeBody[0].z == snakeBody[i].z)
                {
                    gameover = true;
                    break;
                }
            }
        }
        else
        {
            if (IsKeyPressed(KEY_SPACE))
            {
                snakeBody.clear();
                snakeBody.push_back(Vector3{ 0.0f, 0.0f, 0.0f });
                snakeBody.push_back(Vector3{ -1.0f, 0.0f, 0.0f });
                snakeBody.push_back(Vector3{ -2.0f, 0.0f, 0.0f });

                direction = Vector3{ 1.0f, 0.0f, 0.0f };
                currentScore = 0;
                scoreText.text = "Eaten Apples : 0";
                currentFPS = 12;
                SetTargetFPS(currentFPS);

                gameover = false;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode3D(camera);
        DrawGrid(10, 2.0f);
        DrawSphere(applePosition, appleRadius, RED);

        for (size_t i = 0; i < snakeBody.size(); ++i)
        {
            Color segColor = (i == 0) ? LIME : RAYWHITE;
            DrawCube(snakeBody[i], 0.95f, 0.5f, 0.95f, segColor);
            DrawCubeWires(snakeBody[i], 0.95f, 0.5f, 0.95f, DARKGRAY);
        }
        EndMode3D();

        scoreText.Draw();

        if (gameover)
        {
            gameOverText.Draw();
            restartText.Draw();
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}