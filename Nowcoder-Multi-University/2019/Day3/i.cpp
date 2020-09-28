#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, a[N], b[N];
int f[N][3][3], pre[N][3][3], v[N][3], s[3];

int med(int x, int y, int z) {
	s[0] = x, s[1] = y, s[2] = z;
	sort(s, s + 3);
	return s[1];
}

void get(int &x, int &y) {
	x = -1, y = -1;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j) 
			if (f[n][i][j]) {
				x = i;
				y = j;
				return;
			}
}

void solve() {
	int x, y; get(x, y);
	if (x == -1 || y == -1) {
		puts("-1");
		return;
	}
	for (int i = n; i >= 1; --i) {
		b[i] = v[i][x];
		x = pre[i][x][y];
		swap(x, y);
	}
//	for (int i = 2; i < n; ++i) assert(med(b[i - 1], b[i], b[i + 1]) == a[i]);
	for (int i = 1; i <= n; ++i) printf("%d%c", b[i], " \n"[i == n]);
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 2; i < n; ++i) scanf("%d", a + i);
		a[0] = a[1] = a[2];
		a[n] = a[n + 1] = a[n - 1];
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < 3; ++j)
				v[i][j] = a[i + j - 1]; 
			sort(v[i], v[i] + 3);
		}
		for (int i = 1; i <= n; ++i) 
			for (int j = 0; j < 3; ++j)
				for (int k = 0; k < 3; ++k)
					f[i][j][k] = 0;
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				f[2][i][j] = 1;
		for (int i = 3; i <= n; ++i)
			for (int j = 0; j < 3; ++j)
				for (int k = 0; k < 3; ++k)
					for (int l = 0; l < 3; ++l) {
						if (!f[i - 1][k][l]) continue;
						if (med(v[i - 2][l], v[i - 1][k], v[i][j]) != a[i - 1]) continue;
						f[i][j][k] = 1;
						pre[i][j][k] = l;
					}
		solve();	
	}
	return 0;
}
