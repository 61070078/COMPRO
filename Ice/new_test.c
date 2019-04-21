#include "raylib.h"

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 1280;
    int screenHeight = 720;
    int border = 100;

    int playNumber = 0;
    int playerSpeed = 6.5;
    int playerState = 0; // Player not move
    int playerAttack = 10;
    int playerHp = 100;

    int actionState = 0;

    int enemyHp = 150;
    int enemyState = 1;

    int currentPlayerFrame = 0;
    int currentAttackFrame = 0;
    int framesCounter = 0;
    int framesSpeed = 8;     // Number of spritesheet frames shown by second
    int actionCounter = 0;

    InitWindow(screenWidth, screenHeight, "raylib [texture] example - texture rectangle");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Texture2D player[4];
    player[0] = LoadTexture("../src/IMG/player/3_KNIGHT/_WALK/walk_R.png");        // Texture loading
    player[1] = LoadTexture("../src/IMG/player/3_KNIGHT/_WALK/walk_L.png");        // Texture loading

    Rectangle playerFrame = { 0.0f, 0.0f, (float)player[playNumber].width/7, (float)player[playNumber].height };
    Rectangle playerFrame2 = { 0.0f, 0.0f, (float)player[playNumber].width/7, (float)player[playNumber].height };
    Rectangle playerBox = { (float)screenWidth/2, (float)screenHeight/2, (float)player[playNumber].width/7, (float)player[playNumber].height};
    Vector2 playerOrigin = {playerBox.width/2, playerBox.height/2};
    
    Texture2D attack = LoadTexture("../src/IMG/player/3_KNIGHT/_ATTACK/slash.png");
    Rectangle attackFrame = { 0.0f, 0.0f, (float)attack.width/5, (float)attack.height};
    Rectangle playerAttackBox = { playerBox.x + 75, playerBox.y, 50.0, 100.0};
    Vector2 attackOrigin = {25, 50};

    Rectangle enemyBox = {100, 100, (float)player[playNumber].height};

    Rectangle ground = {0.0, 620.0, (float)screenWidth, 100.0};

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Loading PNG--------------------------------------------------------------------------
    Texture2D texture[2];
    texture[0] = LoadTextureFromImage(LoadImage("bg_1.png"));
    texture[1] = LoadTextureFromImage(LoadImage("map.png"));

    Color enemyColor = WHITE;

    UnloadImage(LoadImage("bg_1.png"));
    UnloadImage(LoadImage("bg_2.png"));
  
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        
        framesCounter++;
        if(actionState > 0) actionCounter ++;
        
        int playerTemp = playNumber;

        if(actionState == 0) playerState = 0;
        // Update
        //----------------------------------------------------------------------------------

        if (IsKeyDown(KEY_RIGHT)) {
            playerBox.x += playerSpeed;
            playNumber = 0;
            playerState = 1;
            if(playerBox.x >= screenWidth - border) playerBox.x = screenWidth - border;

            playerAttackBox.x = playerBox.x + 75;
            playerAttackBox.y = playerBox.y;
        }
        
        if (IsKeyDown(KEY_LEFT)) {
            playerBox.x -= playerSpeed;
            playNumber = 1;
            playerState = 1;
            if(playerBox.x <= border) playerBox.x = border;

            playerAttackBox.x = playerBox.x - 75;
            playerAttackBox.y = playerBox.y;    
        }

        if (IsKeyDown(KEY_UP)) {
            playerBox.y -= playerSpeed;
            playerState = 1;
            if(playerBox.y <= border) playerBox.y = border;

            playerAttackBox.x = playerBox.x;
            playerAttackBox.y = playerBox.y - 75;    
        }

        if (IsKeyDown(KEY_DOWN)) {
            playerBox.y += playerSpeed;
            playerState = 1;
            if(playerBox.y >= screenHeight - border) playerBox.y = screenHeight - border;

            playerAttackBox.x = playerBox.y;
            playerAttackBox.y = playerBox.y + 75;    
        }
        
        if (IsKeyPressed(KEY_SPACE) && actionState == 0) {
            currentPlayerFrame = 0;
            playerState = 1;
            actionState = 1;
        }

        if (framesCounter >= (60/framesSpeed))
        {
            framesCounter = 0;
            currentPlayerFrame++;
            if (currentPlayerFrame > 6 ) currentPlayerFrame = 0;
            playerFrame.x = (float)currentPlayerFrame*(float)player[playNumber].width/7;
            
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawTexture(texture[1], 0, 0, WHITE);

            switch(playerState){
                case 1:
                    DrawTexturePro(player[playNumber], playerFrame, playerBox, playerOrigin, 0.0, WHITE);
                    break;
                default:
                    DrawTexturePro(player[playNumber], playerFrame2, playerBox, playerOrigin, 0.0, WHITE);
            }
            
            DrawText(FormatText("HP %d", playerHp), 20, screenHeight - 40, 30, GREEN);
            
            DrawText(FormatText("%f", playerBox.y), 20, 31, 20, GRAY);
            DrawText(FormatText("%f", playerFrame.x), 20, 71, 20, GRAY);        

            switch(enemyState){
               case 1:
                    DrawText(FormatText("%d", enemyHp), enemyBox.x, enemyBox.y - 22, 20, GRAY);
                    DrawRectangleRec(enemyBox, enemyColor);
                    break;
               default:
                    break;
            }

            switch(actionState){
                case 1:
                    DrawRectangleRec(playerAttackBox, RED);
                    break;
                default:
                    DrawRectangleRec(playerAttackBox, WHITE);
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(player[0]);       // Texture unloading
    UnloadTexture(player[1]);       // Texture unloading
    UnloadTexture(texture[0]);
    UnloadTexture(texture[1]);
    UnloadTexture(attack);

    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}