//
// Created by Brian Cassriel on 9/12/23.
//

#include "Logger.h"
#include "Mario.h"
#include "World.h"

/**
 * Constructor for Logger
 * @param logFilePath - The path to the log file which will be created.
 */
Logger::Logger(std::string logFilePath) {
    this->logFilePath = logFilePath;
}

Logger::~Logger() {}

/**
 * Getter for logFilePath
 * @return - The path to the log file.
 */
std::string Logger::getLogFilePath() { return logFilePath; }

/**
 * Setter for logFilePath
 * @param newLogFilePath - The new path to the log file.
 */
void Logger::setLogFilePath(std::string newLogFilePath) { logFilePath = newLogFilePath; }

/**
 * Logs a message to the log file.
 * @param message - The message to be logged.
 */
void Logger::log(std::string message) {
    std::ofstream file;
    file.open(logFilePath, std::ios::app);
    if (file.is_open()) {
        file << message << std::endl;
    }
    file.close();
}

/**
 * Logs an error message to the log file.
 * @param message - The error message to be logged.
 */
void Logger::logError(std::string message) {
    log("<ERROR> " + message);
}

/**
 * Logs a display of the world map to the log file.
 * @param world - The world object.
 */
void Logger::logWorld(World &world) {
    for (int level = 0; level < world.getMapLevels(); level++) {
        logLevel(world, level);
    }
}

/**
 * Logs a display of a single level of the world map to the log file.
 * @param world - The world object.
 * @param level - The level to be displayed.
 */
void Logger::logLevel(World &world, int level) {
    std::ofstream file;
    file.open(logFilePath, std::ios::app);
    if (file.is_open()) {
        for (int yCoord = world.getMapSize() - 1; yCoord >= 0; yCoord--) {
            for (int xCoord = 0; xCoord < world.getMapSize(); xCoord++) {
                file << world.getMap()[level][xCoord][yCoord];
            }
            file << std::endl;
        }
    }
    file.close();
    newline();
}

/**
 * Logs a newline to the log file.
 */
void Logger::newline() {
    log("");
}

/**
 * Logs some of Mario's stats to the log file.
 * @param mario - The Mario object.
 * @param powerLevel - The power level of Mario.
 */
void Logger::logMarioState(Mario mario, int powerLevel) {
    log("Level " + std::to_string(mario.getCurrentLevel())
        + " at [" + std::to_string(mario.position.x) + "][" + std::to_string(mario.position.y) + "]"
        + " | PL" + std::to_string(powerLevel)
        + " | Action: " + mario.getLastAction()
        + " | " + std::to_string(mario.getLives()) + " lives"
        + " | " + std::to_string(mario.getCoins()) + " coins"
        + " | Next move: " + mario.getNextMove());
}
