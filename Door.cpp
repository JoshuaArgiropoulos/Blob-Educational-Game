#include "Door.h"
#include "raylib.h"


// Constructors
Door::Door():Entity(){
    this->open=false;
}

Door::Door(float x, float y, float width, float height, Texture2D texture1, Texture2D texture2):Entity(x,y,width,height,texture){
    this->closedTexture=texture1;
    this->openTexture=texture2;
    this->open=false;
    
}


// Open status mutator and accessor
void Door::setOpen(bool new_status){
    if (this->open != new_status){
        if(new_status) this->setTexture(openTexture);// if new_status is true
        else this->setTexture(closedTexture);
    }
    this->open=new_status;
}
bool Door::isOpen(){
    return this->open;
}

void Door::toggleOpen(){
    if(this->open) this->setOpen(false); 
    else this->setOpen(true);
}

// Player collision physics
void Door::collisionPhysics(Player* p){
    if (!this->isOpen()){
        if (CheckCollisionRecs(p->getRec(), this->getRec())){
            if( p->getXPos()+p->getWidth()/2 < (this->getXPos()+this->getWidth()/2) ) // left side of door
                p->setXPos(this->getXPos()-p->getWidth());
            else if( (this->getXPos()+this->getWidth()/2) < p->getXPos()+p->getWidth()/2) // right side of door
                p->setXPos(this->getXPos()+this->getWidth());
        }
    }
}

