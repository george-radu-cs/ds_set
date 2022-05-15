#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include "RBNode.h"

class RedBlackTree {
private:
  RBNode *root; /* the root of the tree */
  long long int size;     /* no. of elements in the tree */

  /* swap the colors of 2 red-black nodes */
  static void swapColors(RBNode *n1, RBNode *n2);

  /* swap the infos of 2 red-black nodes */
  static void swapInfo(RBNode *n1, RBNode *n2);

  /* rotate to the left the subtree with the root node */
  void leftRotate(RBNode *node);

  /* rotate to the right the subtree with the root node */
  void rightRotate(RBNode *node);

  /* fix the red-red violation of the red-black tree */
  void fixRedRedViolation(RBNode *node);

  /* fix the case when a node has the color double black - a node can become
   * double black only after a deletion from the tree */
  void fixDoubleBlack(RBNode *node);

  /* delete a node, the methode receive a pointer of type RBNode, which
   * points to the node that will be deleted */
  void deleteNode(RBNode *dnode);

  /* method to delete the tree(if is called with root) or a subtree */
  void deleteTree(RBNode *node);

  RBNode *search(long long int x); /* search for an item by value */

  /* return a pointer to the k-th smallest node in the tree */
  RBNode *kthSmallestNode(RBNode *node, long long int &k);

  /* print methods */
  /* left, root, right */
  void Inorder(RBNode *ptr, std::ostream &out);

  /* root, left, right */
  void Preorder(RBNode *ptr, std::ostream &out);

  /* left, right, root */
  void Postorder(RBNode *ptr, std::ostream &out);

  void levelOrder(RBNode *ptr, std::ostream &out);

public:
  RedBlackTree();

  ~RedBlackTree();

  /* insert a unique int in tree */
  void insertElement(long long int x);

  /* delete an element from the tree by value */
  void deleteElement(long long int x);

  long long int min(); /* find the minimum in the set */

  long long int max(); /* find the maximum in the set */

  /* find the successor of a given element by value */
  long long int successor(long long int x);

  /* find the predecessor of a given element by value */
  long long int predecessor(long long int x);

  /* the subscript operator, return the k-element inorder */
  long long int operator[](long long int k);

  /* return the cardinal of the tree */
  long long int cardinal() const { return size; };

  bool isIn(long long int x); /* check if an element x is in the tree */

  void print(std::ostream &out = std::cout); /* print the tree -> SRD, RSD */

  /* print the elements in sorted order */
  friend std::ostream &operator<<(std::ostream &out, RedBlackTree &rbt);
};

#endif