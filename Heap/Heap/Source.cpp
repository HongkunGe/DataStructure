
#include <iostream>
#include <algorithm>
#include <ctime>
#include <assert.h>
#include "heap.h"
#include "test.h"
using namespace std;

int main() {
	srand(time(0));
	Test test1;
	for (int i = 0; i < 100; i++) test1.testVector.push_back(i);
	random_shuffle(test1.testVector.begin(), test1.testVector.end());

	heap h1(test1.testVector);
	heap h2(50);

	assert(test1.checkHeap(h1), true);
	assert(test1.checkHeap(h2), true);

	cout << "\n Test insert: \n";

	h1.print();
	h2.print();
	for (int i = 101; i < 300; i++) {
		h1.insert(i);
		assert(test1.checkHeap(h1), true);
		h2.insert(i);
		assert(test1.checkHeap(h2), true);
	}

	h1.print();
	h2.print();
	assert(test1.checkHeap(h1), true);
	assert(test1.checkHeap(h2), true);

	cout << "\n Test increaseValue: \n";
	h1.increaseValue(150, 600);
	assert(test1.checkHeap(h1), true);
	h1.increaseValue(60, 300);
	assert(test1.checkHeap(h1), true);
	h1.increaseValue(70, 200);
	assert(test1.checkHeap(h1), true);
	h1.increaseValue(40, 100);
	assert(test1.checkHeap(h1), true);

	h1.print();

	cout << "\n Test extractMax: \n";
	int size = h1.getSize();
	for (int i = 0; i < size; i++) {
		cout << h1.extractMax() << " ";
		assert(test1.checkHeap(h1), true);
	}

	h1.print();

	test1.printTest();
	heapSort(test1.testVector);
	test1.printTest();

	// add new test to heap structure

	return 0;
}