#include "Algorithms.h"
/*

You are playing the following Flip Game with your friend: Given a string that contains only these two characters: + and -, 
you and your friend take turns to flip two consecutive "++" into "--". The game ends when a person can no longer make a move 
and therefore the other person will be the winner.

Write a function to determine if the starting player can guarantee a win.
For example, given s = "++++", return true. The starting player can guarantee a win by flipping the middle "++" to become "+--+".

Follow up:
Derive your algorithm's runtime complexity.

T(N) = T(N-2) + T(N-3) + [T(2) + T(N-4)] + [T(3) + T(N-5)] + ...
[T(N-5) + T(3)] + [T(N-4) + T(2)] + T(N-3) + T(N-2)
= 2 * sum(T[i])  (i = 3..N-2)
T(N) = 2^(N-1) satisfies the above equation.

*/
/*
Explanation: for 10:"++++++++++" there is a solution "++++--++++", for all branches of this solution:
"--++--++++"(T),"+--+--++++"(T),"++----++++"(T), all return true. so "++++--++++" returns false. in the top of the recursive function tree, "++++++++++" returns true, jump out of the for loop, we are good.
Construct the strategy tree, "++++++++++", we choose "++++--++++", no matter what position the second player choose in next step. we have a way to win, so we are guaranteed to be the winner.
*/
bool filpGame::canWin(string s) {
	unordered_map<string, bool> record;
	return canWinDfs(s, record);
}
bool filpGame::canWinDfs(string& s, unordered_map<string, bool>& record) {
	if (record.count(s) > 0)
		return record[s];
	bool wins = false;
	for (int i = 1; i < s.length(); i++) {
		if (s[i] == '+' && s[i - 1] == '+') {

			s[i] = s[i - 1] = '-';
			wins = !canWinDfs(s, record);
			record[s] = !wins;
			s[i] = s[i - 1] = '+';

			if (wins)
				return true;
		}
	}
	return wins;
}

vector<string> filpGame::generatePossibleNextMoves(string s) {
	vector<string> res;
	int upper = s.length() - 1;
	for (int i = 0; i < upper; i++) {
		if (s[i] == '+' && s[i + 1] == '+') {
			s[i] = s[i + 1] = '-';
			res.push_back(s);
			s[i] = s[i + 1] = '+';
		}
	}
	return res;
}