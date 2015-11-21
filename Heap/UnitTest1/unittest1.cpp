

#include "stdafx.h"
#include "CppUnitTest.h"

#include "../Heap/heap.h"
#include "test.h"
#include <algorithm>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::vector;
using std::sort;
using std::random_shuffle;
namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		Test test1;
		UnitTest1() {
			for (int i = 0; i < 100; i++)
				test1.testVector.push_back(i);
			random_shuffle(test1.testVector.begin(), test1.testVector.end());
		}

		TEST_METHOD(insertHeapTest)
		{			
			heap h1(test1.testVector);
			heap h2(50);

			Assert::AreEqual(test1.checkHeap(h1), true);
			Assert::AreEqual(test1.checkHeap(h1), true);

			for (int i = 101; i < 300; i++) {
				h1.insert(i);
				Assert::AreEqual(test1.checkHeap(h1), true);
				h2.insert(i);
				Assert::AreEqual(test1.checkHeap(h2), true);
			}
		}

		TEST_METHOD(increaseValueTest) {
			heap h1(test1.testVector);
			h1.increaseValue(150, 600);
			Assert::AreEqual(test1.checkHeap(h1), true);
			h1.increaseValue(60, 300);
			Assert::AreEqual(test1.checkHeap(h1), true);
			h1.increaseValue(70, 200);
			Assert::AreEqual(test1.checkHeap(h1), true);
			h1.increaseValue(40, 100);
			Assert::AreEqual(test1.checkHeap(h1), true);
		}

		TEST_METHOD(heapSortTest) {
			vector<int> testVector2(test1.testVector);
			heapSort(test1.testVector);
			sort(testVector2.begin(), testVector2.end());

			Assert::AreEqual(test1.testVector.size(), testVector2.size());
			for (int i = 0; i < testVector2.size(); i++) {
				Assert::AreEqual(test1.testVector[i], testVector2[i]);
			}
		}
	};
}