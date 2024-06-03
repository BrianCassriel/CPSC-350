// ListNode Header/Implementation
// Created by Brian Cassriel on 9/28/23.
// The ListNode class is a template class that implements a node for a DoublyLinkedList.

#ifndef DOUBLYLINKEDLIST_LISTNODE_H
#define DOUBLYLINKEDLIST_LISTNODE_H

template<typename T>
class ListNode {
public:
    ListNode(T data);
    virtual ~ListNode();

    T getData();
    ListNode<T>* getNextNode();
    ListNode<T>* getPrevNode();

    template<typename S>
    friend class DoublyLinkedList;

private:
    T data;
    ListNode<T>* nextNode;
    ListNode<T>* prevNode;
};

/** Constructor
 * @param data - the data to be stored in the node
 */
template<typename T>
ListNode<T>::ListNode(T data) {
    this->data = data;
    nextNode = NULL;
    prevNode = NULL;
}

/** Destructor
 */
template<typename T>
ListNode<T>::~ListNode() {
    nextNode = NULL;
    prevNode = NULL;
}

/** getData
 * @return the data stored in the node
 */
template<typename T>
T ListNode<T>::getData() { return data; }

/** getNextNode
 * @return the next node in the DoublyLinkedList
 */
template<typename T>
ListNode<T>* ListNode<T>::getNextNode() { return nextNode; }

/** getPrevNode
 * @return the previous node in the DoublyLinkedList
 */
template<typename T>
ListNode<T>* ListNode<T>::getPrevNode() { return prevNode; }

#endif //DOUBLYLINKEDLIST_LISTNODE_H
