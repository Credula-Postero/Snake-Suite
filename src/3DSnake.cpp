#include <string>
#include <deque>
#include <ctime>
#include <cstdlib>
#include "raylib.h"


//Game Text Structure
//----------------------------------------------------
struct GameText
{


	std::string text;
	int textX;
	int textY;
	int textSize;
	Color textColor;

	void Draw()
	{
		DrawText(text.c_str(), textX, textY, textSize, textColor);     // I used c_str() to transform it to a string because it is asked  from DrawText function to insert unsinged char parameter.
	}
};

int main()
{
	//1. Initialization
	//----------------------------------------------------

	//1A - Window Dimenstion
	unsigned int screenWidth = 800;
	unsigned int screenHeight = 800;
	InitWindow(screenWidth, screenHeight, "3d Snake Game");

	//2A - Frame Per 
	int currentFPS = 12;
	SetTargetFPS(currentFPS);


	//Text
	//----------------------------------------------------
	//ScoreText
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	GameText scoreText = { "Eaten Apples : " ,  15 , 15 ,  20, WHITE };
	int currentScore = 0;

	//Game Over Text
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	GameText gameOverText = { "Game Over " , (screenWidth / 4) + 150 , (screenHeight / 2) - 75  , 35 , RED };

	// Restart Text
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	GameText restartText = { "To Restart Again, Press Space " , (screenWidth / 4) + 100 , (screenHeight / 2) - 35 , 20 , WHITE };

	//3A - 3D Camera Properities
	//----------------------------------------------------
	Camera3D camera = { 0 };
	camera.position = Vector3{ 10.0f , 20.0f , 20.0f };
	camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
	camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
	camera.fovy = 45.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	//Grid
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	float gridDimension = 5.0f;

	//Snake
	//----------------------------------------------------
	//Defining snake's body characteristics.
	std::deque<Vector3> snakeBody =
	{
		Vector3{0,0,0} ,
		Vector3{-1,0,0},
		Vector3{-2,0,0}
	};

	float snakeDimention = gridDimension - 0.5f;

	//Apple
	//----------------------------------------------------
	//Defining Apple's Charactarestics.
	float raduis = 0.4f;
	Vector3 applePosition = Vector3{ static_cast<float>(rand() % 14 - 7) , 0 , static_cast<float>(rand() % 14 - 7) };

	//Defining Default snake Direction
	Vector3 direction = { 1.0f, 0.0f, 0.0f };

	int i = 0;

	bool gameover = false;
	while (!WindowShouldClose())
	{

		//Detecting and Changing:
		//----------------------------------------------------
		//Arrow
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		if (!gameover)
		{
			//A- Keyboard Input : Arrows Movement.
			if (IsKeyDown(KEY_UP) and direction.z == 0) direction = Vector3{ 0,0,-1 };
			if (IsKeyDown(KEY_DOWN) and direction.z == 0) direction = Vector3{ 0 , 0 ,+1 };
			if (IsKeyDown(KEY_RIGHT) and direction.x == 0) direction = Vector3{ +1 , 0 ,0 };
			if (IsKeyDown(KEY_LEFT) and direction.x == 0) direction = Vector3{ -1, 0 ,0 };

			//B- Responding to Key Input AND Start moving to Right. not to left :)
			Vector3 nextHead = Vector3{ snakeBody[0].x + direction.x ,0, snakeBody[0].z + direction.z };            //Note : snakeBody[0] indicates the head.
			snakeBody.push_front(nextHead);

			//C- Snake Eats Apple : Collision : Same coordinates.
			if (snakeBody[0].x == applePosition.x and snakeBody[0].z == applePosition.z)
			{
				applePosition = Vector3{ static_cast<float>(rand() % 14 - 7), 0 , static_cast<float>(rand() % 14 - 7) };

				//Updating Score:
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

			//D- Bounderies
			if (snakeBody[0].x > 9 || snakeBody[0].x < -9 || snakeBody[0].z > 9 || snakeBody[0].z < -9) gameover = true;

			//E- Eats himself : Slef collision : deque same coordinates
			for (i = 1; i < snakeBody.size(); i++)
			{
				if (snakeBody[0].x == snakeBody[i].x and snakeBody[0].z == snakeBody[i].z) gameover = true;
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


		//Drawing
		//----------------------------------------------------
		BeginDrawing();
		//BackGround	
		ClearBackground(BLACK);

		//3d Mode Drawing
		BeginMode3D(camera);
		//Drawing Grid
		DrawGrid(10.0f, 2.0f);

		//Drawing Apple
		DrawSphere(applePosition, raduis, RED);

		for (size_t i = 0; i < snakeBody.size(); i++)
		{
			DrawCube(snakeBody[i], 0.95f, 0.5f, 0.95f, RAYWHITE);                 //  Snake 2 flat dimenstions should be equivalent to those of grid.
			DrawCubeWires(snakeBody[i], 0.95f, 0.5f, 0.95f, RAYWHITE);
		}
		EndMode3D();

		//ScoreText
		scoreText.Draw();

		if (gameover)
		{
			//GameOver Text 
			gameOverText.Draw();

			//Restart Text
			restartText.Draw();
		}


		EndDrawing();
	}

	CloseWindow();
	return 0;
}