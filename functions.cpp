#include <cstdlib>

/* return a random number of type long long int between lower_bound and upper_bound */
long long int RNG(long long int lower_bound, long long int upper_bound) {
  /* we only need this to be calculated only once, reason for static, and we
   * don't need to change it so we make it constexpr to be calculated at compile
   * time */
  static constexpr double fraction{1.0 / (RAND_MAX + 1.0)};

  return lower_bound +
         static_cast<long long int>((upper_bound - lower_bound + 1) *
                                    (std::rand() * fraction));
}

/* merge 2 arrays */
void merge(long long int *v, long long int left, long long int mid,
           long long int right) {
  long long int n1 = mid - left + 1; /* size of left array */
  long long int n2 = right - mid;    /* size of right array */

  /* create temp arrays */
  long long int *L = new long long int[n1];
  long long int *R = new long long int[n2];

  /* copy the data from v to L and R */
  for (long long int i = 0; i < n1; i++) {
    L[i] = v[left + i];
  }
  for (long long int i = 0; i < n2; i++) {
    R[i] = v[mid + i + 1];
  }

  /* merge the 2 arrays */
  long long int i{0}, j{0}, k{left}; /* indexes for left array, right and v */

  /*  */
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) { /* the element from L is smaller */
      v[k] = L[i];
      i++;   /* increase the index for L */
    } else { /* the element from R is smaller */
      v[k] = R[j];
      j++; /* increase the index for R */
    }
    k++; /* increase the index for v */
  }

  /* one of the 2 arrays will finish first and the other one will still have
   * elements, so we need to add the rest, but we're not sure which one */

  while (i < n1) { /* if L still has elements */
    v[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) { /* if R still has elements */
    v[k] = R[j];
    j++;
    k++;
  }
}

void mergeSort(long long int *v, long long int left, long long int right) {
  if (left < right) {
    long long int mid = left + (right - left) / 2;
    mergeSort(v, left, mid);
    mergeSort(v, mid + 1, right);
    merge(v, left, mid, right);
  }
}