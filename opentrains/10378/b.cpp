#include <bits/stdc++.h>
using namespace std;

using db = double;
const db eps = 1e-9;
const int N = 330;
db a[N][N], x[N];
int equ, var, k[2], b[2], s[2], h[2][N];
int Gauss() {
	int i, j, k, col, max_r;
	for (k = 0, col = 0; k < equ && col < var; ++k, ++col) {
		max_r = k;

	}
}

int main() {
	vector <int> vec;
	for (int i = 0; i < 2; ++i) {
		scanf("%d%d%d", k + i, b + i, s + i);
		for (int j = 1; j <= k[0]; ++j) {
			scanf("%d", h[i] + j);
		}
		for (int i = 1; i <= k; ++i) {
			vec.push_back(b + (i - 1) * s);
			vec.push_back(b + i * s - 1);
		}
	}
	sort(vec.begin(), vec.end(), [&](int x, int y) { return x < y; });
	vec.erase(unique(vec.begin(), vec.end()), vec.end());
	return 0;
}
