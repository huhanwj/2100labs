#include<stdio.h>
#include<stdlib.h>
int insertPos = 0;
void init(int heap[],int heapsize) {
	for (int i = 0; i < heapsize; i++) {
		heap[i] = 0;
	}
}
void compare(int heap[], int position) {
	if (!position)
		return;
	int parent = (position - 1) / 2;
	int temp = 0;
	if (heap[position] < heap[parent]) {
		temp = heap[parent];
		heap[parent] = heap[position];
		heap[position] = temp;
		compare(heap, parent);
	}
	else
		return;
}
void positionChange(int heap[], int heapsize) {
	while (heap[insertPos] && insertPos < heapsize)
		insertPos++;
}
void insert(int heap[],int insertion,int heapsize) {
	positionChange(heap, heapsize);
	if (!heap[insertPos]) {
		heap[insertPos] = insertion;
		if (insertPos)
			compare(heap, insertPos);
		positionChange(heap, heapsize);
	}
}
int findMin(int heap[], int heapsize) {
	return heap[0];
}
void extractChange(int heap[], int heapsize, int extractLocation) {
	int left, right;
	left = extractLocation * 2 + 1;
	right = extractLocation * 2 + 2;
	if (left <= heapsize && right <= heapsize) {
		if (heap[left] < heap[right]) {
			if (heap[left] == 0) {
				heap[extractLocation] = heap[right];
				heap[right] = 0;
				extractLocation = right;
				extractChange(heap, heapsize, extractLocation);
			}
			else {
				heap[extractLocation] = heap[left];
				heap[left] = 0;
				extractLocation = left;
				extractChange(heap, heapsize, extractLocation);
			}
		}
		else {
			if (heap[right] == 0) {
				heap[extractLocation] = heap[left];
				heap[left] = 0;
				extractLocation = left;
				extractChange(heap, heapsize, extractLocation);
			}
			else {
				heap[extractLocation] = heap[right];
				heap[right] = 0;
				extractLocation = right;
				extractChange(heap, heapsize, extractLocation);
			}
		}
	}
}
int extractMin(int heap[], int heapsize,int extractLocation) {
	int extract = heap[extractLocation];
	heap[extractLocation] = 0;
	extractChange(heap, heapsize, extractLocation);
	return extract;
}
int deleteHeap(int heap[], int heapsize, int deleteLocation) {
	int left, right;
	left = deleteLocation * 2 + 1;
	right = deleteLocation * 2 + 2;
	heap[deleteLocation] = 0;
	if (left < heapsize && right < heapsize) {
		if (heap[left] < heap[right]) {
			if (heap[left] == 0) {
				heap[deleteLocation] = heap[right];
				heap[right] = 0;
				deleteLocation = right;
				extractChange(heap, heapsize, deleteLocation);
			}
			else {
				heap[deleteLocation] = heap[left];
				heap[left] = 0;
				deleteLocation = left;
				extractChange(heap, heapsize, deleteLocation);
			}
		}
		else {
			if (heap[right] == 0) {
				heap[deleteLocation] = heap[left];
				heap[left] = 0;
				deleteLocation = left;
				extractChange(heap, heapsize, deleteLocation);
			}
			else {
				heap[deleteLocation] = heap[right];
				heap[right] = 0;
				deleteLocation = right;
				extractChange(heap, heapsize, deleteLocation);
			}
		}
	}
	return heapsize - 1;
}
int main(void) {
	int heapsize = 5;
	int input[5] = { 9,8,7,6,5 };
	int heap[5];
	init(heap,heapsize);
	for (int i = 0; i < 5; i++) {
		insert(heap, input[i], heapsize);
	}
	for (int i = 0; i < heapsize; i++)
		printf("%d ",heap[i]);
	printf("\n");
	heapsize = deleteHeap(heap, heapsize, 1);
	for (int i = 0; i < heapsize; i++) {
		int output = extractMin(heap, heapsize, 0);
		printf("%d ", output);
	}
	return 0;
}