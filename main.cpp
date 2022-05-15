#include "RedBlackTree.h"
#include "Queue.h"
#include <fstream>

int main() {
  if (1) {
    RedBlackTree s = RedBlackTree();

//  std::cout << s.min();
//  std::cout << s.max();

    s.insertElement(1);
    s.insertElement(2);
    s.insertElement(3);
    s.insertElement(4);
    s.insertElement(5);
    s.insertElement(6);
    s.insertElement(7);
    s.insertElement(8);
    s.insertElement(9);
    s.insertElement(10);
    s.print();

    std::cout << "\nk-th tests\n";
    for(int i=0;i<10;i++)
      std::cout << s[i] << " ";
    std::cout << "\n\n";


    std::cout << s.cardinal() << "cardinal\n";
    std::cout << "min is " << s.min() << " and max is " << s.max() << '\n';

    /* teste de sterge a unui element care nu se afla in set */
//  s.deleteElement(100);
//  s.print();

    /* teste de sterge a nr */
//  s.deleteElement(1);
//  s.print();
    s.deleteElement(1);
    std::cout << s.cardinal() << "cardinal\n";
    s.deleteElement(6);
    std::cout << s.cardinal() << "cardinal\n";
    s.print();

    std::cout << "\nk-th tests\n";
    for(int i=0;i<8;i++)
      std::cout << s[i] << " ";
    std::cout << "\n\n";

    for (int i = 0; i < 13; i++) {
      std::cout << "predecesorul lui " << i << " este " << s.predecessor(i) <<
                '\n';
    }

    std::cout << "\n\n\n";
    for (int i = 0; i < 13; i++) {
      std::cout << "succesorul lui " << i << " este " << s.successor(i) << '\n';
    }

    std::cout << "min is " << s.min() << " and max is " << s.max() << '\n';

    s.print();
    for (int i = 0; i < s.cardinal(); i++) {
      std::cout << "s[" << i << "]: " << s[i] << "\n";
    }
    /* test < 0 */
//  std::cout << s[-1];
    /* test k > size */
//  std::cout << s[s.cardinal()];

    for (int i = 0; i < 14; i++) {
      if (s.isIn(i)) {
        std::cout << i << " is in the tree\n";
      } else {
        std::cout << i << " isn't in the tree\n";
      }
    }

    std::cout << s;
    std::ofstream fout("print.out");
    fout << s;
    fout.close();
  } else {

    Queue q;
    if (q.empty()) {
      std::cout << "queue empty\n";
    } else {
      std::cout << "queue NOT empty\n";
    }

    RBNode *r1 = new RBNode(1);
    q.push(r1);
    if (q.empty()) {
      std::cout << "queue empty\n";
    } else {
      std::cout << "queue NOT empty\n";
    }
    q.print();


    RBNode *r2 = new RBNode(2);
    q.push(r2);
    q.print();
    RBNode *r3 = new RBNode(3);
    q.push(r3);
    q.print();
    RBNode *r4 = new RBNode(4);
    q.push(r4);
    q.print();
    RBNode *r5 = new RBNode(5);
    q.push(r5);
    q.print();
    RBNode *r6 = new RBNode(6);
    q.push(r6);
    q.print();


    if (q.empty()) {
      std::cout << "queue empty\n";
    } else {
      std::cout << "queue NOT empty\n";
    }

    while (!q.empty()) {
      std::cout << *q.pop() << " was popped, the queue contains: ";
      q.print();
    }
    std::cout << "\n\n\n";
    q.push(r1);
    q.print();
    q.push(r5);
    q.print();

    delete r1;
    delete r2;
    delete r3;
    delete r4;
    delete r5;
    delete r6;
  }

  return 0;
}
