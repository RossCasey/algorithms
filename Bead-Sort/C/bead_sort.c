#include <stdio.h>
#include <stdlib.h>



/*
  find_max

  Returns the largest value in an array of ints

  Inputs:
  array - pointer to an array of ints
  size - number of elements in the array

  Outputs:
  int - largest value in the array
*/
int find_max(int * array, int size) {
  int max = array[0];
  int i;
  for(i=1; i < size; i++) {
    if(array[i] > max) {
      max = array[i];
    }
  }
  return max;
}




/*
  bead_sort

  Sorts an array of ints in O(S) time.
  S - the sum of the integers in the input array

  Inputs:
  array - pointer to an array of ints
  size - number of elements in the array

  Outputs:
  NONE
*/
void bead_sort(int * array, int size) {
  int i, j, max;
  max = find_max(array, size);
  unsigned char ** beads;

  beads = (unsigned char **) malloc(size * sizeof(unsigned char*));
  for(i=0; i < size; i++) {
    beads[i] = (unsigned char *) malloc(max * sizeof(unsigned char));
  }

  //mark all beads
  for(i=0; i < size; i++) {
    for(j=0; j < array[i]; j++) {
      beads[i][j] = 1;
    }
  }

  int sum;
  for (j = 0; j < max; j++) {
    // number of beads on each post
    for (sum = i = 0; i < size; i++) {
      sum += beads[i][j];
      beads[i][j] = 0;
    }
    //mark bottom beads
    for (i = size - sum; i < size; i++) {
      beads[i][j] = 1;
    }
  }

  //place values in output array
  for (i = 0; i < size; i++) {
    for (j = 0; (j < max) && beads[i][j]; j++);
    array[i] = j;
  }

  //free memory
  for(i=0; i < size; i++) {
    free(beads[i]);
  }
  free(beads);
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
  //convert string array to array of ints
  int * array = malloc(sizeof(int) * (argc - 1));
  int i;
  for(i=1; i < argc; i++) {
    array[i-1] = atoi(argv[i]);
  }
  print_array(array, argc-1);
  bead_sort(array, argc-1);
  print_array(array, argc-1);
  return 0;
}
