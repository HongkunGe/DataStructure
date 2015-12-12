#include "Algorithms.h"

BigInt::BigInt(string n) : number(n) {}

string BigInt::add(string other) {
	int len1 = number.length(), len2 = other.length();
	int i1 = len1 - 1, i2 = len2 - 1, carry = 0, temp = 0;
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
	return res;
}

