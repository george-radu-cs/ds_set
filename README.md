# Set implementation in C++

## Details

This project is for the Data Structures class. The project doesn't contain
anything from STL(a requirement for the project), reason for the implementation
of a small percentage of the queue class. The final report which contains info
about the class, the complexity of the methods in the chosen data structure(in
this case a red-black tree), why it was chosen, details about the tests made and
final thoughts.

## The structure of a test input file

### test1-5.in

- first row contains the number of elements
- the second row contains the numbers(not all distinct) that will be stored in
  the set

## The structure of a test output file

### test1-5.out

In each output file we will test each method of the class in big chunks of steps
(where is the case). In the file each line specify which task was done, the
time for its completion and print if the operation was done correctly.

- first read the data
- print the set(the elements will be sorted)
- print the cardinal
- print the minimum
- print the maximum
- print the successors of 10% of elements in the set
- time for find all the above successors
- print the predecessors of 10% of elements in the set
- time for find all the above predecessors
- print the k-th element of 10% of indexes in the set
- time for find all the above k-th elements
- check for 10% of values if are in the set
- print the time to check if the values are in the set
- delete 10% of values in the set
- print the time to delete those values
- print the time to complete all the above tests

