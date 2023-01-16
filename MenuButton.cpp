#include "raylib.h"
#include "MenuButton.h"
#include "Level.h"
MenuButton::MenuButton():Entity(){
}

MenuButton::MenuButton(float x, float y, float width, float height, Texture2D texture):Entity(x,y,width,height,texture){
}

MenuButton::MenuButton(float x, float y, float width, float height, Texture2D texture, Level *lvl, Sound sound):Entity(x,y,width,height,texture){
    this->lvl=lvl;
    this->sound=sound;
}

void MenuButton::buttonPressed(){
    if ((GetMouseX()>this->getXPos() && GetMouseX()<this->getXPos()+this->getWidth())&&(GetMouseY()>this->getYPos() && GetMouseY()<this->getYPos()+this->getHeight())){
        PlaySoundMulti(this->sound);
        lvl->Run();
    } 
}