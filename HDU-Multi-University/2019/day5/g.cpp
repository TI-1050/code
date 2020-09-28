#include <bits/stdc++.h>
using namespace std;

int main() {
	vector <int> vec;
	for (int i = 1; i <= 3; ++i) vec.push_back(i);
	do {
		for (int i = 1; i < 3; ++i) {
			printf("%d%c", vec[i] - vec[i - 1], " \n"[i == 2]);
		}
	} while (next_permutation(vec.begin(), vec.end()));
	return 0;
}
