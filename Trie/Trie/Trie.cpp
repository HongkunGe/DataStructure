#include "Trie.h"

#define DELETE(t) {delete t; t = nullptr;}

bool Trie::isEmpty() {
	for (auto e : root->child) {
		if (e != nullptr)
			return false;
	}
	return true;
}
void Trie::insert(string word) {
	TrieNode* node = root;
	
	for (auto c : word) {
		if (node->child[c - 'a'] == nullptr) {
			node->child[c - 'a'] = new TrieNode();
		}
		node = node->child[c - 'a'];
	}
	node->leaf = true;
}

bool Trie::search(string word) {
	TrieNode* node = root;

	for (auto c : word) {
		if (node->child[c - 'a'] == nullptr) {
			return false;
		}
		node = node->child[c - 'a'];
	}
	return node->leaf;
}

// search the trie to test if word is a prefix of words of trie.
bool Trie::prefix(string word) {
	TrieNode* node = root;

	for (auto c : word) {
		if (node->child[c - 'a'] == nullptr) {
			return false;
		}
		node = node->child[c - 'a'];
	}
	return true;
}

// delete a word in Trie
/*
	if word is not in the Trie, return false;
	if there is a word in Trie, remove it but don't affect other words.
	delete all the words in Trie, Trie has only a empty root.
*/
bool Trie::remove(string word) {
	/* 
		1. if the word is not in the Trie, make no change to Trie, return false;
		2. if the word isn't only in the Trie, but also prefix of some words in Trie, mark that char as no-leaf, return true;
		3. if some word is a prefix of the word to be removed, protect remaining chars, remove suffix part, return true;
		4. if the word is exactly the one in the Trie, remove it, return true;
	*/
	int len = word.length();
	return removeDfs(word, 0, len, root);
}

bool Trie::isPrefix(TrieNode* root) {
	// if there is any child which is not nullptr. the word before root is a prefix of other word, return true;
	for (auto e : root->child)
		if (e != nullptr)
			return true;
	return false;
}
bool Trie::removeDfs(string &word, int level, int len, TrieNode* root) {
	// the word is not in the Trie. do nothing.
	if (!root) return false;

	if (level == len) {

		// the word is in the trie. every char is found in Trie, the last one is leaf. 		
		if (root->leaf) {
			// the word is a prefix of other word.
			if (isPrefix(root)) {
				root->leaf = false; // mark the leaf to be false;
				return false;
			}
			else {
				// the word is not a prefix of other word, delete it. 
				return true;
			}
		}
		// the word is not in the Trie. (Only a prefix of other word. do nothing.
		return false; 
	}
	if (removeDfs(word, level + 1, len, root->child[word[level] - 'a'])) {
		DELETE(root->child[word[level] - 'a']);
		
		// the root is neither a leaf nor a prefix of other word.
		// If root is one of the above, the word ending at this char is either a word in the Trie or a prefix of other word.
		return !root->leaf && !isPrefix(root);
	}
	return false;
}