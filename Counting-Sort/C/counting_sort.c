#include <stdio.h>
#include <stdlib.h>



/*
  counting_sort

  Sorts an array of ints in O(n+k) time.
  n - number of elements
  k - prefix sum on the count array

  Inputs:
  input - pointer to an array of ints
  arraySize - size of the array of ints
  min - the minimum value of the array
  max - the maximum value of the array

  Outputs:
  NONE
*/
void counting_sort(int *input, int arraySize, int min, int max) {
  int range = (max - min) + 1;
  int * count = malloc(range * (sizeof(int*)));

  int i;
  //initilise values of array to 0
  for(i=0; i < range; i++) {
    count[i] = 0;
  }

  //Calculate the histogram of key frequencies
  for(i=0; i < arraySize; i++) {
    count[ input[i] - min] ++;
  }

  int j;
  int counter = 0;
  for(i = min; i <= max; i++) {
    for(j = 0; j < count[i - min]; j++) {
      input[counter] = i;
      counter++;
    }
  }
  free(count);
}




/*
  print_array

  Prints an array of ints in the following format:
  Array: a, b, c, d

  Inputs:
  array - pointer to an array of integers
  size - number of elements in the array

  Outputs:
  NONE
*/
void print_array(int * array, int size) {
  int i;

  /*
    Keeps track of the first element in the array as
    the first element does not need to print a comma
  */
  int firstElem = 1;
  printf("Array: ");
  for(i=0; i < size; i++) {
    if(firstElem) {
      printf("%d",array[i]);
      firstElem = 0;
    } else {
      printf(", %d",array[i]);
    }
  }
  printf("\n");
}




int main(int argc, char ** argv) {
  //catch erroneous inputs
  if (argc < 4) {
    printf("Too few arguments. Format: min max [int list]\n");
    return -1;
  }

  int min = atoi(argv[1]);
  int max = atoi(argv[2]);

  //convert string array to array of ints
  int * array = malloc(sizeof(int) * (argc - 3));
  int i;
  for(i=3; i < argc; i++) {
    array[i-3] = atoi(argv[i]);
  }

  print_array(array, (argc - 3));
  counting_sort(array, (argc-3), min, max);
  print_array(array, (argc - 3));
  free(array);
}
