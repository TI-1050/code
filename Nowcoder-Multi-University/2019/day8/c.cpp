#include <bits/stdc++.h>
using namespace std;

const int N = 2e3 + 10;
int m, k;
int s[N][N];

void gao(int x, int y, int k) {
	if (k == 1) {
		s[x][y] = 1;
		s[x + 1][y] = 1;
		s[x][y + 1] = 1;
		s[x + 1][y + 1] = -1;
		return;
	}
	int n = (1 << (k - 1)); 
	gao(x, y, k - 1);
	gao(x + n, y, k - 1);
	gao(x, y + n, k - 1);
	gao(x + n, y + n, k - 1);
	for (int i = x + n; i < x + 2 * n; ++i) {
		for (int j = y + n; j < y + 2 * n; ++j) {
			s[i][j] *= -1;
		}
	}
}

int get(int x) {
	for (int i = 10; i >= 0; --i) {
		if ((x >> i) & 1) {
			return i;
		}
	}
}

int main() {
	while (scanf("%d", &m) != EOF) {
		k = get(m);
		gao(1, 1, k);
		for (int i = 1; i <= m; ++i)
			for (int j = 1; j <= m; ++j)
				printf("%d%c", s[i][j], " \n"[j == m]);
	}
	return 0;
}
