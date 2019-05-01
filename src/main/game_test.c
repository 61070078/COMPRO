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
    int titleTextureValue = 17;
    int itemTextureValue = 10;

    int enemyValue = 0;
    int currentEnemy = 0;
    int killEnemyValue = 0;
    int enemyRemaining = 0;

    int item1 = 0;
    int item2 = 0;
    int item3 = 0;

    int screenWidth = 1280;
    int screenHeight = 720;
    int currentPlayerFrame = 0;
    int currentAttackFrame = 0;
    int framesCounter = 0;
    int timeCounter = 0;
    int framesSpeed = 8;
    int gameState = 0;
    int theMap = 0;
    //----------------------------------------------------------------------------------

    // Set Window----------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "Lost Fantasy");
    InitAudioDevice();
    SetTargetFPS(60);
    //----------------------------------------------------------------------------------


    // Loading Texture And Audio--------------------------------------------------------
    Texture2D playerTexture[playerTextureValue];
    playerTexture[0] = LoadTexture("../IMG/Player/walk_R.png");
    playerTexture[1] = LoadTexture("../IMG/Player/walk_L.png");
    playerTexture[2] = LoadTexture("../IMG/Player/walk_F.png");
    playerTexture[3] = LoadTexture("../IMG/Player/walk_B.png");

    Texture2D attackTexture[4];
    attackTexture[0] = LoadTexture("../IMG/PLayer/HIT/hit_R.png");
    attackTexture[1] = LoadTexture("../IMG/PLayer/HIT/hit_L.png");
    attackTexture[2] = LoadTexture("../IMG/PLayer/HIT/hit_F.png");
    attackTexture[3] = LoadTexture("../IMG/PLayer/HIT/hit_B.png");

    Texture2D enemyTexture[enemyTextureValue];
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

    Texture2D enemyAttackTexture[20];
    enemyAttackTexture[0] = LoadTexture("../IMG/Enemy/EM_1/WP/hit_4.png");
    enemyAttackTexture[1] = LoadTexture("../IMG/Enemy/EM_1/WP/hit_4.png");
    enemyAttackTexture[2] = LoadTexture("../IMG/Enemy/EM_1/WP/hit_4.png");
    enemyAttackTexture[3] = LoadTexture("../IMG/Enemy/EM_1/WP/hit_4.png");

    enemyAttackTexture[4] = LoadTexture("../IMG/Enemy/EM_2/WP/hit_R.png");
    enemyAttackTexture[5] = LoadTexture("../IMG/Enemy/EM_2/WP/hit_L.png");
    enemyAttackTexture[6] = LoadTexture("../IMG/Enemy/EM_2/WP/hit_F.png");
    enemyAttackTexture[7] = LoadTexture("../IMG/Enemy/EM_2/WP/hit_B.png");

    enemyAttackTexture[8] = LoadTexture("../IMG/Enemy/EM_3/WP/hit_3.png");
    enemyAttackTexture[9] = LoadTexture("../IMG/Enemy/EM_3/WP/hit_3.png");
    enemyAttackTexture[10] = LoadTexture("../IMG/Enemy/EM_3/WP/hit_3.png");
    enemyAttackTexture[11] = LoadTexture("../IMG/Enemy/EM_3/WP/hit_3.png");

    enemyAttackTexture[12] = LoadTexture("../IMG/Enemy/EM_4/WP/hit_4.png");
    enemyAttackTexture[13] = LoadTexture("../IMG/Enemy/EM_4/WP/hit_4.png");
    enemyAttackTexture[14] = LoadTexture("../IMG/Enemy/EM_4/WP/hit_4.png");
    enemyAttackTexture[15] = LoadTexture("../IMG/Enemy/EM_4/WP/hit_4.png");

    enemyAttackTexture[16] = LoadTexture("../IMG/Enemy/EM_5/WP/hit_R.png");
    enemyAttackTexture[17] = LoadTexture("../IMG/Enemy/EM_5/WP/hit_L.png");
    enemyAttackTexture[18] = LoadTexture("../IMG/Enemy/EM_5/WP/hit_F.png");
    enemyAttackTexture[19] = LoadTexture("../IMG/Enemy/EM_5/WP/hit_B.png");

    Texture2D mapTexture[mapTextureValue];
    mapTexture[0] = LoadTexture("../IMG/Maps/Map_1.png");
    mapTexture[1] = LoadTexture("../IMG/Maps/Map_2.png");
    mapTexture[2] = LoadTexture("../IMG/Maps/Map_3.png");
    mapTexture[3] = LoadTexture("../IMG/Maps/Map_4.png");
    mapTexture[4] = LoadTexture("../IMG/Maps/Map_5.png");

    Texture2D titleTexture[titleTextureValue];
    titleTexture[0] = LoadTexture("../IMG/Title/manu.png");
    titleTexture[1] = LoadTexture("../IMG/Title/gameOver.png");
    titleTexture[2] = LoadTexture("../IMG/Face/face_T.png");
    titleTexture[3] = LoadTexture("../IMG/items/text_F.png");
    titleTexture[4] = LoadTexture("../IMG/items/text_U.png");
    titleTexture[5] = LoadTexture("../IMG/items/text_Q.png");
    titleTexture[6] = LoadTexture("../IMG/items/text_W.png");
    titleTexture[7] = LoadTexture("../IMG/items/text_E.png");
    titleTexture[8] = LoadTexture("../IMG/items/text_N.png");
    titleTexture[9] = LoadTexture("../IMG/Title/Bar/bar_item_1.png");
    titleTexture[10] = LoadTexture("../IMG/Title/Bar/bar_item_2.png");
    titleTexture[11] = LoadTexture("../IMG/Title/Bar/bar_item_3.png");
    titleTexture[12] = LoadTexture("../IMG/Title/Bar/bar_item_4.png");
    titleTexture[13] = LoadTexture("../IMG/Title/Bar/bar_item_5.png");
    titleTexture[14] = LoadTexture("../IMG/Title/Bar/bar_item_6.png");
    titleTexture[15] = LoadTexture("../IMG/Title/Bar/bar.png");
    titleTexture[16] = LoadTexture("../IMG/Title/Bar/B_A.png");

    Music music[musicValue];
    music[0] = LoadMusicStream("../Audio/Manu/Theme1.ogg");
    music[1] = LoadMusicStream("../Audio/Battle/Battle.ogg");
    music[2] = LoadMusicStream("../Audio/Attack/Attack.ogg");
    music[3] = LoadMusicStream("../Audio/GameOver/Gameover.ogg");

    Sound soundFx[soundFxValue];
    soundFx[0] = LoadSound("../Audio/Attack/Attack.ogg");

    Texture2D itemTexture[itemTextureValue];
    itemTexture[0] = LoadTexture("../IMG/items/atkUp_T.png");
    itemTexture[1] = LoadTexture("../IMG/items/defUp_T.png");
    itemTexture[2] = LoadTexture("../IMG/items/extraArmor_T.png");
    itemTexture[3] = LoadTexture("../IMG/items/immortal_T.png");
    itemTexture[4] = LoadTexture("../IMG/items/maxPotion_T.png");
    itemTexture[5] = LoadTexture("../IMG/items/maxStamina_T.png");
    itemTexture[6] = LoadTexture("../IMG/items/potion_T.png");
    itemTexture[7] = LoadTexture("../IMG/items/revive_T.png");
    itemTexture[8] = LoadTexture("../IMG/items/speedUp_T.png");
    itemTexture[9] = LoadTexture("../IMG/items/stamina_T.png");
    //----------------------------------------------------------------------------------

    // Struct --------------------------------------------------------------------------
    struct Character {
        int maxHp;
        int hp;
        int attack;
        float speed;
        int maxStamina;
        int stamina;
        int staminaRecove;
        int texture;
        int state;
        int action;
        bool hitWall;
        int defend;
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
        int atkFrame;
        Vector2 center; // for long range enemy
        Vector2 target; // for long range enemy
    };

    struct Inventory
    {
        int useStatus;
        int timeCounter;
        int itemValue;
        int timeValue;
        float effectValue;
    };

    struct System
    {
        int level;
        int killEnemy;
        float damageDone;
    };

    struct System game = {1, 0, 0};

    struct Inventory item[6];

    item[0].useStatus = 0; //Potion
    item[0].timeCounter = 0;
    item[0].itemValue = 100;
    item[0].timeValue = 0;

    item[1].useStatus = 0; //Stamina
    item[1].timeCounter = 0;
    item[1].itemValue = 100;
    item[1].timeValue = 0;

    item[2].useStatus = 0; //Immortality Time
    item[2].timeCounter = 0;
    item[2].itemValue = 100;
    item[2].timeValue = 5;

    item[3].useStatus = 0; //Movement Speed Up
    item[3].timeCounter = 0;
    item[3].itemValue = 100;
    item[3].timeValue = 3;

    item[4].useStatus = 0; //Extra Health
    item[4].timeCounter = 0;
    item[4].itemValue = 100;
    item[4].timeValue = 0;
    item[4].effectValue = 0;

    item[5].useStatus = 0; //Grant Revive
    item[5].timeCounter = 0;
    item[5].itemValue = 100;
    item[5].timeValue = 0;

    struct Character player = {100, 100, 10, 6, 50, 50, 1, 0, 0, 0, false, 0};

    struct Enemy monster[5];

    monster[0].type = 0;
    monster[0].hp = 50;
    monster[0].attack = 0;
    monster[0].speed = 6;
    monster[0].atkDelay = 0;
    monster[0].texture = 0;
    monster[0].frame = 0;
    monster[0].state = 1;
    monster[0].action = 0;
    monster[0].hitPlayer = false;
    monster[0].hitWall = false;
    monster[0].atkFrame = 0;

    monster[1].type = 1;
    monster[1].hp = 80;
    monster[1].attack = 1; //1
    monster[1].speed = 4;
    monster[1].atkDelay = 50;
    monster[1].texture = 0;
    monster[1].frame = 0;
    monster[1].state = 1;
    monster[1].action = 0;
    monster[1].hitPlayer = false;
    monster[1].hitWall = false;
    monster[1].atkFrame = 0;

    monster[2].type = 2;
    monster[2].hp = 30;
    monster[2].attack = 2; //2
    monster[2].speed = 5;
    monster[2].atkDelay = 75;
    monster[2].texture = 0;
    monster[2].frame = 0;
    monster[2].state = 1;
    monster[2].action = 0;
    monster[2].hitPlayer = false;
    monster[2].hitWall = false;
    monster[2].atkFrame = 0;

    monster[3].type = 3;
    monster[3].hp = 30;
    monster[3].attack = 3; //3
    monster[3].speed = 3;
    monster[3].atkDelay = 100;
    monster[3].texture = 0;
    monster[3].frame = 0;
    monster[3].state = 1;
    monster[3].action = 0;
    monster[3].hitPlayer = false;
    monster[3].hitWall = false;
    monster[3].atkFrame = 0;

    monster[4].type = 4;
    monster[4].hp = 40;
    monster[4].attack = 2; //2
    monster[4].speed = 5.5;
    monster[4].atkDelay = 60;
    monster[4].texture = 0;
    monster[4].frame = 0;
    monster[4].state = 1;
    monster[4].action = 0;
    monster[4].hitPlayer = false;
    monster[4].hitWall = false;
    monster[4].atkFrame = 0;

    struct Enemy enemy[20];

    //----------------------------------------------------------------------------------

    // Rectangle------------------------------------------------------------------------
    Rectangle playerFrame = { 0.0f, 0.0f, (float)playerTexture[player.texture].width/3, (float)playerTexture[player.texture].height };
    Rectangle playerFrameStop = { 0.0f, 0.0f, (float)playerTexture[player.texture].width/3, (float)playerTexture[player.texture].height };
    Rectangle playerBox = { (float)screenWidth/2, (float)screenHeight/2, 50.0, 50.0 };
    Rectangle playerAttackBox = { playerBox.x + 25, playerBox.y, 50.0, 50.0 };
    Rectangle playerAttackFrame = { 0.0f, 0.0f, 50.0, 50.0};
    Rectangle playerStamina =  {45, 644, 165.0, 20};
    Rectangle playerHp =  {45, 686, 165.0, 20};
    Rectangle armorHp =  {45, 686, 0, 20};

    Rectangle enemyAttackBox[20];
    Rectangle enemyAttackFrame[20];
    
    Rectangle mapBox[24];
    mapBox[0].x = 69; //--------- 1
    mapBox[0].y = 357;
    mapBox[0].width = 153;
    mapBox[0].height = 154;

    mapBox[1].x = 222;
    mapBox[1].y = 511;
    mapBox[1].width = 164;
    mapBox[1].height = 142;

    mapBox[2].x = 893;
    mapBox[2].y = 60;
    mapBox[2].width = 165;
    mapBox[2].height = 152;

    mapBox[3].x = 1058;
    mapBox[3].y = 212;
    mapBox[3].width = 150;
    mapBox[3].height = 158; //---------

    mapBox[4].x = 203; //--------- 2
    mapBox[4].y = 200;
    mapBox[4].width = 380;
    mapBox[4].height = 76;

    mapBox[5].x = 695;
    mapBox[5].y = 200;
    mapBox[5].width = 380;
    mapBox[5].height = 76;

    mapBox[6].x = 203;
    mapBox[6].y = 450;
    mapBox[6].width = 380;
    mapBox[6].height = 76;

    mapBox[7].x = 695;
    mapBox[7].y = 450;
    mapBox[7].width = 380;
    mapBox[7].height = 76; //---------

    mapBox[8].x = 74; //--------- 3
    mapBox[8].y = 194;
    mapBox[8].width = 474;
    mapBox[8].height = 141;

    mapBox[9].x = 407;
    mapBox[9].y = 338;
    mapBox[9].width = 141;
    mapBox[9].height = 156;

    mapBox[10].x = 731;
    mapBox[10].y = 198;
    mapBox[10].width = 141;
    mapBox[10].height = 156;

    mapBox[11].x = 731;
    mapBox[11].y = 354;
    mapBox[11].width = 474;
    mapBox[11].height = 141; //---------

    mapBox[12].x = 238; //--------- 4
    mapBox[12].y = 228;
    mapBox[12].width = 146;
    mapBox[12].height = 265;

    mapBox[13].x = 535;
    mapBox[13].y = 71;
    mapBox[13].width = 209;
    mapBox[13].height = 141;

    mapBox[14].x = 895;
    mapBox[14].y = 228;
    mapBox[14].width = 146;
    mapBox[14].height = 265;

    mapBox[15].x = 535;
    mapBox[15].y = 510;
    mapBox[15].width = 209;
    mapBox[15].height = 141; //---------

    mapBox[16].x = 77; //--------- 5
    mapBox[16].y = 75;
    mapBox[16].width = 1128;
    mapBox[16].height = 75;

    mapBox[17].x = 533;
    mapBox[17].y = 150;
    mapBox[17].width = 213;
    mapBox[17].height = 124;

    mapBox[18].x = 533;
    mapBox[18].y = 450;
    mapBox[18].width = 213;
    mapBox[18].height = 124;

    mapBox[19].x = 77;
    mapBox[19].y = 574;
    mapBox[19].width = 1128;
    mapBox[19].height = 75; //---------


    Rectangle enemyBox[20];

    Rectangle enemyFrame[20];
    //----------------------------------------------------------------------------------

    // Vector2--------------------------------------------------------------------------
    Vector2 origin = {0, 0};
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
            if (IsKeyDown(KEY_ENTER)) {
                gameState = 1;
                player.hp = 100;
                theMap = randoms(0, 4);
                enemyValue = 3;
            }
            break;
        case 1:
            StopMusicStream(music[0]);
            PlayMusicStream(music[1]);
            player.state = 0;
            framesCounter++;
            timeCounter++;



            if(currentEnemy < enemyValue && framesCounter%7 == 0){
                enemy[currentEnemy].type = randoms(0, 4);
                enemy[currentEnemy].hp = monster[enemy[currentEnemy].type].hp + 5 * game.level + 5*(game.level%5 == 0)*game.level;
                enemy[currentEnemy].attack = monster[enemy[currentEnemy].type].attack + 1 * game.level/5;
                enemy[currentEnemy].speed = monster[enemy[currentEnemy].type].speed;
                enemy[currentEnemy].atkDelay = 0;
                enemy[currentEnemy].texture = monster[enemy[currentEnemy].type].texture;
                enemy[currentEnemy].frame = monster[enemy[currentEnemy].type].frame;
                enemy[currentEnemy].state = monster[enemy[currentEnemy].type].state;
                enemy[currentEnemy].action = monster[enemy[currentEnemy].type].action;
                enemy[currentEnemy].hitPlayer = false;
                enemy[currentEnemy].hitWall = true;
                enemy[currentEnemy].atkFrame = monster[enemy[currentEnemy].type].atkFrame;

                enemyBox[currentEnemy].width = 50;
                enemyBox[currentEnemy].height = 50;

                while(enemy[currentEnemy].hitWall){
                    enemyBox[currentEnemy].x = randoms(60, 1170);
                    enemyBox[currentEnemy].y = randoms(60, 610);
                    switch (theMap) {
                        case 0:
                            for(int j = 0; j < 4; j ++){
                                enemy[currentEnemy].hitWall = CheckCollisionRecs(enemyBox[currentEnemy], mapBox[j]);
                                if(enemy[currentEnemy].hitWall) break;
                            }
                            break;
                        case 1:
                            for(int j = 4; j < 8; j ++){
                                enemy[currentEnemy].hitWall = CheckCollisionRecs(enemyBox[currentEnemy], mapBox[j]);
                                if(enemy[currentEnemy].hitWall) break;
                            }
                            break;
                        case 2:
                            for(int j = 8; j < 12; j ++){
                                enemy[currentEnemy].hitWall = CheckCollisionRecs(enemyBox[currentEnemy], mapBox[j]);
                                if(enemy[currentEnemy].hitWall) break;
                            }
                            break;
                        case 3:
                            for(int j = 12; j < 16; j ++){
                                enemy[currentEnemy].hitWall = CheckCollisionRecs(enemyBox[currentEnemy], mapBox[j]);
                                if(enemy[currentEnemy].hitWall) break;
                            }
                            break;
                        case 4:
                            for(int j = 16; j < 20; j ++){
                                enemy[currentEnemy].hitWall = CheckCollisionRecs(enemyBox[currentEnemy], mapBox[j]);
                                if(enemy[currentEnemy].hitWall) break;
                            }
                            break;
                    }
                }      

                enemyFrame[currentEnemy].x = 0;
                enemyFrame[currentEnemy].y = 0;
                enemyFrame[currentEnemy].width = 50;
                enemyFrame[currentEnemy].height = 50;

                enemy[currentEnemy].center.x = enemyBox[currentEnemy].x+25;
                enemy[currentEnemy].center.y = enemyBox[currentEnemy].y+25;

                enemy[currentEnemy].target.x = 0;
                enemy[currentEnemy].target.y = 0;

                enemyAttackBox[currentEnemy].x = enemyBox[currentEnemy].x+50;
                enemyAttackBox[currentEnemy].y = enemyBox[currentEnemy].y;
                enemyAttackBox[currentEnemy].width = 50;
                enemyAttackBox[currentEnemy].height = 50;

                enemyAttackFrame[currentEnemy].x = 0;
                enemyAttackFrame[currentEnemy].y = 0;
                enemyAttackFrame[currentEnemy].width = 50;
                enemyAttackFrame[currentEnemy].height = 50;

                currentEnemy ++;
            }

            // Update
            //----------------------------------------------------------------------------------
            for(int i = 0; i < currentEnemy; i++){
                switch(enemy[i].type){
                    case 2:
                        enemy[i].center.x = enemyBox[i].x+25;
                        enemy[i].center.y = enemyBox[i].y+25;
                        enemy[i].hitPlayer = CheckCollisionCircleRec(enemy[i].center,150.0, playerBox);
                        if(!enemy[i].hitPlayer && !enemy[i].hitWall){
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
                        } else {
                            float distanceX = abs(enemyBox[i].x - playerBox.x);
                            float distanceY = abs(enemyBox[i].y - playerBox.y);
                            if((distanceX <= distanceY) && distanceY != 0){
                                if(enemyBox[i].y < playerBox.y){
                                    enemy[i].texture = 2;
                                } else if(enemyBox[i].y > playerBox.y){
                                    enemy[i].texture = 3;
                                }
                            } else {
                                if(enemyBox[i].x < playerBox.x){
                                    enemy[i].texture = 0;
                                }
                                else if(enemyBox[i].x > playerBox.x){
                                    enemy[i].texture = 1;
                                }
                            }
                        }
                        break;
                    case 3:
                        enemy[i].center.x = enemyBox[i].x+25;
                        enemy[i].center.y = enemyBox[i].y+25;
                        enemy[i].hitPlayer = CheckCollisionCircleRec(enemy[i].center,350.0, playerBox);
                        if(!enemy[i].hitPlayer && !enemy[i].hitWall){
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
                        } else {
                            float distanceX = abs(enemyBox[i].x - playerBox.x);
                            float distanceY = abs(enemyBox[i].y - playerBox.y);
                            if((distanceX <= distanceY) && distanceY != 0){
                                if(enemyBox[i].y < playerBox.y){
                                    enemy[i].texture = 2;
                                } else if(enemyBox[i].y > playerBox.y){
                                    enemy[i].texture = 3;
                                }
                            } else {
                                if(enemyBox[i].x < playerBox.x){
                                    enemy[i].texture = 0;
                                }
                                else if(enemyBox[i].x > playerBox.x){
                                    enemy[i].texture = 1;
                                }
                            }
                        }
                        break;
                    default:
                        enemy[i].hitPlayer = CheckCollisionRecs(playerBox, enemyBox[i]);
                        if(!enemy[i].hitPlayer){
                            float distanceX = abs(enemyBox[i].x - playerBox.x);
                            float distanceY = abs(enemyBox[i].y - playerBox.y);
                            float temp_x = enemyBox[i].x;
                            float temp_y = enemyBox[i].y;
                            if((distanceX <= distanceY && distanceX != 0) || distanceY == 0){
                                if(enemyBox[i].x < playerBox.x){
                                    enemy[i].texture = 0;
                                    enemyBox[i].x += enemy[i].speed;
                                } else if(enemyBox[i].x > playerBox.x){
                                    enemy[i].texture = 1;
                                    enemyBox[i].x -= enemy[i].speed;
                                }
                                if(distanceX < enemy[i].speed) enemyBox[i].x = playerBox.x;
                                switch (theMap) {
                                    case 0:
                                        for(int j = 0; j < 4; j ++){
                                            enemy[i].hitWall = CheckCollisionRecs(enemyBox[i], mapBox[j]);
                                            if(enemy[i].hitWall) break;
                                        }
                                        break;
                                    case 1:
                                        for(int j = 4; j < 8; j ++){
                                            enemy[i].hitWall = CheckCollisionRecs(enemyBox[i], mapBox[j]);
                                            if(enemy[i].hitWall) break;
                                        }
                                        break;
                                    case 2:
                                        for(int j = 8; j < 12; j ++){
                                            enemy[i].hitWall = CheckCollisionRecs(enemyBox[i], mapBox[j]);
                                            if(enemy[i].hitWall) break;
                                        }
                                        break;
                                    case 3:
                                        for(int j = 12; j < 16; j ++){
                                            enemy[i].hitWall = CheckCollisionRecs(enemyBox[i], mapBox[j]);
                                            if(enemy[i].hitWall) break;
                                        }
                                        break;
                                    case 4:
                                        for(int j = 16; j < 20; j ++){
                                            enemy[i].hitWall = CheckCollisionRecs(enemyBox[i], mapBox[j]);
                                            if(enemy[i].hitWall) break;
                                        }
                                        break;
                                }
                                if(enemy[i].hitWall){
                                    enemyBox[i].x = temp_x;
                                    if(enemyBox[i].y < playerBox.y) enemyBox[i].y += enemy[i].speed/2;
                                    else if (enemyBox[i].y > playerBox.y) enemyBox[i].y -= enemy[i].speed/2;
                                }
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
                                switch (theMap) {
                                    case 0:
                                        for(int j = 0; j < 4; j ++){
                                            enemy[i].hitWall = CheckCollisionRecs(enemyBox[i], mapBox[j]);
                                            if(enemy[i].hitWall) break;
                                        }
                                        break;
                                    case 1:
                                        for(int j = 4; j < 8; j ++){
                                            enemy[i].hitWall = CheckCollisionRecs(enemyBox[i], mapBox[j]);
                                            if(enemy[i].hitWall) break;
                                        }
                                        break;
                                    case 2:
                                        for(int j = 8; j < 12; j ++){
                                            enemy[i].hitWall = CheckCollisionRecs(enemyBox[i], mapBox[j]);
                                            if(enemy[i].hitWall) break;
                                        }
                                        break;
                                    case 3:
                                        for(int j = 12; j < 16; j ++){
                                            enemy[i].hitWall = CheckCollisionRecs(enemyBox[i], mapBox[j]);
                                            if(enemy[i].hitWall) break;
                                        }
                                        break;
                                    case 4:
                                        for(int j = 16; j < 20; j ++){
                                            enemy[i].hitWall = CheckCollisionRecs(enemyBox[i], mapBox[j]);
                                            if(enemy[i].hitWall) break;
                                        }
                                        break;
                                }
                                if(enemy[i].hitWall){
                                    enemyBox[i].y = temp_y;
                                    if(enemyBox[i].x < playerBox.x) enemyBox[i].x += enemy[i].speed/2;
                                    else if (enemyBox[i].x > playerBox.x) enemyBox[i].x -= enemy[i].speed/2;
                                }
                            }          
                        } 
                }

                switch(enemy[i].type){
                    case 1:
                        if(enemy[i].texture == 0) enemy[i].texture = 4;
                        else if(enemy[i].texture == 1) enemy[i].texture = 5;
                        else if(enemy[i].texture == 2) enemy[i].texture = 6;
                        else if(enemy[i].texture == 3) enemy[i].texture = 7;
                        break;
                    case 2:
                        if(enemy[i].texture == 0) enemy[i].texture = 8;
                        else if(enemy[i].texture == 1) enemy[i].texture = 9;
                        else if(enemy[i].texture == 2) enemy[i].texture = 10;
                        else if(enemy[i].texture == 3) enemy[i].texture = 11;
                        break;
                    case 3:
                        if(enemy[i].texture == 0) enemy[i].texture = 12;
                        else if(enemy[i].texture == 1) enemy[i].texture = 13;
                        else if(enemy[i].texture == 2) enemy[i].texture = 14;
                        else if(enemy[i].texture == 3) enemy[i].texture = 15;
                        break;
                    case 4:
                        if(enemy[i].texture == 0) enemy[i].texture = 16;
                        else if(enemy[i].texture == 1) enemy[i].texture = 17;
                        else if(enemy[i].texture == 2) enemy[i].texture = 18;
                        else if(enemy[i].texture == 3) enemy[i].texture = 19;
                        break;
                        break;
                    default:
                        break;
                }

                if ((enemy[i].type != 2 && enemy[i].type != 3) || enemy[i].state == 1){
                     if(enemy[i].texture%4 == 0){
                        enemyAttackBox[i].x = enemyBox[i].x+50;
                        enemyAttackBox[i].y = enemyBox[i].y;   
                        } else if(enemy[i].texture%4 == 1) {
                        enemyAttackBox[i].x = enemyBox[i].x-50;
                        enemyAttackBox[i].y = enemyBox[i].y;     
                        } else if(enemy[i].texture%4 == 2) {
                        enemyAttackBox[i].x = enemyBox[i].x;
                        enemyAttackBox[i].y = enemyBox[i].y+50;     
                        } else if(enemy[i].texture%4 == 3) {
                        enemyAttackBox[i].x = enemyBox[i].x;
                        enemyAttackBox[i].y = enemyBox[i].y-50;     
                    }
                }
                

                if (enemy[i].state == 1 && enemy[i].hitPlayer && enemy[i].atkDelay == 0){
                    switch(enemy[i].type){
                        case 0:
                            enemy[i].state = -1;
                            enemy[i].action = 1;
                            player.hp -= enemy[i].hp*0.1;
                            playerHp.width = (player.hp * 165)/player.maxHp;
                            break;
                        case 2:
                        case 3:
                            enemy[i].atkDelay = monster[enemy[i].type].atkDelay;
                            enemy[i].state = 2;
                            enemy[i].action = 1;
                            enemy[i].target.x = playerBox.x;
                            enemy[i].target.y = playerBox.y;
                            break;
                        default:
                            enemy[i].state = 2;
                            enemy[i].action = 1;
                            if (enemy[i].attack > player.defend && CheckCollisionRecs(playerBox, enemyAttackBox[i])) {
                                if (item[4].effectValue > 0) {
                                    item[4].effectValue -= enemy[i].attack;
                                    armorHp.width = (item[4].effectValue/50)*80;
                                } else {
                                    player.hp -= enemy[i].attack - player.defend;
                                }
                            }
                            playerHp.width = (player.hp * 165)/player.maxHp;
                            enemy[i].atkDelay = monster[enemy[i].type].atkDelay;
                    }
                }

                //range attack
                switch(enemy[i].type){
                    case 2:
                        if(enemy[i].action > 0){
                            enemyAttackBox[i].x = enemy[i].target.x;
                            enemyAttackBox[i].y = enemy[i].target.y;
                            if (enemy[i].action > 6){
                                if (enemy[i].attack > player.defend && CheckCollisionRecs(playerBox, enemyAttackBox[i])) {
                                    enemy[i].state = 1;
                                    enemy[i].action = 0;
                                    if (item[4].effectValue > 0) {
                                        item[4].effectValue -= enemy[i].attack;
                                        armorHp.width = (item[4].effectValue/50)*80;
                                    } else {
                                        player.hp -= enemy[i].attack - player.defend;
                                    }
                                }
                                playerHp.width = (player.hp * 165)/player.maxHp;
                            }
                        }
                        break;
                    case 3:
                        if(enemy[i].action > 0){
                            if(abs(enemyAttackBox[i].x - enemy[i].target.x) < 2) enemyAttackBox[i].x = enemy[i].target.x;
                            else if(enemyAttackBox[i].x < enemy[i].target.x) enemyAttackBox[i].x += 2;
                            else if(enemyAttackBox[i].x > enemy[i].target.x) enemyAttackBox[i].x -= 2;

                            if(abs(enemyAttackBox[i].y - enemy[i].target.y) < 2) enemyAttackBox[i].y = enemy[i].target.y;
                            else if(enemyAttackBox[i].y < enemy[i].target.y) enemyAttackBox[i].y += 2;
                            else if(enemyAttackBox[i].y > enemy[i].target.y) enemyAttackBox[i].y -= 2;

                            if (CheckCollisionRecs(playerBox, enemyAttackBox[i])) {
                                enemy[i].state = 1;
                                enemy[i].action = 0;
                                if (item[4].effectValue > 0) {
                                    item[4].effectValue -= enemy[i].attack;
                                    armorHp.width = (item[4].effectValue/50)*80;
                                } else {
                                    player.hp -= enemy[i].attack - player.defend;
                                }
                            } else if (enemyAttackBox[i].x == enemy[i].target.x && enemyAttackBox[i].y == enemy[i].target.y){
                                enemy[i].state = 1;
                                enemy[i].action = 0;
                            }
                            playerHp.width = (player.hp * 165)/player.maxHp;
                        }

                        break;
                    default:
                        break;
                }

                if(enemy[i].action > 0){
                    enemy[i].action ++;
                    if(enemy[i].action % 2 == 0) enemy[i].atkFrame ++;
                    else if (enemy[i].action > 11 && enemy[i].type != 3 && enemy[i].type != 0){
                        enemy[i].action = 0;
                        enemy[i].state = 1;
                        enemy[i].atkFrame = 0;
                    } else if(enemy[i].action > 11 && enemy[i].type == 0){
                        enemy[i].action = 0;
                        enemy[i].state = -1;
                    }
                    
                    if (enemy[i].atkFrame > 4) enemy[i].atkFrame = 0;

                    enemyAttackFrame[i].x = (float)enemy[i].atkFrame*50;
                    enemyAttackFrame[i].y = 0;
                }
                if (enemy[i].atkDelay > 0) enemy[i].atkDelay --;

                // if (enemy[i].hitPlayer && framesCounter%7 == 0 && enemy[i].state > -1){
                //     if (enemy[i].attack > player.defend) {
                //         if (item[4].effectValue > 0) {
                //             item[4].effectValue -= enemy[i].attack;
                //             armorHp.width = (item[4].effectValue/50)*80;
                //         } else {
                //             player.hp -= enemy[i].attack - player.defend;
                //         }
                //     }
                //     playerHp.width = (player.hp * 165)/player.maxHp;
                // }
            }

            if(player.hp <= 0) {
                if (item[5].itemValue > 0) {
                    player.hp = 100;
                    item[5].itemValue -= 1;
                    playerHp.width = (player.hp * 165)/player.maxHp;
                } else {
                    player.hp = 0;
                    player.state = -1;
                    gameState = 2;
                    for (int i = 0; i < currentEnemy; ++i)
                    {
                        if (enemy[i].state == -1) {
                            game.killEnemy += 1;
                        }
                    }
                }
            } else {
                if(player.hp > player.maxHp) player.hp = player.maxHp;
                float playerTempX = playerBox.x;
                float playerTempY = playerBox.y;
                if (IsKeyDown(KEY_RIGHT)) {
                    playerBox.x += player.speed;
                    switch (theMap)
                    {
                        case 0:
                            for(int i = 0; i < 4; i ++){
                                player.hitWall = CheckCollisionRecs(playerBox, mapBox[i]);
                                if(player.hitWall) break;
                            }
                            break;
                        case 1:
                            for(int i = 4; i < 8; i ++){
                                player.hitWall = CheckCollisionRecs(playerBox, mapBox[i]);
                                if(player.hitWall) break;
                            }
                            break;
                        case 2:
                            for(int i = 8; i < 12; i ++){
                                player.hitWall = CheckCollisionRecs(playerBox, mapBox[i]);
                                if(player.hitWall) break;
                            }
                            break;
                        case 3:
                            for(int i = 12; i < 16; i ++){
                                player.hitWall = CheckCollisionRecs(playerBox, mapBox[i]);
                                if(player.hitWall) break;
                            }
                            break;
                        case 4:
                            for(int i = 16; i < 20; i ++){
                                player.hitWall = CheckCollisionRecs(playerBox, mapBox[i]);
                                if(player.hitWall) break;
                            }
                            break;
                    }
                    if(player.hitWall){
                        playerBox.x = playerTempX;
                        playerBox.y = playerTempY;
                    }
                    player.texture = 0;
                    player.state = 1;
                    if(playerBox.x >= screenWidth - 100)
                        playerBox.x = screenWidth - 100;

                    playerAttackBox.x = playerBox.x + 25;
                    playerAttackBox.y = playerBox.y;
                }
                if (IsKeyDown(KEY_LEFT)) {
                    playerBox.x -= player.speed;
                    switch (theMap)
                    {
                        case 0:
                            for(int i = 0; i < 4; i ++){
                                player.hitWall = CheckCollisionRecs(playerBox, mapBox[i]);
                                if(player.hitWall) break;
                            }
                            break;
                        case 1:
                            for(int i = 4; i < 8; i ++){
                                player.hitWall = CheckCollisionRecs(playerBox, mapBox[i]);
                                if(player.hitWall) break;
                            }
                            break;
                        case 2:
                            for(int i = 8; i < 12; i ++){
                                player.hitWall = CheckCollisionRecs(playerBox, mapBox[i]);
                                if(player.hitWall) break;
                            }
                            break;
                        case 3:
                            for(int i = 12; i < 16; i ++){
                                player.hitWall = CheckCollisionRecs(playerBox, mapBox[i]);
                                if(player.hitWall) break;
                            }
                            break;
                        case 4:
                            for(int i = 16; i < 20; i ++){
                                player.hitWall = CheckCollisionRecs(playerBox, mapBox[i]);
                                if(player.hitWall) break;
                            }
                            break;
                    }
                    if(player.hitWall){
                        playerBox.x = playerTempX;
                        playerBox.y = playerTempY;
                    }
                    player.texture = 1;
                    player.state = 1;
                    if(playerBox.x <= 50)
                        playerBox.x = 50;

                    playerAttackBox.x = playerBox.x - 25;
                    playerAttackBox.y = playerBox.y;
                }
                if (IsKeyDown(KEY_UP)) {
                    playerBox.y -= player.speed;
                    switch (theMap)
                    {
                        case 0:
                            for(int i = 0; i < 4; i ++){
                                player.hitWall = CheckCollisionRecs(playerBox, mapBox[i]);
                                if(player.hitWall) break;
                            }
                            break;
                        case 1:
                            for(int i = 4; i < 8; i ++){
                                player.hitWall = CheckCollisionRecs(playerBox, mapBox[i]);
                                if(player.hitWall) break;
                            }
                            break;
                        case 2:
                            for(int i = 8; i < 12; i ++){
                                player.hitWall = CheckCollisionRecs(playerBox, mapBox[i]);
                                if(player.hitWall) break;
                            }
                            break;
                        case 3:
                            for(int i = 12; i < 16; i ++){
                                player.hitWall = CheckCollisionRecs(playerBox, mapBox[i]);
                                if(player.hitWall) break;
                            }
                            break;
                        case 4:
                            for(int i = 16; i < 20; i ++){
                                player.hitWall = CheckCollisionRecs(playerBox, mapBox[i]);
                                if(player.hitWall) break;
                            }
                            break;
                    }
                    if(player.hitWall){
                        playerBox.x = playerTempX;
                        playerBox.y = playerTempY;
                    }
                    player.texture = 3;
                    player.state = 1;
                    if(playerBox.y <= 50)
                        playerBox.y = 50;

                    playerAttackBox.x = playerBox.x;
                    playerAttackBox.y = playerBox.y - 25;
                }
                if (IsKeyDown(KEY_DOWN)) {
                    playerBox.y += player.speed;
                    switch (theMap)
                    {
                        case 0:
                            for(int i = 0; i < 4; i ++){
                                player.hitWall = CheckCollisionRecs(playerBox, mapBox[i]);
                                if(player.hitWall) break;
                            }
                            break;
                        case 1:
                            for(int i = 4; i < 8; i ++){
                                player.hitWall = CheckCollisionRecs(playerBox, mapBox[i]);
                                if(player.hitWall) break;
                            }
                            break;
                        case 2:
                            for(int i = 8; i < 12; i ++){
                                player.hitWall = CheckCollisionRecs(playerBox, mapBox[i]);
                                if(player.hitWall) break;
                            }
                            break;
                        case 3:
                            for(int i = 12; i < 16; i ++){
                                player.hitWall = CheckCollisionRecs(playerBox, mapBox[i]);
                                if(player.hitWall) break;
                            }
                            break;
                        case 4:
                            for(int i = 16; i < 20; i ++){
                                player.hitWall = CheckCollisionRecs(playerBox, mapBox[i]);
                                if(player.hitWall) break;
                            }
                            break;
                    }
                    if(player.hitWall){
                        playerBox.x = playerTempX;
                        playerBox.y = playerTempY;
                    }
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
                            game.damageDone += player.attack;
                            if(enemy[i].hp <= 0){
                                enemy[i].hp = 0;
                                enemy[i].state = -1;
                            }
                        }
                    }
                }
                if (IsKeyPressed(KEY_A) && item[0].itemValue >= 1) {
                    item[0].itemValue -= 1;
                    for (int i = 0; i < 30; ++i)
                    {
                        if (player.hp < player.maxHp) {
                            player.hp += 1;
                        }
                        playerHp.width = (player.hp * 165)/player.maxHp;
                    }
                }
                if (IsKeyPressed(KEY_S) && item[1].itemValue >= 1) {
                    player.stamina += 20;
                    item[1].itemValue -= 1;
                    playerStamina.width = player.stamina * 165/player.maxStamina;
                }
                if (IsKeyPressed(KEY_D) && item[2].useStatus == 0 && item[2].itemValue >= 1) {
                    item[2].itemValue -= 1;
                    item[2].useStatus = 1;
                    item[2].timeCounter = item[2].timeValue;
                }
                if (IsKeyPressed(KEY_F) && item[3].useStatus == 0 && item[3].itemValue >= 1) {
                    item[3].itemValue -= 1;
                    item[3].useStatus = 1;
                    item[3].timeCounter = item[3].timeValue;
                }
                if (IsKeyPressed(KEY_G) && item[4].useStatus == 0 && item[4].itemValue >= 1 && item[4].effectValue <= 0) {
                    item[4].itemValue -= 1;
                    item[4].effectValue = 50;
                    armorHp.width = (item[4].effectValue/50)*80;
                }
            }

            for (int i = 0; i < currentEnemy; ++i) //Cheack End of Rounds
            {
                if (killEnemyValue == enemyValue) {
                    gameState = 3;
                    item1 = randoms(0, 9);
                    item2 = randoms(0, 9);
                    item3 = randoms(0, 9);
                    game.killEnemy += enemyValue;
                }
                if (enemy[i].state == -1) {
                    killEnemyValue += 1;
                }

            }
            if (killEnemyValue != enemyValue) {
                killEnemyValue = 0;
            } // ------Cheack End of Rounds

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
                if(player.stamina > player.maxStamina) player.stamina = player.maxStamina;
                if (currentPlayerFrame > 2) currentPlayerFrame = 0;
                playerFrame.x = (float)currentPlayerFrame*(float)playerTexture[player.texture].width/3;

                for(int i = 0; i < currentEnemy; i++){
                    enemy[i].frame ++;
                    if (enemy[i].frame > 2) enemy[i].frame = 0;
                    enemyFrame[i].x = (float)enemy[i].frame*(float)enemyTexture[enemy[i].texture].width/3;
                }
            }
            if (timeCounter >= 60) {
                timeCounter = 0;
                for (int i = 0; i < 6; ++i)
                {
                    if (item[i].useStatus == 1) {
                        item[i].timeCounter -= 1;
                        switch (i)
                        {
                            case 2:
                                player.defend = player.defend + 1000;
                                break;
                            case 3:
                                player.speed = player.speed + 10;
                                break;
                        }
                        if (item[i].timeCounter == 0) {
                            item[i].useStatus = 0;
                            switch (i)
                            {
                                case 2:
                                    player.defend = player.defend - 5000;
                                    break;
                                case 3:
                                    player.speed = player.speed - 30;
                                    break;
                            }
                        }
                    }
                }
            }
            playerStamina.width = player.stamina * 165/player.maxStamina;
            break;
        case 2:
            StopMusicStream(music[1]);
            PlayMusicStream(music[3]);
            // delay(5);
            if (IsKeyPressed(KEY_R)) {
                gameState = 1;
                player.hp = 100;
                theMap = randoms(0, 4);
                enemyValue = randoms(1, 9);
                currentEnemy = 0;
                game.level = 1;
                game.killEnemy = 0;
                game.damageDone = 0;
            }
            if (IsKeyPressed(KEY_H)) {
                gameState = 0;
                theMap = randoms(0, 4);
                enemyValue = randoms(1, 9);
                currentEnemy = 0;
                game.level = 1;
                game.killEnemy = 0;
                game.damageDone = 0;
            }
            break;
        case 3:
            StopMusicStream(music[0]);
            if (IsKeyDown(KEY_N)) {
                gameState = 1;
                theMap = randoms(0, 4);
                enemyValue = randoms(1, 9);
                currentEnemy = 0;
                game.level += 1;
                player.stamina = player.maxStamina;
                player.hp += player.maxHp*0.2;
            }
            if (IsKeyDown(KEY_Q)) {
                switch (item1)
                {
                    case 6:
                        item[0].itemValue += 1;
                        break;
                    case 9:
                        item[1].itemValue += 1;
                        break;
                    case 3:
                        item[2].itemValue += 1;
                        break;
                    case 8:
                        item[3].itemValue += 1;
                        break;
                    case 2:
                        item[4].itemValue += 1;
                        break;
                    case 7:
                        item[5].itemValue += 1;
                        break;
                    case 0:
                        player.attack += 10;
                        break;
                    case 1:
                        player.defend += 10;
                        break;
                    case 4:
                        player.maxHp += 20;
                        break;
                    case 5:
                        player.maxStamina += 10;
                        break;
                }
                gameState = 1;
                theMap = randoms(0, 4);
                enemyValue = randoms(1, 9);
                currentEnemy = 0;
                game.level += 1;
                player.stamina = player.maxStamina;
                player.hp += player.maxHp*0.2;
            }
            if (IsKeyDown(KEY_W)) {
                switch (item2)
                {
                    case 6:
                        item[0].itemValue += 1;
                        break;
                    case 9:
                        item[1].itemValue += 1;
                        break;
                    case 3:
                        item[2].itemValue += 1;
                        break;
                    case 8:
                        item[3].itemValue += 1;
                        break;
                    case 2:
                        item[4].itemValue += 1;
                        break;
                    case 7:
                        item[5].itemValue += 1;
                        break;
                    case 0:
                        player.attack += 10;
                        break;
                    case 1:
                        player.defend += 10;
                        break;
                    case 4:
                        player.maxHp += 20;
                        break;
                    case 5:
                        player.maxStamina += 10;
                        break;
                }
                gameState = 1;
                theMap = randoms(0, 4);
                enemyValue = randoms(1, 9);
                currentEnemy = 0;
                game.level += 1;
                player.stamina = player.maxStamina;
                player.hp += player.maxHp*0.2;
            }
            if (IsKeyDown(KEY_E)) {
                switch (item3)
                {
                    case 6:
                        item[0].itemValue += 1;
                        break;
                    case 9:
                        item[1].itemValue += 1;
                        break;
                    case 3:
                        item[2].itemValue += 1;
                        break;
                    case 8:
                        item[3].itemValue += 1;
                        break;
                    case 2:
                        item[4].itemValue += 1;
                        break;
                    case 7:
                        item[5].itemValue += 1;
                        break;
                    case 0:
                        player.attack += 10;
                        break;
                    case 1:
                        player.defend += 10;
                        break;
                    case 4:
                        player.maxHp += 20;
                        break;
                    case 5:
                        player.maxStamina += 10;
                        break;
                }
                gameState = 1;
                theMap = randoms(0, 4);
                enemyValue = randoms(1, 9);
                currentEnemy = 0;
                game.level += 1;
                player.stamina = player.maxStamina;
                player.hp += player.maxHp*0.2;
            }
            player.hitWall = 1;
            while(player.hitWall){
                playerBox.x = randoms(60, 1170);
                playerBox.x = randoms(60, 610);
                switch (theMap)
                {
                    case 0:
                        for(int i = 0; i < 4; i ++){
                            player.hitWall = CheckCollisionRecs(playerBox, mapBox[i]);
                            if(player.hitWall) break;
                        }
                        break;
                    case 1:
                        for(int i = 4; i < 8; i ++){
                            player.hitWall = CheckCollisionRecs(playerBox, mapBox[i]);
                            if(player.hitWall) break;
                        }
                        break;
                    case 2:
                        for(int i = 8; i < 12; i ++){
                            player.hitWall = CheckCollisionRecs(playerBox, mapBox[i]);
                            if(player.hitWall) break;
                        }
                        break;
                    case 3:
                        for(int i = 12; i < 16; i ++){
                            player.hitWall = CheckCollisionRecs(playerBox, mapBox[i]);
                            if(player.hitWall) break;
                        }
                        break;
                    case 4:
                        for(int i = 16; i < 20; i ++){
                            player.hitWall = CheckCollisionRecs(playerBox, mapBox[i]);
                            if(player.hitWall) break;
                        }
                        break;
                }
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
                    default:
                        DrawTexturePro(playerTexture[player.texture], playerFrameStop, playerBox, origin, 0.0, WHITE);
                }
                for(int i = 0; i < currentEnemy; i++){
                    switch(enemy[i].state){
                    case -1:
                        break;
                    default:
                        DrawTexturePro(enemyTexture[enemy[i].texture], enemyFrame[i], enemyBox[i], origin, 0.0, WHITE);
                        DrawText(FormatText("%d", enemy[i].hp), enemyBox[i].x, enemyBox[i].y - 22, 20, GRAY);
                    }
                    switch(enemy[i].action){
                    case 0:
                        break;
                    default:
                        DrawTexturePro(enemyAttackTexture[enemy[i].texture], enemyAttackFrame[i], enemyAttackBox[i], origin, 0.0, WHITE);
                    }
                }

                switch(player.action){
                    case 0:
                        break;
                    default:
                        DrawTexturePro(attackTexture[player.texture], playerAttackFrame, playerAttackBox, origin, 0.0, WHITE);
                }
                DrawText(FormatText("%i", game.level), 0, 0, 39, GREEN);
                
                DrawTexture(titleTexture[15], 0, 80, WHITE);
                DrawRectangleRec(playerHp, GREEN);
                DrawRectangleRec(armorHp, BLUE);
                DrawRectangleRec(playerStamina, BLUE);
                DrawTexture(titleTexture[9], 265, 661, WHITE);
                DrawTexture(titleTexture[10], 428, 661, WHITE);
                DrawTexture(titleTexture[11], 591, 661, WHITE);
                DrawTexture(titleTexture[12], 754, 661, WHITE);
                DrawTexture(titleTexture[13], 917, 661, WHITE);
                DrawTexture(titleTexture[14], 1080, 661, WHITE);
                DrawTexture(titleTexture[16], 0, 0, WHITE);
                DrawText(FormatText("x %i", item[0].itemValue), 337, 674, 28, GREEN);
                DrawText(FormatText("x %i", item[1].itemValue), 500, 674, 28, GREEN);
                DrawText(FormatText("x %i", item[2].itemValue), 663, 674, 28, GREEN);
                DrawText(FormatText("x %i", item[3].itemValue), 826, 674, 28, GREEN);
                DrawText(FormatText("x %i", item[4].itemValue), 989, 674, 28, GREEN);
                DrawText(FormatText("x %i", item[5].itemValue), 1152, 674, 28, GREEN);
                break;
            case 2:
                DrawTexture(mapTexture[theMap], 0, 0, WHITE);
                DrawTexture(titleTexture[1], 0, 0, WHITE);
                DrawText(FormatText("%i", game.level),   727, 246, 28, BLACK);
                DrawText(FormatText("%i", game.killEnemy),   727, 338, 28, BLACK);
                DrawText(FormatText("%0.2f", game.damageDone),   727, 435, 28, BLACK);
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
                DrawText(FormatText("Attack"),   90, 412, 28, GREEN);
                DrawText(FormatText("Defend"),   90, 444, 28, GREEN);
                DrawText(FormatText("Max Hp"),   90, 476, 28, GREEN);
                DrawText(FormatText("Max Stamina"),   90, 508, 28, GREEN);
                DrawText(FormatText("Speed"),   90, 540, 28, GREEN);
                DrawText(FormatText("Stamina Recove"),   90, 572, 28, GREEN);

                DrawText(FormatText("%i", player.hp),   298, 348, 28, GREEN);
                DrawText(FormatText("%i", player.stamina),   298, 380, 28, GREEN);
                DrawText(FormatText("%i", player.attack),   298, 412, 28, GREEN);
                DrawText(FormatText("%i", player.defend),   298, 444, 28, GREEN);
                DrawText(FormatText("%i", player.maxHp),   298, 476, 28, GREEN);
                DrawText(FormatText("%i", player.maxStamina),   298, 508, 28, GREEN);
                DrawText(FormatText("%i", player.speed),   298, 540, 28, GREEN);
                DrawText(FormatText("%i", player.staminaRecove),   298, 572, 28, GREEN);
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
    for(int i = 0; i < enemyTextureValue; i++)
    {
        UnloadTexture(enemyAttackTexture[i]);
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