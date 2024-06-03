//
// Created by Brian Cassriel on 9/12/23.
//

#ifndef NOTSOSUPERMARIOBROS_LOGGER_H
#define NOTSOSUPERMARIOBROS_LOGGER_H
#include <string>
#include <fstream>

class Mario;
class World;

class Logger {
public:
    Logger(std::string logFilePath);
    virtual ~Logger();
    std::string getLogFilePath();
    void setLogFilePath(std::string newLogFilePath);
    void log(std::string message);
    void logError(std::string message);
    void logWorld(World &world);
    void logLevel(World &world, int level);
    void newline();
    void logMarioState(Mario mario, int powerLevel);
private:
    std::string logFilePath;
};

#endif //NOTSOSUPERMARIOBROS_LOGGER_H
