#include "raylib.h"
#include "Level.h"

#pragma once

//Level1 level1instance

//LevelSelected = level1instance

//LevelSelected.Run();

class LevelTest: public Level{
        
    public:
    
        LevelTest();
        
        virtual void Run();
        
            // Init();
            
            // while !WindowShouldClose:
                //Physics();
                //Draw();
            
            // after while loop
                // delete attributes
        
/*         void Init();
        void Physics();
        void Draw();
        void Close(); */
        
};
