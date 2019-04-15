#include "raylib.h"

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 1280;
    int screenHeight = 720;
    int gravity = 10;

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
    int jumpCounter = 0;
    int checkJump = 1;

    InitWindow(screenWidth, screenHeight, "raylib [texture] example - texture rectangle");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Texture2D player[4];
    player[0] = LoadTexture("../src/IMG/player/3_KNIGHT/_WALK/walk_R.png");        // Texture loading
    player[1] = LoadTexture("../src/IMG/player/3_KNIGHT/_WALK/walk_L.png");        // Texture loading
    player[2] = LoadTexture("../src/IMG/player/3_KNIGHT/_ATTACK/att_R.png");        // Texture loading
    player[3] = LoadTexture("../src/IMG/player/3_KNIGHT/_ATTACK/att_L.png"); 

    Rectangle playerFrame = { 0.0f, 0.0f, (float)player[playNumber].width/7, (float)player[playNumber].height };
    Rectangle playerFrame2 = { 0.0f, 0.0f, (float)player[playNumber].width/7, (float)player[playNumber].height };
    Rectangle playerHitbox = { (float)screenWidth/2, (float)screenHeight/2, (float)player[playNumber].width/7, 100.0};
    Vector2 playerOrigin = {50, 50};

    Texture2D attack = LoadTexture("slash.png");
    Rectangle attackFrame = { 0.0f, 0.0f, (float)attack.width/5, (float)attack.height };
    Rectangle playerAttackBox = { playerHitbox.x + 75, playerHitbox.y, 100.0, 100.0};
    Vector2 attackOrigin = {25, 50};

    Vector2 enemyPosition = {150, 150};

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
        if(attackState == 0) playerState = 0;
        playerHitbox.y += gravity;
        gravity += 0.1;
        if(playerHitbox.y >= 570){
            playerHitbox.y = 570;
            checkJump = 1;
            gravity = 0;
        }
        framesCounter++;
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_RIGHT)) {
            playerHitbox.x += playerSpeed;
            playNumber = 0;
            playerState = 1;
            if(playerHitbox.x >= screenWidth - 100)
                playerHitbox.x = screenWidth - 100;

            playerAttackBox.x = playerHitbox.x + 75;
            playerAttackBox.y = playerHitbox.y;

        }
        if (IsKeyDown(KEY_LEFT)) {
            playerHitbox.x -= playerSpeed;
            playNumber = 1;
            playerState = 1;
            if(playerHitbox.x <= 100)
                playerHitbox.x = 100;
 
            playerAttackBox.x = playerHitbox.x - 75;
            playerAttackBox.y = playerHitbox.y;    
        }
        if (IsKeyDown(KEY_UP) && checkJump == 1) {
            checkJump = 0;
            gravity = -10;
        }
        if (IsKeyDown(KEY_DOWN)) {     
        }

        int playerTemp = playNumber;
        
        if (IsKeyPressed(KEY_SPACE) && attackState == 0) {
            currentPlayerFrame = 0;
            playerState = 1;
            attackState = 1;
            switch(playerTemp){
                case 0:
                    playNumber = 2;
                    break;
                case 1:
                    playNumber = 3;
                    break;
                default:
                    break;
            }
        }
        if(checkJump == 0) jumpCounter ++;
        if(jumpCounter >= 24){
            gravity = 10;
            jumpCounter = 0;
        }

        if (framesCounter >= (60/framesSpeed))
        {
            framesCounter = 0;
        
            currentPlayerFrame++;
            if (currentPlayerFrame > 6 && attackState == 1){
                currentPlayerFrame = 0;
                playNumber = playerTemp;
                attackState = 0;
            }
            else if (currentPlayerFrame > 6 ) currentPlayerFrame = 0;
            
            playerFrame.x = (float)currentPlayerFrame*(float)player[playNumber].width/7;
            
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

            DrawRectangleRec(ground, BLACK);
            DrawText(FormatText("%d", checkJump), 20, 10, 20, GRAY);
            DrawText(FormatText("%d", playerHitbox.y), 20, 31, 20, GRAY);            

            // switch(enemyState){
            //     case 1:
            //         DrawText(FormatText("%d", enemyHp), enemyPosition.x, enemyPosition.y - 22, 20, GRAY);
            //         break;
            //     default:
            //         break;
            // }

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