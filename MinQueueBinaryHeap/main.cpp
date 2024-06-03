#include <iostream>
#include "MinHeap.h"

int main() {
    MinHeap<int>* binHeap = new MinHeap<int>(20);
    binHeap->insert(7);
    binHeap->insert(16);
    binHeap->insert(5);
    binHeap->insert(4);
    binHeap->insert(6);
    binHeap->insert(12);
    binHeap->insert(8);

    binHeap->linearPrint();

    while (!binHeap->isEmpty()) {
        std::cout << binHeap->getMin() << " ";
        binHeap->deleteMin();
    }

    delete binHeap;
    return 0;
}
