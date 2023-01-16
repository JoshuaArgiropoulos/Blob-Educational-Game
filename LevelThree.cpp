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
    ImageResize(&bgImage, bgImage.width, screenHeight+10);
    Texture2D background = LoadTextureFromImage(bgImage);

    // Import blob image and create player instances
    Image blobImage = LoadImage("./../res/blob.png");
    ImageResize(&blobImage,120, 80);
    Player * blob = new Player(500,200,blobImage.width,blobImage.height,LoadTextureFromImage(blobImage));
    

    // Import Basic platform image and create instance of Entity
    Image floorImage = LoadImage("./../res/floor.png");
    ImageResize(&floorImage,bgImage.width, 60);
    Wall *floor = new Wall(-100,660,floorImage.width, floorImage.height, LoadTextureFromImage(floorImage));
    
    Image platImage = LoadImage("./../res/platform3.png");
    ImageResize(&platImage,350, 60);
    Wall *wall2 = new Wall(screenWidth+500, 500,platImage.width, platImage.height, LoadTextureFromImage(platImage));
    Wall *wall3 = new Wall(screenWidth+980, 350,platImage.width, platImage.height, LoadTextureFromImage(platImage));
    //NOT level solid platform with pressure plate
    Wall *wall4 = new Wall(screenWidth-600, 200,platImage.width, platImage.height, LoadTextureFromImage(platImage));
    // appearing solid platform
    Wall *wall5 = new Wall(screenWidth-20, 100,platImage.width, platImage.height, LoadTextureFromImage(platImage));
    

    // Moveable Box1!
    Image boxImage = LoadImage("./../res/box.png");
    ImageResize(&boxImage, 50, 50);
    Box *box1 = new Box(836.5, 100, boxImage.width, boxImage.height, LoadTextureFromImage(boxImage));
    // Moveable Box2 !
    // Box *box2 = new Box(200, floor->getYPos()-boxImage.height-50, boxImage.width, boxImage.height, LoadTextureFromImage(boxImage));
    
    // Non solid floating platform (brick)
    Image platform_1=LoadImage("./../res/platform3.png");
    ImageResize(&platform_1,300, platform_1.height-50);
    Platform *platform1 = new Platform(200,500,platform_1.width,platform_1.height, true,  LoadTextureFromImage(platform_1));

    // Non solid floating platform (blue)
    Image platform_2=LoadImage("./../res/platform2.png");
    ImageResize(&platform_2,250, platform_2.height);
    // blue platforms to get to pressure plate in NOT level
    Platform *platform2 = new Platform(0,320,platform_1.width,platform_1.height, true,  LoadTextureFromImage(platform_2));
    Platform *platform3 = new Platform(300,120,platform_1.width,platform_1.height, true,  LoadTextureFromImage(platform_2));
    // appearing blue platform in AND level
    Platform *platform4 = new Platform(screenWidth+360, 290,platform_1.width,platform_1.height, true,  LoadTextureFromImage(platform_2));

    // Import door image and create instance of Door
    Image closedDoorImage = LoadImage("./../res/closed-door.png");
    ImageResize(&closedDoorImage, 50, 100);
    Image openDoorImage = LoadImage("./../res/open-door.png");
    ImageResize(&openDoorImage, 50, 100);
    Door *door1 = new Door(screenWidth-150, 660-closedDoorImage.height, closedDoorImage.width, closedDoorImage.height, LoadTextureFromImage(closedDoorImage), LoadTextureFromImage(openDoorImage));
    Door *door2 = new Door(screenWidth+1500, 660-closedDoorImage.height, closedDoorImage.width, closedDoorImage.height, LoadTextureFromImage(closedDoorImage), LoadTextureFromImage(openDoorImage));
    Door *door3 = new Door(screenWidth+3080, 660-closedDoorImage.height, closedDoorImage.width, closedDoorImage.height, LoadTextureFromImage(closedDoorImage), LoadTextureFromImage(openDoorImage));
   
    door1->setOpen(true);
    door2->setOpen(true);
    door3->setOpen(true);

    ImageResize(&floorImage,door1->getWidth(), screenHeight);
    Wall *door1wall = new Wall(door1->getXPos(),door1->getYPos()-floorImage.height, floorImage.width, floorImage.height, LoadTextureFromImage(floorImage));
    Wall *door2wall = new Wall(door2->getXPos(),door2->getYPos()-floorImage.height, floorImage.width, floorImage.height, LoadTextureFromImage(floorImage));
    Wall *door3wall = new Wall(door3->getXPos(),door3->getYPos()-floorImage.height, floorImage.width, floorImage.height, LoadTextureFromImage(floorImage));

    // Import lever image, on and off
    Image leverOn = LoadImage("./../res/leverOn.png");
    Image leverOff = LoadImage("./../res/leverOff.png");
    ImageResize(&leverOn, 120, 60);
    ImageResize(&leverOff, 120, 60);
    // Create instance of a lever THIS IS A TEST LEVER
    Lever *lvr = new Lever(screenWidth+200, floor->getYPos()-leverOff.height, leverOff.width, leverOff.height, LoadTextureFromImage(leverOff));
    Lever *lvr2 = new Lever(screenWidth+625, 500-platImage.height, leverOff.width, leverOff.height, LoadTextureFromImage(leverOff));
    Lever *lvr3 = new Lever(screenWidth+1105, 350-platImage.height, leverOff.width, leverOff.height, LoadTextureFromImage(leverOff)); //on wall3
    Lever *lvr4 = new Lever(screenWidth+125, 100-platImage.height, leverOff.width, leverOff.height, LoadTextureFromImage(leverOff)); //on appearing wall5
    // Import pressure plate on and off
    Image plateOn = LoadImage("./../res/pressurePlateOn.png");
    Image plateOff = LoadImage("./../res/pressurePlateOff.png");
    ImageResize(&plateOn, 100, 10);
    ImageResize(&plateOff, 100, 10);
    
    Plate * plt = new Plate(811, 190, plateOff.width,plateOff.height,LoadTextureFromImage(plateOff));
    //Platform* platforms[numPlatforms] = {platform1, platform2, floor};   
    
    //What does this do
    //blob->addPlatform(platform1);
    //blob->addPlatform(platform2);
    //blob->addPlatform(floor); 

    // camera setup
    Camera2D  camera = {0};
    camera.target = (Vector2){blob->getXPos()+200,blob->getYPos()};
    camera.offset = (Vector2){ screenWidth/2, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

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
            door1->toggleOpen();
            door2->toggleOpen();
        }
        if (IsKeyPressed(KEY_B)){
            box1->toggleHoisted(blob);
            // box2->toggleHoisted(blob);

         if(lvr->getLeverStatus()&&lvr2->getLeverStatus()&&lvr3->getLeverStatus()&&lvr4->getLeverStatus()){
            door2->toggleOpen();
        }


        }
        
        // Camera target follows player
        camera.target = (Vector2){blob->getXPos()+100,350};
        camera.zoom += ((float)GetMouseWheelMove()*0.05f);

        if (camera.zoom > 3.0f) camera.zoom = 3.0f;
        else if (camera.zoom < 0.1f) camera.zoom = 0.1f;
        
        if(lvr->getDistFromUsr(blob->getXPos(), blob->getYPos()) < 100.0 && IsKeyPressed(KEY_LEFT_SHIFT)){ // checks distance from user, if close then change the switch lvr->getDistFromUsr(blob->getXPos(), blob->getYPos()) < 100 && 
            if(lvr->getLeverStatus())
                lvr->setTexture(LoadTextureFromImage(leverOff));
            else
                lvr->setTexture(LoadTextureFromImage(leverOn));
            lvr->setLeverStatus(); // toggles lever status
        }

         if(lvr2->getDistFromUsr(blob->getXPos(), blob->getYPos()) < 100.0 && IsKeyPressed(KEY_LEFT_SHIFT)){ // checks distance from user, if close then change the switch lvr->getDistFromUsr(blob->getXPos(), blob->getYPos()) < 100 && 
            if(lvr2->getLeverStatus())
                lvr2->setTexture(LoadTextureFromImage(leverOff));
            else
                lvr2->setTexture(LoadTextureFromImage(leverOn));
            lvr2->setLeverStatus(); // toggles lever status
        }

          if(lvr3->getDistFromUsr(blob->getXPos(), blob->getYPos()) < 100.0 && IsKeyPressed(KEY_LEFT_SHIFT)){ // checks distance from user, if close then change the switch lvr->getDistFromUsr(blob->getXPos(), blob->getYPos()) < 100 && 
            if(lvr3->getLeverStatus())
                lvr3->setTexture(LoadTextureFromImage(leverOff));
            else
                lvr3->setTexture(LoadTextureFromImage(leverOn));
            lvr3->setLeverStatus(); // toggles lever status
        }
        
          if(lvr4->getDistFromUsr(blob->getXPos(), blob->getYPos()) < 100.0 && IsKeyPressed(KEY_LEFT_SHIFT)){ // checks distance from user, if close then change the switch lvr->getDistFromUsr(blob->getXPos(), blob->getYPos()) < 100 && 
            if(lvr4->getLeverStatus())
                lvr4->setTexture(LoadTextureFromImage(leverOff));
            else
                lvr4->setTexture(LoadTextureFromImage(leverOn));
            lvr4->setLeverStatus(); // toggles lever status
        }

        if(plt->getDistFromEnt(blob->getXPos()+60, blob->getYPos()) < 100.0 || plt->getDistFromEnt(box1->getXPos()+25, box1->getYPos()) < 75.0){
            if(!plt->getPlateStatus()){
                plt->setTexture(LoadTextureFromImage(plateOn));
                plt->setPlateStatus(); // toggles lever status
                door1->setOpen(false);

            }
        }
        else{
            if(plt->getPlateStatus()){
                plt->setTexture(LoadTextureFromImage(plateOff));
                plt->setPlateStatus(); // toggles lever status
                door1->setOpen(true);
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
        // box2->physics(blob);
        
        // Platform collisions with Player
        platform1->collisionPhysics(blob);
        platform2->collisionPhysics(blob);
        platform3->collisionPhysics(blob);
        
        // Platform collisions with Box
        platform1->collisionPhysicsBox(box1);
        platform2->collisionPhysicsBox(box1);
        platform3->collisionPhysicsBox(box1);
        // platform1->collisionPhysicsBox(box2);
        
        // Wall collisions with Player
        floor->collisionPhysics(blob);
        wall2->collisionPhysics(blob);
        wall3->collisionPhysics(blob);
        wall4->collisionPhysics(blob);//new
        door1wall->collisionPhysics(blob);
        door2wall->collisionPhysics(blob);
        door3wall->collisionPhysics(blob);
        
        // Wall collisions with Box
        floor->collisionPhysicsBox(box1);
        wall2->collisionPhysicsBox(box1);
        wall3->collisionPhysicsBox(box1);
        wall4->collisionPhysicsBox(box1);//new
        door1wall->collisionPhysicsBox(box1);
        door2wall->collisionPhysicsBox(box1);
        door3wall->collisionPhysicsBox(box1);

        // floor->collisionPhysicsBox(box2);
        // door1wall->collisionPhysicsBox(box2);
        
        // appearing platforms in AND level
        if(lvr->getLeverStatus()&&lvr2->getLeverStatus()&&lvr3->getLeverStatus()&&door1->isOpen()){
            wall5->collisionPhysics(blob);//new
            wall5->collisionPhysicsBox(box1);
            platform4->collisionPhysics(blob);
            platform4->collisionPhysicsBox(box1);
            }
        
        
        


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(SKY);
           
            
            BeginMode2D(camera);
            
            DrawTexture(background, 0,0, WHITE);
            platform1->Draw();
            platform2->Draw();
            platform3->Draw();
            wall2->Draw();
            wall3->Draw();
            wall4->Draw();//new
            if(lvr->getLeverStatus()&&lvr2->getLeverStatus()&&lvr3->getLeverStatus()&&door1->isOpen()){
                wall5->Draw();
                platform4->Draw();
                lvr4->Draw();
            } // appearing platforms in AND level
            floor->Draw();
            door1->Draw();
            door2->Draw();
            door3->Draw();
            door1wall->Draw();
            door2wall->Draw();
            door3wall->Draw();
            
            blob->Draw();
            box1->Draw();
            // box2->Draw();
            lvr->Draw();
            lvr2->Draw();
            lvr3->Draw();
            plt->Draw();
            
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