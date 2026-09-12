#include "raylib.h"
#include <iostream>




int main(void){
	InitWindow(850, 600, "gravity Simulation");

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
		EndDrawing();


	}
	CloseWindow();
	return 0;

}
