#include "raylib.h"
#include "Entity.h"
//#include "Platform.h"
#include <vector>

#pragma once


class Player: public Entity{
    private:

        float speed_x;
        float speed_y;
        int jumps = 0;
        bool onGround;
        bool falling;
        bool holding_something;
        Sound jumpSound;
        
        //std::vector<Platform> platforms;
        
    public:
        // Constructors
        Player();
        Player(float,float,float,float, Texture2D);
        
        // Position and Speed
        float getXSpeed();
        void setXSpeed(float x);
        float getYSpeed();
        void setYSpeed(float y);
        float getPlayerHeight();
        
        bool isOnGround();
        void setOnGround(bool);
        
        // Movement
        void moveRight();
        void moveLeft();
        void jump();
        int  getJumps();
        void addJumps(int);
        void setJumps(int);
        void physics(); 
        
/*         // Platform collision
        void platformCollision();
        void addPlatform(Platform*); */
        
        // holding stuff
        void setHoldingSomething(bool);
        bool getHoldingSomething();
};