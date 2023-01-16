#include "raylib.h"
#include "LevelFive.h"

// Constructors
LevelFive::LevelFive():Level(){
}


// Run
void LevelFive::Run(){
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 720;
    
    // Image for in game background
    Image bgImage = LoadImage("./../res/level5Background.png");
    ImageResize(&bgImage, bgImage.width, screenHeight);
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
    // Door image
    Image closedDoorImage = LoadImage("./../res/closed-door.png");
    ImageResize(&closedDoorImage, 50, 100);
    Image openDoorImage = LoadImage("./../res/open-door.png");
    ImageResize(&openDoorImage, 50, 100);
    // Import lever image, on and off
    Image leverOn = LoadImage("./../res/leverOn.png");
    Image leverOff = LoadImage("./../res/leverOff.png");
    ImageResize(&leverOn, 120, 60);
    ImageResize(&leverOff, 120, 60);
    // Import pressure plate on and off
    Image plateOn = LoadImage("./../res/pressurePlateOn.png");
    Image plateOff = LoadImage("./../res/pressurePlateOff.png");
    ImageResize(&plateOn, 100, 10);
    ImageResize(&plateOff, 100, 10);
    // Import box image
    Image boxImage = LoadImage("./../res/box.png");
    ImageResize(&boxImage, 50, 50);
    
    Player * blob = new Player(400,200,blobImage.width,blobImage.height,LoadTextureFromImage(blobImage));
   
    //Creates the floor of the level, x coords, y coords, length, height
    //ImageResize(&floorImage,5000, 60); // controlls the length of the main floor
    Wall *floor = new Wall(0,660,floorImage.width, floorImage.height, LoadTextureFromImage(floorImage));
    
    // Doors
    Door *door1 = new Door(1400, floor->getYPos()-closedDoorImage.height, closedDoorImage.width, closedDoorImage.height, LoadTextureFromImage(closedDoorImage), LoadTextureFromImage(openDoorImage));
    Door *door2 = new Door(2500, floor->getYPos()-closedDoorImage.height, closedDoorImage.width, closedDoorImage.height, LoadTextureFromImage(closedDoorImage), LoadTextureFromImage(openDoorImage));
    Door *door3 = new Door(3600, floor->getYPos()-closedDoorImage.height, closedDoorImage.width, closedDoorImage.height, LoadTextureFromImage(closedDoorImage), LoadTextureFromImage(openDoorImage));
    door1->setOpen(true);
    door2->setOpen(true);
    door3->setOpen(true);

    
    // Platforms
     Platform *platform1 = new Platform(door1->getXPos()+50,430,platformImage.width, platformImage.height, true, LoadTextureFromImage(platformImage));
        

    // Moveable Box
    Box *box1 = new Box(door1->getXPos()+100, door1->getYPos(), boxImage.width, boxImage.height, LoadTextureFromImage(boxImage));
    Box *box2 = new Box(door1->getXPos()+120, platform1->getYPos()-boxImage.height-50, boxImage.width, boxImage.height, LoadTextureFromImage(boxImage));
    Box *box3 = new Box(3500, floor->getYPos()-boxImage.height-50, boxImage.width, boxImage.height, LoadTextureFromImage(boxImage));

    // Plates
    Plate *plt1 = new Plate(2000, floor->getYPos()-plateOff.height, plateOff.width,plateOff.height,LoadTextureFromImage(plateOff),LoadTextureFromImage(plateOn));
    Plate *plt2 = new Plate(2300, floor->getYPos()-plateOff.height, plateOff.width,plateOff.height,LoadTextureFromImage(plateOff),LoadTextureFromImage(plateOn));
    Plate *plt3 = new Plate(3000, floor->getYPos()-plateOff.height, plateOff.width,plateOff.height,LoadTextureFromImage(plateOff),LoadTextureFromImage(plateOn));
    // Walls
    ImageResize(&floorImage,door1->getWidth(), 400); // Wall dimensions
    Wall *wall1 = new Wall(door1->getXPos(), door1->getYPos()-400, floorImage.width, 400, LoadTextureFromImage(floorImage)); //door1->getYPos()-floorImage.height-200     floorImage.height+200
    Wall *wall2 = new Wall(door2->getXPos(), door2->getYPos()-400, floorImage.width, 400, LoadTextureFromImage(floorImage));
    Wall *wall3 = new Wall(door3->getXPos(), door3->getYPos()-400, floorImage.width, 400, LoadTextureFromImage(floorImage));
    //ImageResize(&floorImage,platformImage.width, floor->getYPos()-200);
    //Wall *wall2 = new Wall(2350,200,platformImage.width, floor->getYPos()-200, LoadTextureFromImage(floorImage));
    
    // Levers
    Lever *lvr1 = new Lever(400, floor->getYPos()-leverOff.height, leverOff.width, leverOff.height, LoadTextureFromImage(leverOff), LoadTextureFromImage(leverOn));
    Lever *lvr2 = new Lever(600, floor->getYPos()-leverOff.height, leverOff.width, leverOff.height, LoadTextureFromImage(leverOff), LoadTextureFromImage(leverOn));
    Lever *lvr3 = new Lever(800, floor->getYPos()-leverOff.height, leverOff.width, leverOff.height, LoadTextureFromImage(leverOff), LoadTextureFromImage(leverOn));
    Lever *lvr4 = new Lever(1000, floor->getYPos()-leverOff.height, leverOff.width, leverOff.height, LoadTextureFromImage(leverOff), LoadTextureFromImage(leverOn));
    Lever *lvr5 = new Lever(2800, floor->getYPos()-leverOff.height, leverOff.width, leverOff.height, LoadTextureFromImage(leverOff), LoadTextureFromImage(leverOn));
    Lever *lvr6 = new Lever(3200, floor->getYPos()-leverOff.height, leverOff.width, leverOff.height, LoadTextureFromImage(leverOff), LoadTextureFromImage(leverOn));
    
    // camera setup
    Camera2D  camera = {0};
    camera.target = (Vector2){blob->getXPos()+200,blob->getYPos()};
    camera.offset = (Vector2){ screenWidth/2, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    int count = 0;
    // Main game loop
    bool running = true;
    while (running)    // Detect window close button or ESC key
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
        if (IsKeyPressed(KEY_LEFT_ALT)){
            running = false;
            break;
        }
        
        //if (IsKeyPressed(KEY_O)){
          //  door1->toggleOpen();
        //}
        
        if(lvr1->getLeverStatus()&&!lvr2->getLeverStatus()&&lvr3->getLeverStatus()&&lvr4->getLeverStatus()&&!door1->isOpen()){
            door1->toggleOpen();
        }
        else if((!lvr1->getLeverStatus()||lvr2->getLeverStatus()||!lvr3->getLeverStatus()||!lvr4->getLeverStatus())&&door1->isOpen())
            door1->toggleOpen();
        
        if(plt1->getPlateStatus()&&plt2->getPlateStatus()&&!door2->isOpen()){
            door2->toggleOpen();
        }
        else if((!plt1->getPlateStatus()||!plt2->getPlateStatus())&&door2->isOpen())
            door2->toggleOpen();
        
        if(plt3->getPlateStatus()&&count == -4&&!door3->isOpen()){
            door3->toggleOpen();
        }
        else if((!plt3->getPlateStatus()||count != -4)&&door3->isOpen())
            door3->toggleOpen();
        
        
        if (IsKeyPressed(KEY_B)){
            box1->toggleHoisted(blob);
            box2->toggleHoisted(blob);
            box3->toggleHoisted(blob);
        }
        
        // Camera target follows player
        camera.target = (Vector2){blob->getXPos()+100,350};
        camera.zoom += ((float)GetMouseWheelMove()*0.05f);

        if (camera.zoom > 3.0f) camera.zoom = 3.0f;
        else if (camera.zoom < 0.1f) camera.zoom = 0.1f;
        
        // if(lvr1->getDistFromUsr(blob->getXPos(), blob->getYPos()) < 100.0 && IsKeyPressed(KEY_LEFT_SHIFT)){ // checks distance from user, if close then change the switch lvr1->getDistFromUsr(blob->getXPos(), blob->getYPos()) < 100 && 
        //     if(lvr1->getLeverStatus())
        //         lvr1->setTexture(LoadTextureFromImage(leverOff));
        //     else
        //         lvr1->setTexture(LoadTextureFromImage(leverOn));
        //     lvr1->setLeverStatus(); // toggles lever status
        // }
        // if(lvr2->getDistFromUsr(blob->getXPos(), blob->getYPos()) < 100.0 && IsKeyPressed(KEY_LEFT_SHIFT)){ // checks distance from user, if close then change the switch lvr2->getDistFromUsr(blob->getXPos(), blob->getYPos()) < 100 && 
        //     if(lvr2->getLeverStatus())
        //         lvr2->setTexture(LoadTextureFromImage(leverOff));
        //     else
        //         lvr2->setTexture(LoadTextureFromImage(leverOn));
        //     lvr2->setLeverStatus(); // toggles lever status
        // }
        // if(lvr3->getDistFromUsr(blob->getXPos(), blob->getYPos()) < 100.0 && IsKeyPressed(KEY_LEFT_SHIFT)){ // checks distance from user, if close then change the switch lvr3->getDistFromUsr(blob->getXPos(), blob->getYPos()) < 100 && 
        //     if(lvr3->getLeverStatus())
        //         lvr3->setTexture(LoadTextureFromImage(leverOff));
        //     else
        //         lvr3->setTexture(LoadTextureFromImage(leverOn));
        //     lvr3->setLeverStatus(); // toggles lever status
        // }
        // if(lvr4->getDistFromUsr(blob->getXPos(), blob->getYPos()) < 100.0 && IsKeyPressed(KEY_LEFT_SHIFT)){ // checks distance from user, if close then change the switch lvr4->getDistFromUsr(blob->getXPos(), blob->getYPos()) < 100 && 
        //     if(lvr4->getLeverStatus())
        //         lvr4->setTexture(LoadTextureFromImage(leverOff));
        //     else
        //         lvr4->setTexture(LoadTextureFromImage(leverOn));
        //     lvr4->setLeverStatus(); // toggles lever status
        // }
        lvr1->physics(blob);
        lvr2->physics(blob);
        lvr3->physics(blob);
        lvr4->physics(blob);
        //lvr5->physics(blob);
        //lvr6->physics(blob);

        if(lvr5->getDistFromUsr(blob->getXPos(), blob->getYPos()) < 100.0 && IsKeyPressed(KEY_LEFT_SHIFT)){ // checks distance from user, if close then change the switch lvr5->getDistFromUsr(blob->getXPos(), blob->getYPos()) < 100 && 
            lvr5->physics(blob);
            if(lvr5->getLeverStatus()){
                
                if(count > -5)
                    count--;
            }
        }
        if(lvr6->getDistFromUsr(blob->getXPos(), blob->getYPos()) < 100.0 && IsKeyPressed(KEY_LEFT_SHIFT)){ // checks distance from user, if close then change the switch lvr6->getDistFromUsr(blob->getXPos(), blob->getYPos()) < 100 && 
            lvr6->physics(blob);
            if(lvr6->getLeverStatus()){
                if(count < 5)
                    count++;
            }
        }
        
        // if(plt1->getDistFromEnt(blob->getXPos()+60, blob->getYPos()) < 100.0 || plt1->getDistFromEnt(box1->getXPos()+25, box1->getYPos()) < 75.0 || plt1->getDistFromEnt(box2->getXPos()+25, box2->getYPos()) < 75.0|| plt1->getDistFromEnt(box3->getXPos()+25, box3->getYPos()) < 75.0){
        //     if(!plt1->getPlateStatus()){
        //         plt1->setTexture(LoadTextureFromImage(plateOn));
        //         plt1->setPlateStatus(); // toggles lever status
        //     }
        // }
        // else{
        //     if(plt1->getPlateStatus()){
        //         plt1->setTexture(LoadTextureFromImage(plateOff));
        //         plt1->setPlateStatus(); // toggles lever status
        //     }
        // }
        // if(plt2->getDistFromEnt(blob->getXPos()+60, blob->getYPos()) < 100.0 || plt2->getDistFromEnt(box1->getXPos()+25, box1->getYPos()) < 75.0 || plt2->getDistFromEnt(box2->getXPos()+25, box2->getYPos()) < 75.0|| plt2->getDistFromEnt(box3->getXPos()+25, box3->getYPos()) < 75.0){
        //     if(!plt2->getPlateStatus()){
        //         plt2->setTexture(LoadTextureFromImage(plateOn));
        //         plt2->setPlateStatus(); // toggles lever status
        //     }
        // }
        // else{
        //     if(plt2->getPlateStatus()){
        //         plt2->setTexture(LoadTextureFromImage(plateOff));
        //         plt2->setPlateStatus(); // toggles lever status
        //     }
        // }
        // if(plt3->getDistFromEnt(blob->getXPos()+60, blob->getYPos()) < 100.0 || plt3->getDistFromEnt(box1->getXPos()+25, box1->getYPos()) < 75.0 || plt3->getDistFromEnt(box2->getXPos()+25, box2->getYPos()) < 75.0|| plt3->getDistFromEnt(box3->getXPos()+25, box3->getYPos()) < 75.0){
        //     if(!plt3->getPlateStatus()){
        //         plt3->setTexture(LoadTextureFromImage(plateOn));
        //         plt3->setPlateStatus(); // toggles lever status
        //     }
        // }
        // else{
        //     if(plt3->getPlateStatus()){
        //         plt3->setTexture(LoadTextureFromImage(plateOff));
        //         plt3->setPlateStatus(); // toggles lever status
        //     }
        // }
        plt1->setPlateStatus(false);
        plt2->setPlateStatus(false);
        plt3->setPlateStatus(false);
        
        plt1->boxPhysics(box1);
        plt1->boxPhysics(box2);
        plt1->boxPhysics(box3);
        
        plt2->boxPhysics(box1);
        plt2->boxPhysics(box2);
        plt2->boxPhysics(box3);
        
        plt3->boxPhysics(box1);
        plt3->boxPhysics(box2);
        plt3->boxPhysics(box3);
        
        plt1->physics(blob);
        plt2->physics(blob);
        plt3->physics(blob);
        
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
        box3->physics(blob);     
        
        // // Platform collisions with Player
         platform1->collisionPhysics(blob);

        // Platform collisions with Box
         platform1->collisionPhysicsBox(box1);
         platform1->collisionPhysicsBox(box2);
         platform1->collisionPhysicsBox(box3);
        
        // Wall collisions with Player
        floor->collisionPhysics(blob);
        wall1->collisionPhysics(blob);
        wall2->collisionPhysics(blob);
        wall3->collisionPhysics(blob);
        
        
        // Wall collisions with Box
        floor->collisionPhysicsBox(box1);
        floor->collisionPhysicsBox(box2);
        floor->collisionPhysicsBox(box3);
        wall1->collisionPhysicsBox(box1);
        wall1->collisionPhysicsBox(box2);
        wall1->collisionPhysicsBox(box3);
        wall2->collisionPhysicsBox(box1);
        wall2->collisionPhysicsBox(box2);
        wall2->collisionPhysicsBox(box3);
        wall3->collisionPhysicsBox(box1);
        wall3->collisionPhysicsBox(box2);
        wall3->collisionPhysicsBox(box3);
        
        if(blob->getXPos()>bgImage.width-250) running = false;
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(SKY);
            
            BeginMode2D(camera);
            
            DrawTexture(background, 0,0, WHITE);
            
            floor->Draw();
            
            
            platform1->Draw();
            // platform2->Draw();
            // platform3->Draw();
            // platform4->Draw();
            // platform5->Draw();
            // platform6->Draw();
            // platform7->Draw();
            // platform8->Draw();
            
            wall1->Draw();
            wall2->Draw();
            wall3->Draw();
            
            door1->Draw();
            door2->Draw();
            door3->Draw();
            
            box1->Draw();
            box2->Draw();
            box3->Draw();
            
            lvr1->Draw();
            lvr2->Draw();
            lvr3->Draw();
            lvr4->Draw();
            lvr5->Draw();
            lvr6->Draw();
            
           if(lvr1->getLeverStatus()&&lvr2->getLeverStatus()&&lvr3->getLeverStatus()&&lvr4->getLeverStatus())
                DrawText("Value = 15", 650, 250, 50, WHITE);
            else if(lvr1->getLeverStatus()&&lvr2->getLeverStatus()&&lvr3->getLeverStatus()&&!lvr4->getLeverStatus())
                DrawText("Value = 14", 650, 250, 50, WHITE);
            else if(lvr1->getLeverStatus()&&lvr2->getLeverStatus()&&!lvr3->getLeverStatus()&&lvr4->getLeverStatus())
                DrawText("Value = 13", 650, 250, 50, WHITE);
            else if(lvr1->getLeverStatus()&&lvr2->getLeverStatus()&&!lvr3->getLeverStatus()&&!lvr4->getLeverStatus())
                DrawText("Value = 12", 650, 250, 50, WHITE);
            else if(lvr1->getLeverStatus()&&!lvr2->getLeverStatus()&&lvr3->getLeverStatus()&&lvr4->getLeverStatus())
                DrawText("Value = 11", 650, 250, 50, WHITE);
            else if(lvr1->getLeverStatus()&&!lvr2->getLeverStatus()&&lvr3->getLeverStatus()&&!lvr4->getLeverStatus())
                DrawText("Value = 10", 650, 250, 50, WHITE);
            else if(lvr1->getLeverStatus()&&!lvr2->getLeverStatus()&&!lvr3->getLeverStatus()&&lvr4->getLeverStatus())
                DrawText("Value = 9", 650, 250, 50, WHITE);
            else if(lvr1->getLeverStatus()&&!lvr2->getLeverStatus()&&!lvr3->getLeverStatus()&&!lvr4->getLeverStatus())
                DrawText("Value = 8", 650, 250, 50, WHITE);
            else if(!lvr1->getLeverStatus()&&lvr2->getLeverStatus()&&lvr3->getLeverStatus()&&lvr4->getLeverStatus())
                DrawText("Value = 7", 650, 250, 50, WHITE);
            else if(!lvr1->getLeverStatus()&&lvr2->getLeverStatus()&&lvr3->getLeverStatus()&&!lvr4->getLeverStatus())
                DrawText("Value = 6", 650, 250, 50, WHITE);
            else if(!lvr1->getLeverStatus()&&lvr2->getLeverStatus()&&!lvr3->getLeverStatus()&&lvr4->getLeverStatus())
                DrawText("Value = 5", 650, 250, 50, WHITE);
            else if(!lvr1->getLeverStatus()&&lvr2->getLeverStatus()&&!lvr3->getLeverStatus()&&!lvr4->getLeverStatus())
                DrawText("Value = 4", 650, 250, 50, WHITE);
            else if(!lvr1->getLeverStatus()&&!lvr2->getLeverStatus()&&lvr3->getLeverStatus()&&lvr4->getLeverStatus())
                DrawText("Value = 3", 650, 250, 50, WHITE);
            else if(!lvr1->getLeverStatus()&&!lvr2->getLeverStatus()&&lvr3->getLeverStatus()&&!lvr4->getLeverStatus())
                DrawText("Value = 2", 650, 250, 50, WHITE);
            else if(!lvr1->getLeverStatus()&&!lvr2->getLeverStatus()&&!lvr3->getLeverStatus()&&lvr4->getLeverStatus())
                DrawText("Value = 1", 650, 250, 50, WHITE);
            else
                DrawText("Value = 0", 650, 250, 50, WHITE);
            
            switch(count){
                case -5:
                    DrawText("Value = -5", 2900, 500, 50, WHITE);
                break;
                case -4:
                    DrawText("Value = -4", 2900, 500, 50, WHITE);
                break;
                case -3:
                    DrawText("Value = -3", 2900, 500, 50, WHITE);
                break;
                case -2:
                    DrawText("Value = -2", 2900, 500, 50, WHITE);
                break;
                case -1:
                    DrawText("Value = -1", 2900, 500, 50, WHITE);
                break;
                case 1:
                    DrawText("Value = 1", 2900, 500, 50, WHITE);
                break;
                case 2:
                    DrawText("Value = 2", 2900, 500, 50, WHITE);
                break;
                case 3:
                    DrawText("Value = 3", 2900, 500, 50, WHITE);
                break;
                case 4:
                    DrawText("Value = 4", 2900, 500, 50, WHITE);
                break;
                case 5:
                    DrawText("Value = 5", 2900, 500, 50, WHITE);
                break;
                default:
                    DrawText("Value = 0", 2900, 500, 50, WHITE);
            }
            
            
            plt1->Draw();
            plt2->Draw();
            plt3->Draw();
            
            DrawText("11", 1412, 375, 50, WHITE);
            DrawText("-", 2820, 500, 50, WHITE);
            DrawText("+", 3220, 500, 50, WHITE);
            DrawText("-4", 3600, 375, 50, WHITE);
            
            blob->Draw();
            
            EndMode2D();
            
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
    
    
    delete floor;
    delete door1;
    delete door2;
    delete door3;
    delete box1;
    delete box2;
    delete box3;
    delete plt1;
    delete plt2;
    delete plt3;
    delete wall1;
    delete wall2;
    delete wall3;
    delete lvr1;
    delete lvr2;
    delete lvr3;
    delete lvr4;
    delete lvr5;
    delete lvr6;
    delete platform1;
    
    UnloadImage(bgImage);
    UnloadImage(blobImage);
    UnloadImage(platformImage);
    UnloadImage(floorImage);
    UnloadImage(closedDoorImage);
    UnloadImage(openDoorImage);
    UnloadImage(plateOff);
    UnloadImage(plateOn);
    UnloadImage(leverOff);
    UnloadImage(leverOn);
    UnloadImage(boxImage);

    return;
    
}