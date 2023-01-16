#include "raylib.h"
#include "LevelTest.h"

// Constructors
LevelTest::LevelTest():Level(){
    
}


// Run
void LevelTest::Run(){
    // Implement initialization variables
    const int screenWidth = 1280;
    const int screenHeight = 720;
    
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
   
    ImageResize(&floorImage,450, 60);
    Wall *wall2 = new Wall(100,300,floorImage.width, floorImage.height, LoadTextureFromImage(floorImage));

    
    // Moveable Box1!
    Image boxImage = LoadImage("./../res/box.png");
    ImageResize(&boxImage, 50, 50);
    Box *box1 = new Box(100, floor->getYPos()-boxImage.height-50, boxImage.width, boxImage.height, LoadTextureFromImage(boxImage));
    // Moveable Box2 !
    Box *box2 = new Box(200, floor->getYPos()-boxImage.height-50, boxImage.width, boxImage.height, LoadTextureFromImage(boxImage));
    

    
    // Non solid floating platform
    Image platform_1=LoadImage("./../res/platform3.png");
    ImageResize(&platform_1,300, platform_1.height);
    Platform *platform1 = new Platform(600,500,platform_1.width,platform_1.height, true,  LoadTextureFromImage(platform_1));



    // Import door image and create instance of Door
    Image closedDoorImage = LoadImage("./../res/closed-door.png");
    ImageResize(&closedDoorImage, 50, 100);
    Image openDoorImage = LoadImage("./../res/open-door.png");
    ImageResize(&openDoorImage, 50, 100);
    Door *door1 = new Door(screenWidth-150, 660-closedDoorImage.height, closedDoorImage.width, closedDoorImage.height, LoadTextureFromImage(closedDoorImage), LoadTextureFromImage(openDoorImage));
   
    ImageResize(&floorImage,door1->getWidth(), 50);
    Wall *door1wall = new Wall(door1->getXPos(),door1->getYPos()-floorImage.height, floorImage.width, floorImage.height, LoadTextureFromImage(floorImage));

    door1->setOpen(true);
    


    // Import lever image, on and off
    Image leverOn = LoadImage("./../res/leverOn.png");
    Image leverOff = LoadImage("./../res/leverOff.png");
    ImageResize(&leverOn, 120, 60);
    ImageResize(&leverOff, 120, 60);
    // Create instance of a lever THIS IS A TEST LEVER
    Lever *lvr = new Lever(500.0, floor->getYPos()-leverOff.height, leverOff.width, leverOff.height, LoadTextureFromImage(leverOff), LoadTextureFromImage(leverOn));

    // Import pressure plate on and off
    Image plateOn = LoadImage("./../res/pressurePlateOn.png");
    Image plateOff = LoadImage("./../res/pressurePlateOff.png");
    ImageResize(&plateOn, 100, 10);
    ImageResize(&plateOff, 100, 10);
    
    Plate * plt = new Plate(1000, 650, plateOff.width,plateOff.height,LoadTextureFromImage(plateOff), LoadTextureFromImage(plateOn));
    //Platform* platforms[numPlatforms] = {platform1, platform2, floor}; 
    
    Image exit = LoadImage("./../res/exit.png");
    ImageResize(&exit, 400, 120);    
    

    // camera setup
    Camera2D  camera = {0};
    camera.target = (Vector2){blob->getXPos()+200,blob->getYPos()};
    camera.offset = (Vector2){ screenWidth/2, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    
    bool running = true;
    
    while(running){
    
    // Physics
        // Run game physics and/or logic
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
        }
        if (IsKeyPressed(KEY_B)){
            box1->toggleHoisted(blob);
            box2->toggleHoisted(blob);
        }
        if (IsKeyPressed(KEY_LEFT_ALT)){
            running = false;
            break;
        }
        
        // Camera target follows player
        camera.target = (Vector2){blob->getXPos()+100,350};
        camera.zoom += ((float)GetMouseWheelMove()*0.05f);

        if (camera.zoom > 3.0f) camera.zoom = 3.0f;
        else if (camera.zoom < 0.1f) camera.zoom = 0.1f;
        
        lvr->physics(blob);

        plt->setPlateStatus(false);
        plt->boxPhysics(box1);
        plt->boxPhysics(box2);
        plt->physics(blob);
        
        
        // Falling physics
        blob->physics();
        blob->setJumps(0);
        
        // Check for door collisions
        door1->collisionPhysics(blob);
        
        // Box collisions
        box1->physics(blob);
        box2->physics(blob);
        
        // Platform collisions with Player
        platform1->collisionPhysics(blob);
        
        // Platform collisions with Box
        platform1->collisionPhysicsBox(box1);
        platform1->collisionPhysicsBox(box2);
        
        // Wall collisions with Player
        floor->collisionPhysics(blob);
        wall2->collisionPhysics(blob);
        door1wall->collisionPhysics(blob);
        
        // Wall collisions with Box
        floor->collisionPhysicsBox(box1);
        wall2->collisionPhysicsBox(box1);
        door1wall->collisionPhysicsBox(box1);
        floor->collisionPhysicsBox(box2);
        wall2->collisionPhysicsBox(box2);
        door1wall->collisionPhysicsBox(box2);
        

        // Draw everything to the screen
        
        BeginDrawing();
        
            ClearBackground(SKY);
           
            BeginMode2D(camera);
            
                DrawTexture(background, 0,0, WHITE);
                platform1->Draw();
                wall2->Draw();
                floor->Draw();
                door1->Draw();
                door1wall->Draw();
                
                blob->Draw();
                box1->Draw();
                box2->Draw();
                lvr->Draw();
                plt->Draw();
            
            EndMode2D();

        EndDrawing();
    }
    // Unload all memory data
    
    
       
    DrawTexture(LoadTextureFromImage(exit), screenWidth/2-200, screenHeight/2-60, WHITE);
    
    UnloadImage(floorImage);
    UnloadImage(platform_1);
    UnloadImage(blobImage);
    UnloadImage(bgImage);
    UnloadImage(leverOn);
    UnloadImage(leverOff);
    UnloadImage(plateOn);
    UnloadImage(plateOff);
    UnloadImage(boxImage);
    UnloadImage(openDoorImage);
    UnloadImage(closedDoorImage);
    //UnloadImage(exit);
    
    // Free all objects
    delete blob;
    delete box1;
    delete box2;
    delete lvr;
    delete plt;
    delete floor;
    delete platform1;
    delete wall2;
    delete door1wall;
    delete door1;
    
    
    
}