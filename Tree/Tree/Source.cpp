#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;

	TreeNode(int v = 0) {
		val = v;
		left = nullptr;
		right = nullptr;
	}
};

void find_longest_path(TreeNode* root, int& left, int& right, int& res)
{
	if (root == nullptr) {
		left = right = 0;
		return;
	}

	int left_left = 0, left_right = 0, right_left = 0, right_right = 0;
	find_longest_path(root->left, left_left, left_right, res);
	find_longest_path(root->right, right_left, right_right, res);

	left = left_left + 1;
	right = right_right + 1;
	res = max(res, max(left, right));
}
void amplitude2(TreeNode* root, int maxNum, int minNum, int &res) {
	if (!root) return;
	if (!root->left && !root->right) {
		res = max(res, maxNum - minNum); // the end of one path.
	}
	if (root->left) {
		maxNum = max(root->left->val, maxNum);
		minNum = min(root->left->val, minNum);
		amplitude2(root->left, maxNum, minNum, res);
	}
	if (root->right) {
		maxNum = max(root->right->val, maxNum);
		minNum = min(root->right->val, minNum);
		amplitude2(root->right, maxNum, minNum, res);
	}
	return;
}
int amplitude2(TreeNode* root) {
	int maxNum, minNum, res = 0;
	if (!root) return 0;
	maxNum = minNum = root->val;
	amplitude2(root, maxNum, minNum, res);
	return res;
}
void amplitude(TreeNode* root, int maxNum, int minNum, int &res) {
	if (!root) {
		res = max(res, maxNum - minNum); // the end of one path.
		return;
	}
	maxNum = max(maxNum, root->val);
	minNum = min(minNum, root->val);

	amplitude(root->left, maxNum, minNum, res);
	amplitude(root->right, maxNum, minNum, res);
	return;
}
int amplitude(TreeNode* root) {
	int maxNum, minNum, res = 0;
	if (!root) return 0;
	maxNum = minNum = root->val;
	amplitude(root, maxNum, minNum, res);
	return res;
}

double ParseAtom(char*& expr) {
	// Read the number from string
	char* end_ptr;
	double res = strtod(expr, &end_ptr);
	// Advance the pointer and return the result
	expr = end_ptr;
	return res;
}

// Parse multiplication and division
double ParseFactors(char*& expr) {
	double num1 = ParseAtom(expr);
	for (;;) {
		// Save the operation
		char op = *expr;
		if (op != '/' && op != '*')
			return num1;
		expr++;
		double num2 = ParseAtom(expr);
		// Perform the saved operation
		if (op == '/')
			num1 /= num2;
		else
			num1 *= num2;
	}
}

// Parse addition and subtraction
double ParseSummands(char*& expr) {
	double num1 = ParseFactors(expr);
	for (;;) {
		char op = *expr;
		if (op != '-' && op != '+')
			return num1;
		expr++;
		double num2 = ParseFactors(expr);
		if (op == '-')
			num1 -= num2;
		else
			num1 += num2;
	}
}

double EvaluateTheExpression(char* expr) {
	return ParseSummands(expr);
};
int main()
{
	//      0
	//   1    2
	// 3   4
	//       5
	//         6

	char*  op1 = { "    3 * 2 +50 /2" };
	double res1 = EvaluateTheExpression(op1);


	vector<TreeNode*> nodes(7, nullptr);
	for (int i = 0; i < nodes.size(); ++i)
		nodes[i] = new TreeNode(i);

	nodes[0]->left = nodes[1];
	nodes[0]->right = nodes[2];
	nodes[1]->left = nodes[3];
	nodes[1]->right = nodes[4];
	nodes[4]->right = nodes[5];
	nodes[5]->right = nodes[6];

	int res = 0, left = 0, right = 0, test;
	for (int i = 0; i < 7; i++) {
		find_longest_path(nodes[i], left, right, res);
		res = 0;
		test = amplitude(nodes[i]);
		test = amplitude2(nodes[i]);
	}
		

	return 0;
}
