#include "Player.h"
#include <vector>


// Constructors
Player::Player():Entity(){
    this->onGround=true;
    this->speed_x=8;
    this->speed_y=0;
    this->holding_something = false;
}

Player::Player(float x, float y, float width, float height, Texture2D texture):Entity(x,y,width,height,texture){
    this->speed_x=8;
    this->speed_y=0;
    this->onGround=true;
    this->holding_something = false;
}



// Position and Speed Accessors and Mutators
float Player::getXSpeed(){
    return this->speed_x;
}
void Player::setXSpeed(float x){
    this->speed_x=x;
}
float Player::getYSpeed(){
    return this->speed_y;
}
void Player::setYSpeed(float y){
    this->speed_y=y;
}

bool Player::isOnGround(){
    return this->onGround;
}
void Player::setOnGround(bool flag){
    this->onGround=flag;
}
float Player::getPlayerHeight(){
    return (this->getHeight()); // Offset for shadow
}

// Movement
void Player::moveRight(){
   this->setXPos(this->getXPos()+this->speed_x);
}

void Player::moveLeft(){
   this->setXPos(this->getXPos()-this->speed_x);
}

void Player::jump(){
    if (this->getJumps()>0){
        this->speed_y=16;
        this->setOnGround(false);
        this->addJumps( -1 );
    }
}

int Player::getJumps(){
    return this->jumps;
}

void Player::addJumps(int n){
    this->jumps += n;
}
void Player::setJumps(int n){
    this->jumps = n;
}

void Player::physics(){
    if (!this->isOnGround()){
        if(speed_y>-20) this->speed_y-= 0.6;
        this->setYPos(this->getYPos()-this->speed_y);
    }

    if (this->getYPos()>3000 || this->getXPos()<-400 ){
        this->setYPos(200);
        this->setXPos(600);
        this->setYSpeed(0);
    }    
    
    //this->platformCollision();
        
}

/* void Player::addPlatform(Platform* plat){
    platforms.push_back(*plat);
}

void Player::platformCollision(){
    int hitPlatform=-1;
    int i=0;
    for(i=0; i<this->platforms.size(); i++){
        if (CheckCollisionRecs(this->getRec(), platforms.at(i).getRec())){
            if ((this->getYSpeed()<0) && ((this->getYPos()+this->getPlayerHeight()) < platforms.at(i).getYPos()+20)){ // Approaching from top
                hitPlatform=i;
            }
        }
    }
    
    if (hitPlatform>-1){
        this->setYPos(platforms.at(hitPlatform).getYPos()-this->getPlayerHeight());
        this->setYSpeed(0);
        this->setOnGround(true);
    }
    else{
        this->setOnGround(false);
    }
} */

void Player::setHoldingSomething(bool b){
    this->holding_something = b;
}
bool Player::getHoldingSomething(){
    return this->holding_something;
}



