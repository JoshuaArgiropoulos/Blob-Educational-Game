#include "raylib.h"
#include "Entity.h"
#include "Player.h"
#include "Box.h"

#pragma once

class Wall: public Entity{
        
    public:
        // Constructors
        Wall();
        Wall(float,float,float,float, Texture2D);
        
        // Collision function
        
        void collisionPhysics(Player*);
        void collisionPhysicsBox(Box*);
        
};