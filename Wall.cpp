#include "Wall.h"
#include "raylib.h"
#include "Entity.h"
#include "Player.h"


// Constructors
Wall::Wall():Entity(){
}

Wall::Wall(float x, float y, float width, float height, Texture2D texture):Entity(x,y,width,height,texture){
}


// collision physics interacting with a Player
void Wall::collisionPhysics(Player* p){
    if (CheckCollisionRecs(p->getRec(), this->getRec())){
        if(p->getYPos()+p->getHeight() < this->getYPos()+20 and p->getYSpeed() < 0){
            p->setYPos(this->getYPos()-p->getHeight());
            p->setYSpeed(0);
            //p->setOnGround(true);
            p->addJumps(1);
        }
        else if(p->getYPos() > this->getYPos()+this->getHeight()-15){
            p->setYPos(this->getYPos()+this->getHeight());
            p->setYSpeed(0);
            p->setOnGround(false);
            p->setJumps(0);
        }
        if(p->getXPos() > this->getXPos()+this->getWidth()-10 ){
            p->setXPos(this->getXPos()+this->getWidth());
        }
        else if(p->getXPos()+p->getWidth() < this->getXPos()+10 ){
            p->setXPos(this->getXPos()-p->getWidth());
        }
    }
}

// collision physics interacting with a Box
void Wall::collisionPhysicsBox(Box* p){
    if (CheckCollisionRecs(p->getRec(), this->getRec())){
        if(p->getYPos()+p->getHeight() < this->getYPos()+20 and p->getYSpeed() < 0){
            p->setYPos(this->getYPos()-p->getHeight());
            p->setYSpeed(0);
            p->setOnGround(true);
        }
        else if(p->getYPos() > this->getYPos()+this->getHeight()-15){
            p->setYPos(this->getYPos()+this->getHeight());
            p->setYSpeed(0);
            p->setOnGround(false);
        }
        if(p->getXPos() > this->getXPos()+this->getWidth()-10 ){
            p->setXPos(this->getXPos()+this->getWidth());
        }
        else if(p->getXPos()+p->getWidth() < this->getXPos()+10 ){
            p->setXPos(this->getXPos()-p->getWidth());
        }
    }
}

