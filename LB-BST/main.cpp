#include <iostream>
#include "UserInterface.h"

using namespace std;

/** Main method
 * Creates a new User Interface and keeps giving the user options until the user decides to exit.
 * @return 0 for a successfully finished run.
 */
int main() {
    UserInterface* ui = new UserInterface();
//    ui->addDefaultData();
    while (ui->isRunning()) {
        ui->displayMenu();
        ui->doUserSelection();
    }
    delete ui;
    return 0;
}
