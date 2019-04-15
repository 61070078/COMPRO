#include "raylib.h"

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 1280;
    int screenHeight = 720;

    int playNumber = 1;
    int playerSpeed = 6.5;
    int playerState = 0; // Player not move
    int playerAttack = 10;
    int playerHp = 100;

    int attackState = 0;

    int enemyHp = 150;
    int enemyState = 1;

    int currentPlayerFrame = 0;
    int currentAttackFrame = 0;
    int framesCounter = 0;
    int framesSpeed = 8;     // Number of spritesheet frames shown by second

    InitWindow(screenWidth, screenHeight, "raylib [texture] example - texture rectangle");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Texture2D player[4];
    player[0] = LoadTexture("sp_2.png");        // Texture loading
    player[1] = LoadTexture("sp_3.png");        // Texture loading

    Rectangle playerFrame = { 0.0f, 0.0f, (float)player[playNumber].width/6, (float)player[playNumber].height };
    Rectangle playerFrame2 = { 0.0f, 0.0f, (float)player[playNumber].width/6, (float)player[playNumber].height };
    Rectangle playerHitbox = { (float)screenWidth/2, (float)screenHeight/2, 100.0, 100.0};
    Vector2 playerOrigin = {50, 50};


    Texture2D attack = LoadTexture("slash.png");
    int attackDirection = 0;
    Rectangle attackFrame = { 0.0f, 0.0f, (float)attack.width/5, (float)attack.height };
    Rectangle playerAttackBox = { playerHitbox.x + 75, playerHitbox.y, 50.0, 100.0};
    Vector2 attackOrigin = {25, 50};

    Vector2 enemyPosition = {150, 150};

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Loading PNG--------------------------------------------------------------------------
    Texture2D texture[2];
    texture[0] = LoadTextureFromImage(LoadImage("bg_1.png"));
    texture[1] = LoadTextureFromImage(LoadImage("map.png"));

    Color enemyColor = WHITE;

    bool hit = false;

    UnloadImage(LoadImage("bg_1.png"));
    UnloadImage(LoadImage("bg_2.png"));
  
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        enemyColor = WHITE;
        playerState = 0;
        framesCounter++;
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_RIGHT)) {
            playerHitbox.x += playerSpeed;
            playNumber = 0;
            playerState = 1;
            if(playerHitbox.x >= screenWidth - 100)
                playerHitbox.x = screenWidth - 100;

            attackDirection = 0;
            playerAttackBox.x = playerHitbox.x + 75;
            playerAttackBox.y = playerHitbox.y;

        }
        if (IsKeyDown(KEY_LEFT)) {
            playerHitbox.x -= playerSpeed;
            playNumber = 1;
            playerState = 1;
            if(playerHitbox.x <= 100)
                playerHitbox.x = 100;

            attackDirection = 2;    
            playerAttackBox.x = playerHitbox.x - 75;
            playerAttackBox.y = playerHitbox.y;    
        }
        if (IsKeyDown(KEY_UP)) {
            playerHitbox.y -= playerSpeed;
            playerState = 1;
            if(playerHitbox.y <= 100)
                playerHitbox.y = 100;

            attackDirection = 3;
            playerAttackBox.x = playerHitbox.x;
            playerAttackBox.y = playerHitbox.y - 75;
        }
        if (IsKeyDown(KEY_DOWN)) {
            playerHitbox.y += playerSpeed;
            playerState = 1;
            if(playerHitbox.y >= screenHeight - 100)
                playerHitbox.y = screenHeight - 100;

            attackDirection = 1;
            playerAttackBox.x = playerHitbox.x;
            playerAttackBox.y = playerHitbox.y + 75;      
        }

        // if (IsKeyPressed(KEY_SPACE)) {
        //     hit = CheckCollisionRecs(attack_box, enemy);
        //     if(hit){
        //         enemyColor = BLACK;
        //         enemyHp -= playerAttack;
        //         hit = false;
        //         if(enemyHp <= 0){
        //             enemyHp = 0;
        //             enemyState = 0;}
        //     }
        // }

        if (framesCounter >= (60/framesSpeed))
        {
            framesCounter = 0;
            currentPlayerFrame++;
            if (currentPlayerFrame > 5) currentPlayerFrame = 0;
            playerFrame.x = (float)currentPlayerFrame*(float)player[playNumber].width/6;

            currentAttackFrame++;
            if (currentAttackFrame > 4) currentAttackFrame = 0;
            attackFrame.x = (float)currentAttackFrame*(float)attack.width/5;
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawTexture(texture[1], 0, 0, WHITE);

            switch(playerState){
                case 1:
                    DrawTexturePro(player[playNumber], playerFrame, playerHitbox, playerOrigin, 0.0, WHITE);
                    break;
                default:
                    DrawTexturePro(player[playNumber], playerFrame2, playerHitbox, playerOrigin, 0.0, WHITE);
            }

            // switch(enemyState){
            //     case 1:
            //         DrawText(FormatText("%d", enemyHp), enemyPosition.x, enemyPosition.y - 22, 20, GRAY);
            //         break;
            //     default:
            //         break;
            // }

            DrawTexturePro(attack, attackFrame, playerAttackBox, attackOrigin, 90*attackDirection, WHITE);

            // switch(attackState){
            //     case 1:
            // }
            


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