// MonoStack Class Header & Implementation
// Created by Brian Cassriel on 10/3/23.
// The MonoStack class is a template class that implements a special kind of stack.
// MonoStack only allows elements to be pushed onto the stack if they are monotonically increasing or decreasing.

#ifndef DOYOUSEEWHATISEE_MONOSTACK_H
#define DOYOUSEEWHATISEE_MONOSTACK_H

#include "DoublyLinkedList.h"

template<typename T>
class MonoStack {
public:
    MonoStack(char o);
    virtual ~MonoStack();

    void push(T data);
    T pop();
    bool isEmpty();
    int getSize();

private:
    DoublyLinkedList<T>* list;
    bool isDecreasing;

    void pushMonotonically(T data);
    bool hasNotReachedCorrectPosition(T data, ListNode<T> *currentNode);
};

/**
 * Constructor
 * Initializes the DoublyLinkedList and determines the order of the MonoStack.
 * @param o - a char representing the order of the MonoStack. 'i' for increasing, 'd' for decreasing
 */
template<typename T>
MonoStack<T>::MonoStack(char o) {
    switch (o) {
        case 'd':
            isDecreasing = true;
            break;
        case 'i':
        default:
            isDecreasing = false;
            break;
    }
    list = new DoublyLinkedList<T>();
}

/**
 * Destructor
 * Deletes the DoublyLinkedList.
 */
template<typename T>
MonoStack<T>::~MonoStack() {
    delete list;
}

/** push
 * Pushes data onto the stack if it is monotonically increasing or decreasing.
 * If not, it edits the stack accordingly. Elements cannot be duplicated.
 * @param data - the data to be pushed onto the stack
 */
template<typename T>
void MonoStack<T>::push(T data) {
    if (list->isEmpty()) {
        list->prepend(data);
    } else if (!list->contains(data)) {
        pushMonotonically(data);
    }
}

/** pushMonotonically
 * Pushes data onto the stack if it is monotonically increasing or decreasing.
 * If not, it edits the stack accordingly.
 * @param data - the data to be pushed onto the stack
 */
template<typename T>
void MonoStack<T>::pushMonotonically(T data) {
    ListNode<T>* currentNode = list->getHeadNode();
    while (!list->isEmpty() && hasNotReachedCorrectPosition(data, currentNode)) {
        list->removeFront();
        currentNode = list->getHeadNode();
    }
    list->prepend(data);
}

/** hasNotReachedCorrectPosition
 * Determines if the data has reached its monotonic position in the stack.
 * @param data - the data to be pushed onto the stack
 * @param currentNode - the current node being compared to the data
 * @return true if the data has NOT reached the correct position, false if it has
 */
template<typename T>
bool MonoStack<T>::hasNotReachedCorrectPosition(T data, ListNode<T> *currentNode) {
    if (isDecreasing)
        return currentNode->getData() > data;
    return currentNode->getData() < data;
}

/** pop
 * Removes the front element of the stack.
 * @return the data from the popped element
 */
template<typename T>
T MonoStack<T>::pop() {
    return list->removeFront();
}

/** isEmpty
 * @return - true if the stack is empty, false if not
 */
template<typename T>
bool MonoStack<T>::isEmpty() { return list->isEmpty(); }

/** getSize
 * @return - the size of the stack
 */
template<typename T>
int MonoStack<T>::getSize() { return list->getSize(); }


#endif //DOYOUSEEWHATISEE_MONOSTACK_H
