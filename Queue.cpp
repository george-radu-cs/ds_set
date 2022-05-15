#include "Queue.h"

Queue::~Queue() {
  QNode *cross = head;
  if (head != nullptr) {
    while (cross != tail) {
      cross = cross->getNext();
      delete cross->getPrev();
    }
    delete tail;
  }
  cross = nullptr;
  head = nullptr;
  tail = nullptr;
}

void Queue::push(RBNode *x) {
  QNode *new_qnode = new QNode(x);

  if (head == nullptr) { /* base case - when queue is empty */
    /* head will be the same with tail until a new qnode is added */
    head = new_qnode;
    tail = new_qnode;
    /* create the links between nodes */
    head->setNext(tail);
    tail->setPrev(head);
    return;
  } else { /* a new node will be added at the end */
    /* create the links between nodes */
    tail->setNext(new_qnode);
    new_qnode->setPrev(tail);
    tail = new_qnode; /* update the tail */
  }

}

RBNode *Queue::pop() {
  RBNode *rbnode = nullptr;

  if (head == tail) { /* when queue has only one node */
    rbnode = head->getRBNode();
    delete head;
    head = nullptr;
    tail = nullptr;
  } else if (head == tail->getPrev()) { /* when queue has 2 nodes, set up for
    * the case when it will have only one(head==tail) */
    rbnode = head->getRBNode();
    head = head->getNext();
    delete tail->getPrev();
    head->setNext(tail);
    tail->setPrev(head);
  } else if (head != nullptr) { /* normal case */
    rbnode = head->getRBNode(); /* get the first RBNode from the queue */
    /* delete the first qnode and update the links in the queue */
    head = head->getNext();
    delete head->getPrev();
    head->setPrev(nullptr);
  }

  return rbnode;
}

bool Queue::empty() {
  /* the queue is empty iff head is nullptr */
  return head == nullptr;
}