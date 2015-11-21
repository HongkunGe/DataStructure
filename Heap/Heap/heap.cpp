#include <iostream>
#include <algorithm>
#include "heap.h"

using namespace std;

heap::heap(int size): heapLength(size), heapSize(0) {
	container = vector<int>(heapLength, 0);
}

heap::heap(vector<int>& A) {
	heapSize = A.size();
	heapLength = A.size();
	buildMaxHeap(A);
}

int heap::parent(int i) {
	return i / 2;
}

int heap::left(int i) {
	return i * 2;
}

int heap::right(int i) {
	return i * 2 + 1;
}

int heap::setSize(int i) {
	heapSize = i;
	return heapSize;
}

int heap::getSize() {
	return heapSize;
}

void heap::maxHeapify(int i) {
	// T(n) = O(logn);
	int l = left(i), r = right(i);
	int maxIdx = i;
	if (l < heapSize && container[l] > container[i]) {
		maxIdx = l;
	}
	if (r < heapSize && container[r] > container[maxIdx]) {
		maxIdx = r;
	}
	if (maxIdx != i) {
		swap(container[i], container[maxIdx]);
		maxHeapify(maxIdx);
	}
}

void heap::buildMaxHeap(vector<int> & A) {
	// T(n) = O(n);
	container = A;
	int start = (A.size() - 1) / 2;
	for (int i = start; i >= 0; i--) {
		maxHeapify(i);
	}
}

void heap::resize() {
	int heapLength = heapSize * 2;
	container.resize(heapLength);
}

int heap::extractMax() {
	// T(n) = O(logn);
	if (heapSize == 0) {
		cerr << "Empty Container!" << endl;
		return -1;
	}
	int maxValue = container[0];
	container[0] = container[heapSize - 1];
	heapSize--;
	maxHeapify(0);
	return maxValue;
}
// 
void heap::increaseValue(int i, int value) {
	// T(n) = O(logn)
	if (i >= heapSize) {
		cerr << "Overflow!" << endl;
		return;
	}else if (container[i] > value) {
		cerr << "Small Value!" << endl;
		return;
	}
	container[i] = value;
	while (i > 0 && container[i] > container[parent(i)]) {
		swap(container[i], container[parent(i)]);
		i = parent(i);
	}
}

void heap::insert(int value) {
	// T(n) = O(logn)
	if (heapLength == heapSize) {
		heapLength = heapLength * 2;
		container.resize(heapLength);		
	}
	heapSize++;
	container[heapSize - 1] = INT_MIN;
	increaseValue(heapSize - 1, value);
}

void heap::print() {
	cout << "\n heap Size: " << getSize() << endl;
	cout << "\n heap Length: " << heapLength << " " << container.size() << endl;
	cout << "\n heap:" << endl;
	for (int i = 0; i < heapSize; i++) {
		cout << container[i] << " ";
	}
	if (heapSize == 0) cout << "Empty" << endl;
}

void heapSort(vector<int>& A) {
	// T(n) = O(nlogn)
	heap ha(A);
	for (int i = A.size() - 1; i >= 0; i--) {
		A[i] = ha.extractMax();
	}
}