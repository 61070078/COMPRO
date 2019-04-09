#include "raylib.h"

int main()
{
    // confix
    int circle_img = 20;
    int speed_move_x_left = 20.0f;
    int speed_move_x_right = 20.0f;
    int speed_move_y_up = 20.0f;
    int speed_move_y_down = 20.0f;
    //--------------------------------------------------------------------------------------

    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 1280;
    int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");

    Vector2 ballPosition = { (float)screenWidth/2, (float)screenHeight/2 };

    SetTargetFPS(60);       // Set target frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_RIGHT)) ballPosition.x += speed_move_x_right;
        if (IsKeyDown(KEY_LEFT)) ballPosition.x -= speed_move_x_left;
        if (IsKeyDown(KEY_UP)) ballPosition.y -= speed_move_y_up;
        if (IsKeyDown(KEY_DOWN)) ballPosition.y += speed_move_y_down;
        
        if (ballPosition.x >= screenWidth - circle_img) {
            speed_move_x_right = 0.0f;
        } else if (ballPosition.x <= circle_img) {
            speed_move_x_left = 0.0f;
        } else if (ballPosition.y >= screenHeight - circle_img) {
            speed_move_y_down = 0.0f;
        } else if (ballPosition.y <= circle_img) {
            speed_move_y_up = 0.0f;
        } else {
            speed_move_y_up = 20.0f;
            speed_move_y_down = 20.0f;
            speed_move_x_left = 20.0f;
            speed_move_x_right = 20.0f;
        }
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RED);

            DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY);

            DrawCircleV(ballPosition, circle_img, MAROON);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}