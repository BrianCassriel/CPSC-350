//
// Created by Brian Cassriel on 9/12/23.
//

#ifndef NOTSOSUPERMARIOBROS_WORLD_H
#define NOTSOSUPERMARIOBROS_WORLD_H
#include <string>
#include "Mario.h"
#include "Logger.h"

class World {
public:
    World(std::string filePath, Mario &mario, Logger logger);
    virtual ~World();

    int getMapSize();
    int getMapLevels();
    char*** getMap();
    char getItemAtPosition(int level, int xCoord, int yCoord);

    void readWorldSettings(std::string filePath, Mario &mario, Logger logger);
    void generateMap();
    char** generateLevel(int levelNum);
    void singleItemGeneration(char** level, char item);
    void percentageItemGeneration(char** level);
    void placeMario(int level, Mario &mario);
    void clearPosition(int level, int xCoord, int yCoord);
    void setPosition(int level, int xCoord, int yCoord, char item);
private:
    int mapLevels;
    int mapSize;
    int percentCoins;
    int percentEmpty;
    int percentGoombas;
    int percentKoopas;
    int percentMushrooms;
    char*** map;
};


#endif //NOTSOSUPERMARIOBROS_WORLD_H
