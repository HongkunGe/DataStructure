#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Algorithms/Algorithms.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		allSubstr ass;
		TEST_METHOD(TestEmpty)
		{		
			string te = "";
			Assert::AreEqual(ass.sizeOfSubstr(te), 0);
		}
		TEST_METHOD(TestNoDuplicate)
		{
			string te = "qwertyuiop";
			int total = (te.size() + 1) * te.size() / 2;

			Assert::AreEqual(ass.sizeOfSubstr(te), total);
		}
		TEST_METHOD(TestDuplicate)
		{
			string te = "BANANA";
			Assert::AreEqual(ass.sizeOfSubstr(te), 15);
			te = "BANANA";
			Assert::AreEqual(ass.sizeOfSubstr(te), 15);
		}
	};
}