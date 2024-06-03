#include "FileProcessor.h"

/** main Method
 * Takes a file path as a command line argument and reads a WGraph from the file.
 * Then, it computes and displays the Minimum Search Tree of the WGraph.
 * @param argc - the number of command line arguments
 * @param argv - the command line arguments
 * @return int - the exit code
 */
int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <graph file>" << endl;
        return 1;
    }
    FileProcessor fp(argv[1]);
    WGraph* graph = fp.readGraph();
    graph->computeMST();
    return 0;
}
