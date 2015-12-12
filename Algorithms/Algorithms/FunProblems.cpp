#include "Algorithms.h"
#include "linkedList.h"


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