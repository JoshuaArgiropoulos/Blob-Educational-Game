#include "raylib.h"
#include "Entity.h"
#include "Player.h"
#include "Box.h"

#pragma once

class Platform: public Entity{
    private:

        bool passable;
        //bool dropable;
        
    public:
        // Constructors
        Platform();
        Platform(float,float,float,float, bool, Texture2D);
        
        // Position and Speed
        bool getPass();
        void setPass(bool);
        //float getDrop();
        //void setDrop(bool);
        
        void collisionPhysics(Player*);
        void collisionPhysicsBox(Box*);
};