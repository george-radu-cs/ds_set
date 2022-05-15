#ifndef QUEUE_H
#define QUEUE_H

#include "QNode.h"

/* small implementation of a queue using a double linked list
 * a queue use FIFO manner */
class Queue {
private:
  QNode *head, *tail; /* first and last element of the queue */

public:
  Queue() : head(nullptr), tail(nullptr) {}

  ~Queue();

  /* push a rbnode at the final of the queue */
  void push(RBNode *x);

  /* return the first element of the queue */
  RBNode *pop();

  /* return true if queue is empty */
  bool empty();

  void print() {
    QNode *cross = head;
    if (cross != nullptr) {
      while (cross != tail) {
        std::cout << *cross->getRBNode() << " ";
        cross = cross->getNext();
      }
      std::cout << *tail->getRBNode() << "\nINVERS:";
      cross = tail;
      while (cross != head) {
        std::cout << *cross->getRBNode() << " ";
        cross = cross->getPrev();
      }
      std::cout << *head->getRBNode() << '\n';
    }
  }

};

#endif