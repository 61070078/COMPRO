#include "raylib.h"

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 1280;
    int screenHeight = 720;

    int play_number = 1;

    int speed_move_x_left = 6.5;
    int speed_move_x_right = 6.5;
    int speed_move_y_up = 6.5;
    int speed_move_y_down = 6.5;

    InitWindow(screenWidth, screenHeight, "raylib [texture] example - texture rectangle");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Texture2D player[2];
    player[0] = LoadTexture("sp_2.png");        // Texture loading
    player[1] = LoadTexture("sp_3.png");        // Texture loading

    Vector2 position = { 150, 150 };
    Rectangle frameRec = { 0.0f, 0.0f, (float)player[play_number].width/6, (float)player[play_number].height };
    int currentFrame = 0;

    int framesCounter = 0;
    int framesSpeed = 8;           // Number of spritesheet frames shown by second

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Loading PNG--------------------------------------------------------------------------
    Texture2D texture[2];
    texture[0] = LoadTextureFromImage(LoadImage("bg_1.png"));
    texture[1] = LoadTextureFromImage(LoadImage("map.png"));

    UnloadImage(LoadImage("bg_1.png"));
    UnloadImage(LoadImage("bg_2.png"));
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_RIGHT)) {
            position.x += speed_move_x_right;
            framesCounter++;
            play_number = 0;
        }
        if (IsKeyDown(KEY_LEFT)) {
            position.x -= speed_move_x_left;
            framesCounter++;
            play_number = 1;
        }
        if (IsKeyDown(KEY_UP)) {
            position.y -= speed_move_y_up;
            framesCounter++;
        }
        if (IsKeyDown(KEY_DOWN)) {
            position.y += speed_move_y_down;
            framesCounter++;
        }

        if (framesCounter >= (60/framesSpeed))
        {
            framesCounter = 0;
            currentFrame++;

            if (currentFrame > 5) currentFrame = 0;

            frameRec.x = (float)currentFrame*(float)player[play_number].width/6;
        }

        if (position.x >= screenWidth - 150) {
            speed_move_x_right = 0.;
        } else if (position.x <= 50) {
            speed_move_x_left = 0;
        } else if (position.y >= screenHeight - 150) {
            speed_move_y_down = 0;
        } else if (position.y <= 30) {
            speed_move_y_up = 0;
        } else {
            speed_move_y_up = 6.5;
            speed_move_y_down = 6.5;
            speed_move_x_left = 6.5;
            speed_move_x_right = 6.5;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawTexture(texture[1], 0, 0, WHITE);

            DrawTextureRec(player[play_number], frameRec, position, WHITE);  // Draw part of the texture


            DrawText("(c) Scarfy sprite by Eiden Marsal", screenWidth - 200, screenHeight - 20, 10, GRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(player[0]);       // Texture unloading
    UnloadTexture(player[1]);       // Texture unloading
    UnloadTexture(texture[0]);
    UnloadTexture(texture[1]);

    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}