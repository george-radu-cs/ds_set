#include "RedBlackTree.h"
#include "Queue.h"
#include <cassert>

RedBlackTree::RedBlackTree() : root(nullptr), size(0) {}

RedBlackTree::~RedBlackTree() {
  /* 2 methods to free up memory
   * 1st: create a new private recurive method to delete the tree from bottom
   * to top; time complexity O(n) to delete n elements and space complexity is
   * O(h) where h is the height of the tree, h=log n
   * 2nd: delete the tree from top to bottom, delete at each step every level
   * and store it's childrens in a queue; time complexity O(n) to delete n
   * elements and space complexity is O(n), at most it may contain the bottom
   * level n/2 leaves */

  deleteTree(root);
}

void RedBlackTree::swapColors(RBNode *n1, RBNode *n2) {
  Color temp_color;
  temp_color = n1->getColor();
  n1->setColor(n2->getColor());
  n2->setColor(temp_color);
}

void RedBlackTree::swapInfo(RBNode *n1, RBNode *n2) {
  long long int temp_info;
  temp_info = n1->getInfo();
  n1->setInfo(n2->getInfo());
  n2->setInfo(temp_info);
}

void RedBlackTree::leftRotate(RBNode *node) {
  /* the new parent will become the node's right child */
  RBNode *new_parent = node->getRight();

  if (node == root) {  /* if the current node is root, then update the root */
    root = new_parent; /* to be his right child */
  }

  /* interchange the node with his right child */
  /* if the node has a parent, change the parent's son to point to new_parent
   * instead of node */
  if (node->getParent() != nullptr) {
    if (node == node->getParent()->getLeft()) { /* the node is on the left */
      node->getParent()->setLeft(new_parent);
    } else { /* the node is on the right */
      node->getParent()->setRight(new_parent);
    }
  }
  /* make a link from new_parent to old node's parent */
  new_parent->setParent(node->getParent());
  /* set the parent of node to point to the new_parent */
  node->setParent(new_parent);
  /* the right subtree of node will become the new_parent's left subtree */
  node->setRight(new_parent->getLeft());
  /* if the left subtree of new_parent is not null then make a link from it to
   * the node */
  if (new_parent->getLeft() != nullptr) {
    new_parent->getLeft()->setParent(node);
  }
  /* set the parent's left child to point to the node */
  new_parent->setLeft(node);

  /* actualize the size for each node moved */
  new_parent->setSize(node->getSize());
  long long int left_size{0};
  long long int right_size{0};
  if (node->getLeft() != nullptr) {
    left_size = node->getLeft()->getSize();
  }
  if (node->getRight() != nullptr) {
    right_size = node->getRight()->getSize();
  }
  node->setSize(left_size + right_size + 1);
}

void RedBlackTree::rightRotate(RBNode *node) {
  /* the new parent will become the node's left child */
  RBNode *new_parent = node->getLeft();

  if (node == root) {  /* if the current node is root, then update the root */
    root = new_parent; /* to be his right child */
  }

  /* interchange the node with his right child */
  /* if the node has a parent, change the parent's son to point to new_parent
   * instead of node */
  if (node->getParent() != nullptr) {
    if (node == node->getParent()->getLeft()) { /* the node is on the left */
      node->getParent()->setLeft(new_parent);
    } else { /* the node is on the right */
      node->getParent()->setRight(new_parent);
    }
  }
  /* make a link from new_parent to old node's parent */
  new_parent->setParent(node->getParent());
  /* set the parent of node to point to the new_parent */
  node->setParent(new_parent);
  /* the left subtree of node will become the new_parent's right subtree */
  node->setLeft(new_parent->getRight());
  /* if the right subtree of new_parent is not null then make a link from it to
   * the node */
  if (new_parent->getRight() != nullptr) {
    new_parent->getRight()->setParent(node);
  }
  /* set the parent's right child to point to the node */
  new_parent->setRight(node);

  /* actualize the size for each node moved */
  new_parent->setSize(node->getSize());
  long long int left_size{0};
  long long int right_size{0};
  if (node->getLeft() != nullptr) {
    left_size = node->getLeft()->getSize();
  }
  if (node->getRight() != nullptr) {
    right_size = node->getRight()->getSize();
  }
  node->setSize(left_size + right_size + 1);
}

void RedBlackTree::fixRedRedViolation(RBNode *node) {
  /* if the node is the root we simply change it's color to black */
  if (node == root) {
    node->setColor(Color::BLACK);
    return;
  }

  /* initialize the parent, grandparent & uncle of the node */
  RBNode *parent = node->getParent(),
          *grandparent = parent->getParent(),
          *uncle = node->getUncle();

  if (parent->getColor() == Color::RED) {
    if (uncle != nullptr &&
        uncle->getColor() == Color::RED) { /* case red parent, red uncle */
      /* set the color of parent and uncle to black */
      parent->setColor(Color::BLACK);
      uncle->setColor(Color::BLACK);
      grandparent->setColor(Color::RED);
      /* then check the grandparent for validity, as its parent may be red */
      fixRedRedViolation(grandparent);
    } else { /* case red parent, black uncle */
      if (parent == grandparent->getLeft()) {
        /* the parent is to his grandparent's left*/
        if (node == parent->getLeft()) { /* the node is to his parent's left */
          /* case left-left */
          swapColors(parent, grandparent);
        } else { /* the node is to this parent's right */
          /* case left-right */
          leftRotate(parent); /* left rotation of parent -> change to the case
                                 left-left */
          swapColors(node, grandparent);
        }
        /* for both left-left and left-right cases we need to rotate the
         * grandparent to the right */
        rightRotate(grandparent);
      } else { /* the parent is to his grandparent's right */
        if (node == parent->getLeft()) {
          /* case right-left */
          rightRotate(parent); /* right rotation of parent -> change to the case
                                  right-right */
          swapColors(node, grandparent);
        } else {
          /* case right-right */
          swapColors(parent, grandparent);
        }
        /* for both right-left and right-right cases we need to rotate the
         * grandparent to the left */
        leftRotate(grandparent);
      }
    }
  }
}

void RedBlackTree::fixDoubleBlack(RBNode *node) {
  if (node == root) { /* if the root is double black it will become single */
    return;           /* black and return */
  }

  RBNode *sibling = node->sibling();  /* get the sibling of node */
  RBNode *parent = node->getParent(); /* get the parent of node */

  if (sibling == nullptr) { /* if node hasn't a sibling */
    fixDoubleBlack(parent); /* then we move the double black up */
  } else {
    if (sibling->getColor() == Color::BLACK) { /* the sibling is black */
      if (sibling->hasRedChild()) { /* if sibling has a red child */
        /* we have 4 cases ll lr rr rl */
        if (sibling == parent->getLeft()) { /* sibling is on the left */
          if (sibling->getLeft() != nullptr &&
              sibling->getLeft()->getColor() == Color::RED) { /* left-left */
            sibling->getLeft()->setColor(sibling->getColor());
            sibling->setColor(parent->getColor());
            rightRotate(parent);
          } else { /* left-right */
            sibling->getRight()->setColor(parent->getColor());
            leftRotate(sibling);
            rightRotate(parent);
          }
        } else { /* sibling is on the right */
          if (sibling->getLeft() != nullptr &&
              sibling->getLeft()->getColor() == Color::RED) { /* right-left */
            sibling->getLeft()->setColor(parent->getColor());
            rightRotate(sibling);
            leftRotate(parent);
          } else { /* right-right */
            sibling->getRight()->setColor(sibling->getColor());
            sibling->setColor(parent->getColor());
            leftRotate(parent);
          }
        }

        parent->setColor(Color::BLACK);
      } else { /* sibling has both children black */
        sibling->setColor(Color::RED);
        if (parent->getColor() == Color::BLACK) { /* parent is black */
          fixDoubleBlack(parent); /* parent becomes double black */
        } else { /* the parent is red */
          parent->setColor(Color::BLACK); /* red + double black = black */
        }
      }
    } else { /* the sibling is red */
      parent->setColor(Color::RED);
      sibling->setColor(Color::BLACK);
      if (sibling == parent->getLeft()) { /* left case */
        rightRotate(parent);
      } else { /* right case */
        leftRotate(parent);
      }
      fixDoubleBlack(node);
    }
  }
  /* actualize the size for each node moved */
  long long int left_size{0};
  long long int right_size{0};
  if (parent->getLeft() != nullptr) {
    left_size = parent->getLeft()->getSize();
  }
  if (parent->getRight() != nullptr) {
    right_size = parent->getRight()->getSize();
  }
  parent->setSize(left_size + right_size + 1);
  left_size = 0;
  right_size = 0;
  if (sibling->getLeft() != nullptr) {
    left_size = sibling->getLeft()->getSize();
  }
  if (sibling->getRight() != nullptr) {
    right_size = sibling->getRight()->getSize();
  }
  sibling->setSize(left_size + right_size + 1);

  sibling = nullptr;
  parent = nullptr;
}

void RedBlackTree::deleteNode(RBNode *dnode) {
  /* actualize the size for nodes from dnode to root */
  RBNode *temp_fix_size = dnode;
  while (temp_fix_size != nullptr) {
    temp_fix_size->setSize(temp_fix_size->getSize() - 1);
    temp_fix_size = temp_fix_size->getParent();
  }

  /* dbst_node represents the node that replace dnode in a BST, if we were to
   * delete dnode in a BST */
  RBNode *rd_bst_node;
  /* when dnode is a leaf */
  if (dnode->getLeft() == nullptr && dnode->getRight() == nullptr) {
    rd_bst_node = nullptr;
  }
    /* when dnode has 2 children */
  else if (dnode->getLeft() != nullptr && dnode->getRight() != nullptr) {
    rd_bst_node = dnode->getRight();
    while (rd_bst_node->getLeft() != nullptr) {
      rd_bst_node = rd_bst_node->getLeft();
    }
  }
    /* when dnode has only a child */
  else if (dnode->getLeft() != nullptr) { /* dnode has only the left child */
    rd_bst_node = dnode->getLeft();
  } else { /* dnode the only the right child */
    rd_bst_node = dnode->getRight();
  }

  RBNode *dnode_parent = dnode->getParent();
  if (rd_bst_node == nullptr) { /* dnode is a leaf */
    if (dnode == root) { /* dnode is root */
      root = nullptr;
    } else {
      /* if both rd_bst_node and dnode are black */
      if (dnode->getColor() == Color::BLACK) {
        /* case dnode is leaf and has color black, fix double black at dnode */
        fixDoubleBlack(dnode);
      } else if (dnode->sibling() != nullptr) {
        dnode->sibling()->setColor(Color::RED);
      }

      /* delete the link of dnode from the tree */
      if (dnode == dnode_parent->getLeft()) {
        /* dnode is his parent's left child*/
        dnode_parent->setLeft(nullptr);
      } else { /* dnode is his parent's right child */
        dnode_parent->setRight(nullptr);
      }
    }

    delete dnode; /* delete the node from memory */
    dnode = nullptr;
    dnode_parent = nullptr;
    return;
  }

  /* if dnode has only a child */
  if (dnode->getLeft() == nullptr || dnode->getRight() == nullptr) {
    if (dnode == root) {
      dnode->setInfo(rd_bst_node->getInfo());
      /* delete his children */
      dnode->setLeft(nullptr);
      dnode->setRight(nullptr);
      delete rd_bst_node;
      rd_bst_node = nullptr;
      return;
    } else {
      /* eliminate dnode from the tree and move rd_bst_node up */
      if (dnode == dnode_parent->getLeft()) {
        /* dnode is his parent's left child */
        dnode_parent->setLeft(rd_bst_node);
      } else { /* dnode is his parent's right child */
        dnode_parent->setRight(rd_bst_node);
      }

      Color dnode_color = dnode->getColor(); /* remember the color of dnode */
      delete dnode;

      /* repair the link from bottom to top */
      rd_bst_node->setParent(dnode_parent);
      if (rd_bst_node->getColor() == Color::BLACK &&
          dnode_color == Color::BLACK) { /* if both are black */
        fixDoubleBlack(rd_bst_node);
      } else { /* one of them is red */
        rd_bst_node->setColor(Color::BLACK);
      }
    }

    return;
  }

  /* if the control reaches here then dnode has 2 children
   * in that case swap values between dnode and rd_bst_node and recurse to
   * complete the deletion */
  swapInfo(dnode, rd_bst_node);
  deleteNode(rd_bst_node);
}

void RedBlackTree::deleteTree(RBNode *node) {
  if (node == nullptr) {
    return;
  }

  /* delete the left and right subtree, i.e. postorder */
  deleteTree(node->getLeft());
  deleteTree(node->getRight());

  /* delete the node and set the pointer to nullptr */
  delete node;
  node = nullptr;
}

RBNode *RedBlackTree::search(long long int x) {
  RBNode *v = root; /* we cross through the tree */

  /* we search for the value x
   * if x is found in the tree we return the node
   * else we return the last node in the traversing */
  while (v != nullptr) {
    if (x < v->getInfo() && v->getLeft() != nullptr) {
      v = v->getLeft();
    } else if (x > v->getInfo() && v->getRight() != nullptr) {
      v = v->getRight();
    } else if (x == v->getInfo()) {
      break; /* we found x, we don't need to search it anymore */
    } else {
      break;
    }
  }

  return v;
}

RBNode *RedBlackTree::kthSmallestNode(RBNode *node, long long int &k) {
  if (node == nullptr) {
    return nullptr;
  }

  /* first search in the left subtree of node */
  RBNode *left = kthSmallestNode(node->getLeft(), k);

  /* if the k-th smallest element was found in the left subtree */
  if (left != nullptr) {
    return left;
  }

  k--; /* marks crossing through a node from the tree */
  if (k == 0) { /* found the k-th smallest element */
    return node;
  }

  /* otherwise search in the right subtree */
  return kthSmallestNode(node->getRight(), k);
}

void RedBlackTree::Inorder(RBNode *ptr, std::ostream &out) {
  if (ptr != nullptr) {
    Inorder(ptr->getLeft(), out);
    out << *ptr << " ";
    Inorder(ptr->getRight(), out);
  }
}

void RedBlackTree::Preorder(RBNode *ptr, std::ostream &out) {
  if (ptr != nullptr) {
    out << *ptr << " ";
    Preorder(ptr->getLeft(), out);
    Preorder(ptr->getRight(), out);
  }
}

void RedBlackTree::Postorder(RBNode *ptr, std::ostream &out) {
  if (ptr != nullptr) {
    Postorder(ptr->getLeft(), out);
    Postorder(ptr->getRight(), out);
    out << *ptr << " ";
  }
}

void RedBlackTree::levelOrder(RBNode *ptr, std::ostream &out) {
  if (ptr == nullptr)
    return;

  Queue q;
  RBNode *curr;
  q.push(ptr);

  while (!q.empty()) {
    curr = q.pop();

    out << "val: " << curr->getInfo() << " | color: ";
    if (curr->getColor() == Color::RED)
      out << "red";
    else
      out << "black";
    out << " | size: " << curr->getSize();
    out << " | parent: ";
    if (curr->getParent() != nullptr)
      out << curr->getParent()->getInfo();
    out << '\n';

    if (curr->getLeft() != nullptr)
      q.push(curr->getLeft());
    if (curr->getRight() != nullptr)
      q.push(curr->getRight());
  }
}

void RedBlackTree::insertElement(long long int x) {
  RBNode *new_rb_node = new RBNode(x); /* create the new node */

  if (root == nullptr) { /* we don't have nodes in the tree - base case */
    new_rb_node->setColor(Color::BLACK);
    root = new_rb_node;
  } else {
    RBNode *temp = this->search(x);

    if (temp->getInfo() == x) { /* we already have the value in the tree */
      delete new_rb_node;
      return;
    }

    /* actualize the size for each node from root until new node */
    RBNode *temp_increase = temp;
    while (temp_increase != nullptr) {
      temp_increase->setSize(temp_increase->getSize() + 1);
      temp_increase = temp_increase->getParent();
    }

    /* if we don't have the value in the tree, the search will return the parent
     * of the new node */
    new_rb_node->setParent(temp); /* we set the new node's parent to temp */
    if (x < temp->getInfo()) {
      temp->setLeft(new_rb_node);
    } else {
      temp->setRight(new_rb_node);
    }

    /* and then fix the red-red violation if 	y->size = x->size; exists */
    this->fixRedRedViolation(new_rb_node);
  }

  size++;
}

void RedBlackTree::deleteElement(long long int x) {
  /* find the pointer to the node with value x which we want to delete */
  RBNode *dnode = search(x);

  if (dnode == nullptr || dnode->getInfo() != x) { /* check if we have x to
                                                    * delete in the tree */
    std::cout << "The value " << x
              << " is not in the set, we have nothing to delete\n";
  } else {
    deleteNode(dnode);
    size--; /* adjust the cardinal of the set */
  }
}

long long int RedBlackTree::min() {
  RBNode *v = root;
  long long int min_value;

  assert((v != nullptr) && "The tree is empty");

  /* the smallest element in a tree is the leftmost leaf */
  while (v->getLeft() != nullptr) {
    v = v->getLeft();
  }
  min_value = v->getInfo();

  v = nullptr;
  return min_value;
}

long long int RedBlackTree::max() {
  RBNode *v = root;
  long long int max_value;

  assert((v != nullptr) && "The tree is empty");

  /* the biggest element in a tree is the rightmost leaf */
  while (v->getRight() != nullptr) {
    v = v->getRight();
  }
  max_value = v->getInfo();

  v = nullptr;
  return max_value;
}

long long int RedBlackTree::successor(long long int x) {
  RBNode *succ = search(x); /* find the node with value x */

  if (succ == nullptr || succ->getInfo() != x) { /* if x is not in the tree */
    std::cout << x << " is not in the tree, we can't find it's successor\n";
    succ = nullptr;
    return -1; /* maybe change here to return a bool and send the successor
 * in with a reference param, same with predecessor */
  }

  /* if the node has a right subtree then the successor is the leftmost
   * node in it */
  if (succ->getRight() != nullptr) {
    /* move the pointer to the root of the right subtree */
    succ = succ->getRight();
    /* and search for the leftmost node */
    while (succ->getLeft() != nullptr) {
      succ = succ->getLeft();
    }

    return succ->getInfo();
  } else { /* if the node hasn't a right subtree, then the successor can
    * only be in the parent nodes(parent, grandparent, grand-grandparent...
    * until root */
    while (succ->getParent() != nullptr) { /* search in parents */
      succ = succ->getParent();
      if (succ->getInfo() > x) { /* we found the successor */
        return succ->getInfo();
      }
    }

    /* if the control reaches here, then x represent the max in the tree, and
     * obviusly it can't have a successor */
    std::cout << x << " is the maximum element in the tree so it cannot have a "
                      "successor\n";
    succ = nullptr;
    return -1;
  }
}

long long int RedBlackTree::predecessor(long long int x) {
  RBNode *pred = search(x); /* find the node with value x */

  if (pred == nullptr || pred->getInfo() != x) { /* if x is not in the tree */
    std::cout << x << " is not in the tree, we can't find it's predecessor\n";
    pred = nullptr;
    return -1;
  }

  /* if the node has a left subtree then the predecessor is the rightmost
   * node in it */
  if (pred->getLeft() != nullptr) {
    /* move the pointer to the root of the left subtree */
    pred = pred->getLeft();
    while (pred->getRight() !=
           nullptr) { /* and search for the rightmost node */
      pred = pred->getRight();
    }

    return pred->getInfo();
  } else { /* if the node hasn't a left subtree, then the predecessor can
    * only be in the parent nodes(parent, grandparent, grand-grandparent...
    * until root */
    while (pred->getParent() != nullptr) { /* search in parents */
      pred = pred->getParent();
      if (pred->getInfo() < x) { /* we found the predecessor */
        return pred->getInfo();
      }
    }

    /* if the control reaches here, then x represent the min in the tree, and
     * obviusly it can't have a predecessor */
    std::cout << x << " is the minimum element in the tree so it cannot have a "
                      "predecessor\n";
    pred = nullptr;
    return -1;
  }
}

long long int RedBlackTree::operator[](long long int k) {
  assert((0 <= k && k < size) && "Index out of range!");

  k++;
//  return kthSmallestNode(root, k)->getInfo();

  long long int curr_rank{1};
  if (root->getLeft() != nullptr) {
    curr_rank = root->getLeft()->getSize() + 1;
  }
  RBNode *ptr = root;
  while (ptr != nullptr && curr_rank != k) {
    if (k < curr_rank) {
      ptr = ptr->getLeft();
    } else {
      k -= curr_rank;
      ptr = ptr->getRight();
    }
    if (ptr == nullptr) {
      return -1;
    }
    if (ptr->getLeft() != nullptr)
      curr_rank = ptr->getLeft()->getSize() + 1;
    else
      curr_rank = 1;
  }
  return ptr->getInfo();
}

bool RedBlackTree::isIn(long long int x) {
  RBNode *v = root; /* pointer to cross the tree */
  bool is{false}; /* remember if we find the value in the tree */

  while (v != nullptr) {
    if (x < v->getInfo() && v->getLeft() != nullptr) {
      v = v->getLeft();
    } else if (x > v->getInfo() && v->getRight() != nullptr) {
      v = v->getRight();
    } else if (x == v->getInfo()) {
      is = true;
      break; /* we found x, we don't need to search it anymore */
    } else {
      break;
    }
  }

  v = nullptr; /* clean up */
  return is;
}

void RedBlackTree::print(std::ostream &out) {
  out << "Inorder: ";
  Inorder(root, out);
  out << "\nPreorder: ";
  Preorder(root, out);
  out << "\nPostorder: ";
  Postorder(root, out);
  out << "\nLevel order: ";
  levelOrder(root, out);
  out << '\n';
}

std::ostream &operator<<(std::ostream &out, RedBlackTree &rbt) {
  rbt.Inorder(rbt.root, out);

  return out;
}