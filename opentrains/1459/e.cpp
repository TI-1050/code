#include <bits/stdc++.h>

using namespace std;

#define N 510

int n, m;
int d[N];
int a[N][N];
int ans[N];
int free_x[N], free_num; 
int vis[N];
int x[N];

int gauss() {
	int max_r, col, k;
	free_num = 0;
	for (k = 0, col = 0; k < n && col < n; ++k, ++col) {
		max_r = k;
		for (int i = k + 1; i < n; ++i) {
			if (abs(a[i][col]) > abs(a[max_r][col])) {
				max_r = i;
			}
		}
		if (a[max_r][col] == 0) {
			k--;
			free_x[free_num++] = col;
			continue;
		}
		if (k != max_r) {
			for (int j = col; j < n + 1; ++j) {
				swap(a[k][j], a[max_r][j]);
			}
		}
		for (int i = k + 1; i < n; ++i) {
			if (a[i][col] != 0) {
				for (int j = col; j < n + 1; ++j) {
					a[i][j] ^= a[k][j];
				}
			}
		}
	}
	for (int i = k; i < n; ++i) {
		if (a[i][col] != 0) {
			return -1;
		}
	}
	for (int i = n - 1; i >= 0; --i) {
		ans[i] = a[i][n];
		for (int j = i + 1; j < n; ++j) {
			ans[i] ^= (a[i][j] && ans[j]);
		}
	}
	if (k < n) return n - k;
	return 0;
}

int main() {
	while (scanf("%d %d", &n, &m) != EOF) {
		memset(a, 0, sizeof a);
		memset(d, 0, sizeof d);
		memset(vis, 0, sizeof vis);
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d %d", &u, &v);
			--u, --v;
			a[u][v] = a[v][u] = 1;
			d[u]++, d[v]++;
		}
		for (int i = 0; i < n; ++i) {
			if (d[i] & 1) {
				a[i][i] = 1;
			}
			a[i][n] = d[i] % 2;
		}
		int sta = gauss();
		if (sta == -1) {
			puts("IMPOSSIBLE");		
		} else if (sta == 0) {
			for (int i = 0; i < n; ++i) {
				putchar(ans[i] + 'A');
			}
			puts("");
		} else {
			cout << sta << endl;
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j <= n; ++j)
					printf("%d ", a[i][j]);
				cout << endl;
			}
			for (int i = 0; i < free_num; ++i)
				cout << free_x[i] << " ";
			cout << endl;
			for (int i = 0; i < free_num; ++i) {
				vis[free_x[i]] = 1;
				x[free_x[i]] = 0;
			}
			for (int i = 0, cnt = 0; i < n; ++i) { 
				if (!vis[i]) {
					x[i] = a[cnt++][n]; 
				}
			}
			for (int i = 0; i < n; ++i) 
				printf("%d%c", ans[i], " \n"[i == n - 1]);
			for (int i = 0; i < n; ++i) {
				putchar(x[i] + 'A');
			}
			puts("");
		}
	}
	return 0;
}
