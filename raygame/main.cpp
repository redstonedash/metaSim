#include "raylib.h"
#include <iostream>
#include <ctime>
#include <cmath>
#define GLSL_VERSION            330
#define DEFAULT_VERTEX_SHADER   "resources/shaders/glsl400/base.vs"

int main()
{
	// Initialization //////////////////////////////////////////////////////////////////////////////////////////////////
	int screenWidth = 800;
	int screenHeight = 450;
	InitWindow(screenWidth, screenHeight, "raylib [shaders] example - postprocessing shader");
	int metaBlobPos[8];
	float metaBlobArr[8][2];
	float metaBlobVelocity[8][2];

	Image image = LoadImage("resources/test.png");   // Loaded in CPU memory (RAM)
	ImageFormat(&image, UNCOMPRESSED_R8G8B8A8);         // Format image to RGBA 32bit (required for texture update)
	Texture2D texture = LoadTextureFromImage(image);    // Image converted to texture, GPU memory (VRAM)

	Shader shader = LoadShader(0, FormatText("resources/shaders/glsl%i/gameMechanics.fs", GLSL_VERSION));
	metaBlobPos[0] = GetShaderLocation(shader, "mb1");
	metaBlobPos[1] = GetShaderLocation(shader, "mb2");
	metaBlobPos[2] = GetShaderLocation(shader, "mb3");
	metaBlobPos[3] = GetShaderLocation(shader, "mb4");
	metaBlobPos[4] = GetShaderLocation(shader, "mb5");
	metaBlobPos[5] = GetShaderLocation(shader, "mb6");
	metaBlobPos[6] = GetShaderLocation(shader, "mb7");
	metaBlobPos[7] = GetShaderLocation(shader, "mb8");
	// Create a RenderTexture2D to be used for render to texture
	RenderTexture2D buffer = LoadRenderTexture(screenWidth, screenHeight);
	SetTargetFPS(120);
	srand(time(0));
	for (int i = 0; i < 8; i++) {
		metaBlobArr[i][0] = (float) rand()/RAND_MAX;
		metaBlobArr[i][1] = (float) rand() / RAND_MAX;
		metaBlobVelocity[i][0] = (float)(rand() % 100-50) / 120;
		metaBlobVelocity[i][1] = (float)(rand() % 100-50) / 120;
		SetShaderValue(shader, metaBlobPos[i], metaBlobArr[i], 2);
	}
	int tempMouseX = 0;
	int tempMouseY = 0;
	while (!WindowShouldClose())            // Detect window close button or ESC key
	{
		
		for (int i = 0; i < 8; i++) {
			//for (int j = 0; j < 8; j++) {
			//	float inverseDist = 1/sqrt(pow(metaBlobVelocity[i][0], 2) + pow(metaBlobVelocity[i][1], 2));
			//	metaBlobArr[i][0] ;
			//	metaBlobArr[i][1] ;
			//	metaBlobArr[j][0] ;
			//	metaBlobArr[j][1] ;
			//
			//}
			metaBlobArr[i][0] += metaBlobVelocity[i][0]/screenWidth;
			metaBlobArr[i][1] += metaBlobVelocity[i][1]/screenHeight;
			metaBlobVelocity[i][1] *= 0.999f;
			if (metaBlobArr[i][0]>1) {
				metaBlobVelocity[i][0] *= -1;
				metaBlobArr[i][0] = 1;
				metaBlobArr[i][0] += metaBlobVelocity[i][0] / screenWidth;
			}
			if (metaBlobArr[i][1]>1) {
				metaBlobVelocity[i][1] *= -1;
				metaBlobArr[i][1] = 1;
				metaBlobArr[i][1] += metaBlobVelocity[i][1] / screenHeight;
			}
			if (metaBlobArr[i][0]<0) {
				metaBlobVelocity[i][0] *= -1;
				metaBlobArr[i][0] = 0;
				metaBlobArr[i][0] += metaBlobVelocity[i][0] / screenWidth;
			}
			if (metaBlobArr[i][1]<0) {
				metaBlobVelocity[i][1] *= -1;
				metaBlobArr[i][1] = 0;
				metaBlobArr[i][1] += metaBlobVelocity[i][1] / screenHeight;
			}
			metaBlobVelocity[i][1] += 0.1f;
			SetShaderValue(shader, metaBlobPos[i], metaBlobArr[i], 2);
		}
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			int deltaX = tempMouseX - GetMousePosition().x;
			int deltaY = tempMouseY - GetMousePosition().y;
			tempMouseX = GetMousePosition().x;
			tempMouseY = GetMousePosition().y;
			for (int i = 0; i < 8; i++) {			
				if (sqrt(pow(metaBlobArr[i][0] * screenWidth - GetMousePosition().x, 2) + pow(metaBlobArr[i][1] * screenHeight - GetMousePosition().y, 2))<=64.0f) {
					metaBlobArr[i][0] = GetMousePosition().x / screenWidth;
					metaBlobArr[i][1] = GetMousePosition().y / screenHeight;
					metaBlobVelocity[i][0] = 0;
					metaBlobVelocity[i][1] = 0;
					break;
				}
			}
		}
		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
			int deltaX = (tempMouseX - GetMousePosition().x)/4;
			int deltaY = (tempMouseY - GetMousePosition().y)/4;
			tempMouseX = GetMousePosition().x;
			tempMouseY = GetMousePosition().y;
			for (int i = 0; i < 8; i++) {
				if (sqrt(pow(metaBlobArr[i][0] * screenWidth - GetMousePosition().x, 2) + pow(metaBlobArr[i][1] * screenHeight - GetMousePosition().y, 2)) <= 64.0f) {
					metaBlobVelocity[i][0] = -deltaX;
					metaBlobVelocity[i][1] = -deltaY;
					metaBlobArr[i][0] = GetMousePosition().x / screenWidth;
					metaBlobArr[i][1] = GetMousePosition().y / screenHeight;
					float velLen = sqrt(pow(metaBlobVelocity[i][0], 2) + pow(metaBlobVelocity[i][1], 2));
					if (velLen>5) {
						metaBlobVelocity[i][0] = (metaBlobVelocity[i][0] / velLen) * 5;
						metaBlobVelocity[i][1] = (metaBlobVelocity[i][1] / velLen) * 5;
					}
					break;
				}
			}
		}
		// Update //////////////////////////////////////////////////////////////////////////////////////////////////

		// Draw //////////////////////////////////////////////////////////////////////////////////////////////////
		BeginDrawing();

			BeginTextureMode(buffer);   // Enable drawing to texture
				BeginShaderMode(shader);
					DrawTexture(texture, 0, 0, WHITE);
					//DrawRectangle(0, 0, screenWidth, screenHeight, { 0,0,10,255 });
					//DrawRectangle(100, 100, 100, 100, { 255,10,0,255 });
				EndShaderMode();

			EndTextureMode();
						// NOTE: Render texture must be y-flipped due to default OpenGL coordinates (left-bottom)
				DrawTextureRec(buffer.texture, { 0.0f, 0.0f, (float)buffer.texture.width, (float) -buffer.texture.height }, { 0.0f, 0.0f }, WHITE);
			DrawFPS(700, 15);
		EndDrawing();
		
		//////////////////////////////////////////////////////////////////////////////////////////////////
	}

	// De-Initialization //////////////////////////////////////////////////////////////////////////////////////////////////

	UnloadTexture(texture);

	UnloadShader(shader);

	UnloadRenderTexture(buffer);

	CloseWindow();

	return 0;
}