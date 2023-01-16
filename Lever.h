#include "raylib.h"
#include "Entity.h"
#include "Player.h"
//#pragma once

class Lever: public Entity{
    private:
        Texture2D offTexture;
        Texture2D onTexture;
        bool leverStatus;
        
    public:
        //Lever();
        Lever(float,float,float,float, Texture2D, Texture2D);
        
        bool getLeverStatus();
        float getDistFromUsr(float, float); // players location
        
        void physics(Player*);
        
        void setLeverStatus();
};