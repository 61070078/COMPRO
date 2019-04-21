#include "raylib.h"
#include "stdlib.h"
#include "time.h"
#include "stdio.h" 

int randoms(int lower, int upper);

int main()
{
    // Variable And Config-------------------------------------------------------------------------
    int playerTextureValue = 4;
    int mapTextureValue = 5;
    int enemyTectureValue = 20;
    int screenWidth = 1280;
    int screenHeight = 720;
    int currentPlayerFrame = 0;
    int currentAttackFrame = 0;
    int framesCounter = 0;
    int framesSpeed = 8;
    int theEnemy = 3;
    int enemyFrames = 0;
    int valueEnemy = 0;
    int gameState = 0;
    int theMap = 0;
    //----------------------------------------------------------------------------------

    // Set Window----------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "Game Beta");
    InitAudioDevice(); 
    SetTargetFPS(60); 
    //----------------------------------------------------------------------------------


    // Loading Texture And Audio--------------------------------------------------------
    Texture2D playerTexture[playerTextureValue];
    playerTexture[0] = LoadTexture("../IMG/Player/walk_R.png");
    playerTexture[1] = LoadTexture("../IMG/Player/walk_L.png");
    playerTexture[2] = LoadTexture("../IMG/Player/walk_F.png");
    playerTexture[3] = LoadTexture("../IMG/Player/walk_B.png");

    Texture2D enemyTexture[enemyTectureValue];
    enemyTexture[0] = LoadTexture("../IMG/Enemy/EM_1/EM/walk_R.png");
    enemyTexture[1] = LoadTexture("../IMG/Enemy/EM_1/EM/walk_L.png");
    enemyTexture[2] = LoadTexture("../IMG/Enemy/EM_1/EM/walk_F.png");
    enemyTexture[3] = LoadTexture("../IMG/Enemy/EM_1/EM/walk_B.png");

    enemyTexture[4] = LoadTexture("../IMG/Enemy/EM_2/EM/walk_R.png");
    enemyTexture[5] = LoadTexture("../IMG/Enemy/EM_2/EM/walk_L.png");
    enemyTexture[6] = LoadTexture("../IMG/Enemy/EM_2/EM/walk_F.png");
    enemyTexture[7] = LoadTexture("../IMG/Enemy/EM_2/EM/walk_B.png");

    enemyTexture[8] = LoadTexture("../IMG/Enemy/EM_3/EM/walk_R.png");
    enemyTexture[9] = LoadTexture("../IMG/Enemy/EM_3/EM/walk_L.png");
    enemyTexture[10] = LoadTexture("../IMG/Enemy/EM_3/EM/walk_F.png");
    enemyTexture[11] = LoadTexture("../IMG/Enemy/EM_3/EM/walk_B.png");

    enemyTexture[12] = LoadTexture("../IMG/Enemy/EM_4/EM/walk_R.png");
    enemyTexture[13] = LoadTexture("../IMG/Enemy/EM_4/EM/walk_L.png");
    enemyTexture[14] = LoadTexture("../IMG/Enemy/EM_4/EM/walk_F.png");
    enemyTexture[15] = LoadTexture("../IMG/Enemy/EM_4/EM/walk_B.png");

    enemyTexture[16] = LoadTexture("../IMG/Enemy/EM_5/EM/walk_R.png");
    enemyTexture[17] = LoadTexture("../IMG/Enemy/EM_5/EM/walk_L.png");
    enemyTexture[18] = LoadTexture("../IMG/Enemy/EM_5/EM/walk_F.png");
    enemyTexture[19] = LoadTexture("../IMG/Enemy/EM_5/EM/walk_B.png");
    
    Texture2D mapTexture[mapTextureValue];
    mapTexture[0] = LoadTexture("../IMG/Maps/Map_1.png");
    mapTexture[1] = LoadTexture("../IMG/Maps/Map_2.png");
    mapTexture[2] = LoadTexture("../IMG/Maps/Map_3.png");
    mapTexture[3] = LoadTexture("../IMG/Maps/Map_4.png");
    mapTexture[4] = LoadTexture("../IMG/Maps/Map_5.png");

    Texture2D titleTexture[2];
    titleTexture[0] = LoadTexture("../IMG/Title/manu.png");
    titleTexture[1] = LoadTexture("../IMG/Title/gameOver.png");

    Music music[4];
    music[0] = LoadMusicStream("../Audio/Manu/Theme1.ogg");
    music[1] = LoadMusicStream("../Audio/Battle/Battle.ogg");
    music[2] = LoadMusicStream("../Audio/Attack/Attack.ogg");
    music[3] = LoadMusicStream("../Audio/GameOver/Gameover.ogg");
    //----------------------------------------------------------------------------------

    // Struct --------------------------------------------------------------------------
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

    struct Monster enemy[5];
    enemy[0].hp = 200;
    enemy[0].attack = 2;
    enemy[0].speed = 4;
    enemy[0].atkDelay = 50;
    enemy[0].texture = 0;
    enemy[0].state = 1;
    enemy[0].action = 0;
    enemy[0].hitWall = false;
    //----------------------------------------------------------------------------------

    // Rectangle------------------------------------------------------------------------
    Rectangle playerFrame = { 0.0f, 0.0f, (float)playerTexture[player.texture].width/3, (float)playerTexture[player.texture].height };
    Rectangle playerFrameStop = { 0.0f, 0.0f, (float)playerTexture[player.texture].width/3, (float)playerTexture[player.texture].height };
    Rectangle playerBox = { (float)screenWidth/2, (float)screenHeight/2, 50.0, 50.0 };
    Rectangle enemyBox = {150, 150, 50, 50};
    Rectangle playerAttackBox = { playerBox.x + 50, playerBox.y, 50.0, 50.0 };
    // Rectangle attackFrame = { 0.0f, 0.0f, (float)attack.width/5, (float)attack.height };
    //----------------------------------------------------------------------------------

    // Vector2--------------------------------------------------------------------------
    Vector2 origin = {0, 0};
    //----------------------------------------------------------------------------------

    // Color----------------------------------------------------------------------------
    // Color enemyColor = WHITE;
    //----------------------------------------------------------------------------------

    PlayMusicStream(music[0]);
    PlayMusicStream(music[1]);
    PlayMusicStream(music[2]);
    PlayMusicStream(music[3]);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateMusicStream(music[0]);
        UpdateMusicStream(music[1]);
        UpdateMusicStream(music[2]);
        UpdateMusicStream(music[3]);

        switch (gameState)
        {
        case 0:
            PlayMusicStream(music[0]);
            StopMusicStream(music[1]);
            StopMusicStream(music[2]);
            StopMusicStream(music[3]);
            if (IsKeyDown(KEY_G)) {
                gameState = 1;
                player.hp = 100;
                theMap = randoms(0, 4);
            }
            break;
        case 1:
            StopMusicStream(music[0]);
            PlayMusicStream(music[1]);
            player.action = 0;
            player.state = 0;
            framesCounter++;

            if (theEnemy == 1) {
                enemyFrames = 0;
            } else if (theEnemy == 2) {
                enemyFrames = 4;
            } else if (theEnemy == 3) {
                enemyFrames = 8;
            } else if (theEnemy == 4) {
                enemyFrames = 12;
            } else if (theEnemy == 5) {
                enemyFrames = 16;
            }

            // Update-----------------------------------------------------------------------
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
                gameState = 2;
            } else {
                
                if (IsKeyDown(KEY_RIGHT)) {
                    playerBox.x += (player.speed - CheckCollisionRecs(playerBox, enemyBox)*0.4*player.speed);
                    player.texture = 0;
                    enemy[0].texture = 0 + enemyFrames;
                    player.state = 1;
                    if(playerBox.x >= screenWidth - 100)
                        playerBox.x = screenWidth - 100;

                    playerAttackBox.x = playerBox.x + 50;
                    playerAttackBox.y = playerBox.y;
                }
                if (IsKeyDown(KEY_LEFT)) {
                    playerBox.x -= (player.speed - CheckCollisionRecs(playerBox, enemyBox)*0.4*player.speed);
                    player.texture = 1;
                    enemy[0].texture = 1 + enemyFrames;
                    player.state = 1;
                    if(playerBox.x <= 50)
                        playerBox.x = 50;

                    playerAttackBox.x = playerBox.x - 50;
                    playerAttackBox.y = playerBox.y;    
                }
                if (IsKeyDown(KEY_UP)) {
                    playerBox.y -= (player.speed - CheckCollisionRecs(playerBox, enemyBox)*0.4*player.speed);
                    player.texture = 3;
                    enemy[0].texture = 3 + enemyFrames;
                    player.state = 1;
                    if(playerBox.y <= 50)
                        playerBox.y = 50;

                    playerAttackBox.x = playerBox.x;
                    playerAttackBox.y = playerBox.y - 50;
                }
                if (IsKeyDown(KEY_DOWN)) {
                    playerBox.y += (player.speed - CheckCollisionRecs(playerBox, enemyBox)*0.4*player.speed);
                    player.texture = 2;
                    enemy[0].texture = 2 + enemyFrames;
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
                    playerFrame.x = (float)currentPlayerFrame*(float)playerTexture[player.texture].width/3;
                }
            }
            break;
        case 2:
            StopMusicStream(music[1]);
            PlayMusicStream(music[3]);
            // delay(5);
            if ((int)(GetMusicTimePlayed(music[3])/GetMusicTimeLength(music[3])*100) == 99) {
                gameState = 0;
            }
            break;
        }

        //----------------------------------------------------------------------------------

        // Draw------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            switch (gameState)
            {
            case 0:
                DrawTexture(titleTexture[0], 0, 0, WHITE);
                break;
            case 1:
                DrawTexture(mapTexture[theMap], 0, 0, WHITE);

                switch(player.state){
                    case 1:
                        DrawTexturePro(playerTexture[player.texture], playerFrame, playerBox, origin, 0.0, WHITE);
                        break;
                    case -1:
                        DrawText("GameOver", screenWidth/2, screenHeight/2 - 35, 70, GRAY);
                        break;
                    default:
                        DrawTexturePro(playerTexture[player.texture], playerFrameStop, playerBox, origin, 0.0, WHITE);
                }

                switch(enemy[0].state){
                    case 1:
                        if(player.state != -1){
                            DrawTexturePro(enemyTexture[enemy[0].texture], playerFrame, enemyBox, origin, 0.0, WHITE);
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
                break;
            case 2:
                DrawTexture(titleTexture[1], 0, 0, WHITE);
                DrawText(FormatText("%i", (int)(GetMusicTimePlayed(music[3])/GetMusicTimeLength(music[3])*100)), 10, screenHeight - 40, 25, GREEN);
                break;
            }
            
            


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // Texture And Audio Unloading----------------------------------------------------------
    for(int i = 0; i < playerTextureValue; i++)
    {
        UnloadTexture(playerTexture[i]);
    }
    for(int i = 0; i < mapTextureValue; i++)
    {
        UnloadTexture(mapTexture[i]);
    }
    for(int i = 0; i < enemyTectureValue; i++)
    {
        UnloadTexture(enemyTexture[i]);
    }
    for (int i = 0; i < 2; i++)
    {
        UnloadTexture(titleTexture[i]);
    }
    for (int i = 0; i < 4; i++)
    {
        UnloadMusicStream(music[i]);
    }
    //--------------------------------------------------------------------------------------

    CloseAudioDevice();
    CloseWindow();
    
    return 0;
}

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Stroing start time
    clock_t start_time = clock();

    // looping till required time is not acheived
    while (clock() < start_time + milli_seconds);
}

int randoms(int lower, int upper) 
{ 
	int num = (rand() % (upper - lower + 1)) + lower; 
    return num;
} 