#include "Entity.h"
#include "raylib.h"

// Constructors
Entity::Entity(){
    this->object ={(float)0,(float)0,(float)40,(float)10};
    this->texture=LoadTextureFromImage(LoadImage("./../res/black-square.png"));
}

Entity::Entity(float x, float y, float width, float height, Texture2D texture){
    this->object = {x,y,width,height};
    this->texture=texture;
}

// Mutators and Accessors
float Entity::getXPos(){
    return this->object.x;
}
void Entity::setXPos(float x){
    this->object.x=x;
}
float Entity::getYPos(){
    return this->object.y;
}
void Entity::setYPos(float y){
    this->object.y=y;
}

float Entity::getWidth(){
    return this->object.width;
}
void Entity::setWidth(float w){
    this->object.width=w;
}
float Entity::getHeight(){
    return this->object.height;
}
void Entity::setHeight(float h){
    this->object.height=h;
}

Rectangle Entity::getRec(){
    return this->object;
}

// Textures
Texture2D Entity::getTexture(){
    return this->texture;
}
void Entity::setTexture(Texture2D texture){
    this->texture=texture;
}



// Draw
void Entity::Draw(){
        DrawTextureV(this->texture, {this->getXPos(),this->getYPos()}, WHITE);
}