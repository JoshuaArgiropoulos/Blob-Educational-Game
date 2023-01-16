#include "raylib.h"
#include "Entity.h"
#include "Player.h"
#include "Box.h"
#include <cmath>
#pragma once

class Plate: public Entity{
    private:
        Texture2D onTexture;
        Texture2D offTexture;
        bool plateStatus;
        
    public:
        Plate();
        Plate(float,float,float,float, Texture2D, Texture2D);
        
        bool getPlateStatus();
        float getDistFromEnt(float, float); // players location
        
        void setPlateStatus(bool);
        
        void physics(Player*);
        void boxPhysics(Box*);
};