//
// Created by Brian Cassriel on 11/2/23.
//

#ifndef MINQUEUEBINARYHEAP_BINARYHEAP_H
#define MINQUEUEBINARYHEAP_BINARYHEAP_H


template<typename T>
class MinHeap {
public:
    MinHeap(int capacity);
    virtual ~MinHeap();
    void insert(T data);
    T getMin();
    void deleteMin();
    bool isEmpty();
    int getSize();
    void linearPrint();
private:
    T* heap;
    int size{};
    int capacity{};
    int getLeftIndex(int index);
    int getRightIndex(int index);
    int getParentIndex(int index);

    void fixBottomUp();
    void fixTopDown();
    int getSmallerChildIndex(int index);
    void swapSelfAndChild(int index);
    void swapSelfAndParent(int index);
};

template<typename T>
MinHeap<T>::MinHeap(int capacity) {
    this->heap = new T[capacity];
    this->size = 0;
    this->capacity = capacity;
}

template<typename T>
MinHeap<T>::~MinHeap() {
    delete[] heap;
}

template<typename T>
T MinHeap<T>::getMin() {
    if (!isEmpty())
        return heap[0];
    else
        throw std::out_of_range("Heap is empty");
}

template<typename T>
void MinHeap<T>::deleteMin() {
    if (isEmpty())
        throw std::out_of_range("Heap is empty");
    heap[0] = heap[size - 1];
    fixTopDown();
    size--;
}

template<typename T>
void MinHeap<T>::insert(T data) {
    if (size == capacity)
        throw std::out_of_range("Heap is full");
    heap[size] = data;
    fixBottomUp();
    size++;
}

template<typename T>
void MinHeap<T>::fixBottomUp() {
    int currIndex = size;
    int parentIndex = getParentIndex(currIndex);
    while (this->heap[currIndex] < this->heap[parentIndex] && currIndex != 0) {
        swapSelfAndParent(currIndex);
        currIndex = parentIndex;
        parentIndex = getParentIndex(currIndex);
    }
}

template<typename T>
void MinHeap<T>::fixTopDown() {
    int currIndex = 0;
    int childIndex = getSmallerChildIndex(currIndex);
    while (this->heap[currIndex] > this->heap[childIndex] && childIndex < size) {
        swapSelfAndChild(currIndex);
        currIndex = childIndex;
        childIndex = getSmallerChildIndex(currIndex);
    }
}

template<typename T>
void MinHeap<T>::swapSelfAndParent(int index) {
    int parentIndex = getParentIndex(index);
    int temp = this->heap[parentIndex];
    this->heap[parentIndex] = this->heap[index];
    this->heap[index] = temp;
}

template<typename T>
void MinHeap<T>::swapSelfAndChild(int index) {
    int childIndex = getSmallerChildIndex(index);
    int temp = this->heap[childIndex];
    this->heap[childIndex] = this->heap[index];
    this->heap[index] = temp;
}

template<typename T>
int MinHeap<T>::getSmallerChildIndex(int index) {
    if (this->heap[getLeftIndex(index)] < this->heap[getRightIndex(index)])
        return this->getLeftIndex(index);
    else
        return this->getRightIndex(index);
}

template<typename T>
int MinHeap<T>::getParentIndex(int index) {
    return (index - 1) / 2;
}

template<typename T>
int MinHeap<T>::getRightIndex(int index) {
    return 2*index + 2;
}

template<typename T>
int MinHeap<T>::getLeftIndex(int index) {
    return 2*index + 1;
}

template<typename T>
void MinHeap<T>::linearPrint() {
    for (int i = 0; i < size; i++) {
        std::cout << heap[i] << ", ";
    }
    std::cout << std::endl;
}

template<typename T>
int MinHeap<T>::getSize() {
    return size;
}

template<typename T>
bool MinHeap<T>::isEmpty() {
    if (size > 0)
        return false;
    return true;
}

#endif //MINQUEUEBINARYHEAP_BINARYHEAP_H
