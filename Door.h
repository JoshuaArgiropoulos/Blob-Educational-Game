#include "raylib.h"
#include "Entity.h"
#include "Player.h"

#pragma once

class Door: public Entity{
    private:
        Texture2D openTexture;
        Texture2D closedTexture;
        bool open;
        
    public:
        // Constructors
        Door();
        Door(float,float,float,float, Texture2D, Texture2D);
        
        // Open & Closing functions
        void setOpen(bool);
        void toggleOpen();
        bool isOpen();
        
        // Player interaction functions
        void collisionPhysics(Player*);
        
};