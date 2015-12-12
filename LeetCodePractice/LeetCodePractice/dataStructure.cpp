#include "LeetCode.h"
/*
Two data structure to implement the disjoint set.
1. linked list  https://www.youtube.com/watch?v=ID00PMy0-vE
2. hash table.  Using here.

*/
template<class T>
disjointSet<T>::disjointSet(vector<T> items) {
	for (auto i : items) {
		parent[i] = i;
		rank[i] = 0;
	}
}


template<class T>
void disjointSet<T>::makeSet(T c) {
	// if c is already in the sets, do nothing.
	if (parent.count(c) == 0) {
		parent[c] = c;
		rank[c] = 0;
		count++;
	}
}
/* Given a char in the disjoint set, return the root of the set.  Also does the path compression.*/
template<class T>
T disjointSet<T>::find(T c) {
	if (parent.count(c) == 0) {
		cout << "Not Found!\n";
		return 0;
	}
	if (parent[c] == c)
		return c;

	// does the path compression.
	parent[c] = find(parent[c]);
	return parent[c];
}
/* Test if c is in the disjoint Set*/
template<class T>
bool disjointSet<T>::contain(T c) {
	if (parent.count(c) == 0)
		return false;
	return true;
}
/* Combine two sets into one single set by rank. */
template<class T>
void disjointSet<T>::unionSet(T set1, T set2) {

	T parent1 = find(set1);
	T parent2 = find(set2);

	// if set1 and set2 are already in the same set, do nothing.
	if (parent1 == parent2)
		return;

	// if set1 or set2 is not in the disjoint sets, they'll be automatically added in.
	if (rank[parent1] > rank[parent2]) {
		parent[parent2] = parent1;
	}
	else if (rank[parent1] < rank[parent2]) {
		parent[parent1] = parent2;
	}
	else {
		// increase rank only if they have the same rank.
		parent[parent1] = parent2;
		rank[parent2] ++;
	}
	count--; // one set less;
}


template<class T>
int disjointSet<T>::size() {
	return count;
}


Trie::Trie() {
	root = new TrieNode();
}
void Trie::insert(const string& word) {
	TrieNode* node = root;
	for (int i = 0; i < word.length(); i++) {
		if (node->child[word[i] - 'a'] == nullptr) {
			node->child[word[i] - 'a'] = new TrieNode();
		}
		node = node->child[word[i] - 'a'];
	}
	node->leaf = true;
}
bool Trie::search(const string& word) {
	for (int i = 0; i < word.length(); i++) {
		if (root->child[word[i] - 'a'] == nullptr) {
			return false;
		}
		root = root->child[word[i] - 'a'];
	}
	return root->leaf;
}

linkedList::linkedList(vector<int>& A) {
	head = new ListNode(A[0]);
	ListNode* temp = head;
	for (int i = 1; i < A.size(); i++) {
		temp->next = new ListNode(A[i]);
		temp = temp->next;
	}
}