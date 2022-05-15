#ifndef Q_NODE_H
#define Q_NODE_H

#include "RBNode.h"

/* a qnode is used only for queue class, the qnode contains a pointer to a
 * RBNode and 2 pointers to qnode for crossing through queue */
class QNode {
private:
  RBNode *node; /* the info of qnode represents a pointer to RBNode */
  QNode *prev, *next; /* links for crossing a queue */

public:
  QNode() : node(nullptr), prev(nullptr), next(nullptr) {}

  explicit QNode(RBNode *n) : node(n), prev(nullptr), next(nullptr) {}

  /* we won't delete here the pointer node because it will be deleted in
   * other parts of the program, same with prev and next */
  ~QNode() = default;

  RBNode *getRBNode() { return node; }

  QNode *getPrev() { return prev; }

  QNode *getNext() { return next; }

  void setPrev(QNode *p) { prev = p; }

  void setNext(QNode *n) { next = n; }
};

#endif