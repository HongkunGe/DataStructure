#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Algorithms/Algorithms.h"
#include "../Algorithms/disjointSet.cpp"  
// template class implemented here. Deleting cause linker error.
//http://www.codeproject.com/Articles/48575/How-to-define-a-template-class-in-a-h-file-and-imp
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{
	TEST_CLASS(UnitTestSuffix)
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

	TEST_CLASS(test_test)
	{
	public:
		TEST_METHOD(TestDuplicate)
		{
			alienDict ad;
			vector<string> vs({"word"});
			ad.alienOrder(vs);
		}
	};

	TEST_CLASS(UnitTestDisjointSet)
	{
	public:
		
		
		TEST_METHOD(TestMakeSet)
		{
			disjointSet<char> ds;
			ds.makeSet('a');
			ds.makeSet('b');
			ds.makeSet('c');
			ds.makeSet('d');
			ds.makeSet('e');
			ds.makeSet('f');
			for (char i = 'a'; i <= 'f'; i++)
				Assert::AreEqual(ds.find(i), i);
		}
		TEST_METHOD(TestConstructor)
		{
			disjointSet<char> ds({ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'});
			for (char i = 'a'; i <= 'h'; i++)
				Assert::AreEqual(ds.find(i), i);			
		}

		
		TEST_METHOD(TestUnionFind1)
		{
			disjointSet<char> ds;
			ds = disjointSet<char>({ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' });

			ds.unionSet('a', 'b');
			Assert::AreEqual(ds.find('a'), 'b');
			Assert::AreEqual(ds.find('b'), 'b');

			ds.unionSet('c', 'd');
			Assert::AreEqual(ds.find('c'), 'd');
			Assert::AreEqual(ds.find('d'), 'd');

			// 'e' is attached to 'd', which has a higher rank.
			ds.unionSet('e', 'c');
			Assert::AreEqual(ds.find('e'), 'd');
			Assert::AreEqual(ds.find('c'), 'd');

			// 'd' and 'b' have the same rank, attached to 'b'.
			ds.unionSet('e', 'b');
			Assert::AreEqual(ds.find('a'), 'b');
			Assert::AreEqual(ds.find('b'), 'b');


			ds.unionSet('f', 'g');
			ds.unionSet('f', 'a');
			ds.unionSet('f', 'h');
			Assert::AreEqual(ds.find('f'), 'b');
			Assert::AreEqual(ds.find('g'), 'b');
			Assert::AreEqual(ds.find('h'), 'b');
		}
		TEST_METHOD(TestUnionFind2)
		{
			disjointSet<int> ds;
			ds = disjointSet<int>({ 1,2,3,4,5,6,7,8,9,0 });

			ds.unionSet(0, 1);
			ds.unionSet(1, 2);
			ds.unionSet(2, 3);
			ds.unionSet(3, 4);
			ds.unionSet(4, 5);
			ds.unionSet(5, 6);
			ds.unionSet(6, 7);
			ds.unionSet(7, 8);
			ds.unionSet(8, 9);

			for (int i = 0; i < 10; i ++)
				Assert::AreEqual(ds.find(i), 1);
		}
	};

	TEST_CLASS(UnitTestBigInt) 
	{
		TEST_METHOD(ADD)
		{
			string n1 = "123234234", n2 = "893827";
			BigInt bi(n1);
			string res = bi.add(n2);
			Assert::AreEqual(stoi(res), stoi(n1) + stoi(n2));
		}
	};
}