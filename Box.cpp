#include "Box.h"
#include "Player.h"
#include <cmath>

/*

vector<Box> boxesv;

Box createBox(){
    return Box
}

Box box1 = new Box()

boxesv.push_back(box1);

for(i = 0 to boxesv.size()){
    box = new Box()
    boxesv.push_back(box)
}

*/

// Constructors
Box::Box():Entity(){
    this->hoisted=false;
    this->speed_y = 0;
}

Box::Box(float x, float y, float width, float height, Texture2D texture):Entity(x,y,width,height,texture){
    this->hoisted=false;
    this->speed_y = 0;
}


// Open status mutator and accessor
void Box::physics(Player* p){
    if(this->getHoisted()){
        // set x and y pos to match player with offset
        this->setYSpeed(0);
        this->setXPos(p->getXPos()+p->getWidth()/2-this->getWidth()/2); // middle of box = middle of player
        this->setYPos(p->getYPos()-this->getHeight()-5);
    }
    else if (CheckCollisionRecs(p->getRec(), this->getRec())){
        if(p->getYPos()+p->getHeight() < this->getYPos()+20 and p->getYSpeed() < 0){
            p->setYPos(this->getYPos()-p->getHeight());
            p->setYSpeed(0);
            //p->setOnGround(true);
            p->addJumps(1);
        }
/*         else if(p->getYPos() > this->getYPos()+this->getHeight()-15){
            p->setYPos(this->getYPos()+this->getHeight());
            p->setYSpeed(0);
            p->setOnGround(false);
            p->setJumps(0);
        } */
        if(p->getXPos() > this->getXPos()+this->getWidth()-10 ){
            this->setXPos(this->getXPos()-p->getXSpeed()/2);
            p->setXPos(this->getXPos()+this->getWidth());
        }
        else if(p->getXPos()+p->getWidth() < this->getXPos()+10 ){
            this->setXPos(this->getXPos()+p->getXSpeed()/2);
            p->setXPos(this->getXPos()-p->getWidth());
        }
        
    }
    if(!this->getHoisted()){
        this->speed_y-= 0.6;
        this->setYPos(this->getYPos()-this->speed_y);
    }

}

// Hoist functions
bool Box::getHoisted(){
    return this->hoisted;
}

void Box::toggleHoisted(Player* p){
    if(distFrom(p->getXPos()+p->getWidth()/2, p->getYPos()+p->getHeight()/2) < 150){
        if(!p->getHoldingSomething()){
            p->setHoldingSomething(true);
            this->hoisted = true;
        }
        else{
            this->hoisted = false;
            p->setHoldingSomething(false);
        }
    }

}

float Box::distFrom(float usrX, float usrY){ 
    return sqrt(pow(this->getXPos() - usrX, 2) + pow(this->getYPos() - usrY, 2));
}

// Y Speed functions
void Box::setYSpeed(float f){
    this->speed_y = f;
}
float Box::getYSpeed(){
    return this->speed_y;
}
void Box::setOnGround(bool b){
    this->onGround = b;
}
bool Box::getOnGround(){
    return this->onGround;
}

