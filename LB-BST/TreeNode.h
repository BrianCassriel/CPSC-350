// Tree Node Class Header/Implementation
// This is a template class that implements a node for a binary search tree.

#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <cstdlib>
#include <iostream>
using namespace std;

template <typename T>
class TreeNode{
public:
  TreeNode(T d);
  virtual ~TreeNode();
  T getData();
  int getSubtreeHeight();

  template <typename S>
  friend class LazyBST;

private:
  TreeNode<T>* m_left;
  TreeNode<T>* m_right;
  T m_data;

  int getSubtreeHeightHelper(TreeNode<T>* subTreeRoot);
};

/** Constructor
 * @tparam T - the type of data to be stored in the node
 * @param d - the data to be stored
 */
template <typename T>
TreeNode<T>::TreeNode(T d){
  m_left = NULL;
  m_right = NULL;
  m_data = d;
}

/** Destructor
 * Deletes the left and right subtrees
 */
template <typename T>
TreeNode<T>::~TreeNode(){
  if(m_left != NULL){
    delete m_left;
  }
  if(m_right != NULL){
    delete m_right;
  }
}

/** getData
 * @return the data stored in the node
 */
template <typename T>
T TreeNode<T>::getData(){
  return m_data;
}

/** getSubtreeHeight
 * @return the height of the subtree rooted at this node
 */
template<typename T>
int TreeNode<T>::getSubtreeHeight() {
    return getSubtreeHeightHelper(this);
}

/** getSubtreeHeightHelper
 * A recursive method that helps getSubtreeHeight() find the height of the subtree rooted at the current node.
 * @param subTreeRoot - the root of the subtree to find the height of
 * @return the height of the subtree rooted at subTreeRoot
 */
template<typename T>
int TreeNode<T>::getSubtreeHeightHelper(TreeNode<T>* subTreeRoot) {
    if (subTreeRoot == nullptr)
        return 0;
    int leftTreeHeight = getSubtreeHeightHelper(subTreeRoot->m_left);
    int rightTreeHeight = getSubtreeHeightHelper(subTreeRoot->m_right);
    if (rightTreeHeight < leftTreeHeight)
        return 1 + leftTreeHeight;
    else if (rightTreeHeight >= leftTreeHeight)
        return 1 + rightTreeHeight;
    return 0;
}

#endif
