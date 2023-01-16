#include "raylib.h"

#pragma once

class Entity{
    protected:
        Texture2D texture;
        Rectangle object;
        
    public:
        Entity();
        Entity(float,float,float,float, Texture2D);
        
        float getXPos();
        void setXPos(float);
        float getYPos();
        void setYPos(float);
        float getWidth();
        void setWidth(float);
        float getHeight();
        void setHeight(float);
        Rectangle getRec();
        
        
        Texture2D getTexture();
        void setTexture(Texture2D);
        
        void Draw();
};
