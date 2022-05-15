#ifndef RB_NODE_H
#define RB_NODE_H

#include <iostream>

enum class Color { /* the color of a node */
  RED,
  BLACK,

  MAX_COLOR __attribute__((unused))
};

class RBNode {
private:
  long long int info; /* the information stored by the node */
  RBNode *left, *right, *parent; /* links to his children(left and right) and
                                  * his parent */
  Color color; /* the color of the node */
  long long int size;

public:
  RBNode()
          : info(0), left(nullptr), right(nullptr), parent(nullptr),
            color(Color::RED), size(1) {}

  explicit RBNode(long long int i)
          : info(i), left(nullptr), right(nullptr), parent(nullptr),
            color(Color::RED), size(1) {}

  long long int getInfo() const { return info; }

  RBNode *getLeft() { return left; }

  RBNode *getRight() { return right; }

  RBNode *getParent() { return parent; }

  Color getColor() { return color; }

  long long int getSize() const { return size; }

  void setInfo(long long int i) { info = i; }

  void setLeft(RBNode *node) { left = node; }

  void setRight(RBNode *node) { right = node; }

  void setParent(RBNode *node) { parent = node; }

  void setColor(Color c) { color = c; }

  void setSize(long long int x) { size = x; }

  /* returns pointer to uncle, if exists */
  RBNode *getUncle() {
    /* the current node can't have an uncle if it doesn't have a parent and a
     * grandparent */
    if (parent == nullptr || parent->parent == nullptr) {
      return nullptr;
    }

    if (parent == parent->parent->getLeft()) { /* uncle on right */
      return parent->parent->right;
    } else { /* uncle on left */
      return parent->parent->left;
    }
  }

  /* return pointer to sibling, if exists */
  RBNode *sibling() {
    if (parent == nullptr) { /* if the node doesn't have a parent */
      return nullptr;
    }

    /* find the sibling */
    if (this == parent->left) { /* sibling on right */
      return parent->right;
    } else { /* sibling on left */
      return parent->left;
    }
  }

  /* check if the current node has a red child */
  bool hasRedChild() {
    return (left != nullptr && left->color == Color::RED) ||
           (right != nullptr && right->color == Color::RED);
  }

  /* print the node's info */
  friend std::ostream &operator<<(std::ostream &out, const RBNode &node) {
    out << node.info;
    return out;
  }
};

#endif
