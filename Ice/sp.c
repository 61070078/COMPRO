#include "raylib.h"

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 1280;
    int screenHeight = 720;

    int play_number = 1;
    int player_speed = 6.5;
    int player_state = 0;
    int player_attack = 10;
    int player_hp = 100;

    int enemy_hp = 150;
    int enemy_state = 1;

    InitWindow(screenWidth, screenHeight, "raylib [texture] example - texture rectangle");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Texture2D player[4];
    player[0] = LoadTexture("sp_2.png");        // Texture loading
    player[1] = LoadTexture("sp_3.png");        // Texture loading

    Vector2 position = { screenWidth/2, screenHeight/2};
    // Vector2 attackBox = {position.x - ((100 - (150*play_number)) * (direction - 1)), position.y + ((-50 + (150*(play_number-2))) * direction)};
    // Vector2 attackSize = {50 + (50*direction), 100 - (50*direction)};
    Vector2 attackP = {position.x + 100, position.y};
    Vector2 attackS = {100, 100};
    Vector2 enemy_position = {150, 150};

    Rectangle frameRec = { 0.0f, 0.0f, (float)player[play_number].width/6, (float)player[play_number].height };
    Rectangle frameRec2 = { 0.0f, 0.0f, (float)player[play_number].width/6, (float)player[play_number].height };

    Rectangle attack_box = {attackP.x, attackP.y, 100, 100};
    Rectangle enemy = {enemy_position.x, enemy_position.y, 100, 100};
    int currentFrame = 0;

    int framesCounter = 0;
    int framesSpeed = 8;           // Number of spritesheet frames shown by second

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Loading PNG--------------------------------------------------------------------------
    Texture2D texture[2];
    texture[0] = LoadTextureFromImage(LoadImage("bg_1.png"));
    texture[1] = LoadTextureFromImage(LoadImage("map.png"));

    Color e_color = WHITE;

    bool hit = false;

    UnloadImage(LoadImage("bg_1.png"));
    UnloadImage(LoadImage("bg_2.png"));
  
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        e_color = WHITE;
        player_state = 0;
        framesCounter++;
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_RIGHT) && position.x < screenWidth - 150) {
            position.x += player_speed;
            play_number = 0;
            player_state = 1;
            attackP.x = position.x + 100;
            attackP.y = position.y;
        }
        if (IsKeyDown(KEY_LEFT) && position.x > 50) {
            position.x -= player_speed;
            play_number = 1;
            player_state = 1;
            attackP.x = position.x - 100;
            attackP.y = position.y;
        }
        if (IsKeyDown(KEY_UP) && position.y > 50) {
            position.y -= player_speed;
            player_state = 1;
            attackP.x = position.x;
            attackP.y = position.y - 100;
        }
        if (IsKeyDown(KEY_DOWN) && position.y < screenHeight - 150) {
            position.y += player_speed;
            player_state = 1;
            attackP.x = position.x;
            attackP.y = position.y + 100;
        }
        attack_box.x = attackP.x;
        attack_box.y = attackP.y;

        if (IsKeyPressed(KEY_SPACE)) {
            hit = CheckCollisionRecs(attack_box, enemy);
            if(hit){
                e_color = BLACK;
                enemy_hp -= player_attack;
                hit = false;
                if(enemy_hp <= 0){
                    enemy_hp = 0;
                    enemy_state = 0;}
            }
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

            switch(player_state){
                case 1:
                    DrawTextureRec(player[play_number], frameRec, position, WHITE);  // Draw part of the texture
                    break;
                default:
                    DrawTextureRec(player[play_number], frameRec2, position, WHITE);   // Draw part of the texture
            }

            switch(enemy_state){
                case 1:
                    DrawText(FormatText("%d", enemy_hp), enemy_position.x, enemy_position.y - 22, 20, GRAY);
                    DrawRectangleV(enemy_position, attackS, e_color);
                    break;
                default:
                    break;
            }
            
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