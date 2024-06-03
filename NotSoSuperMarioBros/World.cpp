//
// Created by Brian Cassriel on 9/12/23.
//

#include "World.h"
#include <fstream>

/**
 * Constructor for World class
 * @param filePath - The path to the settings file where the world settings are stored
 * @param mario - The Mario object.
 * @param logger - The logger object.
 */
World::World(std::string filePath, Mario &mario, Logger logger) {
    readWorldSettings(filePath, mario, logger);
    generateMap();
    logger.logWorld(*this);
}

/**
 * Destructor for World class that frees the memory allocated for the 3D map array.
 */
World::~World() {
    for (int level = 0; level < mapLevels; level++) {
        for (int mapCoord = 0; mapCoord < mapSize; mapCoord++) {
            delete[] map[level][mapCoord];
        }
        delete[] map[level];
    }
    delete[] map;
}

/**
 * Getter for mapSize
 * @return - The size of the map.
 */
int World::getMapSize() { return mapSize; }

/**
 * Getter for mapLevels
 * @return - The number of levels in the map.
 */
int World::getMapLevels() { return mapLevels; }

/**
 * Getter for the map
 * @return - The 3D map array.
 */
char*** World::getMap() { return map; }

/**
 * Gets the item at a specific position on the map.
 * @param level - The level of the map.
 * @param xCoord - The x coordinate of the item.
 * @param yCoord - The y coordinate of the item.
 * @return - The item at the specified position.
 */
char World::getItemAtPosition(int level, int xCoord, int yCoord) { return map[level][xCoord][yCoord]; }

/**
 * Reads the world settings from the settings file and stores them in their respective locations.
 * @param filePath - The path to the settings file.
 * @param mario - The Mario object.
 * @param logger - The logger object.
 */
void World::readWorldSettings(std::string filePath, Mario &mario, Logger logger) {
    std::ifstream settingsFile;
    int initLives;

    try {
        settingsFile.open(filePath, std::ios::in);
        if (settingsFile.is_open()) {
            settingsFile >> mapLevels;
            settingsFile >> mapSize;
            settingsFile >> initLives;
            mario.setLivesLeft(initLives);
            settingsFile >> percentCoins;
            settingsFile >> percentEmpty;
            settingsFile >> percentGoombas;
            settingsFile >> percentKoopas;
            settingsFile >> percentMushrooms;

            logger.log("World settings read successfully.");
            logger.log("World levels: " + std::to_string(mapLevels));
            logger.log("Map size: " + std::to_string(mapSize));
            logger.log("Initial lives: " + std::to_string(initLives));
            logger.log("Percent coins: " + std::to_string(percentCoins));
            logger.log("Percent empty: " + std::to_string(percentEmpty));
            logger.log("Percent goombas: " + std::to_string(percentGoombas));
            logger.log("Percent koopas: " + std::to_string(percentKoopas));
            logger.log("Percent mushrooms: " + std::to_string(percentMushrooms));
        } else {
            throw std::runtime_error("Could not open file.");
        }
    } catch (std::exception &error) {
        logger.logError(error.what());
    }
    settingsFile.close();
}

/**
 * Generates the map.
 */
void World::generateMap() {
    map = new char**[mapLevels];
    for (int level = 0; level < mapLevels; level++) {
        map[level] = generateLevel(level);
    }
}

/**
 * Generates a single level of the map.
 * @param levelNum - The level number.
 * @return - A 2D array of the generated level.
 */
char** World::generateLevel(int levelNum) {
    char** level = new char*[mapSize];
    for (int i = 0; i < mapSize; i++) {
        level[i] = new char[mapSize];
    }
    if (levelNum != mapLevels - 1)
        World::singleItemGeneration(level, 'w');
    World::singleItemGeneration(level, 'b');
    World::percentageItemGeneration(level);
    return level;
}

/**
 * The first pass of level generation.
 * Generates a single item in a random location on the map. Avoids other single items.
 * @param level - The level of the map.
 * @param item - The item to be generated.
 */
void World::singleItemGeneration(char** level, char item) {
    int randX = rand() % mapSize;
    int randY = rand() % mapSize;
    if (level[randX][randY] == 'w' || level[randX][randY] == 'b')
        World::singleItemGeneration(level, item);
    else
        level[randX][randY] = item;
}

/**
 * The second pass of level generation.
 * Generates items in random locations on the map based on the percentages specified in the settings file.
 * The level array is modified directly when passed in.
 * @param level - The 2D array of a level of the map
 */
void World::percentageItemGeneration(char** level) {
    int randInt = rand() % 100;
    for (int i = 0; i < mapSize; i++) {
        for (int j = 0; j < mapSize; j++) {
            if (level[i][j] == 'w' || level[i][j] == 'b')
                continue;
            if (randInt < percentCoins)
                level[i][j] = 'c';
            else if (randInt < percentCoins + percentGoombas)
                level[i][j] = 'g';
            else if (randInt < percentCoins + percentGoombas + percentKoopas)
                level[i][j] = 'k';
            else if (randInt < percentCoins + percentGoombas + percentKoopas + percentMushrooms)
                level[i][j] = 'm';
            else
                level[i][j] = 'x';
            randInt = rand() % 100;
        }
    }
}

/**
 * Places mario in a random location on the map.
 * Avoids warps and bosses since those need to exist on every level.
 * @param level - The level of the map.
 * @param mario - The Mario object.
 */
void World::placeMario(int level, Mario &mario) {
    int randX = rand() % mapSize;
    int randY = rand() % mapSize;
    if (map[level][randX][randY] == 'w' || map[level][randX][randY] == 'b')
        World::placeMario(level, mario);
    else {
        map[level][randX][randY] = 'H';
        mario.position.x = randX;
        mario.position.y = randY;
    }
}

/**
 * Sets a position on the map to empty.
 * @param level - The level of the map.
 * @param xCoord - The x coordinate of the position.
 * @param yCoord - The y coordinate of the position.
 */
void World::clearPosition(int level, int xCoord, int yCoord) {
    map[level][xCoord][yCoord] = 'x';
}

/**
 * Sets a position on the map to a specified item.
 * @param level - The level of the map.
 * @param xCoord - The x coordinate of the position.
 * @param yCoord - The y coordinate of the position.
 * @param item - The item to be placed.
 */
void World::setPosition(int level, int xCoord, int yCoord, char item) {
    map[level][xCoord][yCoord] = item;
}
