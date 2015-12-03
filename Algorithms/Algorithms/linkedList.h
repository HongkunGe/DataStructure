#pragma once
#pragma once
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <vector>

using namespace std;

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
	linkedList(vector<int>& A) {
		head = new ListNode(A[0]);
		ListNode* temp = head;
		for (int i = 1; i < A.size(); i++) {
			temp->next = new ListNode(A[i]);
			temp = temp->next;
		}
	}
};
void print(ListNode* head) {
	while (head) {
		cout << head->val << " ";
		head = head->next;
	}
}
#endif LINKEDLIST_H