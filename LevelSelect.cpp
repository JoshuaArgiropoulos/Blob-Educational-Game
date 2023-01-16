#include "raylib.h"
#include "LevelSelect.h"
#include "LevelTest.h"
#include "LevelFive.h"

// Constructors
LevelSelect::LevelSelect():Level(){
}


// Run
void LevelSelect::Run(){
    // Implement initialization variables
    const int screenWidth = 1280;
    const int screenHeight = 720;    
    
        
    // Image for in game background
    Image bgImage = LoadImage("./../res/levelSelectBack.png");
    ImageResize(&bgImage, bgImage.width, screenHeight+10);
    Texture2D background = LoadTextureFromImage(bgImage);
    

    // Import blob image and create player instances
    Image blobImage = LoadImage("./../res/blob.png");
    ImageResize(&blobImage,120, 80);
    Player * blob = new Player(500,200,blobImage.width,blobImage.height,LoadTextureFromImage(blobImage));
    
    

    // Import Basic platform image and create instance of Entity
    Image floorImage = LoadImage("./../res/floor.png");
    ImageResize(&floorImage,bgImage.width, 60);
    Wall *floor = new Wall(-300,660,floorImage.width, floorImage.height, LoadTextureFromImage(floorImage));

    
    // Moveable Box1!
    Image boxImage = LoadImage("./../res/box.png");
    ImageResize(&boxImage, 50, 50);
    Box *box1 = new Box(3000, floor->getYPos()-boxImage.height-50, boxImage.width, boxImage.height, LoadTextureFromImage(boxImage));
    

    // Level 1 Platform
    Image l1Img=LoadImage("./../res/levelPlat1.png");
    ImageResize(&l1Img,300, 100);
    Platform *level1 = new Platform(1200,450,l1Img.width,l1Img.height, true, LoadTextureFromImage(l1Img));


    // Level 2 Platform
    Image l2Img=LoadImage("./../res/levelPlat2.png");
    ImageResize(&l2Img,300, 100);
    Platform *level2 = new Platform(1700,300,l2Img.width,l2Img.height, true, LoadTextureFromImage(l2Img));
    
    // Level 3 Platform
    Image l3Img=LoadImage("./../res/levelPlat3.png");
    ImageResize(&l3Img,300, 100);
    Platform *level3 = new Platform(2200,480,l3Img.width,l3Img.height, true, LoadTextureFromImage(l3Img));
    
    // Level 4 Platform
    Image l4Img=LoadImage("./../res/levelPlat4.png");
    ImageResize(&l4Img,300, 100);
    Platform *level4 = new Platform(2800,330,l4Img.width,l4Img.height, true, LoadTextureFromImage(l4Img));
    
    // Level 5 Platform
    Image l5Img=LoadImage("./../res/levelPlat5.png");
    ImageResize(&l5Img,300, 100);
    Platform *level5 = new Platform(3575,200,l5Img.width,l5Img.height, true, LoadTextureFromImage(l5Img));
    
    
   
    // Image to idicate going back to home, MAY NOT BE NEEDED
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
        if (IsKeyPressed(KEY_B)){
            box1->toggleHoisted(blob);
        }
        if (IsKeyPressed(KEY_LEFT_ALT)){
            running = false;
            break;
        }
        if (IsKeyPressed(KEY_ENTER)|| IsKeyPressed(KEY_KP_ENTER)){
            if (blob->getYPos()<level1->getYPos()&&blob->getXPos()>level1->getXPos()&&blob->getXPos()+blob->getWidth()<level1->getXPos()+level1->getWidth()){
                LevelTest* leveltest = new LevelTest();
                leveltest->Run();
            }
            else if (blob->getYPos()<level2->getYPos()&&blob->getXPos()>level2->getXPos()&&blob->getXPos()+blob->getWidth()<level2->getXPos()+level2->getWidth()){
                LevelTest* leveltest = new LevelTest();
                leveltest->Run();
            }
            else if(blob->getYPos()<level3->getYPos()&&blob->getXPos()>level3->getXPos()&&blob->getXPos()+blob->getWidth()<level3->getXPos()+level3->getWidth()){
                LevelTest* leveltest = new LevelTest();
                leveltest->Run();
            }
            else if (blob->getYPos()<level4->getYPos()&&blob->getXPos()>level4->getXPos()&&blob->getXPos()+blob->getWidth()<level4->getXPos()+level4->getWidth()){
                LevelTest* leveltest = new LevelTest();
                leveltest->Run();
            }
            else if(blob->getYPos()<level5->getYPos()&&blob->getXPos()>level5->getXPos()&&blob->getXPos()+blob->getWidth()<level5->getXPos()+level5->getWidth()){
                LevelFive* levelfive = new LevelFive();
                levelfive->Run();
            }
        }
        
        // Camera target follows player
        camera.target = (Vector2){blob->getXPos()+100,350};
        camera.zoom += ((float)GetMouseWheelMove()*0.05f);

        if (camera.zoom > 3.0f) camera.zoom = 3.0f;
        else if (camera.zoom < 0.1f) camera.zoom = 0.1f;        
        
        // Falling physics
        blob->physics();
        blob->setJumps(0);
        
        // Box collisions
        box1->physics(blob);
        
        // Platform collisions with Player
        level1->collisionPhysics(blob);
        level2->collisionPhysics(blob);
        level3->collisionPhysics(blob);
        level4->collisionPhysics(blob);
        level5->collisionPhysics(blob);
        
        // Platform collisions with Box
        level1->collisionPhysicsBox(box1);
        level2->collisionPhysicsBox(box1);
        level3->collisionPhysicsBox(box1);
        level4->collisionPhysicsBox(box1);
        level5->collisionPhysicsBox(box1);

        
        // Wall collisions with Player
        floor->collisionPhysics(blob);
        
        // Wall collisions with Box
        floor->collisionPhysicsBox(box1);

        

        // Draw everything to the screen
        
        BeginDrawing();
        
            ClearBackground(SKY);
           
            BeginMode2D(camera);
            
                DrawTexture(background, 0,0, WHITE);
                level1->Draw();
                level2->Draw();
                level3->Draw();
                level4->Draw();
                level5->Draw();
                floor->Draw();
                
                blob->Draw();
                box1->Draw();
            
            EndMode2D();

        EndDrawing();
    }
    // Unload all memory data
   
    //DrawTexture(LoadTextureFromImage(exit), screenWidth/2-200, screenHeight/2-60, WHITE);
    UnloadImage(l1Img);
    UnloadImage(l2Img);
    UnloadImage(l3Img);
    UnloadImage(l4Img);
    UnloadImage(l5Img);
    UnloadImage(blobImage);
    UnloadImage(bgImage);
    UnloadImage(boxImage);
    //UnloadImage(exit);
    
    // Free all objects
    delete blob;
    delete box1;
    delete floor;
    delete level1;
    delete level2;
    delete level3;
    delete level4;
    delete level5;
    return;
}