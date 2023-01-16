//#include "Level.h"
#include "raylib.h"
#include <string>
#include "Entity.h"
#include "Player.h"

using namespace std;

class LevelOne /*: public Level*/{
    protected:
        
        
    public:
        LevelOne();
        void setEntityList(Entity newList[]);
        Entity* getEntityList();
        int getNumOfEntities();
        string getBackgroundImage();
        string getLevelName();
        void game(Player* blob);
        void drawLevel();
        Entity* basePlate();
    private:
        const int numOfEntities = 57;
        Entity entityList[57];        
        const string backgroundImage;
        bool completionStatus = false;
        const string levelName = "Level One";
        const int levelWidth = 7500;
        const int levelHeight = 1500;
        const int platformThickness = 15;
        void initEntities();
        int** initPlatform();
        int** initPartAPlatforms();
        int** initPartBPlatforms();
        int** initPartCPlatforms();
        int boxNum = 1;
        const int platformNum = 35;
        const int switchNum = 7;
        const int pressurePlateNum = 3;
        const int doorNum = 3;
        int partAPlatformNum = 8;
        int partBPlatformNum = 11;
        int partCPlatformNum = 20;
        void checkCollision(Player* blob);
        
        
};
