#include <bits/stdc++.h>

using namespace std;

const int N = 510;

int n, m;
char mp[N][N];

int main() {
	while (scanf("%d %d", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				scanf(" %c", mp[i] + j);
			}
		}
		int res = 0;
		if (n == 1) {
			for (int j = 2; j < m; ++j) {
				if (mp[1][j] == '.') res++;
			}
		} else if (m == 1) {
			for (int i = 2; i < n; ++i) {
				if (mp[i][1] == '.') res++;
			}
		} else if (n == 2 && m == 2) {
			res = 0;
		} else if (n == 2) {
			for (int j = 2; j < m; ++j) {
				if (mp[1][j] == '.' && mp[2][j] == '.') res++;
			}
		} else if (m == 2) {
			for (int i = 2; i < n; ++i) {
				if (mp[i][1] == '.' && mp[i][2] == '.') res++;
			}
		} else {
			bool F = false;
			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j <= m; ++j) {
					if ((i == 1 && j == 1) || (i == 1 && j == m) || (i == n && j == 1) || (i == n && j == m)) continue;
					if (i == 1 || i == n || j == 1 || j == m) {
						if (mp[i][j] == '#') F = true;
					} else {
						if (mp[i][j] == '.') res++;
					}
				}
			}
			if (!F) res++;
		}
		printf("%d\n", res);
	}
	return 0;
}
