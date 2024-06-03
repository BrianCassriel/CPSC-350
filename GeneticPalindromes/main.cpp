#include "DNAPalindromeFinder.h"

/** Main method
 * Creates a DNAPalindromeFinder object which reads in the file at the path specified by the first command line argument.
 * @param argc - the number of command line arguments
 * @param argv - an array of strings containing the command line arguments
 * @return - 0 if the program ran successfully, 1 if not
 */
int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <input file path>" << std::endl;
        return 1;
    }

    DNAPalindromeFinder dnaPalindromeFinder(argv[1]);
    return 0;
}
