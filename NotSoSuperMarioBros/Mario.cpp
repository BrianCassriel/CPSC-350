//
// Created by Brian Cassriel on 9/12/23.
//

#include "Mario.h"
#include "World.h"

/**
 * Constructor for Mario class
 * Initializes all variables to 0 or empty strings.
 */
Mario::Mario() {
    livesLeft = 0;
    powerLevel = 0;
    coins = 0;
    currentLevel = 0;
    position = {
            .x = 0,
            .y = 0
    };
    lastAction = "";
    nextMove = "";
    movesTaken = 0;
    enemiesKilledDuringLife = 0;
    win = false;
}

Mario::~Mario() {}

/**
 * Getter for livesLeft
 * @return - The number of lives Mario has left.
 */
int Mario::getLives() { return livesLeft; }

/**
 * Getter for powerLevel
 * @return - The power level of Mario. (PL0, PL1, PL2)
 */
int Mario::getPowerLevel() { return powerLevel; }

/**
 * Getter for coins
 * @return - The number of coins Mario has collected.
 */
int Mario::getCoins() { return coins; }

/**
 * Getter for currentLevel
 * @return - The current level Mario is on.
 */
int Mario::getCurrentLevel() { return currentLevel; }

/**
 * Getter for lastAction
 * @return - The last interaction Mario his position on the map.
 */
std::string Mario::getLastAction() { return lastAction; }

/**
 * Getter for nextMove
 * @return - The next move Mario will take across the map.
 */
std::string Mario::getNextMove() { return nextMove; }

/**
 * Getter for movesTaken
 * @return - The number of moves Mario has taken.
 */
int Mario::getMovesTaken() { return movesTaken; }

/**
 * Setter for livesLeft
 * @param newLivesLeft - The new number of remaining lives for Mario.
 */
void Mario::setLivesLeft(int newLivesLeft) { livesLeft = newLivesLeft; }

/**
 * Setter for powerLevel
 * @param newPowerLevel - The new power level for Mario. (PL0, PL1, PL2)
 */
void Mario::setPowerLevel(int newPowerLevel) { powerLevel = newPowerLevel; }

/**
 * Setter for nextMove
 * @param newNextMove - The new next move for Mario.
 */
void Mario::setNextMove(std::string newNextMove) { nextMove = newNextMove; }

/**
 * Checks if Mario is alive (has more than 0 lives remaining)
 * @return - True if Mario is alive, false if he is not.
 */
bool Mario::isAlive() { return livesLeft >= 0; }

/**
 * Checks if Mario has won (has beaten the boss on the last level)
 * @return - True if Mario has won, false if he has not.
 */
bool Mario::hasWon() { return win; }

/**
 * Gives Mario one life.
 */
void Mario::addLife() { livesLeft++; }

/**
 * Gives Mario one coin and clears the coin from the map.
 * @param world - The world object.
 */
void Mario::addCoin(World &world) {
    coins++;
    world.clearPosition(currentLevel, position.x, position.y);
}

/**
 * Increments the number of moves Mario has taken.
 */
void Mario::incrementMovesTaken() { movesTaken++; }

/**
 * Gives Mario one power level and clears the mushroom from the map.
 * If Mario is already at PL2, the mushroom is cleared but Mario's power level does not increase.
 * @param world - The world object.
 */
void Mario::eatMushroom(World &world) {
    powerLevel++;
    if (powerLevel > 2)
        powerLevel = 2;
    world.clearPosition(currentLevel, position.x, position.y);
}

/**
 * Decrements the number of lives Mario has left.
 * Also resets the number of enemies killed during the current life to 0.
 */
void Mario::decrementLives() {
    livesLeft--;
    enemiesKilledDuringLife = 0;
}

/**
 * Decides Mario's next move direction.
 * @return - The next move direction Mario will take.
 */
std::string Mario::decideNextMove() {
    if (nextMove == "STAY PUT")
        return "STAY PUT";

    int randInt = rand() % 4;
    switch (randInt) {
        case 0:
            nextMove = "UP";
            break;
        case 1:
            nextMove = "DOWN";
            break;
        case 2:
            nextMove = "LEFT";
            break;
        case 3:
            nextMove = "RIGHT";
            break;
    }
    return nextMove;
}

/**
 * Moves Mario in the specified direction.
 * If Mario goes off one side of the map, he comes back on the other.
 * @param direction - The direction Mario will move.
 * @param world - The world object.
 * @return - The direction Mario moved.
 */
std::string Mario::move(std::string direction, World &world) {
    if (direction == "UP") {
        position.y++;
    } else if (direction == "DOWN") {
        position.y--;
    } else if (direction == "LEFT") {
        position.x--;
    } else if (direction == "RIGHT") {
        position.x++;
    }

    if (position.x < 0)
        position.x = world.getMapSize() - 1;
    else if (position.x >= world.getMapSize())
        position.x = 0;
    else if (position.y < 0)
        position.y = world.getMapSize() - 1;
    else if (position.y >= world.getMapSize())
        position.y = 0;

    return direction;
}

/**
 * Updates Mario's position on the world map.
 * @param direction - The direction Mario moved.
 * @param world - The world object.
 */
void Mario::updatePosition(std::string direction, World &world) {
    int formerPositionX = position.x;
    int formerPositionY = position.y;

    if (direction == "UP")
        formerPositionY--;
    else if (direction == "DOWN")
        formerPositionY++;
    else if (direction == "LEFT")
        formerPositionX++;
    else if (direction == "RIGHT")
        formerPositionX--;

    if (formerPositionX < 0)
        formerPositionX = world.getMapSize() - 1;
    else if (formerPositionX >= world.getMapSize())
        formerPositionX = 0;
    else if (formerPositionY < 0)
        formerPositionY = world.getMapSize() - 1;
    else if (formerPositionY >= world.getMapSize())
        formerPositionY = 0;

    world.clearPosition(currentLevel, formerPositionX, formerPositionY);
    world.setPosition(currentLevel, position.x, position.y, 'H');
}

/**
 * Interacts with the item at Mario's current position.
 *      Empty - None.               (No interaction)
 *      Coin - Collect Coin.        (Increases coin count by 1)
 *      Goomba - Fight Goomba.      (80% chance of winning)
 *      Koopa - Fight Koopa.        (65% chance of winning)
 *      Mushroom - Eat Mushroom.    (Increases power level by 1)
 *      Warp - Warp to next level.  (Goes to the next level)
 *      Boss - Fight Boss.          (50% chance of winning. Goes to next level or wins game.)
 * @param world - The world object.
 * @param lastInteraction - The last interaction Mario had with an item.
 * @return - The item Mario interacted with.
 */
char Mario::interact(World &world, char lastInteraction) {
    char item = world.getItemAtPosition(currentLevel, position.x, position.y);
    if (lastInteraction == 'g')
        item = 'g';
    else if (lastInteraction == 'k')
        item = 'k';
    else if (lastInteraction == 'b')
        item = 'b';

    switch (item) {
        case 'x':
            lastAction = "None.";
            return 'x';
        case 'c':
            lastAction = "Collected coin.";
            addCoin(world);
            tryConvertCoinsToLife();
            return 'c';
        case 'g':
            lastAction = "Fought goomba and ";
            if (fightEnemy(80, world, 1)) {
                lastAction += "won.";
                return 'x';
            }
            lastAction += "lost.";
            return 'g';
        case 'k':
            lastAction = "Fought koopa and ";
            if (fightEnemy(65, world, 1)) {
                lastAction += "won.";
                return 'x';
            }
            lastAction += "lost.";
            return 'k';
        case 'm':
            lastAction = "Ate mushroom.";
            eatMushroom(world);
            return 'm';
        case 'w':
            lastAction = "Warped.";
            nextLevel(world);
            return 'w';
        case 'b':
            lastAction = "Fought boss and ";
            if (fightBoss(world)) {
                lastAction += "won.";
                nextLevel(world);
                return 'x';
            }
            lastAction += "lost.";
            return 'b';
    }
}

/**
 * Simulates a fight between Mario and an enemy.
 * If he wins, the enemy is cleared from the map and Mario's next move is decided.
 * If he loses, he takes damage.
 *      If he goes below power level 0, his next move is to "STAY PUT".
 *      Otherwise, his next move is decided normally (without removing the enemy).
 * @param winChance - The chance Mario has of winning the fight.
 * @param world - The world object.
 * @param damageMultiplier - The amount of damage Mario will take if he loses the fight.
 * @return - True if Mario won the fight, false if he lost.
 */
bool Mario::fightEnemy(int winChance, World &world, int damageMultiplier) {
    if (rand() % 100 < winChance) {
        enemiesKilledDuringLife++;
        tryConvertKillsToLife();
        world.clearPosition(currentLevel, position.x, position.y);
        nextMove = "";
        nextMove = decideNextMove();
        return true;
    } else {
        bool hasLostLife = getHit(damageMultiplier);
        if (hasLostLife) {
            nextMove = "STAY PUT";
        } else {
            nextMove = "";
            nextMove = decideNextMove();
        }
        return false;
    }
}

/**
 * Simulates a fight between Mario and a boss.
 * Mario has a 50% chance of beating any boss.
 * @param world - The world object.
 * @return - True if Mario won the fight, false if he lost.
 */
bool Mario::fightBoss(World &world) {
    if (fightEnemy(50, world, 2)) {
        return true;
    } else {
        nextMove = "STAY PUT";
        return false;
    }
}

/**
 * Checks if Mario has enough coins to convert 20 of them into a life.
 * If he does, he loses 20 coins and gains a life.
 */
void Mario::tryConvertCoinsToLife() {
    if (coins >= 20) {
        coins -= 20;
        addLife();
    }
}

/**
 * Checks if Mario has killed enough enemies to convert 7 of them into a life.
 * If he does, he loses 7 kills and gains a life.
 */
void Mario::tryConvertKillsToLife() {
    if (enemiesKilledDuringLife >= 7) {
        enemiesKilledDuringLife -= 7;
        addLife();
    }
}

/**
 * Simulates Mario getting hit by an enemy.
 * If he has a power level, he loses one power level.
 * If he does not have a power level, he loses a life.
 * @param times - The number of times Mario will get hit.
 * @return - True if Mario lost a life, false if he did not.
 */
bool Mario::getHit(int times) {
    if (powerLevel > 0) {
        powerLevel -= times;
        return false;
    } else {
        decrementLives();
        return true;
    }
}

/**
 * Moves Mario to the next level.
 * If he is on the last level, he wins the game.
 * @param world - The world object.
 */
void Mario::nextLevel(World &world) {
    if (currentLevel == world.getMapLevels() - 1) {
        win = true;
    } else {
        currentLevel++;
        world.placeMario(currentLevel, *this);
    }
}
