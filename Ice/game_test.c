#include "raylib.h"
#include "stdlib.h"

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 1280;
    int screenHeight = 720;

    int currentPlayerFrame = 0;
    int currentAttackFrame = 0;
    int framesCounter = 0;
    int framesSpeed = 8;     // Number of spritesheet frames shown by second

    InitWindow(screenWidth, screenHeight, "raylib [texture] example - texture rectangle");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Texture2D playerTexture[4];
    playerTexture[0] = LoadTexture("sp_2.png");        // Texture loading
    playerTexture[1] = LoadTexture("sp_3.png");        // Texture loading

     // Loading PNG--------------------------------------------------------------------------
    Texture2D texture[2];
    texture[0] = LoadTextureFromImage(LoadImage("bg_1.png"));
    texture[1] = LoadTextureFromImage(LoadImage("map.png"));

    UnloadImage(LoadImage("bg_1.png"));
    UnloadImage(LoadImage("bg_2.png"));
    
    Texture2D attack = LoadTexture("../src/IMG/playerTexture/3_KNIGHT/_ATTACK/slash.png");

    struct Character {
        int hp;
        int attack;
        float speed;
        int stamina;
        int staminaRecove;
        int texture;
        int state;
        int action;
        bool hitWall;
    };

    struct Monster {
        int hp;
        int attack;
        float speed;
        int atkDelay;
        int texture;
        int state;
        int action;
        bool hitWall;
    };

    struct Character player = {100, 10, 8, 50, 1, 0, 0, 0, false};
    Rectangle playerFrame = { 0.0f, 0.0f, (float)playerTexture[player.texture].width/6, (float)playerTexture[player.texture].height };
    Rectangle playerFrame2 = { 0.0f, 0.0f, (float)playerTexture[player.texture].width/6, (float)playerTexture[player.texture].height };
    Rectangle playerBox = { (float)screenWidth/2, (float)screenHeight/2, 50.0, 50.0};

    struct Monster enemy[10];
    enemy[0].hp = 200;
    enemy[0].attack = 2;
    enemy[0].speed = 4;
    enemy[0].atkDelay = 50;
    enemy[0].texture = 0;
    enemy[0].state = 1;
    enemy[0].action = 0;
    enemy[0].hitWall = false;
    Rectangle enemyBox = {150, 150, 50, 50};

    Vector2 origin = {0, 0};

    // Rectangle attackFrame = { 0.0f, 0.0f, (float)attack.width/5, (float)attack.height };
    Rectangle playerAttackBox = { playerBox.x + 50, playerBox.y, 50.0, 50.0};

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    Color enemyColor = WHITE;

    UnloadImage(LoadImage("bg_1.png"));
    UnloadImage(LoadImage("bg_2.png"));
  
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        player.action = 0;
        enemyColor = WHITE;
        player.state = 0;
        framesCounter++;
        // Update
        //----------------------------------------------------------------------------------
        enemy[0].hitWall = CheckCollisionRecs(playerBox, enemyBox);
        if(!enemy[0].hitWall){
            if(abs(enemyBox.x - playerBox.x) < enemy[0].speed) enemyBox.x = playerBox.x;
            else if(enemyBox.x < playerBox.x) enemyBox.x += enemy[0].speed;
            else if(enemyBox.x > playerBox.x) enemyBox.x -= enemy[0].speed;
        
            if(abs(enemyBox.y - playerBox.y) < enemy[0].speed) enemyBox.y = playerBox.y;
            else if(enemyBox.y < playerBox.y) enemyBox.y += enemy[0].speed;
            else if(enemyBox.y > playerBox.y) enemyBox.y -= enemy[0].speed;    
        } else if (enemy[0].hitWall && framesCounter%7 == 0 && enemy[0].state > -1) player.hp -= enemy[0].attack;
        
        if(player.hp <= 0) {
            player.hp = 0;
            player.state = -1;
        } else {
            if (IsKeyDown(KEY_RIGHT)) {
            playerBox.x += (player.speed - CheckCollisionRecs(playerBox, enemyBox)*0.4*player.speed);
            player.texture = 0;
            player.state = 1;
            if(playerBox.x >= screenWidth - 100)
                playerBox.x = screenWidth - 100;

            playerAttackBox.x = playerBox.x + 50;
            playerAttackBox.y = playerBox.y;
            

            }
            if (IsKeyDown(KEY_LEFT)) {
                playerBox.x -= (player.speed - CheckCollisionRecs(playerBox, enemyBox)*0.4*player.speed);
                player.texture = 1;
                player.state = 1;
                if(playerBox.x <= 50)
                    playerBox.x = 50;

                playerAttackBox.x = playerBox.x - 50;
                playerAttackBox.y = playerBox.y;    
            }
            if (IsKeyDown(KEY_UP)) {
                playerBox.y -= (player.speed - CheckCollisionRecs(playerBox, enemyBox)*0.4*player.speed);
                player.state = 1;
                if(playerBox.y <= 50)
                    playerBox.y = 50;

                playerAttackBox.x = playerBox.x;
                playerAttackBox.y = playerBox.y - 50;
            }
            if (IsKeyDown(KEY_DOWN)) {
                playerBox.y += (player.speed - CheckCollisionRecs(playerBox, enemyBox)*0.4*player.speed);
                player.state = 1;
                if(playerBox.y >= screenHeight - 100)
                    playerBox.y = screenHeight - 100;

                playerAttackBox.x = playerBox.x;
                playerAttackBox.y = playerBox.y + 50;      
            }

            if (IsKeyPressed(KEY_SPACE) && player.stamina >= 5) {
                player.action = 1;
                player.stamina  -= 5;
                if(CheckCollisionRecs(playerAttackBox, enemyBox)){
                    enemyColor = BLACK;
                    enemy[0].hp -= player.attack;
                    if(enemy[0].hp <= 0){
                        enemy[0].hp = 0;
                        enemy[0].state = -1;
                    }
                }
            }

            if (framesCounter >= (60/framesSpeed))
            {
                framesCounter = 0;
                currentPlayerFrame++;
                player.stamina += player.staminaRecove;
                if(player.stamina > 50) player.stamina = 50;
                if (currentPlayerFrame > 5) currentPlayerFrame = 0;
                playerFrame.x = (float)currentPlayerFrame*(float)playerTexture[player.texture].width/6;
            }
        }
        
        

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawTexture(texture[1], 0, 0, WHITE);

            switch(player.state){
                case 1:
                    DrawTexturePro(playerTexture[player.texture], playerFrame, playerBox, origin, 0.0, WHITE);
                    break;
                case -1:
                    DrawText("GameOver", screenWidth/2, screenHeight/2 - 35, 70, GRAY);
                    break;    
                default:
                    DrawTexturePro(playerTexture[player.texture], playerFrame2, playerBox, origin, 0.0, WHITE);
            }

            switch(enemy[0].state){
                case 1:
                    if(player.state != -1){
                        DrawRectangleRec(enemyBox, enemyColor);
                        DrawText(FormatText("%d", enemy[0].hp), enemyBox.x, enemyBox.y - 22, 20, GRAY);
                    }
                    break;
                default:
                    break;
            }

            switch(player.action){
                case 1:
                    DrawRectangleRec(playerAttackBox, RED);
                    break;
                default:
                    if(player.state != -1) DrawRectangleRec(playerAttackBox, WHITE);
            }
            
            DrawText(FormatText("Hp %d", player.hp), 10, screenHeight - 40, 25, GREEN);
            DrawText(FormatText("Stamina %d", player.stamina), 100, screenHeight - 40, 20, BLUE);
            


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(playerTexture[0]);       // Texture unloading
    UnloadTexture(playerTexture[1]);       // Texture unloading
    UnloadTexture(texture[0]);
    UnloadTexture(texture[1]);
    // UnloadTexture(attack);

    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}