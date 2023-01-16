#include "raylib.h"
#include "Entity.h"
#include "Player.h"

#pragma once

class Box: public Entity{
        
    private:
        float speed_y;
        bool hoisted;
        bool onGround;
        
    public:
        // Constructors
        Box();
        Box(float,float,float,float, Texture2D);
        
        // Collision and physics function
        
        void physics(Player*);
        
        // Accessors and Mutators
        
        // Hoist functions
        bool getHoisted();
        void toggleHoisted(Player*);
        float distFrom(float, float);
        
        // Y Speed
        void    setYSpeed(float);
        float   getYSpeed();
        void    setOnGround(bool);
        bool    getOnGround();
        
        
        
};