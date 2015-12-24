#pragma once
#ifndef LEETCODE_H
#define LEETCODE_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <numeric>
#include <unordered_map>
using namespace std;

////////////////////////////////////////////////////////////////////////
//Data Structure 
////////////////////////////////////////////////////////////////////////

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}

};
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}

};
struct RandomListNode {
	int label;
	RandomListNode *next, *random;
	RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};
class linkedList {
public:
	ListNode* head;
	linkedList(vector<int>& A);
};


struct TrieNode {
	TrieNode* child[26];
	bool leaf;
	TrieNode() : leaf(false) {
		fill_n(child, 26, nullptr);
	}
};
class Trie {
public:
	TrieNode* root;
	Trie();
	void insert(const string& word);
	bool search(const string& word);
};


template<class T>
class disjointSet {
	unordered_map<T, T> parent;
	unordered_map<T, int> rank;  // record the depth of the set
	int count;
public:
	disjointSet(vector<T>);
	disjointSet() {};
	void makeSet(T);
	T find(T);
	bool contain(T);
	void unionSet(T set1, T set2);
	int size();
};
////////////////////////////////////////////////////////////////////////
//Fun Problems
////////////////////////////////////////////////////////////////////////
class parseStringToTree {
	TreeNode* parseTree(string input, int& idx);
public:
	TreeNode* parseTree(string input);
};

class allSubstr {

	void getSortedSubstr(vector<string>& res, string);
	int longestCommonPrefix(string, string);
public:
	vector<string> getAllSubstr(string);
	int sizeOfSubstr(string);
};


class BigInt {
	string number;
public:
	BigInt(string number);
	string add(string otherNum);
	BigInt operator+(const BigInt& b);
	void set(string s) {
		number = s;
	}
	string multiply(string otherNum);

	BigInt operator*(const BigInt& b);
	string value() {
		return number;
	}
};


////////////////////////////////////////////////////////////////////////
//LeetCode Practice
////////////////////////////////////////////////////////////////////////



class alienDict {
public:
	string alienOrder(vector<string>& words);
};

class filpGame {
	bool canWinDfs(string& s, unordered_map<string, bool>& record);
public:
	vector<string> generatePossibleNextMoves(string s);
	bool canWin(string s);
};

class wordPattern {
	bool dfs(string& pattern, string& str,
		unordered_map<string, int>& s2i,
		unordered_map<char, int>& c2i,
		unordered_map<char, int>& c2Len, int cIdx, int sIdx);
public:
	bool wordPatternMatch(string pattern, string str);
};

class LongestSubstringTwoDistinct {
public:
	int lengthOfLongestSubstringTwoDistinct(string s);
};

class numIslands {
	disjointSet<int> ds;
	int index(int x, int y, int n, int m);
public:
	int add(int x, int y, int n, int m);
	vector<int> numIslands2(int m, int n, vector<pair<int, int>>& positions);
};

class StrobogrammaticNumber {
	string l, h;
	int minus(string n1, string n2);
	void numDfs(int& count, string instance, int max);
public:
	int strobogrammaticInRange(string low, string high);
};

#endif