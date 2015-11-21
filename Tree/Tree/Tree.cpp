#include <iostream>
#include "Tree.h"

using namespace std;

tree::~tree() {

}

bool tree::search(int x) {
	TreeNode* runner = root;
	while (runner) {
		if (x < runner->val) {
			runner = runner->left;
		}
		else if(x > runner->val){
			runner = runner->right;
		}
		else {
			return true;
		}
	}
	return false;
}

void tree::inOrderPrint() {
	inOrderPrint(root);
}
void tree::preOrderPrint() {
	inOrderPrint(root);
}
void tree::postOrderPrint() {
	inOrderPrint(root);
}

void tree::inOrderPrint(TreeNode* root) {
	inOrderPrint(root->left);
	cout << root->val << " ";
	inOrderPrint(root->right);
}

void tree::postOrderPrint(TreeNode* root) {
	postOrderPrint(root->left);
	postOrderPrint(root->right);
	cout << root->val << " ";
}

void tree::preOrderPrint(TreeNode* root) {
	cout << root->val << " ";
	preOrderPrint(root->left);
	preOrderPrint(root->right);
}

