#include "stdafx.h"
#include "CppUnitTest.h"
#include "../BloomFilter/BloomFilter.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(MaybeThere1)
		{
			// If contains return true, maybe there or collision.
			BloomFilter bf(10, 32, 2);
			string s = "test";
			bf.add(s);
			Assert::AreEqual(bf.contains(s), bf.containsCheck(s));

			s += "a";
			bf.add(s);
			Assert::AreEqual(bf.contains(s), bf.containsCheck(s));

			s += "b";
			bf.add(s);
			Assert::AreEqual(bf.contains(s), bf.containsCheck(s));
		}
		TEST_METHOD(MaybeThere2)
		{
			// If contains return true, maybe there or collision.
			BloomFilter bf(10, 32, 2);
			string s = "QWER";
			bf.add(s);
			Assert::AreEqual(bf.contains(s), bf.containsCheck(s));

			s = "ASDSDFDF";
			bf.add(s);
			Assert::AreEqual(bf.contains(s), bf.containsCheck(s));

			s += "QWEERWE";
			bf.add(s);
			Assert::AreEqual(bf.contains(s), bf.containsCheck(s));
		}
		TEST_METHOD(NotThere) {  
			// those tests may fail. because collision happens so 
			// contains may return true, but containsCheck return false;
			BloomFilter bf(10, 32, 2);
			string s = "test";
			bf.add(s); // test
			s = "b";
			Assert::AreEqual(bf.contains(s), bf.containsCheck(s)); 

			bf.add(s); // testb
			s += "abc";			
			Assert::AreEqual(bf.contains(s), bf.containsCheck(s)); 

			bf.add(s); // testbb
			s += "ijuhkb";			
			Assert::AreEqual(bf.contains(s), bf.containsCheck(s));
		}
	};
}