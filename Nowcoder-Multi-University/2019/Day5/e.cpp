#include <bits/stdc++.h>
using namespace std;

int n, m;
int e[30];
char f[1 << 26];
char max(char x, int y) {
	if (x > y) return x;
	else return y;
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 0; i < n; ++i) e[i] = 1 << i;
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d%d", &u, &v);
			e[u] |= 1 << v;
			e[v] |= 1 << u;
		}
		for (int i = 0; i < n; ++i) {
			e[i] = ~e[i];
		}
		memset(f, 0, sizeof f);
		int ans = 0;
		int it = 0;
		for (int i = 1; i < 1 << n; ++i) {
			if ((i >> (it + 1)) & 1) ++it;
			for (int j = 0; j < n; ++j)
				if ((i >> j) & 1) {
					it = j;
					break;
				}
			f[i] = max(f[i ^ (1 << it)], f[i & e[it]] + 1);
			ans += f[i];
		}
		printf("%d\n", ans);
	}
	return 0;
}
