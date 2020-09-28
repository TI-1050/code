#include <bits/stdc++.h>
using namespace std;

int main() {
	int n = 20, m = 20;
	printf("%d %d\n", n, m);
	vector <int> vec;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			vec.push_back((i - 1) * m + j);
		}
	}
	mt19937 rnd(time(NULL));
//	shuffle(vec.begin(), vec.end(), rnd);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			printf("%d%c", vec[(i - 1) * m + j - 1], " \n"[j == m]);
		}
	}
	return 0;
}

