#include "raylib.h"
#include "MenuButton.h"
#include <vector>
#include "Level.h"
#include "LevelTest.h"
#include "LevelFive.h"
#include "LevelSelect.h"



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
    
    InitAudioDevice();
    Sound buttonPressSound=LoadSound("./../res/sounds/buttonPressed.wav");

    // Image for in game background
    Image mainMenu = LoadImage("./../res/TitlePage.png");
    ImageResize(&mainMenu, screenWidth, screenHeight);
    Texture2D background = LoadTextureFromImage(mainMenu);
    UnloadImage(mainMenu);

    LevelTest* leveltest = new LevelTest();
    LevelSelect* levelselect=new LevelSelect();
    LevelFive* levelfive = new LevelFive();
    
    
   
    Image button=LoadImage("./../res/rec.png");
    ImageResize(&button, 680, 80);
    MenuButton *startButton=new MenuButton(310, 363, button.width, button.height, LoadTextureFromImage(button), leveltest, buttonPressSound);



    ImageResize(&button, 320, 80);
    MenuButton *levelButton=new MenuButton(310, 467, button.width, button.height, LoadTextureFromImage(button), levelselect, buttonPressSound);
    MenuButton *achButton=new MenuButton(662, 467, button.width, button.height, LoadTextureFromImage(button), leveltest, buttonPressSound);
    
    ImageResize(&button, 150, 80);
    MenuButton *profileButton=new MenuButton(1116, 560, button.width, button.height, LoadTextureFromImage(button), levelfive, buttonPressSound);
    UnloadImage(button);
    
    
   
    /* void deleteObjects(){
        delete startButton;
        delete levelButton;
        delete achButton;
        delete profileButton;
    } */
    
    // Main game loop
    
    
    
    while (1)   
    {
        if (!IsKeyPressed(KEY_ESCAPE)&&WindowShouldClose()){
            break;
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            startButton->buttonPressed();
            levelButton->buttonPressed();
            achButton->buttonPressed();
            profileButton->buttonPressed();
        }
        


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(SKY);
           
                        
            DrawTexture(background, 0,0, WHITE);
            startButton->Draw();
            levelButton->Draw();
            achButton->Draw();
            profileButton->Draw();
            
            EndMode2D();


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    StopSoundMulti();
    UnloadSound(buttonPressSound); 
    CloseAudioDevice();
    
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}