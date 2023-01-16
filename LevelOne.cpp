#include "raylib.h"
#include "Player.h"
#include "Door.h"
#include "Wall.h"
#include "Entity.h"
#include "Platform.h"
#include "Box.h"
#include "Lever.h"
#include "Plate.h"
#include <vector>
#include <iostream>

#define SKY (Color){ 202,157,129, 255 }

using namespace std;
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Blob Game");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Image for in game background
    Image bgImage = LoadImage("./../res/blankBackgroundLong.png");
    //ImageResize(&bgImage, bgImage.width, screenHeight+10);
    ImageResize(&bgImage,9550, 1050);
    Texture2D background = LoadTextureFromImage(bgImage);

    // Import blob image and create player instances
    Image blobImage = LoadImage("./../res/blob.png");
    ImageResize(&blobImage,120, 80);
    // Non solid floating platform
    Image platformImage=LoadImage("./../res/platform3.png");
    ImageResize(&platformImage,300, platformImage.height);
    // Import Basic platform image and create instance of Entity
    Image floorImage = LoadImage("./../res/floor.png");
    
    ImageResize(&floorImage,bgImage.width, 60);
    Image closedDoorImage = LoadImage("./../res/closed-door.png");
    ImageResize(&closedDoorImage, 50, 100);
    Image openDoorImage = LoadImage("./../res/open-door.png");
    ImageResize(&openDoorImage, 50, 100);
    // Import lever image, on and off
    Image leverOn = LoadImage("./../res/leverOn.png");
    Image leverOff = LoadImage("./../res/leverOff.png");
    
    // Import pressure plate on and off
    Image plateOn = LoadImage("./../res/pressurePlateOn.png");
    Image plateOff = LoadImage("./../res/pressurePlateOff.png");
    ImageResize(&plateOn, 100, 10);
    ImageResize(&plateOff, 100, 10);
    
    
    Player * blob = new Player(400,200,blobImage.width,blobImage.height,LoadTextureFromImage(blobImage));
    

    
    //Creates the floor of the level, x coords, y coords, length, height
    Wall *floor = new Wall(0,660,floorImage.width, floorImage.height, LoadTextureFromImage(floorImage));
    
    ImageResize(&floorImage,450, 60);
    
    
    
    
    
    
    // Moveable Box1!
    Image boxImage = LoadImage("./../res/box.png");
    ImageResize(&boxImage, 50, 50);
    Box *box1 = new Box(5500, floor->getYPos()-boxImage.height-50, boxImage.width, boxImage.height, LoadTextureFromImage(boxImage));
    // Moveable Box2 !
    Box *box2 = new Box(200, floor->getYPos()-boxImage.height-50, boxImage.width, boxImage.height, LoadTextureFromImage(boxImage));
    //Code for the first section platform parkour 
    Platform *platformOne = new Platform(700,500,platformImage.width, platformImage.height, true, LoadTextureFromImage(platformImage));
    
    Platform *platform1 = new Platform(1250,400,platformImage.width,platformImage.height, true,  LoadTextureFromImage(platformImage));
    
    Platform *platform2 = new Platform(1800,300,platformImage.width,platformImage.height, true,  LoadTextureFromImage(platformImage));
    
    Platform *platform3 = new Platform(2350,200,platformImage.width,platformImage.height, true,  LoadTextureFromImage(platformImage));

    // Import door image and create instance of Door
    
    Door *door1 = new Door(2550, 200-closedDoorImage.height, closedDoorImage.width, closedDoorImage.height, LoadTextureFromImage(closedDoorImage), LoadTextureFromImage(openDoorImage));
    
    
    
    
    Plate * plt = new Plate(2400, 200, plateOff.width,plateOff.height,LoadTextureFromImage(plateOff));
    ImageResize(&floorImage,door1->getWidth(), 400);
    Wall *door1wall = new Wall(door1->getXPos(),door1->getYPos()-floorImage.height, floorImage.width, floorImage.height, LoadTextureFromImage(floorImage));
    
    ImageResize(&floorImage,platformImage.width, 660-200);
    Wall *wall2 = new Wall(2350,200,platformImage.width, 660-200, LoadTextureFromImage(floorImage));
   
    Platform *platform4 = new Platform(3350,500,platformImage.width,platformImage.height, true,  LoadTextureFromImage(platformImage));
    
    Platform *platform5 = new Platform(3900,400,platformImage.width,platformImage.height, true,  LoadTextureFromImage(platformImage));
    
    Platform *platform6 = new Platform(3500,250,platformImage.width,platformImage.height, true,  LoadTextureFromImage(platformImage));
    
    Platform *platform7 = new Platform(4450,300,platformImage.width,platformImage.height, true,  LoadTextureFromImage(platformImage));
    
    ImageResize(&leverOn, 120, 60);
    ImageResize(&leverOff, 120, 60);
    // Create instance of a lever THIS IS A TEST LEVER
    Lever *lvr = new Lever(3600, 250-leverOff.height, leverOff.width, leverOff.height, LoadTextureFromImage(leverOff));

    Platform *platform8 = new Platform(4900,200,platformImage.width,platformImage.height, true,  LoadTextureFromImage(platformImage));

    // Import door image and create instance of Door
    
    Door *door2 = new Door(5150, 200-closedDoorImage.height, closedDoorImage.width, closedDoorImage.height, LoadTextureFromImage(closedDoorImage), LoadTextureFromImage(openDoorImage));
    
    
    ImageResize(&floorImage,platformImage.width, 660-200);
    Wall *wall3 = new Wall(4900,200,platformImage.width, 660-200, LoadTextureFromImage(floorImage));
    
    ImageResize(&floorImage,door1->getWidth(), 400);
    Wall *door2wall = new Wall(door2->getXPos(),door2->getYPos()-floorImage.height, floorImage.width, floorImage.height, LoadTextureFromImage(floorImage));

    
    Platform *platform9 = new Platform(6000,500,platformImage.width,platformImage.height, true,  LoadTextureFromImage(platformImage));
    
    Platform *platform10 = new Platform(6550,400,platformImage.width,platformImage.height, true,  LoadTextureFromImage(platformImage));
    
    Platform *platform11 = new Platform(7000,300,platformImage.width,platformImage.height, true,  LoadTextureFromImage(platformImage));
    
    Platform *platform12 = new Platform(8000,400,platformImage.width,platformImage.height, true,  LoadTextureFromImage(platformImage));

    Platform *platform13 = new Platform(7600,200,platformImage.width,platformImage.height, true,  LoadTextureFromImage(platformImage));
    
    ImageResize(&floorImage,platformImage.width, 660-200);
    Wall *wall4 = new Wall(7550+1000,200,platformImage.width, 660-200, LoadTextureFromImage(floorImage));
    Door *door3 = new Door(7800+1000, 200-closedDoorImage.height, closedDoorImage.width, closedDoorImage.height, LoadTextureFromImage(closedDoorImage), LoadTextureFromImage(openDoorImage));
    
    ImageResize(&floorImage,door1->getWidth(), 400);
    Wall *door3wall = new Wall(door3->getXPos(),door3->getYPos()-floorImage.height, floorImage.width, floorImage.height, LoadTextureFromImage(floorImage));
    
    Plate * plt2 = new Plate(8100, 400, plateOff.width,plateOff.height,LoadTextureFromImage(plateOff));
    
    ImageResize(&floorImage,50, 1000);
    Wall *borderWall1 = new Wall(0,-(1000-660),50, 1000, LoadTextureFromImage(floorImage));
    ImageResize(&floorImage,9500, 50);
    Wall *ceiling = new Wall(0,-(1000-660),9500, 50, LoadTextureFromImage(floorImage));
    ImageResize(&floorImage,50, 1000);
    Wall *borderWall2 = new Wall(9500,-(1000-660),50, 1000, LoadTextureFromImage(floorImage));
    
    // camera setup
    Camera2D  camera = {0};
    camera.target = (Vector2){blob->getXPos()+200,blob->getYPos()};
    camera.offset = (Vector2){ screenWidth/2, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    
    //Used to fix invisable doors, do not remove
    door1->setOpen(true);
    door2 ->setOpen(true);
    door3 ->setOpen(true);
    plt->setTexture(LoadTextureFromImage(plateOn));
    int doorFix = 1;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Checking for keypress
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){
            blob->moveRight();
        }
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)){
            blob->moveLeft();
        }
        if (IsKeyPressed(KEY_SPACE)){
            blob->jump();
        }
        if (IsKeyPressed(KEY_O)){
            
        }
        if (IsKeyPressed(KEY_B)){
            box1->toggleHoisted(blob);
            box2->toggleHoisted(blob);
        }
        
        // Camera target follows player
        camera.target = (Vector2){blob->getXPos()+100,350};
        camera.zoom += ((float)GetMouseWheelMove()*0.05f);
        
        //Fix invisable doors
        
        while (doorFix ==1) {
            door1->setOpen(false);
            door2 ->setOpen(false);
            door3 ->setOpen(false);
            plt->setTexture(LoadTextureFromImage(plateOff));
            doorFix = 0;
        }
        //Level Complete 
        if (blob->getXPos() > door3->getXPos() && blob->getYPos()+100 > floor->getYPos()) {
            CloseWindow();
        }

        if (camera.zoom > 3.0f) camera.zoom = 3.0f;
        else if (camera.zoom < 0.1f) camera.zoom = 0.1f;
        
        if(lvr->getDistFromUsr(blob->getXPos(), blob->getYPos()) < 100.0 && IsKeyPressed(KEY_LEFT_SHIFT)){ // checks distance from user, if close then change the switch lvr->getDistFromUsr(blob->getXPos(), blob->getYPos()) < 100 && 
            if(lvr->getLeverStatus()) {
                lvr->setTexture(LoadTextureFromImage(leverOff));
                door2->toggleOpen();
            }
            
            else{
                lvr->setTexture(LoadTextureFromImage(leverOn));
                lvr->setLeverStatus(); // toggles lever status
                door2->toggleOpen();
                
            }
                
        }
        
        if(plt->getDistFromEnt(blob->getXPos()+60, blob->getYPos()) < 100.0 || plt->getDistFromEnt(box1->getXPos()+25, box1->getYPos()) < 75.0 || plt->getDistFromEnt(box2->getXPos()+25, box2->getYPos()) < 75.0){
            if(!plt->getPlateStatus()){
                plt->setTexture(LoadTextureFromImage(plateOn));
                plt->setPlateStatus(); // toggles lever status
                door1->setOpen(true);

            }
        }
        else{
            if(plt->getPlateStatus()){
                
                plt->setPlateStatus(); // toggles lever status
            }
            
         if(plt2->getDistFromEnt(blob->getXPos()+60, blob->getYPos()) < 100.0 || plt2->getDistFromEnt(box1->getXPos()+25, box1->getYPos()) < 75.0 || plt2->getDistFromEnt(box2->getXPos()+25, box2->getYPos()) < 75.0){
            if(!plt2->getPlateStatus()){
                plt2->setTexture(LoadTextureFromImage(plateOn));
                plt2->setPlateStatus(); // toggles lever status
                door3->setOpen(true);

            }
        }
        else{
            if(plt2->getPlateStatus()){
                plt2->setTexture(LoadTextureFromImage(plateOff));
                plt2->setPlateStatus(); // toggles lever status
                door3->setOpen(false);
            }   
        }
        
        }
        // Falling physics
        blob->physics();
        blob->setJumps(0);
        
        // Check for door collisions
        door1->collisionPhysics(blob);
        door2->collisionPhysics(blob);
        door3->collisionPhysics(blob);
        // Box collisions
        box1->physics(blob);
        box2->physics(blob);
        
        // Platform collisions with Player
        platformOne->collisionPhysics(blob);
        platform1->collisionPhysics(blob);
        platform2->collisionPhysics(blob);
        platform3->collisionPhysics(blob);
        platform4->collisionPhysics(blob);
        platform5->collisionPhysics(blob);
        platform6->collisionPhysics(blob);
        platform7->collisionPhysics(blob);
        platform8->collisionPhysics(blob);
        platform9->collisionPhysics(blob);
        platform10->collisionPhysics(blob);
        platform11->collisionPhysics(blob);
        platform12->collisionPhysics(blob);
        platform13->collisionPhysics(blob);
        
        // Platform collisions with Box
        platformOne->collisionPhysicsBox(box1);
        platformOne->collisionPhysicsBox(box2);
        platform1->collisionPhysicsBox(box1);
        platform1->collisionPhysicsBox(box2);
        platform2->collisionPhysicsBox(box1);
        platform2->collisionPhysicsBox(box2);
        platform3->collisionPhysicsBox(box1);
        platform3->collisionPhysicsBox(box2);
        platform4->collisionPhysicsBox(box1);
        platform4->collisionPhysicsBox(box2);
        platform5->collisionPhysicsBox(box1);
        platform5->collisionPhysicsBox(box2);
        platform6->collisionPhysicsBox(box1);
        platform6->collisionPhysicsBox(box2);
        platform7->collisionPhysicsBox(box1);
        platform7->collisionPhysicsBox(box2);
        
        platform8->collisionPhysicsBox(box1);
        platform8->collisionPhysicsBox(box2);
        platform9->collisionPhysicsBox(box1);
        platform9->collisionPhysicsBox(box2);
        platform10->collisionPhysicsBox(box1);
        platform10->collisionPhysicsBox(box2);
        platform11->collisionPhysicsBox(box1);
        platform11->collisionPhysicsBox(box2);
        platform12->collisionPhysicsBox(box1);
        platform12->collisionPhysicsBox(box2);
        platform13->collisionPhysicsBox(box1);
        platform13->collisionPhysicsBox(box2);
        // Wall collisions with Player
        
        floor->collisionPhysics(blob);
        wall2->collisionPhysics(blob);
        door1wall->collisionPhysics(blob);
        wall3->collisionPhysics(blob);
        door2wall->collisionPhysics(blob);
        wall4->collisionPhysics(blob);
        door3wall->collisionPhysics(blob);
        
        borderWall1->collisionPhysics(blob);
        ceiling->collisionPhysics(blob);
        borderWall2->collisionPhysics(blob);
        
        // Wall collisions with Box
        
        floor->collisionPhysicsBox(box1);
        floor->collisionPhysicsBox(box2);
        
        wall2->collisionPhysicsBox(box1);
        wall2->collisionPhysicsBox(box2);
        door1wall->collisionPhysicsBox(box1);
        door1wall->collisionPhysicsBox(box2);
        
        
        door3wall->collisionPhysicsBox(box1);
        door3wall->collisionPhysicsBox(box2);
        
        wall3->collisionPhysicsBox(box1);
        wall3->collisionPhysicsBox(box2);
        
        door2wall->collisionPhysicsBox(box1);
        door2wall->collisionPhysicsBox(box2);
        
        borderWall1->collisionPhysicsBox(box1);
        borderWall1->collisionPhysicsBox(box2);
        
        borderWall2->collisionPhysicsBox(box1);
        borderWall2->collisionPhysicsBox(box2);
        
        ceiling->collisionPhysicsBox(box1);
        ceiling->collisionPhysicsBox(box2);


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(SKY);
           
            
            BeginMode2D(camera);
            
            DrawTexture(background, 0,-300, WHITE);
            
            platformOne->Draw();
            platform1->Draw();
            platform2->Draw();
            platform3->Draw();
            platform4->Draw();
            platform5->Draw();
            platform6->Draw();
            platform7->Draw();
            platform8->Draw();
            platform9->Draw();
            platform10->Draw();
            platform11->Draw();
            platform12->Draw();
            platform13->Draw();
            
            floor->Draw();
            
            wall2->Draw();
            door1->Draw();
            door1wall->Draw();
            
            wall3->Draw();
            door2wall->Draw();
            door2->Draw();
            
            wall4->Draw();
            door3wall->Draw();
            door3->Draw();
            
            borderWall1->Draw();
            borderWall2->Draw();
            ceiling->Draw();
            
            blob->Draw();
            box1->Draw();
            //box2->Draw();
            lvr->Draw();
            plt->Draw();
            plt2->Draw();
            
            EndMode2D();


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}