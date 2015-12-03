#include "Algorithms.h"

/*

A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).
Write a function to count the total strobogrammatic numbers that exist in the range of low <= num <= high.

For example,
Given low = "50", high = "100", return 3. Because 69, 88, and 96 are three strobogrammatic numbers.

Note:
Because the range might be a large number, the low and high numbers are represented as string.

*/

int StrobogrammaticNumber::minus(string n1, string n2) {
	int len1 = n1.length(), len2 = n2.length();
	if (len1 > len2)
		return 1;
	else if (len1 < len2)
		return -1;

	for (int i = 0; i < len1; i++) {
		if (n1[i] > n2[i])
			return 1;
		else if (n1[i] < n2[i])
			return -1;
	}
	return 0;
}
void StrobogrammaticNumber::numDfs(int& count, string instance, int max) {
	if (instance.length() == max) {
		if (minus(instance, l) >= 0 && minus(h, instance) >= 0)
			count++;
		return;
	}
	if (instance.length() > max) {
		return;
	}
	if (instance.length() == 0) {
		vector<string> start = { "0", "1", "8" };
		for (auto s : start)
			numDfs(count, s, max);
	}
	if (instance.length() < max - 2)
		numDfs(count, "0" + instance + "0", max);
	numDfs(count, "1" + instance + "1", max);
	numDfs(count, "8" + instance + "8", max);
	numDfs(count, "6" + instance + "9", max);
	numDfs(count, "9" + instance + "6", max);
}

int StrobogrammaticNumber::strobogrammaticInRange(string low, string high) {
	l = low;
	h = high;
	int lowLen = low.length(), highLen = high.length();
	int count = 0;
	for (int i = lowLen; i <= highLen; i++) {
		numDfs(count, "", i);
	}
	return count;
}