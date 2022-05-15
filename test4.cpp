/* test 4 - 1 set with few items: 1 000 000 */

#include "RedBlackTree.h"
#include "functions.cpp"
#include <chrono>
#include <ctime>
#include <fstream>
#include <random>

int main() {
  std::srand(static_cast<unsigned int>(std::time(nullptr)));

  /* use this timer to show up in console intermediate steps, so we now that
   * our program still works and which task is doing */
  std::chrono::time_point<std::chrono::high_resolution_clock> timer_for_console;
  timer_for_console = std::chrono::high_resolution_clock::now();

  /* create the data for the test and write to test4.in */
  long long int n = 1000000; /* no of elements */
  long long int lower_bound{-10000000}, upper_bound{10000000};
  long long int *v = new long long int[n];
  long long int x;
  bool is_duplicate;
  for (long long int i = 0; i < n; i++) {
    is_duplicate = false;
    x = RNG(lower_bound, upper_bound);
    for (long long int j = 0; j < i; j++) {
      if (v[j] == x) {
        is_duplicate = true;
        break;
      }
    }
    if (!is_duplicate) {
      v[i] = x;
    } else {
      i--;
    }
  }
  long long int number_testing = ceil(10 * n / 100.0);
  long long int index;
  lower_bound = 0;
  upper_bound = n - 1;

  /* write the data */
  std::ofstream create_fout("test4.in");
  create_fout << n + number_testing << '\n';
  for (long long int i = 0; i < n; i++) { /* add all the elements */
    create_fout << v[i] << " ";
  }
  for (long long int i = 0; i < number_testing; i++) { /* add some duplicates */
    index = RNG(lower_bound, upper_bound);
    create_fout << v[index] << " ";
  }

  create_fout.close();
  std::cout << "finished generating the input file\n"
            << std::chrono::duration_cast<
                   std::chrono::duration<double, std::ratio<1>>>(
                   std::chrono::high_resolution_clock::now() -
                   timer_for_console)
                   .count()
            << '\n';

  /* sort the array */
  mergeSort(v, 0, n - 1);
  std::cout << "finished sorting the array for testing\n"
            << std::chrono::duration_cast<
                   std::chrono::duration<double, std::ratio<1>>>(
                   std::chrono::high_resolution_clock::now() -
                   timer_for_console)
                   .count()
            << '\n';

  /* run the test */

  /* open the file for writing  */
  std::ofstream fout("test4.out");

  /* set up the timers */
  /* timer for the total of all task */
  std::chrono::time_point<std::chrono::high_resolution_clock> timer_total;
  /* timer for every intermediary step like insertion, deletion, etc */
  std::chrono::time_point<std::chrono::high_resolution_clock> timer_step;
  /* timer for each task in a step */
  std::chrono::time_point<std::chrono::high_resolution_clock> timer;
  timer_total = std::chrono::high_resolution_clock::now();
  timer = std::chrono::high_resolution_clock::now();

  /* read the data */
  std::ifstream fin("test4.in");
  long long int size;
  fin >> size;
  RedBlackTree rbt;
  for (long long int i = 0; i < size; i++) {
    fin >> x;
    rbt.insertElement(x);
  }
  fout << "Time to read: "
       << std::chrono::duration_cast<
              std::chrono::duration<double, std::ratio<1>>>(
              std::chrono::high_resolution_clock::now() - timer)
              .count()
       << "s\n\n";
  fin.close();

  /* printing */
  fout << "Print the set: ";
  timer = std::chrono::high_resolution_clock::now();
  fout << rbt << '\n';
  fout << "Time to print: "
       << std::chrono::duration_cast<
              std::chrono::duration<double, std::ratio<1>>>(
              std::chrono::high_resolution_clock::now() - timer)
              .count()
       << "s\n\n";

  /* cardinal */
  timer = std::chrono::high_resolution_clock::now();
  fout << "Cardinal: " << rbt.cardinal() << '\n';
  fout << "Time to get and print the cardinal: "
       << std::chrono::duration_cast<
              std::chrono::duration<double, std::ratio<1>>>(
              std::chrono::high_resolution_clock::now() - timer)
              .count()
       << "s\n";
  if (rbt.cardinal() == n) {
    fout << "The cardinal was calculated correctly.\n\n";
  } else {
    fout << "The cardinal was calculated correctly.\n\n";
  }
  size = rbt.cardinal(); /* actualize the new cardinal */

  /* min */
  timer = std::chrono::high_resolution_clock::now();
  fout << "The minimum is: " << rbt.min() << '\n';
  fout << "Time to get and print the minimum: "
       << std::chrono::duration_cast<
              std::chrono::duration<double, std::ratio<1>>>(
              std::chrono::high_resolution_clock::now() - timer)
              .count()
       << "s\n";
  if (rbt.min() == v[0]) {
    fout << "The minimum is found correctly.\n\n";
  } else {
    fout << "The minimum is not found correctly.\n\n";
  }

  /* max */
  timer = std::chrono::high_resolution_clock::now();
  fout << "The maximum is: " << rbt.max() << '\n';
  fout << "Time to get and print the maximum: "
       << std::chrono::duration_cast<
              std::chrono::duration<double, std::ratio<1>>>(
              std::chrono::high_resolution_clock::now() - timer)
              .count()
       << "s\n";
  if (rbt.max() == v[size - 1]) {
    fout << "The maximum is found correctly.\n\n";
  } else {
    fout << "The maximum is not found correctly.\n\n";
  }

  /* successor */
  lower_bound = 0;
  upper_bound = size - 2;
  timer_step = std::chrono::high_resolution_clock::now();
  for (long long int i = 0; i < number_testing; i++) {
    index = RNG(lower_bound, upper_bound);

    timer = std::chrono::high_resolution_clock::now();
    fout << "The successor of " << v[index] << " is " << rbt.successor(v[index])
         << '\n';
    fout << "Time to get and print the successor: "
         << std::chrono::duration_cast<
                std::chrono::duration<double, std::ratio<1>>>(
                std::chrono::high_resolution_clock::now() - timer)
                .count()
         << "s\n";
    if (index + 1 < size) {
      if (rbt.successor(v[index]) == v[index + 1]) {
        fout << "The successor is found correctly.\n";
      } else {
        fout << "The successor is not found correctly.\n";
      }
    }
    fout << '\n';
  }
  fout << "Time to get and print all the above successors is: "
       << std::chrono::duration_cast<
              std::chrono::duration<double, std::ratio<1>>>(
              std::chrono::high_resolution_clock::now() - timer_step)
              .count()
       << "s\n\n";

  /* predecessor */
  lower_bound = 1;
  upper_bound = size - 1;
  timer_step = std::chrono::high_resolution_clock::now();
  for (long long int i = 0; i < number_testing; i++) {
    index = RNG(lower_bound, upper_bound);

    timer = std::chrono::high_resolution_clock::now();
    fout << "The predecessor of " << v[index] << " is "
         << rbt.predecessor(v[index]) << '\n';
    fout << "Time to get and print the predecessor: "
         << std::chrono::duration_cast<
                std::chrono::duration<double, std::ratio<1>>>(
                std::chrono::high_resolution_clock::now() - timer)
                .count()
         << "s\n";
    if (index - 1 >= 0) {
      if (rbt.predecessor(v[index]) == v[index - 1]) {
        fout << "The predecessor is found correctly.\n";
      } else {
        fout << "The predecessor is not found correctly.\n";
      }
    }
    fout << '\n';
  }
  fout << "Time to get and print all the above predecessors is: "
       << std::chrono::duration_cast<
              std::chrono::duration<double, std::ratio<1>>>(
              std::chrono::high_resolution_clock::now() - timer_step)
              .count()
       << "s\n\n";

  /* k-th element */
  lower_bound = 1;
  upper_bound = size;
  timer_step = std::chrono::high_resolution_clock::now();
  for (long long int i = 1; i <= number_testing; i++) {
    index = RNG(lower_bound, upper_bound);

    /* the index for rbt starts from 0, reason for decrementing */
    timer = std::chrono::high_resolution_clock::now();
    fout << "The " << index << "-th element is " << rbt[index - 1] << '\n';
    fout << "Time to get and print the " << index << "-th element: "
         << std::chrono::duration_cast<
                std::chrono::duration<double, std::ratio<1>>>(
                std::chrono::high_resolution_clock::now() - timer)
                .count()
         << "s\n";
    if (rbt[index - 1] == v[index - 1]) {
      fout << "The " << index << "-th element is found correctly.\n";
    } else {
      fout << "The " << index << "-th element is not found correctly.\n";
    }
    fout << '\n';
  }
  fout << "Time to get and print all the above k-th elements is: "
       << std::chrono::duration_cast<
              std::chrono::duration<double, std::ratio<1>>>(
              std::chrono::high_resolution_clock::now() - timer_step)
              .count()
       << "s\n\n";

  /* isIn */
  /* all these tests must return true */
  lower_bound = 0;
  upper_bound = size - 1;
  timer_step = std::chrono::high_resolution_clock::now();
  for (long long int i = 0; i < number_testing; i++) {
    index = RNG(lower_bound, upper_bound);

    timer = std::chrono::high_resolution_clock::now();
    if (rbt.isIn(v[index])) {
      fout << v[index] << " is in the set\n";
    } else {
      fout << v[index] << " is not in the set\n";
    }
    fout << "Time to get and print if " << v[index] << " is in the set: "
         << std::chrono::duration_cast<
                std::chrono::duration<double, std::ratio<1>>>(
                std::chrono::high_resolution_clock::now() - timer)
                .count()
         << "s\n";
    if (rbt.isIn(v[index])) {
      fout << "The isIn method run correctly.\n";
    } else {
      fout << "The isIn method did not run correctly.\n";
    }
    fout << '\n';
  }
  fout << "Time to check all the above elements if they are in the set is: "
       << std::chrono::duration_cast<
              std::chrono::duration<double, std::ratio<1>>>(
              std::chrono::high_resolution_clock::now() - timer_step)
              .count()
       << "s\n\n";

  /* all these tests for isIn must return false */
  lower_bound = rbt.min() - 1000;
  upper_bound = rbt.min() - 1;
  timer_step = std::chrono::high_resolution_clock::now();
  for (long long int i = 0; i < number_testing / 2; i++) {
    x = RNG(lower_bound, upper_bound);

    timer = std::chrono::high_resolution_clock::now();
    if (rbt.isIn(x)) {
      fout << x << " is in the set\n";
    } else {
      fout << x << " isn't in the set\n";
    }
    fout << "Time to find if " << x << " is in the set: "
         << std::chrono::duration_cast<
                std::chrono::duration<double, std::ratio<1>>>(
                std::chrono::high_resolution_clock::now() - timer)
                .count()
         << "s\n";
    if (!rbt.isIn(x)) { /* isIn should return false */
      fout << "The isIn method run correctly.\n";
    } else {
      fout << "The isIn method did not run correctly.\n";
    }
    fout << '\n';
  }
  fout << "Time to check all the above elements if they are in the set is: "
       << std::chrono::duration_cast<
              std::chrono::duration<double, std::ratio<1>>>(
              std::chrono::high_resolution_clock::now() - timer_step)
              .count()
       << "s\n\n";

  lower_bound = rbt.max() + 1;
  upper_bound = rbt.max() + 1000;
  timer_step = std::chrono::high_resolution_clock::now();
  for (long long int i = 0; i < number_testing / 2; i++) {
    x = RNG(lower_bound, upper_bound);

    timer = std::chrono::high_resolution_clock::now();
    if (rbt.isIn(x)) {
      fout << x << " is in the set\n";
    } else {
      fout << x << " isn't in the set\n";
    }
    fout << "Time to find if " << x << " is in the set: "
         << std::chrono::duration_cast<
                std::chrono::duration<double, std::ratio<1>>>(
                std::chrono::high_resolution_clock::now() - timer)
                .count()
         << "s\n";
    if (!rbt.isIn(x)) { /* isIn should return false */
      fout << "The isIn method run correctly.\n";
    } else {
      fout << "The isIn method did not run correctly.\n";
    }
    fout << '\n';
  }
  fout << "Time to check all the above elements if they are in the set is: "
       << std::chrono::duration_cast<
              std::chrono::duration<double, std::ratio<1>>>(
              std::chrono::high_resolution_clock::now() - timer_step)
              .count()
       << "s\n\n";

  /* delete some elements then check if they are in the set, the isIn method
   * must return false in this case */

  /* create a vector in which we will remember what numbers to delete */
  long long int *to_delete = new long long int[number_testing];
  lower_bound = 0;
  upper_bound = n - 1;
  for (long long int i = 0; i < number_testing; i++) {
    is_duplicate = false;
    x = v[RNG(lower_bound, upper_bound)];
    for (long long int j = 0; j < i; j++) {
      if (x == to_delete[j]) {
        is_duplicate = true;
      }
    }
    if (!is_duplicate) {
      to_delete[i] = x;
    } else {
      i--;
    }
  }

  /* all these tests must return false */
  timer_step = std::chrono::high_resolution_clock::now();
  for (long long int i = 0; i < number_testing; i++) {
    timer = std::chrono::high_resolution_clock::now();
    rbt.deleteElement(to_delete[i]);
    fout << "Time to delete " << to_delete[i] << " is: "
         << std::chrono::duration_cast<
                std::chrono::duration<double, std::ratio<1>>>(
                std::chrono::high_resolution_clock::now() - timer)
                .count()
         << "s\n";
    if (!rbt.isIn(to_delete[i])) {
      fout << to_delete[i] << " was deleted successfully.\n";
    } else {
      fout << to_delete[i] << " was not deleted successfully.\n";
    }
    fout << '\n';
  }
  fout << "Time to delete all the above elements is: "
       << std::chrono::duration_cast<
              std::chrono::duration<double, std::ratio<1>>>(
              std::chrono::high_resolution_clock::now() - timer_step)
              .count()
       << "s\n\n";

  fout << "Time to finish the test: "
       << std::chrono::duration_cast<
              std::chrono::duration<double, std::ratio<1>>>(
              std::chrono::high_resolution_clock::now() - timer_total)
              .count()
       << "s\n\n";
  fout.close();

  /* clean up the memory */
  delete[] v;
  delete[] to_delete;
  return 0;
}
