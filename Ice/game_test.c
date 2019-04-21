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
    playerTexture[0] = LoadTexture("D:/work/project/COMPRO/src/IMG/Player/walk_R.png");
    playerTexture[1] = LoadTexture("D:/work/project/COMPRO/src/IMG/Player/walk_L.png");
    playerTexture[2] = LoadTexture("D:/work/project/COMPRO/src/IMG/Player/walk_B.png"); 
    playerTexture[3] = LoadTexture("D:/work/project/COMPRO/src/IMG/Player/walk_F.png");
    
    Texture2D attackTexture[4];
    attackTexture[0] = LoadTexture("D:/work/project/COMPRO/src/IMG/HITBOX/hit_R.png");
    attackTexture[1] = LoadTexture("D:/work/project/COMPRO/src/IMG/HITBOX/hit_L.png");
    attackTexture[2] = LoadTexture("D:/work/project/COMPRO/src/IMG/HITBOX/hit_B.png");
    attackTexture[3] = LoadTexture("D:/work/project/COMPRO/src/IMG/HITBOX/hit_F.png");
    
    Texture2D enemyTexture[4];
    enemyTexture[0] = LoadTexture("D:/work/project/COMPRO/src/IMG/Enemy/EM_1/EM/walk_R.png");
    enemyTexture[1] = LoadTexture("D:/work/project/COMPRO/src/IMG/Enemy/EM_1/EM/walk_L.png");
    enemyTexture[2] = LoadTexture("D:/work/project/COMPRO/src/IMG/Enemy/EM_1/EM/walk_B.png");
    enemyTexture[3] = LoadTexture("D:/work/project/COMPRO/src/IMG/Enemy/EM_1/EM/walk_F.png");
     // Loading PNG--------------------------------------------------------------------------
    Texture2D texture[2];
    texture[0] = LoadTextureFromImage(LoadImage("bg_1.png"));
    texture[1] = LoadTextureFromImage(LoadImage("map.png"));
    
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

    struct Enemy {
        int type;
        int hp;
        int attack;
        float speed;
        int atkDelay;
        int texture;
        int frame;
        int state;
        int action;
        bool hitPlayer;
        bool hitWall;
    };

    struct Character player = {100, 10, 7, 50, 1, 0, 0, 0, false};
    Rectangle playerFrame = { 0.0f, 0.0f, (float)playerTexture[player.texture].width/3, (float)playerTexture[player.texture].height };
    Rectangle playerFrame2 = { 0.0f, 0.0f, (float)playerTexture[player.texture].width/3, (float)playerTexture[player.texture].height };
    Rectangle playerBox = { (float)screenWidth/2, (float)screenHeight/2, 50.0, 50.0};

    struct Enemy enemy[10];
    enemy[0].type = 1;
    enemy[0].hp = 200;
    enemy[0].attack = 1;
    enemy[0].speed = 4;
    enemy[0].atkDelay = 50;
    enemy[0].texture = 0;
    enemy[0].frame = 0;
    enemy[0].state = 1;
    enemy[0].action = 0;
    enemy[0].hitPlayer = false;
    enemy[0].hitWall = false;
    
    Rectangle enemyBox[10];
    enemyBox[0].x = 150;
    enemyBox[0].y = 150;
    enemyBox[0].width = 50;
    enemyBox[0].height = 50;

    Rectangle enemyFrame[10];
    enemyFrame[0].x = 0;
    enemyFrame[0].y = 0;
    enemyFrame[0].width = 50;
    enemyFrame[0].height = 50;

    Vector2 origin = {0, 0};

    Rectangle playerAttackFrame = { 0.0f, 0.0f, 50.0, 50.0};
    Rectangle playerAttackBox = { playerBox.x + 25, playerBox.y, 50.0, 50.0};

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    Color enemyColor = WHITE;

    UnloadImage(LoadImage("bg_1.png"));
    UnloadImage(LoadImage("bg_2.png"));
  
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        enemyColor = WHITE;
        player.state = 0;
        framesCounter++;
        // Update
        //----------------------------------------------------------------------------------
        enemy[0].hitPlayer = CheckCollisionRecs(playerBox, enemyBox[0]);
        if(!enemy[0].hitPlayer){
            float distanceX = abs(enemyBox[0].x - playerBox.x);
            float distanceY = abs(enemyBox[0].y - playerBox.y);
            if((distanceX <= distanceY && distanceX != 0) || distanceY == 0){
                if(enemyBox[0].x < playerBox.x){
                    enemy[0].texture = 0;
                    enemyBox[0].x += enemy[0].speed;
                } else if(enemyBox[0].x > playerBox.x){
                    enemy[0].texture = 1;
                    enemyBox[0].x -= enemy[0].speed;
                }
                if(distanceX < enemy[0].speed) enemyBox[0].x = playerBox.x;
            } else {
                if(enemyBox[0].y < playerBox.y){
                    enemy[0].texture = 3;
                    enemyBox[0].y += enemy[0].speed;
                }
                else if(enemyBox[0].y > playerBox.y){
                    enemy[0].texture = 2;
                    enemyBox[0].y -= enemy[0].speed;
                }
                if(distanceY < enemy[0].speed) enemyBox[0].y = playerBox.y;   
            }
        }

        if (enemy[0].hitWall && framesCounter%7 == 0 && enemy[0].state > -1) player.hp -= enemy[0].attack;
        
        if(player.hp <= 0) {
            player.hp = 0;
            player.state = -1;
        } else if (!player.hitWall) {
            if (IsKeyDown(KEY_RIGHT)) {
            playerBox.x += (player.speed - CheckCollisionRecs(playerBox, enemyBox[0])*0.4*player.speed);
            player.texture = 0;
            player.state = 1;
            if(playerBox.x >= screenWidth - 100)
                playerBox.x = screenWidth - 100;

            playerAttackBox.x = playerBox.x + 25;
            playerAttackBox.y = playerBox.y;
            

            }
            if (IsKeyDown(KEY_LEFT)) {
                playerBox.x -= (player.speed - CheckCollisionRecs(playerBox, enemyBox[0])*0.4*player.speed);
                player.texture = 1;
                player.state = 1;
                if(playerBox.x <= 50)
                    playerBox.x = 50;

                playerAttackBox.x = playerBox.x - 25;
                playerAttackBox.y = playerBox.y;    
            }
            if (IsKeyDown(KEY_UP)) {
                playerBox.y -= (player.speed - CheckCollisionRecs(playerBox, enemyBox[0])*0.4*player.speed);
                player.texture = 2;
                player.state = 1;
                if(playerBox.y <= 50)
                    playerBox.y = 50;

                playerAttackBox.x = playerBox.x;
                playerAttackBox.y = playerBox.y - 25;
            }
            if (IsKeyDown(KEY_DOWN)) {
                playerBox.y += (player.speed - CheckCollisionRecs(playerBox, enemyBox[0])*0.4*player.speed);
                player.texture = 3;
                player.state = 1;
                if(playerBox.y >= screenHeight - 100)
                    playerBox.y = screenHeight - 100;

                playerAttackBox.x = playerBox.x;
                playerAttackBox.y = playerBox.y + 25;      
            }

            if (IsKeyPressed(KEY_SPACE) && player.stamina >= 5) {
                player.action = 1;
                player.stamina  -= 5;
                if(CheckCollisionRecs(playerAttackBox, enemyBox[0])){
                    enemyColor = BLACK;
                    enemy[0].hp -= player.attack;
                    if(enemy[0].hp <= 0){
                        enemy[0].hp = 0;
                        enemy[0].state = -1;
                    }
                }
            }   
    
        }
        
         if(player.action > 0){
                player.action ++;
                if(player.action % 3 == 0) currentAttackFrame ++;
                else if (player.action > 16){
                    player.action = 0;
                    currentAttackFrame = 0;                    
                }
                switch(player.texture){
                    case 0:
                    case 1:
                        if (currentAttackFrame > 4) currentAttackFrame = 0;
                        playerAttackFrame.y = (float)currentAttackFrame*(float)attackTexture[player.texture].height/5;
                        playerAttackFrame.x = 0;
                        break;
                    case 2:
                    case 3:
                        if (currentAttackFrame > 4) currentAttackFrame = 0;
                        playerAttackFrame.x = (float)currentAttackFrame*(float)attackTexture[player.texture].width/5;
                        playerAttackFrame.y = 0;
                        break;
                    default:
                        break;
                }
            }

            if (framesCounter >= (60/framesSpeed))
            {
                framesCounter = 0;
                if (player.state > 0) currentPlayerFrame++;
                player.stamina += player.staminaRecove;
                if(player.stamina > 50) player.stamina = 50;
                if (currentPlayerFrame > 2) currentPlayerFrame = 0;
                playerFrame.x = (float)currentPlayerFrame*(float)playerTexture[player.texture].width/3;

                enemy[0].frame ++;
                if (enemy[0].frame > 2) enemy[0].frame = 0;
                enemyFrame[0].x = (float)enemy[0].frame*(float)enemyTexture[enemy[0].texture].width/3;
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
                        DrawTexturePro(enemyTexture[enemy[0].texture], enemyFrame[0], enemyBox[0], origin, 0.0, WHITE);
                        DrawText(FormatText("%d", enemy[0].hp), enemyBox[0].x, enemyBox[0].y - 22, 20, GRAY);
                    }
                    break;
                default:
                    break;
            }
         
            switch(player.action){
                case 0:
                    break;
                default:
                     DrawTexturePro(attackTexture[player.texture], playerAttackFrame, playerAttackBox, origin, 0.0, WHITE);
            }
            
            DrawText(FormatText("Hp %d", player.hp), 10, screenHeight - 40, 25, GREEN);
            DrawText(FormatText("Stamina %d", player.stamina), 100, screenHeight - 40, 20, BLUE);
            
            DrawText(FormatText("%d", currentAttackFrame), 50, 100, 19, GRAY);
            DrawText(FormatText("%.1f", playerAttackFrame.x), 50, 120, 19, GRAY);
            DrawText(FormatText("%.1f", playerAttackFrame.y), 50,  140, 19, GRAY);
            DrawText(FormatText("%d", player.action), 50,  80, 19, GRAY);
            
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(playerTexture[0]);       // Texture unloading
    UnloadTexture(playerTexture[1]);       // Texture unloading
    UnloadTexture(playerTexture[2]);       // Texture unloading
    UnloadTexture(playerTexture[3]);       // Texture unloading
    UnloadTexture(attackTexture[0]);       // Texture unloading
    UnloadTexture(attackTexture[1]);       // Texture unloading
    UnloadTexture(attackTexture[2]);       // Texture unloading
    UnloadTexture(attackTexture[3]);       // Texture unloading
    UnloadTexture(enemyTexture[0]);       // Texture unloading
    UnloadTexture(enemyTexture[1]);       // Texture unloading
    UnloadTexture(enemyTexture[2]);       // Texture unloading
    UnloadTexture(enemyTexture[3]);       // Texture unloading
    UnloadTexture(texture[0]);
    UnloadTexture(texture[1]);
    // UnloadTexture(attack);

    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}