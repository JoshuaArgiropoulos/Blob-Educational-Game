#include "Plate.h"
#include <stdio.h>

Plate::Plate():Entity(){
    this->plateStatus = false;
}

Plate::Plate(float x, float y, float width, float height, Texture2D texture1, Texture2D texture2):Entity(x,y,width,height,texture){
    this->offTexture = texture1;
    this->onTexture = texture2;
    this->plateStatus = false;
    this->setTexture(offTexture);
}

//Accessors and mutators
bool Plate::getPlateStatus(){
    return this->plateStatus;
}

float Plate::getDistFromEnt(float usrX, float usrY){ 
    return sqrt(pow(this->getXPos() + 50 - usrX, 2) + pow(this->getYPos() - usrY, 2));
}

void Plate::setPlateStatus(bool new_status){
        if (this->plateStatus != new_status){
        if(new_status) this->setTexture(onTexture);// if new_status is true
        else this->setTexture(offTexture);
    }
    this->plateStatus=new_status;

}

void Plate::physics(Player* p){
    if(this->getDistFromEnt(p->getXPos()+60, p->getYPos()) < 100.0){
        this->setPlateStatus(true);
    }
}

void Plate::boxPhysics(Box* b){
    if(this->getDistFromEnt(b->getXPos()+25, b->getYPos())<75){
        this->setPlateStatus(true);
    }
}