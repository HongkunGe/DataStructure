#include "Algorithms.h"
/*
Use string "(value, lt, rt)" to restore a tree. For example,
(5,(3,(1,null,null),(4,null,null)),(8,null,(9,null,null))

*/
TreeNode* parseStringToTree::parseTree(string input, int& idx) {
	if (idx == input.length())
		return NULL;
	if (input[idx] == 'n') {
		idx += 4;
		return NULL;
	}

	TreeNode* root = NULL;
	if (input[idx] == '(') {
		root = new TreeNode(0);
		idx++;
		int num = 0;
		while (idx < input.length() && '0' <= input[idx] && input[idx] <= '9') {
			num = 10 * num + (input[idx] - '0');
			idx++;
		}
		root->val = num;
		idx++; // skip the ','
		root->left = parseTree(input, idx);
		idx++; // skip the ','
		root->right = parseTree(input, idx);
		idx++; // skip the ')'
	}
	return root;
}
TreeNode* parseStringToTree::parseTree(string input) {
	int idx = 0;
	return parseTree(input, idx);
}