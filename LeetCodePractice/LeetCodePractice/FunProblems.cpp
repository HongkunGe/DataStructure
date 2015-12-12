#include "LeetCode.h"

/*
input: [ [1, 2, 3], [4, 5, 6] ]
output: [ [1], [2, 3], [3, 5], [6] ]
*/
void zigzagPrint(const vector<vector<int>>& matrix) {
	if (matrix.empty())
		return;
	int row = matrix.size(), col = matrix[0].size();
	for (int cnt = 0; cnt <= row + col - 2; cnt++) {
		for (int i = cnt; i >= 0; i--) {
			if (cnt - row < i && i < col) {
				cout << matrix[cnt - i][i] << " ";
			}
		}
		cout << endl;
	}
}

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


/*
find all the strings in dictionary whose character belongs to alpher.
alper "aaterr" dic = {"aaa", "aar", "qsc", "aate"} => {"aar", "aate"}
*/
void checkInDicDFS(vector<string>& res, string instance, unordered_map<char, int>& alpStore, TrieNode* root) {
	if (root->leaf) {
		res.push_back(instance);
	}
	for (char c = 'a'; c <= 'z'; c++) {
		if (root->child[c - 'a'] != nullptr) {
			if (alpStore.count(c) > 0 && alpStore[c] > 0) {
				alpStore[c] --;
				TrieNode *node = root->child[c - 'a'];
				instance += c;
				checkInDicDFS(res, instance, alpStore, node);
				instance.erase(instance.end() - 1);
				alpStore[c] ++;
			}
		}
	}
}
vector<string> checkInDic(vector<char> alpher, vector<string> dic) {
	Trie dicTree;
	for (auto word : dic) {
		dicTree.insert(word);
	}
	unordered_map<char, int> alpStore;
	for (auto c : alpher)
		alpStore[c] ++;
	vector<string> res;
	string instance;
	checkInDicDFS(res, instance, alpStore, dicTree.root);
	return res;
}



void allSubstr::getSortedSubstr(vector<string>& res, string word) {
	for (int i = 0; i < word.size(); i++) {
		string suffix = word.substr(i, word.size() - i);
		res.push_back(suffix);
	}
	sort(res.begin(), res.end());
}

int allSubstr::longestCommonPrefix(string word1, string word2) {
	int l = 0, minLen = min(word1.length(), word2.length());

	while (l < minLen) {
		if (word1[l] == word2[l])
			l++;
		else
			break;
	}

	return l;
}

/* Get the number of distinct substring of input word*/
int allSubstr::sizeOfSubstr(string word) {

	if (word.empty())
		return 0;
	// generate sorted suffixes vector of given word albetically.
	vector<string> suffixes;
	getSortedSubstr(suffixes, word);

	int total = suffixes[0].length();
	for (int i = 1; i < suffixes.size(); i++) {
		int LCP = longestCommonPrefix(suffixes[i], suffixes[i - 1]);
		total += (suffixes[i].length() - LCP);
	}

	return total;
}

/* TODO: Generate all distinct substring of input word*/
vector<string> allSubstr::getAllSubstr(string word) {
	vector<string> res;
	return res;
}


BigInt::BigInt(string n) : number(n) {}

string BigInt::add(string other) {
	int len1 = number.length(), len2 = other.length();
	int i1 = len1 - 1, i2 = len2 - 1, carry = 0;
	string res;
	while (i1 >= 0 || i2 >= 0) {
		int cur = 0;
		if (i1 >= 0) {
			cur += (number[i1] - '0');
			i1--;
		}
		if (i2 >= 0) {
			cur += (other[i2] - '0');
			i2--;
		}
		cur += carry;
		res.insert(0, 1, (cur % 10 + '0'));
		carry = cur / 10;
	}
	if (carry)
		res.insert(0, 1, (carry + '0'));
	return res;
}

BigInt BigInt::operator+(const BigInt& bi) {
	BigInt res(this->number);
	res.set(res.add(bi.number));
	return res;
}

BigInt BigInt::operator*(const BigInt& bi) {
	BigInt res(this->number);
	res.set(res.multiply(bi.number));
	return res;
}
string BigInt::multiply(string other) {
	int len1 = number.length(), len2 = other.length();
	string multiplyRes(len1 + len2, '0');
	for (int i = len1 - 1; i >= 0; i--) {
		int carry = 0;
		for (int j = len2 - 1; j >= 0; j--) {
			int current = carry + (multiplyRes[i + j + 1] - '0') + (number[i] - '0') * (other[j] - '0');
			multiplyRes[i + j + 1] = current % 10 + '0';
			carry = current / 10;
		}
		multiplyRes[i] += carry;
	}
	size_t found = multiplyRes.find_first_not_of("0");
	if (found != string::npos)
		return multiplyRes.substr(found);
	return "0";

}


/*

"abc01", "abc000", "abcd000" => "abc000", "abc01", "abcd000";

"abc012", "abc013", "abc0001", "abc010", "abc2", "abc11", "bbc11" =>
"abc0001", "abc2", "abc010", "abc11", "abc012", "abc013", "bbc11"
*/
bool isAlper(char c) {
	return 'a' <= c && c <= 'z' || 'A' <= c && c <= 'Z';
}
// s2 is larger than s1.
bool cString(const string& s1, const string& s2) {
	int i = 0;
	while (i < min(s1.length(), s2.length())) {
		if (isAlper(s1[i]) && isAlper(s1[i])) {
			if (s1[i] < s2[i])
				return true;
			else if (s1[i] > s2[i])
				return false;
		}
		else if (isAlper(s1[i])) { // s1 is one more letter. 
			return false;
		}
		else if (isAlper(s2[i])) { // s2 is one more letter. 
			return true;
		}
		else {
			break; // abcd012, abcd012, 0;
		}
		i++;
	}
	if (i == s1.length())
		return true; // s2 is longer
	else if (i == s2.length())
		return false; // s1 is longer

					  // compare the digit part.
	size_t found1 = s1.find_first_of("123456789");
	size_t found2 = s2.find_first_of("123456789");
	if (found1 == string::npos && found2 == string::npos)
		return s1.length() < s2.length();
	else if (found2 == string::npos)
		return false; // s2 is abcd000
	else if (found1 == string::npos)
		return true; // s1 is abcd000

	string digit1 = s1.substr(found1), digit2 = s2.substr(found2);
	if (digit1.length() != digit2.length())
		return digit1.length() < digit2.length();

	i = 0;
	while (i < digit1.length()) {
		if (digit1[i] < digit2[i])
			return true;
		else if (digit1[i] > digit2[i])
			return false;
		i++;
	}
	return true;
}

/*
find the next excel number A=>B   ZZ => AAA
*/
string nextExcel(string s) {
	int carry = 1;
	for (int i = s.length() - 1; i >= 0; i--) {
		s[i] += carry;
		if (s[i] > 'Z') {
			s[i] = 'A';
			carry = 1;
		}
		else {
			carry = 0;
			break;
		}
	}
	if (carry)
		s.insert(0, 1, 'A');
	return s;
}

/*

One-direction path: the path that starts from one node and continues in 
one single direction(continously left or continously right). 
find One-direction path, the node may not be the root of the tree.

*/
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


/*

get the amplitude of a tree. 
the amplitude of a path in a tree is the difference between the max and min in one path
from root to leaves. the amplitude of a tree is the max of amplitude of all the path.

*/
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

