#include <iostream>
#include "World.h"
#include "Logger.h"
#include "Mario.h"

/**
 * The main method contains the game loop, among other things. The logger, mario, world, and random number generator
 * are initialized here. The while loop controls mario's decisions each turn until he either wins or or dies trying.
 * The logger is used to display the world, mario's stats, and the ending message.
 */
int main(int argc, char** argv) {
    Logger logger(argv[2]);
    Mario mario;
    World world(argv[1], mario, logger);
    srand(static_cast<unsigned int>(time(nullptr))); // Cite: OpenAI ChatGPT (August 3 Version)
    std::string direction;
    int powerLevel;
    char lastInteraction;

    world.placeMario(0, mario);
    mario.decideNextMove();
    while (mario.isAlive() && !mario.hasWon()) {
        direction = mario.move(mario.getNextMove(), world);
        mario.decideNextMove();
        powerLevel = mario.getPowerLevel();
        lastInteraction = mario.interact(world, lastInteraction);
        mario.updatePosition(direction, world);
        logger.logMarioState(mario, powerLevel);
        logger.logLevel(world, mario.getCurrentLevel());
        mario.incrementMovesTaken();
    }
    std::string endMessage = "You took " + std::to_string(mario.getMovesTaken()) + " moves";
    if (mario.hasWon()) {
        endMessage += " and you saved the princess! You win!";
        std::cout << "Mario won!" << std::endl;
    } else {
        endMessage += " but the princess is in another castle! You lose!";
    }
    logger.log(endMessage);

    return 0;
}
