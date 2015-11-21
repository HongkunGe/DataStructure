
#ifndef HEAP_H
#define HEAP_H

#include <vector>
using namespace std;

class heap {
	friend class Test;
private:
	vector<int> container;
	int heapLength; // the length of the array.
	int heapSize;   // the number of elements.

	int parent(int i);
	int left(int i);
	int right(int i);

	void resize();

	void maxHeapify(int i);
	void buildMaxHeap(vector<int>& A);

public:
	heap(int size);
	heap(vector<int>& A);
	~heap() {};

	int setSize(int i);
	int getSize();

	void insert(int value);
	void increaseValue(int i, int value);
	int extractMax();
	//void heapSort();
	void print();
};

void heapSort(vector<int>& A);

#endif