#include "Platform.h"
#include "raylib.h"

Platform::Platform():Entity(){
    this->passable=true;
    //this->dropable=true;

}

Platform::Platform(float x, float y, float width, float height, bool passable, Texture2D texture):Entity(x,y,width,height,texture){
    this->passable=passable;
    //this->dropable=passable;
}

bool Platform::getPass(){
    return this->passable;
}
void Platform::setPass(bool flag){
    this->passable=flag;
}

// bool Platform::getDrop(){
    // return this->dropable;
// }
// void Platform::setDrop(bool flag){
    // this->dropable=flag;
// }

 void Platform::collisionPhysics(Player* p){
    if (CheckCollisionRecs(p->getRec(), this->getRec())){
        if(!p->isOnGround()){
            if ((p->getYSpeed()<0) && ((p->getYPos()+p->getHeight())<this->getYPos()+20) && !(IsKeyDown(KEY_S))){ // Approaching from top
                p->setYSpeed(0);
                //p->setOnGround(true);
                p->addJumps(1);
                p->setYPos(this->getYPos()-p->getHeight());
            }
        }
    }
          else if (!CheckCollisionRecs(p->getRec(), this->getRec())){
        p->setOnGround(false);
    }   
}

 void Platform::collisionPhysicsBox(Box* p){
    if (CheckCollisionRecs(p->getRec(), this->getRec())){
        if(!p->getOnGround()){
            if ((p->getYSpeed()<0) && ((p->getYPos()+p->getHeight())<this->getYPos()+20)){ // Approaching from top
                p->setYSpeed(0);
                //p->setOnGround(true);
                p->setYPos(this->getYPos()-p->getHeight());
            }
        }
    }
          else if (!CheckCollisionRecs(p->getRec(), this->getRec())){
        p->setOnGround(false);
    }   
}