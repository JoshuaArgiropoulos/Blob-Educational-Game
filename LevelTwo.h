#include "Level.h"
#include "raylib.h"
#include <string>
#include "Entity.h"
#include "Player.h"
#include "Wall.h"
#include "Platform.h"
#include "Door.h"
#include "Plate.h"
#include "Lever.h"
#include "Box.h"
using namespace std;

class LevelTwo : public Level{
    #define numberOfPlatforms 28
    #define numberOfDoors 3
    #define numberOfPlates 3
    #define numberOfLevers 7
    #define numberOfWalls 12
    #define numberOfEntities 54
    #define numberOfBoxs 1
    
    protected:
        
        
    public:
        LevelTwo();
        ~LevelTwo();
        string getLevelName();
        bool getCompletionStatus();
        void game(Player* blob);
        void drawLevel();       
        void Run() override ;
        
        
    private:
   
        bool completionStatus = false;
        const string levelName ="Level Two";
        const int levelWidth = 7500;
        const int levelHeight = 1500;
        const int platformThickness = 15;
        bool platformsLoaded = false;
        const int wallThickness = 50;
        const int plateThickness = 35;
        const int switchThickness = 150;
        
        
        
        void initEntities(); //initalizes the entities
        int** initEntity(); //loads the information for each entity 
        void checkCollision(Player* blob); //checks to collision of each entity        
        void gameLogic(Player* blob); //logic for the level


        
        //variables to hold the number of each type of entity
        const int boxNum = numberOfBoxs;
        const int doorNum = numberOfDoors;
        const int plateNum = numberOfPlates;
        const int leverNum = numberOfLevers;
        const int wallNum = numberOfWalls;  
        const int entityNum = numberOfEntities;
        const int  platformNum = numberOfPlatforms;
        
        //holds the different entities
        Wall wallList[numberOfWalls];
        Platform* platformList[numberOfPlatforms];  
        Door doorList[numberOfDoors];
        Plate plateList[numberOfPlates];
        Lever leverList[numberOfLevers];
        Box boxList[numberOfBoxs];
};
