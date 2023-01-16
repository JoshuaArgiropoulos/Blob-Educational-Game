#include "raylib.h"
#include "LevelTwo.h"
#include "Player.h"
#include <string>
#include <iostream>
        
using namespace std;
        LevelTwo::LevelTwo():Level(){          
            initEntities();
        }

        string LevelTwo::getLevelName(){
            return levelName;
        }
        bool LevelTwo::getCompletionStatus(){
            return completionStatus;
        }
        void LevelTwo::Run(){
            const int screenWidth = 1500;
            const int screenHeight = 720;

            // Import blob image and create player instance
            Image blobImage = LoadImage("./../res/blob.png");
            ImageResize(&blobImage,120, 80);
            Player * blob = new Player(500,200,blobImage.width,blobImage.height,LoadTextureFromImage(blobImage));

            Image bgImage = LoadImage("./../res/background.png");
            ImageResize(&bgImage,3500, 1000);
            Texture2D background = LoadTextureFromImage(bgImage);

            //camera setting 
            Camera2D  camera = {0};
            camera.target = (Vector2){blob->getXPos()+200,blob->getYPos()};
            camera.offset = (Vector2){ screenWidth/2, screenHeight/2.0f };
            camera.rotation = 0.0f;
            camera.zoom = 1.0f;

            // Main game loop
            
            while(completionStatus == false){
                
                if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){
                   blob->moveRight();
                }
                if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)){
                    blob->moveLeft();
                }
                if (IsKeyPressed(KEY_SPACE)){
                   blob->jump();
                }
                
                //camera follows
                camera.target = (Vector2){blob->getXPos()+200,blob->getYPos()};
                camera.zoom += ((float)GetMouseWheelMove()*0.05f);

                if (camera.zoom > 3.0f){
                    camera.zoom = 3.0f;
                }
                else if (camera.zoom < 0.1f){
                    camera.zoom = 0.1f;
                }
                game(blob);
                
                // Falling physics  
                blob->physics();
                

                // Draw
                //----------------------------------------------------------------------------------
                BeginDrawing();
                    ClearBackground(RAYWHITE);
                    DrawTexture(background, 0,0, WHITE);
                    
                    //stuff for camera
                    
                    BeginMode2D(camera);
                        DrawText("A not inverts the input \nand ouputs the opposite.", 750 ,-400,75,WHITE);
                        DrawText("An OR gate requires only one \ninput to be true", 2850 ,-400,75,WHITE);
                        DrawText("An AND Gate requires all inputs to be true to work", 5000 ,-400,75,WHITE);
                        drawLevel();
                        blob->Draw();
                    EndMode2D();
                   
                EndDrawing();
                }
            printf("COMPLETED");
        }
        
        void LevelTwo::game(Player* blob){
            
            gameLogic(blob);
            checkCollision(blob);
            
            
            //win condition
            if((blob->getXPos() >= 7350)&&(blob->getXPos() > -200)){
                completionStatus = true;                
                printf("COMPLETED");
                //CloseWindow();
            }
            
        }
        
        void LevelTwo::checkCollision(Player* blob){
            
            bool singleCollision[leverNum];
            for(int x =0;x<leverNum;x++){
                singleCollision[x] = false;
            }
            
            //if player falls off map
            if(blob->getYPos()>650){
                blob->setYPos(100);
                blob->setXPos(300);
            }
            
            //platform collisions
            for(int x = 0; x< platformNum;x++){
                platformList[x]->collisionPhysics(blob);
                for(int y =0;y<boxNum;y++){
                    
                    platformList[x]->collisionPhysicsBox(&boxList[y]);
                    
                }
            
            }
            
            //wall collisions
            for(int x = 0; x< wallNum;x++){
                wallList[x].collisionPhysics(blob);
                for(int y =0;y<boxNum;y++){
                    wallList[x].collisionPhysicsBox(&boxList[y]);
                }
            }
            
            //door collisions
            for(int x=0;x<doorNum;x++){
                doorList[x].collisionPhysics(blob);
            }
            
            //presure plate collisions
            for(int x=0;x<plateNum;x++){   
                plateList[x].setPlateStatus(false);
                plateList[x].physics(blob);
                for(int y=0;y<boxNum;y++){
                    plateList[x].boxPhysics(&boxList[y]);                    
                }
            }
            
            //lever collisions
            for(int x=0;x<leverNum;x++){
                leverList[x].physics(blob);
            }
            
            //box collisions
            for(int x=0;x<boxNum;x++){
                if (IsKeyDown(KEY_R)){
                   boxList[x].toggleHoisted(blob);
                }                
                boxList[x].physics(blob);
            }
            
            
            
        }
        void LevelTwo::drawLevel(){
            //platform draw
            for (int x =0;x<platformNum;x++){
                platformList[x]->Draw();
                
            }
            //walls draw
            for(int x = 0;x<wallNum;x++){
                wallList[x].Draw();
            }
            //doors draw
            for(int x=0;x<doorNum;x++){
                doorList[x].Draw();
            }
            //plate draw
            for(int x=0;x<plateNum;x++){
                plateList[x].Draw();
            }
            //lever draw
            for(int x=0;x<leverNum;x++){
                leverList[x].Draw();
            }
            //box draw
            for(int x=0;x<boxNum;x++){
                boxList[x].Draw();
            }

        }
        
        void LevelTwo::gameLogic(Player* blob){
            //door 1 (part A)
            if(!plateList[0].getPlateStatus()){
                doorList[0].setOpen(true);
            }
            else{
                doorList[0].setOpen(false);
            }
            
            //door 2 (part B)
            if(leverList[0].getLeverStatus() || plateList[1].getPlateStatus()||plateList[2].getPlateStatus() ){
                doorList[1].setOpen(true);
            }
            else{
                doorList[1].setOpen(false);
            }
            
            //door 3 (part C)
            int total=0;
            for(int x =1;x<leverNum;x++){
                if(leverList[x].getLeverStatus()){
                    total++;
                }
            }
            if(total == (leverNum-1)){
                doorList[2].setOpen(true);
            }
        }
        
        void LevelTwo::initEntities(){
                        
            //platforms
            int ** pInfo;
            
            //wall and platform info
            int countWall =0;
            int countPlatform =0;            
            Image platformEntitiesImages[entityNum];
            Wall *wallEntities[wallNum];
            Platform *platEntities[platformNum];

            //door info
            int countDoor =0;
            Image openDoorImageList[doorNum];
            Image closedDoorImageList[doorNum];
            Door *doorEntities[doorNum];

            //plate info
            int countPlate=0;
            Image plateOnImageList[plateNum];
            Plate *plateEntities[plateNum];
            Image plateOffImageList[plateNum];
            
            //lever info
            int countLever=0;
            Image leverOnImageList[leverNum];
            Image leverOffImageList[leverNum];
            Lever *leverEntities[leverNum];
            
            //box info
            int countBox=0;
            Image boxImageList[boxNum];
            Box *boxEntities[boxNum];
            
            pInfo = initEntity();
            for(int x = 0; x< entityNum;x++){
                platformEntitiesImages[x] = LoadImage("./../res/platform2.png");
                ImageResize(&platformEntitiesImages[x],pInfo[x][2], pInfo[x][3]);                
                //wall
                if((x==4)||(x==13)||(x==15)||(x==17)||(x==22)||(x==28)||(x==29)||(x==30)||(x==31)||(x==32)||(x==33)||(x==34)/*||(x>=37)*/){
                    wallEntities[countWall] = new Wall(pInfo[x][0],pInfo[x][1],pInfo[x][2],pInfo[x][3], LoadTextureFromImage(platformEntitiesImages[x]));
                    wallList[countWall] = *wallEntities[countWall];
                    countWall++;
                }
                
                //door
                else if((x>=37)&&(x<40)){
                    openDoorImageList[countDoor] = LoadImage("./../res/openDoor.png");
                    ImageResize(&openDoorImageList[countDoor], pInfo[x][2], pInfo[x][3]);
                    closedDoorImageList[countDoor] = LoadImage("./../res/closedDoor.png");
                    ImageResize(&closedDoorImageList[countDoor], pInfo[x][2], pInfo[x][3]);
                    doorEntities[countDoor] = new Door(pInfo[x][0],pInfo[x][1],pInfo[x][2],pInfo[x][3], LoadTextureFromImage(closedDoorImageList[countDoor]), LoadTextureFromImage(openDoorImageList[countDoor]));
                    doorList[countDoor] = *doorEntities[countDoor];
                    countDoor++;
                }
                //plate
                else if((x>=40)&&(x<43)){
                    plateOnImageList[countPlate]= LoadImage("./../res/pressurePlateOn.png");
                    ImageResize(&plateOnImageList[countPlate], pInfo[x][2], pInfo[x][3]);
                    plateOffImageList[countPlate]= LoadImage("./../res/pressurePlateOff.png");
                    ImageResize(&plateOffImageList[countPlate], pInfo[x][2], pInfo[x][3]);
                    plateEntities[countPlate]=new Plate(pInfo[x][0],pInfo[x][1],pInfo[x][2],pInfo[x][3], LoadTextureFromImage(plateOnImageList[countPlate]), LoadTextureFromImage(plateOffImageList[countPlate]));
                    plateList[countPlate]=*plateEntities[countPlate];
                    countPlate++;
                }
                //lever
                else if((x>=43)&&(x<50)){
                    leverOnImageList[countLever]= LoadImage("./../res/leverOn.png");
                    ImageResize(&leverOnImageList[countLever], pInfo[x][2], pInfo[x][3]);
                    leverOffImageList[countLever]= LoadImage("./../res/leverOff.png");
                    ImageResize(&leverOffImageList[countLever], pInfo[x][2], pInfo[x][3]);
                    leverEntities[countLever]=new Lever(pInfo[x][0],pInfo[x][1],pInfo[x][2],pInfo[x][3], LoadTextureFromImage(leverOnImageList[countLever]), LoadTextureFromImage(leverOffImageList[countLever]));
                    leverList[countLever]=*leverEntities[countLever];
                    countLever++;
                }
                //box
                else if((x>=50)&&(x<51)){
                    boxImageList[countBox] = LoadImage("./../res/box.png");
                    ImageResize(&boxImageList[countBox], pInfo[x][2], pInfo[x][3]);
                    boxEntities[countBox]=new Box(pInfo[x][0],pInfo[x][1],pInfo[x][2],pInfo[x][3], LoadTextureFromImage(boxImageList[countBox]));
                    boxList[countBox]=*boxEntities[countBox];
                    countBox++;
                }
                //platform creation
                else{
                    if(x ==0){
                        platformEntitiesImages[x] = LoadImage("./../res/floor.png");
                        ImageResize(&platformEntitiesImages[x],pInfo[x][2], pInfo[x][3]);
                    }
                    platEntities[countPlatform] = new Platform(pInfo[x][0],pInfo[x][1],pInfo[x][2],pInfo[x][3], true,LoadTextureFromImage(platformEntitiesImages[x]));
                    platformList[countPlatform] = platEntities[countPlatform];
                    countPlatform++;
                }
                
            }
        }
        int** LevelTwo::initEntity(){
            int ** entityInfo = new int*[entityNum];
            for(int x =0;x<entityNum;x++){
                entityInfo[x]=new int[4];
            }
            //[0] = xPos, [1] = yPos, [2] = xSize, [3] = ySize
            //horizontal platforms
            entityInfo[0][0] = 140;
            entityInfo[0][1] = 600;
            entityInfo[0][2] = levelWidth;
            entityInfo[0][3] = 100;
            entityInfo[1][0] = 750;
            entityInfo[1][1] = 400;
            entityInfo[1][2] = 250;
            entityInfo[1][3] = platformThickness;
            entityInfo[2][0] = 1250;
            entityInfo[2][1] = 450;
            entityInfo[2][2] = 350;
            entityInfo[2][3] = platformThickness;
            entityInfo[3][0] = 950;
            entityInfo[3][1] = 200; 
            entityInfo[3][2] = 400;
            entityInfo[3][3] = platformThickness;             
            entityInfo[5][0] = 350;
            entityInfo[5][1] = 0;
            entityInfo[5][2] = 350;
            entityInfo[5][3] = platformThickness;
            entityInfo[6][0] = 1450;
            entityInfo[6][1] = 0;
            entityInfo[6][2] = 350;
            entityInfo[6][3] = platformThickness;
            
            //part b
            entityInfo[7][0] = 2500;
            entityInfo[7][1] = 400;
            entityInfo[7][2] = 350;
            entityInfo[7][3] = platformThickness;            
            entityInfo[8][0] = 4000;
            entityInfo[8][1] = 400;
            entityInfo[8][2] = 350;
            entityInfo[8][3] = platformThickness;
            entityInfo[9][0] = 2950;
            entityInfo[9][1] = 200;
            entityInfo[9][2] = 400;
            entityInfo[9][3] = platformThickness;
            entityInfo[10][0] = 3750;
            entityInfo[10][1] = 50;
            entityInfo[10][2] = 350;
            entityInfo[10][3] = platformThickness;
            entityInfo[11][0] = 2750;
            entityInfo[11][1] = -250;
            entityInfo[11][2] = 250;
            entityInfo[11][3] = platformThickness;
            entityInfo[12][0] = 3500;
            entityInfo[12][1] = -150;
            entityInfo[12][2] = 350;
            entityInfo[12][3] = platformThickness;
            entityInfo[14][0] = 2250;
            entityInfo[14][1] = -300;
            entityInfo[14][2] = 350;
            entityInfo[14][3] = platformThickness;
            entityInfo[16][0] = 2975;
            entityInfo[16][1] = -450; 
            entityInfo[16][2] = 250;
            entityInfo[16][3] = platformThickness;      
            entityInfo[51][0] = 4350;
            entityInfo[51][1] = 200;
            entityInfo[51][2] = 150;;
            entityInfo[51][3] = platformThickness;
            entityInfo[52][0] = 3350;
            entityInfo[52][1] = -50;
            entityInfo[52][2] = 200;;
            entityInfo[52][3] = platformThickness;
            
            
            //parb c
            entityInfo[18][0] = 6000;
            entityInfo[18][1] = 400;
            entityInfo[18][2] = 250;
            entityInfo[18][3] = platformThickness;
            entityInfo[19][0] = 6750;
            entityInfo[19][1] = 400;
            entityInfo[19][2] = 250;
            entityInfo[19][3] = platformThickness;
            entityInfo[20][0] = 4750;
            entityInfo[20][1] = 400;
            entityInfo[20][2] = 350;
            entityInfo[20][3] = platformThickness;
            entityInfo[21][0] = 5650;
            entityInfo[21][1] = 50;   
            entityInfo[21][2] = 350;
            entityInfo[21][3] = platformThickness;                 
            entityInfo[23][0] = 7000;
            entityInfo[23][1] = -50;
            entityInfo[23][2] = 500;
            entityInfo[23][3] = platformThickness;
            entityInfo[24][0] = 5225;
            entityInfo[24][1] = -150;
            entityInfo[24][2] = 350;
            entityInfo[24][3] = platformThickness;
            entityInfo[25][0] = 4750;
            entityInfo[25][1] = -300;
            entityInfo[25][2] = 350;
            entityInfo[25][3] = platformThickness;
            entityInfo[26][0] = 5650;
            entityInfo[26][1] = -500;    
            entityInfo[26][2] = 800;
            entityInfo[26][3] = platformThickness;  
            entityInfo[27][0] = 6850;
            entityInfo[27][1] = -550;
            entityInfo[27][2] = 350;;
            entityInfo[27][3] = platformThickness;
            entityInfo[35][0] = 5750;
            entityInfo[35][1] = -300;
            entityInfo[35][2] = 350;;
            entityInfo[35][3] = platformThickness;
            entityInfo[36][0] = 6325;
            entityInfo[36][1] = 200;
            entityInfo[36][2] = 350;;
            entityInfo[36][3] = platformThickness;
            entityInfo[53][0] = 6500;
            entityInfo[53][1] = 0;
            entityInfo[53][2] = 150;;
            entityInfo[53][3] = platformThickness;
            
            //walls 
            entityInfo[4][0] = 1150;
            entityInfo[4][1] = 50;
            entityInfo[4][2] = platformThickness;
            entityInfo[4][3] = 150;
            entityInfo[13][0] = 3500;
            entityInfo[13][1] = -400;            
            entityInfo[13][2] = platformThickness;
            entityInfo[13][3] = 250;      
            entityInfo[15][0] = 2600;
            entityInfo[15][1] = -550;
            entityInfo[15][2] = platformThickness;
            entityInfo[15][3] = 250;
            entityInfo[17][0] = 5500;
            entityInfo[17][1] = 350;
            entityInfo[17][2] = platformThickness;
            entityInfo[17][3] = 250;
            entityInfo[22][0] = 6500;
            entityInfo[22][1] = -150;
            entityInfo[22][2] = platformThickness;
            entityInfo[22][3] = 400;                              
            entityInfo[28][0] = 6450;
            entityInfo[28][1] = -750;
            entityInfo[28][2] = platformThickness;
            entityInfo[28][3] = 250;
            entityInfo[29][0] = 6050;
            entityInfo[29][1] = -850;
            entityInfo[29][2] = platformThickness;
            entityInfo[29][3] = 350;
            entityInfo[30][0] = 5350;
            entityInfo[30][1] = -750;
            entityInfo[30][2] = platformThickness;;
            entityInfo[30][3] = 250;
            entityInfo[31][0] = 2250;
            entityInfo[31][1] = -700;
            entityInfo[31][2] = wallThickness;
            entityInfo[31][3] = 1150;
            entityInfo[32][0] = 4500;
            entityInfo[32][1] = -700;
            entityInfo[32][2] = wallThickness;
            entityInfo[32][3] = 1150;
            entityInfo[33][0] = 7350;
            entityInfo[33][1] = -750;
            entityInfo[33][2] = wallThickness;
            entityInfo[33][3] = 550;
            entityInfo[34][0] = 7350;
            entityInfo[34][1] = -50;
            entityInfo[34][2] = wallThickness;
            entityInfo[34][3] = 650;
            
            //Doors
            entityInfo[37][0] = 2215;
            entityInfo[37][1] = 450;
            entityInfo[37][2] = 75;
            entityInfo[37][3] = 150;
            entityInfo[38][0] = 4465;
            entityInfo[38][1] = 450;
            entityInfo[38][2] = 75;
            entityInfo[38][3] = 150;            
            entityInfo[39][0] = 7315;
            entityInfo[39][1] = -200;
            entityInfo[39][2] = 75;
            entityInfo[39][3] = 150;
            
            //Plates
            entityInfo[40][0] = 1575;
            entityInfo[40][1] = -35;
            entityInfo[40][2] = 150;
            entityInfo[40][3] = plateThickness;            
            entityInfo[41][0] = 2650;
            entityInfo[41][1] = 565;
            entityInfo[41][2] = 150;
            entityInfo[41][3] = plateThickness;            
            entityInfo[42][0] = 4350;
            entityInfo[42][1] = 565;
            entityInfo[42][2] = 150;
            entityInfo[42][3] = plateThickness;
            
            //Levers
            entityInfo[43][0] = 2325;
            entityInfo[43][1] = -450;
            entityInfo[43][2] = switchThickness;
            entityInfo[43][3] = switchThickness;            
            entityInfo[44][0] = 4850;
            entityInfo[44][1] = 250;
            entityInfo[44][2] = switchThickness;
            entityInfo[44][3] = switchThickness;            
            entityInfo[45][0] = 6800;
            entityInfo[45][1] = 250;
            entityInfo[45][2] = switchThickness;
            entityInfo[45][3] = switchThickness;
            entityInfo[46][0] = 5750;
            entityInfo[46][1] = -100;
            entityInfo[46][2] = switchThickness;
            entityInfo[46][3] = switchThickness;            
            entityInfo[47][0] = 4850;
            entityInfo[47][1] = -450;
            entityInfo[47][2] = switchThickness;
            entityInfo[47][3] = switchThickness;            
            entityInfo[48][0] = 5750;
            entityInfo[48][1] = -650;
            entityInfo[48][2] = switchThickness;
            entityInfo[48][3] = switchThickness;
            entityInfo[49][0] = 6175;
            entityInfo[49][1] = -650;
            entityInfo[49][2] = switchThickness;
            entityInfo[49][3] = switchThickness;
            
            //boxes
            entityInfo[50][0] = 1575;
            entityInfo[50][1] = -150;
            entityInfo[50][2] = 100;
            entityInfo[50][3] = 100;
            
            return entityInfo;
        }
        
    LevelTwo::~LevelTwo(){
        delete[] wallList;
        delete[] platformList;
        delete[] doorList;
        delete[] plateList;
        delete[] leverList;
        delete[] boxList;
    }