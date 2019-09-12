#include<stdio.h>
int size = 10;
void swap(int* xp, int* yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}
void displayArray(int intArray[]) {
	for (int i = 0; i < size; i++) {
		printf("%d ", intArray[i]);
	}
	printf("\n");
}
int partition(int intArray[], int left, int right, int pivot) {
	int leftPointer = left;
	int rightPointer = right;

	printf("Calling quick sort, index %d to %d with pivot %d...\n", left, right, pivot);
	while (1) {

		while (intArray[leftPointer] < pivot) {
			leftPointer++;
			// keep increasing left pointer until run into something greater than pivot
		}

		while (rightPointer > 0 && intArray[--rightPointer] > pivot) {
			// keep decreasing right pointer until run into something smaller than pivot
		}

		if (leftPointer >= rightPointer) {
			break;
		}
		else {
			printf("item swapped: %d,%d\n", intArray[leftPointer], intArray[rightPointer]);
			swap(&intArray[leftPointer], &intArray[rightPointer]);
		}
	}

	printf("pivot swapped to final position: %d,%d\n", intArray[leftPointer], intArray[right]);
	swap(&intArray[leftPointer], &intArray[right]);
	displayArray(intArray);
	return leftPointer;
}

void quickSort(int intArray[], int left, int right) {
	if (right - left <= 0) {
		return;
	}
	else {
		int pivot = intArray[right];  // use the rightmost as pivot (lazy!)
		int partitionPoint = partition(intArray, left, right, pivot);
		quickSort(intArray, left, partitionPoint - 1);
		quickSort(intArray, partitionPoint + 1, right);
	}
}



void main() {
	//int a[] = { 1,4,5,2,3,6,7,8 };
	int b[] = { 1,2,3,4,5,6,7,8,9,10 };

	//printf("\nSorting a: ");
	//displayArray(a);
	//quickSort(a, 0, size - 1);

	printf("\nSorting b: ");
	displayArray(b);
	quickSort(b, 0, size - 1);

}

