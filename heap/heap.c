#include<stdio.h>
#include<stdlib.h>
void insert(int heap[], int position, int heapsize) {
	int temp, min, left, right;
	left = 2 * position + 1;
	right = 2 * position + 2;
	if (left >= heapsize)
		return;
	else {
		if (left < heapsize && heap[left] < heap[position])
			min = left;
		else
			min = position;
		if (right < heapsize && heap[right] < heap[min])
			min = right;
		if (min != position) {
			temp = heap[position];
			heap[position] = heap[min];
			heap[min] = temp;
			insert(heap, min, heapsize);
		}
	}
}
int* minheap(int heap[], int heapsize) {
	int n = heapsize;
	for (int i = heapsize / 2; i >= 0; i--) {
		insert(heap, i, n);
	}
	return heap;
}
int main(void) {
	int nodeNum = 0;
	printf("Insert the number of nodes:\n");
	scanf("%d", &nodeNum);
	int* input = malloc(nodeNum * sizeof(int));
	int* result = malloc(nodeNum * sizeof(int));
	printf("Enter the unsorted array:\n");
	for (int i = 0; i < nodeNum; i++) {
		scanf("%d", &input[i]);
	}
	result = minheap(input, nodeNum);
	printf("The heap is ");
	for (int i = 0; i < nodeNum; i++) {
		printf("%d ", result[i]);
	}
	printf("\n");
	free(input);
	free(result);
	return 0;
}