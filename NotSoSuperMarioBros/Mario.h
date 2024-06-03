//
// Created by Brian Cassriel on 9/12/23.
//

#ifndef NOTSOSUPERMARIOBROS_MARIO_H
#define NOTSOSUPERMARIOBROS_MARIO_H
#include <string>

class World;

class Mario {
public:
    Mario();
    virtual ~Mario();

    int getLives();
    int getPowerLevel();
    int getCoins();
    int getCurrentLevel();
    std::string getLastAction();
    std::string getNextMove();
    int getMovesTaken();
    void setLivesLeft(int newLivesLeft);
    void setPowerLevel(int newPowerLevel);
    void setNextMove(std::string newNextMove);
    bool isAlive();
    bool hasWon();

    void addLife();
    void addCoin(World &world);
    void incrementMovesTaken();
    void eatMushroom(World &world);
    void decrementLives();

    std::string decideNextMove();
    std::string move(std::string direction, World &world);
    void updatePosition(std::string direction, World &world);
    char interact(World &world, char lastInteraction);
    bool fightEnemy(int winChance, World &world, int damageMultiplier);
    bool fightBoss(World &world);
    bool getHit(int times);
    void tryConvertCoinsToLife();
    void tryConvertKillsToLife();
    void nextLevel(World &world);

    struct Position {
        int x;
        int y;
    } position{};
private:
    int livesLeft;
    int powerLevel;
    int coins;
    int currentLevel;
    std::string lastAction;
    std::string nextMove;
    int movesTaken;
    int enemiesKilledDuringLife;
    bool win = false;
};


#endif //NOTSOSUPERMARIOBROS_MARIO_H
