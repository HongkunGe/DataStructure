#pragma once
#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <vector>
using namespace std;

class Test {
public:
	vector<int> testVector;
	void printTest() {
		cout << "\n Vector:" << endl;
		for (int i = 0; i < testVector.size(); i++) {
			cout << testVector[i] << " ";
		}
	};
	bool checkHeap(heap& h) {
		bool result = true;
		int end = (h.getSize() - 1) / 2;
		for (int i = 0; i < end; i++) {
			if (h.container[i] < h.container[h.left(i)] \
				|| h.container[i] < h.container[h.right(i)]) return false;
		}
		return true;
	};
};
#endif