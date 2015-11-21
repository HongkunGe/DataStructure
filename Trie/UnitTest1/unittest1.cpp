#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Trie/Trie.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		Trie t;
		TEST_METHOD(TestInsert1)
		{
			t.insert("abcde");
			Assert::AreEqual(t.prefix("ab"), true);
			Assert::AreEqual(t.prefix("ac"), false);
			Assert::AreEqual(t.prefix("abc"), true);
		}
		TEST_METHOD(TestInsert2)
		{
			t.insert("aac");
			Assert::AreEqual(t.prefix("ac"), false);
			Assert::AreEqual(t.prefix("aa"), true);
		}
		TEST_METHOD(TestInsert3)
		{

			t.insert("ac");
			Assert::AreEqual(t.prefix("ac"), true);
		}
		TEST_METHOD(TestInsertDuplicate)
		{

			t.insert("bbb");
			t.insert("bbb");
			t.insert("bbb");
			Assert::AreEqual(t.prefix("b"), true);
			Assert::AreEqual(t.prefix("bb"), true);
			Assert::AreEqual(t.prefix("bbc"), false);
			Assert::AreEqual(t.search("bb"), false);
			Assert::AreEqual(t.search("bbb"), true);
		}
		TEST_METHOD(TestInsertSingleChar)
		{
			t.insert("z");
			Assert::AreEqual(t.search("z"), true);
			Assert::AreEqual(t.prefix("z"), true);
		}
		TEST_METHOD(TestInsertEmpty)
		{
			t.insert("");
			Assert::AreEqual(t.search(""), true);
			Assert::AreEqual(t.prefix(""), true);
		}

	};

	TEST_CLASS(UnitTest2)
	{
	public:
		Trie t, t2;
		string testString;
		TEST_METHOD(TestRemove1)
		{
			t.insert("abcdefg");
			Assert::AreEqual(t.search("abcdefg"), true);
			Assert::AreEqual(t.remove("abc"), false);
			Assert::AreEqual(t.remove("abcd"), false);
			Assert::AreEqual(t.remove("abcdef"), false);
			Assert::AreEqual(t.remove("abcdefg"), true);
						
			Assert::AreEqual(t.isEmpty(), true);
		}
		TEST_METHOD(TestRemove2)
		{
			
			// insert(a, ab, abc, abcd, .... ,)
			for (char c = 'a'; c <= 'z'; c++) {
				testString += c;
				t.insert(testString);
				Assert::AreEqual(t.search(testString), true);
				Assert::AreEqual(t.prefix(testString.substr(0, testString.length() - 1)), true);
			}
		}
		TEST_METHOD(TestRemove3)
		{
			testString.clear();
			for (char c = 'z'; c >= 'a'; c--) {
				testString += c;
				Assert::AreEqual(t.search(testString), false);
				Assert::AreEqual(t.prefix(testString.substr(0, testString.length() - 1)), false);
				Assert::AreEqual(t.remove(testString), false);

			}
		}
		TEST_METHOD(TestRemove4)
		{
			testString.clear();
			for (char c = 'a'; c <= 'z'; c++) {
				testString += c;
				Assert::AreEqual(t.search(testString), true);
				Assert::AreEqual(t.remove(testString), true);
				Assert::AreEqual(t.search(testString), false);
			}

			Assert::AreEqual(t.isEmpty(), true);
		}

		TEST_METHOD(TestRemove5)
		{
			t2.insert("abcdefg");
			t2.insert("abcde");
			t2.insert("abc");
			Assert::AreEqual(t2.remove("zxcv"), false);

		}
		TEST_METHOD(TestRemove6)
		{
			Assert::AreEqual(t2.search("abc"), true);
			Assert::AreEqual(t2.search("abcdefg"), true);
			Assert::AreEqual(t2.search("abcde"), true);
		}
		TEST_METHOD(TestRemove7)
		{
			Assert::AreEqual(t2.remove("abcde"), true);

			Assert::AreEqual(t2.search("abc"), true);
			Assert::AreEqual(t2.search("abcdefg"), true);
			Assert::AreEqual(t2.search("abcde"), false);

			Assert::AreEqual(t2.isEmpty(), false);
		}
	};
}