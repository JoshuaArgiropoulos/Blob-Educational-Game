#include "raylib.h"
#include "Entity.h"
#include "Level.h"

#pragma once

class MenuButton: public Entity{
    private:
        Level *lvl;
        Sound sound;

    public:
        MenuButton();
        MenuButton(float,float,float,float, Texture2D);
        MenuButton(float,float,float,float, Texture2D, Level*, Sound); // Include level as well

        void buttonPressed();
};