#include "Lever.h"
#include <cmath>

/* Lever::Lever():Entity(){
    this->leverStatus = false;
} */

Lever::Lever(float x, float y, float width, float height, Texture2D texture1, Texture2D texture2):Entity(x,y,width,height,texture){
    this->offTexture = texture1;
    this->onTexture = texture2;
    this->leverStatus = false;
    this->setTexture(offTexture);
}

//Accessors and mutators
bool Lever::getLeverStatus(){
    return this->leverStatus;
}

float Lever::getDistFromUsr(float usrX, float usrY){ 
    return sqrt(pow(this->getXPos() - usrX, 2) + pow(this->getYPos() - usrY, 2));
}

void Lever::physics(Player* p){
    if(this->getDistFromUsr(p->getXPos(), p->getYPos()) < 100.0 && IsKeyPressed(KEY_LEFT_SHIFT)){ // checks distance from user, if close then change the switch this->getDistFromUsr(p->getXPos(), p->getYPos()) < 100 && 

    this->setLeverStatus(); // toggles lever status
}
}

void Lever::setLeverStatus(){
    if(this->getLeverStatus()){  
        this->leverStatus = false;
        this->setTexture(offTexture);
    }
    else{
        this->leverStatus = true;
        this->setTexture(onTexture);
    }
}