// LazyBST Class Implementation
// Created By Erik Linstead, Brian Cassriel
// LazyBST is a binary search tree that is self-balancing.
// It's self-balancing method is to rebuild the tree from an array of the tree's data.

#ifndef BST_H
#define BST_H

#include <fstream>
#include "TreeNode.h"

template <typename T>
class LazyBST{
public:
    LazyBST();
    virtual ~LazyBST();
    int getSize();
    void insert(T d);
    void remove(T d);
    bool contains(T d);
    T getMin();
    T getMax();
    void printTreeInOrder();
    T* find(T data);
    void printToFile(std::ofstream& file);

private:
    TreeNode<T>* m_root;
    int m_size;
    void insertHelper(TreeNode<T>*& subTreeRoot,TreeNode<T>* newNode);
    bool containsHelper(TreeNode<T>* subTreeRoot, TreeNode<T>* target);
    T getMinHelper(TreeNode<T>* subTreeRoot);
    T getMaxHelper(TreeNode<T>* subTreeRoot);
    void printTreeInOrderHelper(TreeNode<T>* subTreeRoot);
    void findTarget(T key, TreeNode<T>*& target,TreeNode<T>*& parent);
    TreeNode<T>* getSuccessor(TreeNode<T>* rightChild);
    void rebalance();
    double getTreeImbalanceFactor();
    T* getAsInOrderArray();
    void getAsInOrderArrayHelper(TreeNode<T>* subTreeRoot, T* outputArr, int& currIndex);
    void deleteTreeData();
    void rebuildFromArray(T* arr);
    TreeNode<T>* rebuildFromArrayHelper(T* arr, int start, int end);
    void printToFileHelper(TreeNode<T>* subTreeRoot, std::ofstream& outFile);
};

/** Constructor
 * @tparam T - the type of data to be stored in the tree
 */
template <typename T>
LazyBST<T>::LazyBST(){
  m_root = nullptr;
  m_size = 0;
}

/** Destructor
 * Deletes the allocated memory for the tree
 */
template <typename T>
LazyBST<T>::~LazyBST(){
  if(m_root != nullptr){
    delete m_root;
  }
}

/** getSize
 * @return the number of nodes in the tree
 */
template <typename T>
int LazyBST<T>::getSize(){
  return m_size;
}

/** insert
 * Inserts a new node into the tree
 * @param d - the data to be stored in the new node
 */
template <typename T>
void LazyBST<T>::insert(T d){
    TreeNode<T>* newNode = new TreeNode<T>(d);
    insertHelper(m_root,newNode);
    ++m_size;
    rebalance();
}

/** insertHelper
 * Uses recursion to help insert a new node into the tree
 * @param subTreeRoot - the root of the subtree to insert into
 * @param newNode - the node to be inserted
 */
template <typename T>
void LazyBST<T>::insertHelper(TreeNode<T>*& subTreeRoot, TreeNode<T>* newNode){
    if (subTreeRoot == nullptr) {
        subTreeRoot = newNode;
    } else if (newNode->m_data < subTreeRoot->m_data) {
        insertHelper(subTreeRoot->m_left, newNode);
    } else {
        insertHelper(subTreeRoot->m_right, newNode);
    }
}

/** remove
 * Removes a node from the tree
 * @param d - the data to be removed
 */
template <typename T>
void LazyBST<T>::remove(T d){
    if (m_root == nullptr) {
        std::cout << "Cannot remove from an empty tree!" << std::endl;
        return;
    }
    TreeNode<T>* target = nullptr;
    TreeNode<T>* parent = nullptr;
    target = m_root;
    findTarget(d,target,parent);
    if(target == nullptr){ //value doesn't exist
        std::cout << "Value does not exist in tree." << std::endl;
        return;
    }
    if(target->m_left==nullptr && target->m_right==nullptr){ //it's a leaf
        if(target == m_root){ //leaf we found is the root
            m_root = nullptr;
        } else { //leaf isn't the root
            if(target == parent->m_left){
                parent->m_left = nullptr;
            } else {
                parent->m_right = nullptr;
            }
        }
    } else if(target->m_left!=nullptr && target->m_right!=nullptr){ //2 child case
        TreeNode<T>* suc = getSuccessor(target->m_right);
        T value = suc->m_data;
        remove(value);
        target->m_data = value;
    } else { // 1 child case
        TreeNode<T>* child; // the thing to replace the target with
        //which side is the child on?
        if(target->m_left != nullptr){ // child on left
            child = target->m_left;
        } else {//child is on the right
            child = target->m_right;
        }
        if(target == m_root){
            m_root = child;
        } else { //the thing to delete isn't the root
            if (target == parent->m_left) {
                parent->m_left = child;
            } else {
            parent->m_right = child;
            }
        }
    }
    --m_size;
    rebalance();
}

/** contains
 * Checks if the tree contains a certain value
 * @param d - the value to check for
 * @return true if the tree contains the value, false otherwise
 */
template <typename T>
bool LazyBST<T>::contains(T d){
    TreeNode<T>* newNode = new TreeNode<T>(d);
    bool ret = containsHelper(m_root,newNode);
    delete newNode;
    return ret;
}

/** containsHelper
 * Uses recursion to help check if the tree contains a certain value
 * @param subTreeRoot - the root of the subtree to check
 * @param target - the value to check for
 * @return true if the tree contains the value, false otherwise
 */
template <typename T>
bool LazyBST<T>::containsHelper(TreeNode<T>* subTreeRoot, TreeNode<T>* target){
    if(subTreeRoot == nullptr){
        return false;
    } else if(target->m_data < subTreeRoot->m_data){
        return containsHelper(subTreeRoot->m_left,target);
    } else if (target->m_data > subTreeRoot->m_data){
        return containsHelper(subTreeRoot->m_right,target);
    } else{
        return true;
    }
}

/** getMin
 * @return the minimum value in the tree
 */
template <typename T>
T LazyBST<T>::getMin(){
    if (m_root == nullptr)
        throw std::runtime_error("Could not get minimum value. Tree is empty");
    return getMinHelper(m_root);
}

/** getMinHelper
 * Uses recursion to help find the minimum value in the tree
 * @param subTreeRoot - the root of the subtree to check
 * @return the minimum value in the tree
 */
template <typename T>
T LazyBST<T>::getMinHelper(TreeNode<T>* subTreeRoot){
    if(subTreeRoot->m_left == nullptr){
        return subTreeRoot->m_data;
    } else {
        return getMinHelper(subTreeRoot->m_left);
    }
}

/** getMax
 * @return the maximum value in the tree
 */
template <typename T>
T LazyBST<T>::getMax(){
    if (m_root == nullptr)
        throw std::runtime_error("Could not get maximum value. Tree is empty");
    return getMaxHelper(m_root);
}

/** getMaxHelper
 * Uses recursion to help find the maximum value in the tree
 * @param subTreeRoot - the root of the subtree to check
 * @return the maximum value in the tree
 */
template <typename T>
T LazyBST<T>::getMaxHelper(TreeNode<T>* subTreeRoot){
    if(subTreeRoot->m_right == nullptr){
        return subTreeRoot->m_data;
    } else {
        return getMaxHelper(subTreeRoot->m_right);
    }
}

/** printTreeInOrder
 * Prints the tree in order from least to greatest
 */
template <typename T>
void LazyBST<T>::printTreeInOrder(){
    printTreeInOrderHelper(m_root);
}

/** printTreeInOrderHelper
 * Uses recursion to help print the tree in order from least to greatest
 * @param subTreeRoot - the root of the subtree to print
 */
template <typename T>
void LazyBST<T>::printTreeInOrderHelper(TreeNode<T>* subTreeRoot){
    if (subTreeRoot != nullptr) {
        printTreeInOrderHelper(subTreeRoot->m_left);
        cout << subTreeRoot->m_data << endl;
        printTreeInOrderHelper(subTreeRoot->m_right);
    }
}

/** findTarget
 * Finds the target node and its parent. Arguments are also outputs.
 * @param key - the value to find
 * @param target - the node to be found
 * @param parent - the parent of the node to be found
 */
template <typename T>
void LazyBST<T>::findTarget(T key, TreeNode<T>*& target, TreeNode<T>*& parent){
    while(target != nullptr && target->m_data != key){
        parent = target;
        if (key < target->m_data) {
            target = target->m_left;
        } else {
        target = target->m_right;
        }
    }
}

/** getSuccessor
 * Finds the successor of a node
 * @param rightChild - the right child of the node to find the successor of
 * @return the successor of the node
 */
template <typename T>
TreeNode<T>* LazyBST<T>::getSuccessor(TreeNode<T>* rightChild){
    while (rightChild->m_left != nullptr) {
        rightChild = rightChild->m_left;
    }
    return rightChild;
}

/** getTreeImbalanceFactor
 * @return the imbalance factor of the tree
 */
template<typename T>
double LazyBST<T>::getTreeImbalanceFactor() {
    if (m_root == nullptr)
        return 0.0;
    int leftHeight = m_root->m_left->getSubtreeHeight();
    int rightHeight = m_root->m_right->getSubtreeHeight();
    double temp = max(rightHeight / (double)leftHeight, leftHeight / (double)rightHeight);
    return temp;
}

/** rebalance
 * Rebuilds the tree if the imbalance factor is greater than 1.5
 */
template<typename T>
void LazyBST<T>::rebalance() {
    if (getTreeImbalanceFactor() > 1.5) {
        T* tempArr = getAsInOrderArray();
        deleteTreeData();
        rebuildFromArray(tempArr);
    }
}

/** rebuildFromArray
 * Rebuilds the tree from a sorted array of the tree's data
 * @param arr - the array of the tree's data
 */
template<typename T>
void LazyBST<T>::rebuildFromArray(T* arr) {
    m_root = rebuildFromArrayHelper(arr, 0, m_size - 1);
}

/** rebuildFromArrayHelper
 * Uses recursion to help rebuild the tree from a sorted array of the tree's data
 * @param arr - the array of the tree's data
 * @param start - the starting index of the array
 * @param end - the ending index of the array
 * @return the root of the rebuilt tree
 */
template<typename T>
TreeNode<T> *LazyBST<T>::rebuildFromArrayHelper(T* arr, int start, int end) {
    if (start > end)
        return nullptr;
    int mid = start + (end - start) / 2;
    TreeNode<T>* newNode = new TreeNode<T>(arr[mid]);
    newNode->m_left = rebuildFromArrayHelper(arr, start, mid - 1);
    newNode->m_right = rebuildFromArrayHelper(arr, mid + 1, end);
    return newNode;
}

/** getAsInOrderArray
 * @return an array of the tree's data sorted in order from least to greatest
 */
template<typename T>
T* LazyBST<T>::getAsInOrderArray() {
    T* arr = new T[m_size];
    int currIndex = 0;
    getAsInOrderArrayHelper(m_root, arr, currIndex);
    return arr;
}

/** getAsInOrderArrayHelper
 * Uses recursion to help get an array of the tree's data sorted in order from least to greatest
 * @param subTreeRoot - the root of the subtree to get the data from
 * @param outputArr - the array to store the data in
 * @param currIndex - the current index of the array
 */
template<typename T>
void LazyBST<T>::getAsInOrderArrayHelper(TreeNode<T>* subTreeRoot, T* outputArr, int& currIndex) {
    if (subTreeRoot == nullptr)
        return;
    getAsInOrderArrayHelper(subTreeRoot->m_left, outputArr, currIndex);
    outputArr[currIndex++] = subTreeRoot->m_data;
    getAsInOrderArrayHelper(subTreeRoot->m_right, outputArr, currIndex);
}

/** deleteTreeData
 * Deletes the allocated memory for the tree without destroying the LazyBST object
 */
template<typename T>
void LazyBST<T>::deleteTreeData() {
    if (m_root != nullptr) {
        delete m_root;
    }
    m_root = nullptr;
}

/** find
 * Finds a node in the tree
 * @param data - the data to find
 * @return a pointer to the data if it exists, nullptr otherwise
 */
template<typename T>
T* LazyBST<T>::find(T data) {
    TreeNode<T>* target = m_root;
    while (target != nullptr && target->m_data != data) {
        if (data < target->m_data) {
            target = target->m_left;
        } else {
            target = target->m_right;
        }
    }
    if (target == nullptr)
        return nullptr;
    return &target->m_data;
}

/** printToFile
 * Prints the tree to a file in order from least to greatest
 * @param file - an ofstream representing the file to print to
 */
template<typename T>
void LazyBST<T>::printToFile(std::ofstream& file) {
    printToFileHelper(m_root, file);
}

/** printToFileHelper
 * Uses recursion to help print the tree to a file in order from least to greatest
 * @param subTreeRoot - the root of the subtree to print
 * @param outFile - an ofstream representing the file to print to
 */
template<typename T>
void LazyBST<T>::printToFileHelper(TreeNode<T>* subTreeRoot, std::ofstream& outFile) {
    if (subTreeRoot == nullptr)
        return;
    printToFileHelper(subTreeRoot->m_left, outFile);
    outFile << subTreeRoot->m_data << std::endl;
    printToFileHelper(subTreeRoot->m_right, outFile);
}

#endif
