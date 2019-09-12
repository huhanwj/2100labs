#include <stdio.h>
#include<stdlib.h>
#include<time.h>
int comparisonUsed_Linear = 0;
int comparisonUsed_Binary = 0;
// Binary search function using recursion - this function
// should return -1 if no match is found
// assume a is always sorted in ascending order
int binarySearch(int a[], int left, int right, int x)
{
	//printf("Using binary search from left=%d to right=%d \n", left, right);
	if (right >= left)
	{
		int i = 0;
		//printf("Sublist considered: ");
		//for (i = left; i <= right; i++) {
			//printf("%d ", a[i]);
		//}
		//printf("\n");
		int mid = left + (right - left) / 2;

		if (a[mid] == x) {
			comparisonUsed_Binary++;
			return mid;
		}

		if (a[mid] > x) {
			//printf("Choosing left half to continue search...\n");
			comparisonUsed_Binary++;
			return binarySearch(a, left, mid - 1, x);

		}
		else {
			//printf("Choosing right half to continue search...\n");
			comparisonUsed_Binary++;
			return binarySearch(a, mid + 1, right, x);
		}


	}
	else {
		//printf("No sublist to consider anymore...\n");
	}

	// not found!
	return -1;
}
int fillArray(int a[], int size, double skipProb, int skipMagnitude) {
	// a crude random sorted array generation function
	// we use skipProb and skipMagnitude to simulate "not found" cases
	int i;
	int x = -1;
	for (i = 0; i < size; i++) {
		x++; // x must increment
		if ((rand() % 100) < (skipProb * 100))
			x += skipMagnitude;
		a[i] = x;
	}
	return size + (int)(skipProb * skipMagnitude * size) - 1;
}

int linearSearch(int a[], int lastIndex, int x) {
	// last Index is the last index of the array
	// x is the number to search for in the array
	int i = 0;
	while (i <= lastIndex && a[i] <= x) {
		comparisonUsed_Linear++;
		if (x == a[i])
			return i;
		i++;
	}
	return -1;
}
int main(void)
{
	srand(time(NULL));
	int times = 0;
	while (times < 1000) {
		int a[100] = { 0 };
		int b[100] = { 0 };
		int size = 100;
		int max1 = fillArray(a, size, 0.5, 30);
		int max2 = fillArray(b, size, 0.5, 30);
		int x = rand() % (max1 + 1);
		int y = rand() % (max2 + 1);
		int result1 = binarySearch(b, 0, size - 1, y);
		int result2 = linearSearch(a, size - 1, x);
		times++;
	}
	printf("Linear:%d\n", comparisonUsed_Linear);
	printf("Binary:%d\n", comparisonUsed_Binary);
	return 0;
}
