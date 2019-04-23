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
    int enemyTextureValue = 20;
    int soundFxValue = 1;
    int musicValue = 4;
    int titleTextureValue = 16;
    int itemTextureValue = 10;

    int enemyValue = 0;
    int currentEnemy = 0;
    int killEnemyValue = 0;

    int item1 = 0;
    int item2 = 0;
    int item3 = 0;

    int screenWidth = 1280;
    int screenHeight = 720;
    int currentPlayerFrame = 0;
    int currentAttackFrame = 0;
    int framesCounter = 0;
    int framesSpeed = 8;
    int gameState = 0;
    int theMap = 0;

    int lettersCount = 0;
    int topSideRecWidth = 16;
    int leftSideRecHeight = 16;
    int bottomSideRecWidth = 16;
    int rightSideRecHeight = 16;
    int state = 0;                  // Tracking animation states (State Machine)
    float alpha = 1.0f;
    int logoPositionX = screenWidth/2 - 128;
    int logoPositionY = screenHeight/2 - 128;
    //----------------------------------------------------------------------------------

    // Set Window----------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "Lost Fantasy");
    InitAudioDevice();
    SetTargetFPS(60);
    //----------------------------------------------------------------------------------


    // Loading Texture And Audio--------------------------------------------------------
    Texture2D playerTexture[playerTextureValue];
    playerTexture[0] = LoadTexture("../src/IMG/Player/walk_R.png");
    playerTexture[1] = LoadTexture("../src/IMG/Player/walk_L.png");
    playerTexture[2] = LoadTexture("../src/IMG/Player/walk_F.png");
    playerTexture[3] = LoadTexture("../src/IMG/Player/walk_B.png");

    Texture2D attackTexture[4];
    attackTexture[0] = LoadTexture("../src/IMG/PLayer/HIT/hit_R.png");
    attackTexture[1] = LoadTexture("../src/IMG/PLayer/HIT/hit_L.png");
    attackTexture[2] = LoadTexture("../src/IMG/PLayer/HIT/hit_F.png");
    attackTexture[3] = LoadTexture("../src/IMG/PLayer/HIT/hit_B.png");

    Texture2D enemyTexture[enemyTextureValue];
    enemyTexture[0] = LoadTexture("../src/IMG/Enemy/EM_1/EM/walk_R.png");
    enemyTexture[1] = LoadTexture("../src/IMG/Enemy/EM_1/EM/walk_L.png");
    enemyTexture[2] = LoadTexture("../src/IMG/Enemy/EM_1/EM/walk_F.png");
    enemyTexture[3] = LoadTexture("../src/IMG/Enemy/EM_1/EM/walk_B.png");

    enemyTexture[4] = LoadTexture("../src/IMG/Enemy/EM_2/EM/walk_R.png");
    enemyTexture[5] = LoadTexture("../src/IMG/Enemy/EM_2/EM/walk_L.png");
    enemyTexture[6] = LoadTexture("../src/IMG/Enemy/EM_2/EM/walk_F.png");
    enemyTexture[7] = LoadTexture("../src/IMG/Enemy/EM_2/EM/walk_B.png");

    enemyTexture[8] = LoadTexture("../src/IMG/Enemy/EM_3/EM/walk_R.png");
    enemyTexture[9] = LoadTexture("../src/IMG/Enemy/EM_3/EM/walk_L.png");
    enemyTexture[10] = LoadTexture("../src/IMG/Enemy/EM_3/EM/walk_F.png");
    enemyTexture[11] = LoadTexture("../src/IMG/Enemy/EM_3/EM/walk_B.png");

    enemyTexture[12] = LoadTexture("../src/IMG/Enemy/EM_4/EM/walk_R.png");
    enemyTexture[13] = LoadTexture("../src/IMG/Enemy/EM_4/EM/walk_L.png");
    enemyTexture[14] = LoadTexture("../src/IMG/Enemy/EM_4/EM/walk_F.png");
    enemyTexture[15] = LoadTexture("../src/IMG/Enemy/EM_4/EM/walk_B.png");

    enemyTexture[16] = LoadTexture("../src/IMG/Enemy/EM_5/EM/walk_R.png");
    enemyTexture[17] = LoadTexture("../src/IMG/Enemy/EM_5/EM/walk_L.png");
    enemyTexture[18] = LoadTexture("../src/IMG/Enemy/EM_5/EM/walk_F.png");
    enemyTexture[19] = LoadTexture("../src/IMG/Enemy/EM_5/EM/walk_B.png");

    Texture2D mapTexture[mapTextureValue];
    mapTexture[0] = LoadTexture("../src/IMG/Maps/Map_1.png");
    mapTexture[1] = LoadTexture("../src/IMG/Maps/Map_2.png");
    mapTexture[2] = LoadTexture("../src/IMG/Maps/Map_3.png");
    mapTexture[3] = LoadTexture("../src/IMG/Maps/Map_4.png");
    mapTexture[4] = LoadTexture("../src/IMG/Maps/Map_5.png");

    Texture2D titleTexture[titleTextureValue];
    titleTexture[0] = LoadTexture("../src/IMG/Title/manu.png");
    titleTexture[1] = LoadTexture("../src/IMG/Title/gameOver.png");
    titleTexture[2] = LoadTexture("../src/IMG/Face/face_T.png");
    titleTexture[3] = LoadTexture("../src/IMG/items/text_F.png");
    titleTexture[4] = LoadTexture("../src/IMG/items/text_U.png");
    titleTexture[5] = LoadTexture("../src/IMG/items/text_Q.png");
    titleTexture[6] = LoadTexture("../src/IMG/items/text_W.png");
    titleTexture[7] = LoadTexture("../src/IMG/items/text_E.png");
    titleTexture[8] = LoadTexture("../src/IMG/items/text_N.png");
    titleTexture[9] = LoadTexture("../src/IMG/Title/Bar/bar_item_1.png");
    titleTexture[10] = LoadTexture("../src/IMG/Title/Bar/bar_item_2.png");
    titleTexture[11] = LoadTexture("../src/IMG/Title/Bar/bar_item_3.png");
    titleTexture[12] = LoadTexture("../src/IMG/Title/Bar/bar_item_4.png");
    titleTexture[13] = LoadTexture("../src/IMG/Title/Bar/bar_item_5.png");
    titleTexture[14] = LoadTexture("../src/IMG/Title/Bar/bar_item_6.png");
    titleTexture[15] = LoadTexture("../src/IMG/Title/Bar/bar.png");

    Music music[musicValue];
    music[0] = LoadMusicStream("../src/Audio/Manu/Theme1.ogg");
    music[1] = LoadMusicStream("../src/Audio/Battle/Battle.ogg");
    music[2] = LoadMusicStream("../src/Audio/Attack/Attack.ogg");
    music[3] = LoadMusicStream("../src/Audio/GameOver/Gameover.ogg");

    Sound soundFx[soundFxValue];
    soundFx[0] = LoadSound("../src/Audio/Attack/Attack.ogg");

    Texture2D itemTexture[itemTextureValue];
    itemTexture[0] = LoadTexture("../src/IMG/items/atkUp_T.png");
    itemTexture[1] = LoadTexture("../src/IMG/items/defUp_T.png");
    itemTexture[2] = LoadTexture("../src/IMG/items/extraArmor_T.png");
    itemTexture[3] = LoadTexture("../src/IMG/items/immortal_T.png");
    itemTexture[4] = LoadTexture("../src/IMG/items/maxPotion_T.png");
    itemTexture[5] = LoadTexture("../src/IMG/items/maxStamina_T.png");
    itemTexture[6] = LoadTexture("../src/IMG/items/potion_T.png");
    itemTexture[7] = LoadTexture("../src/IMG/items/revive_T.png");
    itemTexture[8] = LoadTexture("../src/IMG/items/speedUp_T.png");
    itemTexture[9] = LoadTexture("../src/IMG/items/stamina_T.png");
    //----------------------------------------------------------------------------------

    // Struct --------------------------------------------------------------------------
    struct Character {
        int maxHp; //4
        int hp;
        int attack; //0
        float speed;
        int maxStamina; //5
        int stamina;
        int staminaRecove;
        int texture;
        int state;
        int action;
        bool hitWall;
        int defend; //1
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

    // struct Inventory
    // {
    //     int potion; 6
    //     int stamina; 9
    //     int immortality; 3
    //     int speed; 8
    //     int armor; 2
    //     int revive; 7
    // };

    struct Character player = {100, 100, 10, 7, 50, 50, 1, 0, 0, 0, false};

    struct Enemy enemy[10];
    // enemy[0].type = 2;
    // enemy[0].hp = 200;
    // enemy[0].attack = 2;
    // enemy[0].speed = 4;
    // enemy[0].atkDelay = 0.5;
    // enemy[0].texture = 0;
    // enemy[0].frame = 0;
    // enemy[0].state = 1;
    // enemy[0].action = 0;
    // enemy[0].hitPlayer = false;
    // enemy[0].hitWall = false;

    //----------------------------------------------------------------------------------

    // Rectangle------------------------------------------------------------------------
    Rectangle playerFrame = { 0.0f, 0.0f, (float)playerTexture[player.texture].width/3, (float)playerTexture[player.texture].height };
    Rectangle playerFrameStop = { 0.0f, 0.0f, (float)playerTexture[player.texture].width/3, (float)playerTexture[player.texture].height };
    Rectangle playerBox = { (float)screenWidth/2, (float)screenHeight/2, 50.0, 50.0 };
    Rectangle playerAttackBox = { playerBox.x + 25, playerBox.y, 50.0, 50.0 };
    Rectangle playerAttackFrame = { 0.0f, 0.0f, 50.0, 50.0};
    Rectangle playerStamina =  {45, 644, 165.0, 20};
    Rectangle playerHp =  {45, 686, 165.0, 20};

    Rectangle enemyBox[10];
    // enemyBox[0].x = 150;
    // enemyBox[0].y = 150;
    // enemyBox[0].width = 50;
    // enemyBox[0].height = 50;

    Rectangle enemyFrame[10];
    // enemyFrame[0].x = 0;
    // enemyFrame[0].y = 0;
    // enemyFrame[0].width = 50;
    // enemyFrame[0].height = 50;
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
            StopMusicStream(music[1]);
            StopMusicStream(music[2]);
            StopMusicStream(music[3]);
            if (state == 0)                 // State 0: Small box blinking
            {
                StopMusicStream(music[0]);
                framesCounter++;
                if (framesCounter == 120)
                {
                    state = 1;
                    framesCounter = 0;      // Reset counter... will be used later...
                }
            }
            else if (state == 1)            // State 1: Top and left bars growing
            {
                StopMusicStream(music[0]);
                topSideRecWidth += 4;
                leftSideRecHeight += 4;
                if (topSideRecWidth == 256) state = 2;
            }
            else if (state == 2)            // State 2: Bottom and right bars growing
            {
                StopMusicStream(music[0]);
                bottomSideRecWidth += 4;
                rightSideRecHeight += 4;
                if (bottomSideRecWidth == 256) state = 3;
            }
            else if (state == 3)            // State 3: Letters appearing (one by one)
            {
                StopMusicStream(music[0]);
                framesCounter++;
                if (framesCounter/12)       // Every 12 frames, one more letter!
                {
                    lettersCount++;
                    framesCounter = 0;
                }
                if (lettersCount >= 10)     // When all letters have appeared, just fade out everything
                {
                    alpha -= 0.02f;
                    if (alpha <= 0.0f)
                    {
                        alpha = 0.0f;
                        state = 4;
                    }
                }
            }
            else if (state == 4)            // State 4: Reset and Replay
            {
                PlayMusicStream(music[0]);
                if (IsKeyDown(KEY_G)) {
                    gameState = 1;
                    player.hp = 100;
                    theMap = randoms(0, 4);
                    enemyValue = randoms(1, 9);
                }
            }
            break;
        case 1:
            StopMusicStream(music[0]);
            PlayMusicStream(music[1]);
            player.state = 0;
            framesCounter++;

            if(currentEnemy < enemyValue && framesCounter%7 == 0){
                enemy[currentEnemy].type = randoms(1, 5);
                enemy[currentEnemy].hp = 50;
                enemy[currentEnemy].attack = 1;
                enemy[currentEnemy].speed = 4;
                enemy[currentEnemy].atkDelay = 0.5;
                enemy[currentEnemy].texture = 0;
                enemy[currentEnemy].frame = 0;
                enemy[currentEnemy].state = 1;
                enemy[currentEnemy].action = 0;
                enemy[currentEnemy].hitPlayer = false;
                enemy[currentEnemy].hitWall = false;

                enemyBox[currentEnemy].x = 150 + currentEnemy*150;
                enemyBox[currentEnemy].y = 150;
                enemyBox[currentEnemy].width = 50;
                enemyBox[currentEnemy].height = 50;

                enemyFrame[currentEnemy].x = 0;
                enemyFrame[currentEnemy].y = 0;
                enemyFrame[currentEnemy].width = 50;
                enemyFrame[currentEnemy].height = 50;
                currentEnemy ++;
            }

            // Update
            //----------------------------------------------------------------------------------
            for(int i = 0; i < currentEnemy; i++){
                enemy[i].hitPlayer = CheckCollisionRecs(playerBox, enemyBox[i]);
                if(!enemy[i].hitPlayer){
                    float distanceX = abs(enemyBox[i].x - playerBox.x);
                    float distanceY = abs(enemyBox[i].y - playerBox.y);
                    if((distanceX <= distanceY && distanceX != 0) || distanceY == 0){
                        if(enemyBox[i].x < playerBox.x){
                            enemy[i].texture = 0;
                            enemyBox[i].x += enemy[i].speed;
                        } else if(enemyBox[i].x > playerBox.x){
                            enemy[i].texture = 1;
                            enemyBox[i].x -= enemy[i].speed;
                        }
                        if(distanceX < enemy[i].speed) enemyBox[i].x = playerBox.x;
                    } else {
                        if(enemyBox[i].y < playerBox.y){
                            enemy[i].texture = 2;
                            enemyBox[i].y += enemy[i].speed;
                        }
                        else if(enemyBox[i].y > playerBox.y){
                            enemy[i].texture = 3;
                            enemyBox[i].y -= enemy[i].speed;
                        }
                        if(distanceY < enemy[i].speed) enemyBox[i].y = playerBox.y;
                    }
                }

                switch(enemy[i].type){
                    case 2:
                        if(enemy[i].texture == 0) enemy[i].texture = 4;
                        else if(enemy[i].texture == 1) enemy[i].texture = 5;
                        else if(enemy[i].texture == 2) enemy[i].texture = 6;
                        else if(enemy[i].texture == 3) enemy[i].texture = 7;
                        break;
                    case 3:
                        if(enemy[i].texture == 0) enemy[i].texture = 8;
                        else if(enemy[i].texture == 1) enemy[i].texture = 9;
                        else if(enemy[i].texture == 2) enemy[i].texture = 10;
                        else if(enemy[i].texture == 3) enemy[i].texture = 11;
                        break;
                    case 4:
                        if(enemy[i].texture == 0) enemy[i].texture = 12;
                        else if(enemy[i].texture == 1) enemy[i].texture = 13;
                        else if(enemy[i].texture == 2) enemy[i].texture = 14;
                        else if(enemy[i].texture == 3) enemy[i].texture = 15;
                        break;
                        break;
                    case 5:
                        if(enemy[i].texture == 0) enemy[i].texture = 16;
                        else if(enemy[i].texture == 1) enemy[i].texture = 17;
                        else if(enemy[i].texture == 2) enemy[i].texture = 18;
                        else if(enemy[i].texture == 3) enemy[i].texture = 19;
                        break;
                        break;
                    default:
                        break;
                }

                if (enemy[i].hitPlayer && framesCounter%7 == 0 && enemy[i].state > -1){
                    player.hp -= enemy[i].attack;
                    playerHp.width = player.hp * 165/player.maxHp;
                }
            }

            if(player.hp <= 0) {
                player.hp = 0;
                player.state = -1;
                gameState = 2;
            } else {
                if (IsKeyDown(KEY_RIGHT)) {
                    playerBox.x += player.speed;
                    player.texture = 0;
                    player.state = 1;
                    if(playerBox.x >= screenWidth - 100)
                        playerBox.x = screenWidth - 100;

                    playerAttackBox.x = playerBox.x + 25;
                    playerAttackBox.y = playerBox.y;
                }
                if (IsKeyDown(KEY_LEFT)) {
                    playerBox.x -= player.speed;
                    player.texture = 1;
                    player.state = 1;
                    if(playerBox.x <= 50)
                        playerBox.x = 50;

                    playerAttackBox.x = playerBox.x - 25;
                    playerAttackBox.y = playerBox.y;
                }
                if (IsKeyDown(KEY_UP)) {
                    playerBox.y -= player.speed;
                    player.texture = 3;
                    player.state = 1;
                    if(playerBox.y <= 50)
                        playerBox.y = 50;

                    playerAttackBox.x = playerBox.x;
                    playerAttackBox.y = playerBox.y - 25;
                }
                if (IsKeyDown(KEY_DOWN)) {
                    playerBox.y += player.speed;
                    player.texture = 2;
                    player.state = 1;
                    if(playerBox.y >= screenHeight - 100)
                        playerBox.y = screenHeight - 100;

                    playerAttackBox.x = playerBox.x;
                    playerAttackBox.y = playerBox.y + 25;
                }

                if (IsKeyPressed(KEY_SPACE) && player.stamina >= 5) {
                    PlaySound(soundFx[0]);
                    player.action = 1;
                    player.stamina  -= 5;
                    for(int i = 0; i < currentEnemy; i++){
                        if(CheckCollisionRecs(playerAttackBox, enemyBox[i])){
                            enemy[i].hp -= player.attack;
                            if(enemy[i].hp <= 0){
                                enemy[i].hp = 0;
                                enemy[i].state = -1;
                            }
                        }
                    }
                }
            }

            for (int i = 0; i < currentEnemy; ++i)
            {
                if (killEnemyValue == enemyValue) {
                    gameState = 3;
                    item1 = randoms(0, 9);
                    item2 = randoms(0, 9);
                    item3 = randoms(0, 9);
                }
                if (enemy[i].state == -1) {
                    killEnemyValue += 1;
                }

            }
            if (killEnemyValue != enemyValue) {
                killEnemyValue = 0;
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

                for(int i = 0; i < currentEnemy; i++){
                    enemy[i].frame ++;
                    if (enemy[i].frame > 2) enemy[i].frame = 0;
                    enemyFrame[i].x = (float)enemy[i].frame*(float)enemyTexture[enemy[i].texture].width/3;
                }

            }
            playerStamina.width = player.stamina * 165/player.maxStamina;
            break;
        case 2:
            StopMusicStream(music[1]);
            PlayMusicStream(music[3]);
            // delay(5);
            if ((int)(GetMusicTimePlayed(music[3])/GetMusicTimeLength(music[3])*100) == 99) {
                gameState = 0;
            }
            break;
        case 3:
            StopMusicStream(music[0]);
            if (IsKeyDown(KEY_N)) {
                gameState = 1;
                theMap = randoms(0, 4);
                enemyValue = randoms(1, 9);
                currentEnemy = 0;
            }
            // if (IsKeyDown(KEY_Q)) {
            //     switch ()
            //     {
            //         case 1:
            //             break;
            //         case 1:
            //             break;
            //         case 1:
            //             break;
            //         case 1:
            //             break;
            //         case 1:
            //             break;
            //         case 1:
            //             break;
            //         case 1:
            //             break;
            //         case 1:
            //             break;
            //         case 1:
            //             break;
            //         case 1:
            //             break;
            //     }
            // }
            // if (IsKeyDown(KEY_W)) {
            //     case 1:
            //             break;
            //         case 1:
            //             break;
            //         case 1:
            //             break;
            //         case 1:
            //             break;
            //         case 1:
            //             break;
            //         case 1:
            //             break;
            //         case 1:
            //             break;
            //         case 1:
            //             break;
            //         case 1:
            //             break;
            //         case 1:
            //             break;
            // }
            // if (IsKeyDown(KEY_E)) {
            //     case 1:
            //             break;
            //         case 1:
            //             break;
            //         case 1:
            //             break;
            //         case 1:
            //             break;
            //         case 1:
            //             break;
            //         case 1:
            //             break;
            //         case 1:
            //             break;
            //         case 1:
            //             break;
            //         case 1:
            //             break;
            //         case 1:
            //             break;
            // }
            // break;
        }

        //----------------------------------------------------------------------------------

        // Draw------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            switch (gameState)
            {
            case 0:
                ClearBackground(RAYWHITE);
                if (state == 0)
                {
                    if ((framesCounter/15)%2) DrawRectangle(logoPositionX, logoPositionY, 16, 16, BLACK);
                }
                else if (state == 1)
                {
                    DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, BLACK);
                    DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, BLACK);
                }
                else if (state == 2)
                {
                    DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, BLACK);
                    DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, BLACK);

                    DrawRectangle(logoPositionX + 240, logoPositionY, 16, rightSideRecHeight, BLACK);
                    DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, BLACK);
                }
                else if (state == 3)
                {
                    DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, Fade(BLACK, alpha));
                    DrawRectangle(logoPositionX, logoPositionY + 16, 16, leftSideRecHeight - 32, Fade(BLACK, alpha));

                    DrawRectangle(logoPositionX + 240, logoPositionY + 16, 16, rightSideRecHeight - 32, Fade(BLACK, alpha));
                    DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, Fade(BLACK, alpha));

                    DrawRectangle(screenWidth/2 - 112, screenHeight/2 - 112, 224, 224, Fade(RAYWHITE, alpha));

                    DrawText(SubText("raylib", 0, lettersCount), screenWidth/2 - 44, screenHeight/2 + 48, 50, Fade(BLACK, alpha));
                }
                else if (state == 4)
                {
                    DrawTexture(titleTexture[0], 0, 0, WHITE);
                }
                break;
            case 1:
                DrawTexture(mapTexture[theMap], 0, 0, WHITE);

                switch(player.state){
                    case 1:
                        DrawTexturePro(playerTexture[player.texture], playerFrame, playerBox, origin, 0.0, WHITE);
                        break;
                    default:
                        DrawTexturePro(playerTexture[player.texture], playerFrameStop, playerBox, origin, 0.0, WHITE);
                }

                for(int i = 0; i < currentEnemy; i++){
                    switch(enemy[i].state){
                        case 1:
                            DrawTexturePro(enemyTexture[enemy[i].texture], enemyFrame[i], enemyBox[i], origin, 0.0, WHITE);
                            DrawText(FormatText("%d", enemy[i].hp), enemyBox[i].x, enemyBox[i].y - 22, 20, GRAY);
                            break;
                        default:
                            break;
                    }
                }

                switch(player.action){
                    case 0:
                        break;
                    default:
                        DrawTexturePro(attackTexture[player.texture], playerAttackFrame, playerAttackBox, origin, 0.0, WHITE);
                }
                DrawText(FormatText("%i", enemyValue), 0, 0, 50, GREEN);
                DrawText(FormatText("%i", currentEnemy), 0, 60, 50, GREEN);
                DrawText(FormatText("%i", killEnemyValue), 0, 120, 50, GREEN);

                DrawTexture(titleTexture[15], 0, 80, WHITE);
                DrawRectangleRec(playerHp, GREEN);
                DrawRectangleRec(playerStamina, BLUE);
                DrawTexture(titleTexture[9], 265, 661, WHITE);
                DrawTexture(titleTexture[10], 428, 661, WHITE);
                DrawTexture(titleTexture[11], 591, 661, WHITE);
                DrawTexture(titleTexture[12], 754, 661, WHITE);
                DrawTexture(titleTexture[13], 917, 661, WHITE);
                DrawTexture(titleTexture[14], 1080, 661, WHITE);
                DrawText(FormatText("X %i", randoms(1, 99)), 337, 674, 28, GREEN);
                DrawText(FormatText("X %i", randoms(1, 99)), 500, 674, 28, GREEN);
                DrawText(FormatText("X %i", randoms(1, 99)), 663, 674, 28, GREEN);
                DrawText(FormatText("X %i", randoms(1, 99)), 826, 674, 28, GREEN);
                DrawText(FormatText("X %i", randoms(1, 99)), 989, 674, 28, GREEN);
                DrawText(FormatText("X %i", randoms(1, 99)), 1152, 674, 28, GREEN);
                break;
            case 2:
                DrawTexture(titleTexture[1], 0, 0, WHITE);
                DrawText(FormatText("%i", (int)(GetMusicTimePlayed(music[3])/GetMusicTimeLength(music[3])*100)), 10, screenHeight - 40, 25, GREEN);
                break;
            case 3:
                DrawTexture(mapTexture[theMap], 0, 0, WHITE);
                DrawTexture(titleTexture[2], 54, 108, WHITE);

                DrawTexture(itemTexture[item1], 456, 108, WHITE);
                DrawTexture(itemTexture[item2], 729, 108, WHITE);
                DrawTexture(itemTexture[item3], 1002, 108, WHITE);

                DrawTexture(titleTexture[5], 456, 442, WHITE);
                DrawTexture(titleTexture[6], 729, 442, WHITE);
                DrawTexture(titleTexture[7], 1002, 442, WHITE);

                DrawTexture(titleTexture[3], 456, 560, WHITE);
                DrawTexture(titleTexture[4], 729, 560, WHITE);
                DrawTexture(titleTexture[8], 1002, 560, WHITE);

                DrawText(FormatText("HP :"),   90, 348, 28, GREEN);
                DrawText(FormatText("SP :"),   90, 380, 28, GREEN);
                DrawText(FormatText("Potion"),   90, 412, 28, GREEN);
                DrawText(FormatText("Staminai"),   90, 444, 28, GREEN);
                DrawText(FormatText("Movement"),   90, 476, 28, GREEN);
                DrawText(FormatText("Immortality"),   90, 508, 28, GREEN);
                DrawText(FormatText("Grant Revive"),   90, 540, 28, GREEN);
                DrawText(FormatText("Extra Health"),   90, 572, 28, GREEN);

                DrawText(FormatText("%i", randoms(0, 99)),   298, 348, 28, GREEN);
                DrawText(FormatText("%i", randoms(0, 99)),   298, 380, 28, GREEN);
                DrawText(FormatText("%i", randoms(0, 99)),   298, 412, 28, GREEN);
                DrawText(FormatText("%i", randoms(0, 99)),   298, 444, 28, GREEN);
                DrawText(FormatText("%i", randoms(0, 99)),   298, 476, 28, GREEN);
                DrawText(FormatText("%i", randoms(0, 99)),   298, 508, 28, GREEN);
                DrawText(FormatText("%i", randoms(0, 99)),   298, 540, 28, GREEN);
                DrawText(FormatText("%i", randoms(0, 99)),   298, 572, 28, GREEN);
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
    for(int i = 0; i < enemyTextureValue; i++)
    {
        UnloadTexture(enemyTexture[i]);
    }
    for (int i = 0; i < titleTextureValue; i++)
    {
        UnloadTexture(titleTexture[i]);
    }
    for (int i = 0; i < musicValue; i++)
    {
        UnloadMusicStream(music[i]);
    }
    for (int i = 0; i < soundFxValue; i++)
    {
        UnloadSound(soundFx[i]);
    }
    for (int i = 0; i < itemTextureValue; ++i)
    {
        UnloadTexture(itemTexture[i]);
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
