#include "raylib.h"

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 1280;
    int screenHeight = 720;

    int play_number = 1;

    int player_speed = 6.5;

    InitWindow(screenWidth, screenHeight, "raylib [texture] example - texture rectangle");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Texture2D player[4];
    player[0] = LoadTexture("sp_2.png");        // Texture loading
    player[1] = LoadTexture("sp_3.png");        // Texture loading

    Vector2 position = { 150, 150 };
    // Vector2 attackBox = {position.x - ((100 - (150*play_number)) * (direction - 1)), position.y + ((-50 + (150*(play_number-2))) * direction)};
    // Vector2 attackSize = {50 + (50*direction), 100 - (50*direction)};
    Vector2 attackP = {position.x + 100, position.y};
    Vector2 attackS = {50, 100};
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
        if (IsKeyDown(KEY_RIGHT) && position.x < screenWidth - 150) {
            position.x += player_speed;
            framesCounter++;
            play_number = 0;
            attackP.x = position.x + 100;
            attackP.y = position.y;
            attackS.x = 50;
            attackS.y = 100;
        }
        if (IsKeyDown(KEY_LEFT) && position.x > 50) {
            position.x -= player_speed;
            framesCounter++;
            play_number = 1;
            attackP.x = position.x - 50;
            attackP.y = position.y;
            attackS.x = 50;
            attackS.y = 100;
        }
        if (IsKeyDown(KEY_UP) && position.y > 50) {
            position.y -= player_speed;
            framesCounter++;
            attackP.x = position.x;
            attackP.y = position.y - 50;
            attackS.x = 100;
            attackS.y = 50;
        }
        if (IsKeyDown(KEY_DOWN) && position.y < screenHeight - 150) {
            position.y += player_speed;
            framesCounter++;
            attackP.x = position.x;
            attackP.y = position.y + 100;
            attackS.x = 100;
            attackS.y = 50;
        }

        if (framesCounter >= (60/framesSpeed))
        {
            framesCounter = 0;
            currentFrame++;

            if (currentFrame > 5) currentFrame = 0;

            frameRec.x = (float)currentFrame*(float)player[play_number].width/6;
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawTexture(texture[1], 0, 0, WHITE);

            DrawTextureRec(player[play_number], frameRec, position, WHITE);  // Draw part of the texture

            DrawRectangleV(attackP, attackS, WHITE);         

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