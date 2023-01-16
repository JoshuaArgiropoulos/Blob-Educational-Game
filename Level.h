#include "raylib.h"
#include "Entity.h"
#include "Player.h"
#include "Wall.h"
#include "Platform.h"
#include "Door.h"
#include "Plate.h"
#include "Box.h"
#include "Lever.h"

#define SKY (Color){ 202,157,129, 255 }

#pragma once

//Level1 level1instance

//LevelSelected = level1instance

//LevelSelected.Run();

class Level{
    //protected:
        //bool selected;
        
    public:
        //virtual void f() = 0;
    
        Level();
        
        virtual void Run();
            // Init();
            
            // while !WindowShouldClose:
                //Physics();
                //Draw();
            
            // after while loop
                // delete attributes
        
        // Mutators and accessors
        /* void setSelected(bool);
        bool getSelected(); */
};
