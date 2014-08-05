#include <stdio.h>
#include <stdlib.h>

struct tuple {
	int low;
	int high;
	int sum;
};


/*
 * This function finds the maximum subarray which crosses the centre point "mid"
 *
 * O(n)
 */
struct tuple * findMaximumCrossingSubarray(int low, int mid, int high, int * array) {
	int leftSum = -2147483647;
	int sum = 0;
	int maxLeft = 0;
	for(int i=mid; i >= low; i--) {
		sum = sum + array[i];
		if(sum > leftSum) {
			leftSum = sum;
			maxLeft = i;
		}
	}
	int rightSum = -2147483647;
	sum = 0;
	int maxRight = 0;
	for(int i=mid+1; i <= high; i++) {
		sum = sum + array[i];
		if(sum > rightSum) {
			rightSum = sum;
			maxRight = i;
		}
	}
	struct tuple * returnValue = malloc(sizeof(struct tuple));
	returnValue->low = maxLeft;
	returnValue->high = maxRight;
	returnValue->sum = leftSum + rightSum;
	return returnValue;
}

/*
 * This function finds the maximum subarray by attempting to locate the largest subarray
 * in the left side, the right side and crossing the centre line recusively.
 *
 * O(n)
 */
struct tuple * findMaximumSubarray(int low, int high, int * array) {
	if (high == low) {
		struct tuple * returnValue = malloc(sizeof(struct tuple));
		returnValue->low = low;
		returnValue->high = high;
		returnValue->sum = array[low];
		return returnValue;
	} else {
		int mid = (low + high) / 2;
		struct tuple * leftMax = findMaximumSubarray(low, mid, array);
		struct tuple * rightMax = findMaximumSubarray(mid+1, high, array);
		struct tuple * crossMax = findMaximumCrossingSubarray(low, mid, high, array);
		if ((leftMax->sum >= rightMax->sum) && (leftMax->sum >= crossMax->sum)) {
			free(rightMax);
			free(crossMax);
			return leftMax;
		} else if ((rightMax->sum >= leftMax->sum) && (rightMax->sum >= crossMax->sum)) {
			free(leftMax);
			free(crossMax);
			return rightMax;
		} else {
			free(leftMax);
			free(rightMax);
			return crossMax;
		}
	}
}

void printTuple(struct tuple * tuple) {
	printf("[%d][%d][%d]\n",tuple->low,tuple->high,tuple->sum);
}

/*
 * The program takes in the array of integers as commandline parameters.
 *
 * You can test this program using the array:
 * 13 -3 -25 20 -3 -16 -23 18 20 -7 12 -5 -22 15 -4 7
 *
 * The maxiumum subarray in the above array is [7][10][43] where:
 *	[7] - lower index
 *	[10] - upper index
 * 	[43] - sum of integers between these indexes.
 */
int main(int argc, char ** argv) {
	int * array = malloc(sizeof(int) * (argc - 1));
	for(int i=1; i < argc; i++) {
		array[i-1] = atoi(argv[i]);
	}

	struct tuple * result = findMaximumSubarray(0, argc-1, array);
	printTuple(result);
	free(array);
	free(result);
}
