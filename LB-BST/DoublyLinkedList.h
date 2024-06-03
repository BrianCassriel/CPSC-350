// DoublyLinkedList Class Header/Implementation
// Created by Brian Cassriel on 9/28/23.
// The DoublyLinkedList class is a template class that implements a doubly linked list
// & provides a useful interface for interacting with the list.

#ifndef DOUBLYLINKEDLIST_DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_DOUBLYLINKEDLIST_H

#include "ListNode.h"

template<typename T>
class DoublyLinkedList {
public:
    DoublyLinkedList();
    DoublyLinkedList(T data);
    virtual ~DoublyLinkedList();
    int getSize();
    bool isEmpty();

    ListNode<T>* getHeadNode();
    ListNode<T>* getTailNode();

    void append(T data);
    void prepend(T data);
    void insert(int position, T data);

    T removeBack();
    T removeFront();
    T remove(int position);

    T get(int position);
    bool contains(T data);
    int find(T data);

private:
    ListNode<T>* headNode;
    ListNode<T>* tailNode;
    int size;

    ListNode<T> *getNode(int position) const;
};

/**
 * Constructor
 * Initializes the list to contain no elements.
 */
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
    size = 0;
    headNode = nullptr;
    tailNode = nullptr;
}

/**
 * Constructor
 * Initializes the list to contain one element.
 * @param data - the data to be stored in the list
 */
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(T data) {
    size = 0;
    headNode = nullptr;
    tailNode = nullptr;
    append(data);
}

/**
 * Destructor
 * Deletes all elements in the list.
 */
template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    while (!isEmpty()) {
        removeFront();
    }
    size = 0;
    headNode = nullptr;
    tailNode = nullptr;
}

/** getSize
 * @return the number of elements in the list
 */
template<typename T>
int DoublyLinkedList<T>::getSize() { return size; } //O(1)

/** isEmpty
 * @return true if the list is empty, false if not
 */
template<typename T>
bool DoublyLinkedList<T>::isEmpty() { return size == 0; } //O(1)

/** getHeadNode
 * @return the head ListNode of the list
 */
template<typename T>
ListNode<T>* DoublyLinkedList<T>::getHeadNode() { return headNode; }

/** getTailNode
 * @return the tail ListNode of the list
 */
template<typename T>
ListNode<T>* DoublyLinkedList<T>::getTailNode() { return headNode; }

/** get
 * @param position - the position of the node in the list to get data from
 * @return the data stored in the node at the specified position
 */
template<typename T>
T DoublyLinkedList<T>::get(int position) { //O(n)
    if (position < 0 || position >= size) {
        throw std::runtime_error("Position is out of bounds");
    }
    ListNode<T>* currentNode = headNode;
    for (int i = 0; i < position; i++) {
        currentNode = currentNode->nextNode;
    }
    return currentNode->getData();
}

/** contains
 * Determines if the list contains the specified data.
 * @param data - the data to search for in the list
 * @return true if the list contains the data, false if not
 */
template<typename T>
bool DoublyLinkedList<T>::contains(T data) { //O(n)
    ListNode<T>* currentNode = headNode;
    while (currentNode != nullptr) {
        if (currentNode->getData() == data) {
            return true;
        }
        currentNode = currentNode->nextNode;
    }
    return false;
}

/** prepend
 * Prepends a node containing the specified data to the front of the list.
 * @param data - the data to be stored in the new node
 */
template<typename T>
void DoublyLinkedList<T>::prepend(T data) { // O(1)
    ListNode<T>* newNode = new ListNode<T>(data);
    if (!isEmpty()) {
        headNode->prevNode = newNode;
        newNode->nextNode = headNode;
    } else {
        tailNode = newNode;
    }
    ++size;
    headNode = newNode;
}

/** append
 * Appends a node containing the specified data to the end of the list.
 * @param data - the data to be stored in the new node
 */
template<typename T>
void DoublyLinkedList<T>::append(T data) { //O(1)
    ListNode<T>* newNode = new ListNode<T>(data);
    if (!isEmpty()) {
        tailNode->nextNode = newNode;
        newNode->prevNode = tailNode;
    } else {
        headNode = newNode;
    }
    ++size;
    tailNode = newNode;
}

/** removeFront
 * Removes the first node in the list.
 * @return the data stored in the removed node
 */
template<typename T>
T DoublyLinkedList<T>::removeFront() { //O(1)
    if (isEmpty()) {
        throw std::runtime_error("Cannot remove from empty list");
    }
    T data = headNode->getData();
    if (size == 1) {
        delete headNode;
        headNode = nullptr;
        tailNode = nullptr;
    } else {
        ListNode<T>* oldHeadNode = headNode;
        headNode = headNode->nextNode;
        headNode->prevNode = nullptr;
        oldHeadNode->nextNode = nullptr;
        delete oldHeadNode;
    }
    --size;
    return data;
}

/** removeBack
 * Removes the last node in the list.
 * @return the data stored in the last node in the list
 */
template<typename T>
T DoublyLinkedList<T>::removeBack() { //O(1)
    if (isEmpty()) {
        throw std::runtime_error("Cannot remove from empty list");
    }
    T data = tailNode->getData();
    if (size == 1) {
        delete tailNode;
        headNode = nullptr;
        tailNode = nullptr;
    } else {
        ListNode<T>* oldTailNode = tailNode;
        tailNode = tailNode->prevNode;
        tailNode->nextNode = nullptr;
        oldTailNode->prevNode = nullptr;
        delete oldTailNode;
    }
    --size;
    return data;
}

/** insert
 * Inserts a node containing the specified data at the specified position in the list.
 * @param position - the position in the list to insert the node
 * @param data - the data to be stored in the new node
 */
template<typename T>
void DoublyLinkedList<T>::insert(int position, T data) { //O(n)
    if (position == 0 || isEmpty()) {
        prepend(data);
    } else if (position >= size) {
        append(data);
    } else {
        ListNode<T>* currentNode = getNode(position);
        ListNode<T>* newNode = new ListNode<T>(data);
        currentNode->prevNode->nextNode = newNode;
        newNode->prevNode = currentNode->prevNode;
        currentNode->prevNode = newNode;
        newNode->nextNode = currentNode;
        ++size;
    }
}

/** remove
 * Removes the node at the specified position in the list.
 * @param position - the position of the node to remove
 * @return the data stored in the removed node
 */
template<typename T>
T DoublyLinkedList<T>::remove(int position) { //O(n)
    if (isEmpty()) {
        throw std::runtime_error("Cannot remove from empty list");
    }
    if (position == 0) {
        return removeFront();
    } else if (position >= size - 1) {
        return removeBack();
    } else {
        ListNode<T>* currentNode = getNode(position);
        T data = currentNode->getData();
        currentNode->prevNode->nextNode = currentNode->nextNode;
        currentNode->nextNode->prevNode = currentNode->prevNode;
        delete currentNode;
        --size;
        return data;
    }
}

/** getNode
 * Gets the ListNode* object at the specified position in the list.
 * @param position - the position of the ListNode* to get
 * @return the ListNode* at the specified position
 */
template<typename T>
ListNode<T>* DoublyLinkedList<T>::getNode(int position) const { //O(n)
    ListNode<T>* currentNode = headNode;
    for (int i = 0; i < position; ++i) {
        currentNode = currentNode->nextNode;
    }
    return currentNode;
}

/** find
 * Finds the position of the first node containing the specified data.
 * @param data - the data to search for
 * @return the position of the first node containing the specified data
 */
template<typename T>
int DoublyLinkedList<T>::find(T data) {
    ListNode<T>* currentNode = headNode;
    int position = 0;
    while (currentNode != nullptr) {
        if (currentNode->getData() == data) {
            return position;
        }
        currentNode = currentNode->nextNode;
        ++position;
    }
    return -1;
}

#endif //DOUBLYLINKEDLIST_DOUBLYLINKEDLIST_H
