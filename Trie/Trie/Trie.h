#pragma once
#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using std::vector;
using std::string;

struct TrieNode
{
	bool leaf;
	TrieNode* child[26];
	TrieNode() : leaf(false) {
		std::fill_n(child, 26, nullptr);
	}
};

class Trie 
{
	bool removeDfs(string &word, int level, int len, TrieNode* root);
	bool isPrefix(TrieNode* root);
public:
	TrieNode* root;
	Trie() {
		root = new TrieNode();
	};
	void insert(string word);
	bool search(string word);
	bool prefix(string word);
	bool remove(string word);
	bool isEmpty();
};
#endif TRIE_H