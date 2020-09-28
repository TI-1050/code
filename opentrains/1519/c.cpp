#include <bits/stdc++.h>

using namespace std;

using db = double;

const dp eps = 1e-8;
const int N = 8e2 + 10;

int sgn(db x) {
	if (fabs(x) < eps) return 0;
	else return x > 0 ? 1 : -1;
}

db a[N][N], x[N][N];

int gao() {
	int i, j, k, col, max_r;
	for (k = 0, col = 0; k < equ && col < var; ++k, ++col) {
		max_r = k;
		for (i = k + 1; i < equ; ++i) {
			if (sgn(fabs(a[i][col]) - fabs(a[max_r][col]))) {
				max_r = i;
			}
		}
		if (sgn(a[max_r][col]) == 0) return 0;
		if (k != max_r) {
			for (j = col; j < var; ++j) {
				swap(a[k][j], a[max_r][j]);
			}
			swap(x[k], x[max_r]);
		}
		x[k] /= a[k][col];
		for (j = col + 1; j < var; ++j) {
			a[k][j] /= a[k][col];
		}
		a[k][col] = 1;
		for (i = 0; i < equ; ++i) {
			if (i != k) {
				x[i] -= x[k] * a[i][col];
				for (j = col + 1; j < var; ++j) {
					a[i][j] -= a[k][j] * a[i][col];
				}
				a[i][col] = 0;
			}
		}
	}
	return 1;
}

int n, m;
int id[N][N];
char s[N], t[N];
db f[N][N];

int main() {
	while (scanf("%s %s", s + 1, t + 1) != EOF) {
		n = strlen(s + 1), m = strlen(t + 1);
		memset(f, 0, sizeof f);
		memset(a, 0, sizeof a);
		memset(x, 0, sizeof x);
		int tot = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				id[i][j] = ++tot;
			}
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				int Id = id[i][j];
				a[Id][Id] = 1;
				if (s[i] == t[j]) {
					if (s[i + 1] == t[j + 1] && i + 1 <= n && j + 1 <= m) {
						a[Id][id[i + 1][j + 1]] = -0.5;
						a[0][Id] -= 0.5;
					} else {
						
					}
				}
			}
		}
	}
	return 0;
}
