#pragma once
#ifndef TREE_H
#define TREE_H

#include <iostream>
using namespace std;
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class tree {
	TreeNode* root;

	void inOrderPrint(TreeNode*);
	void postOrderPrint(TreeNode*);
	void preOrderPrint(TreeNode*);
public:
	tree() : root(NULL) {};
	~tree();

	void inOrderPrint();
	void postOrderPrint();
	void preOrderPrint();

	bool search(int x);
	TreeNode* successor(TreeNode* x);

};

#endif TREE_H