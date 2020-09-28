#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;

const int N = 1e5 + 10;

int n, m;
int fa[N];
ll sze[N];

int find(int x) {
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}

int main() {
	while (~scanf("%d %d", &n, &m)) {
		for (int i = 1; i <= n; ++i) {
			fa[i] = i;
			sze[i] = 1;
		}
		ull tmp = n;
		ull res = 1ll * tmp * (tmp - 1) / 2 * (tmp - 2) / 3 * (tmp - 3) / 4;
		printf("%llu\n", res);
		ull S = 1ll * n * (n - 1) / 2;
		for (int _m = 1, u, v; _m <= m; ++_m) {
			scanf("%d %d", &u, &v);
			int x = find(u), y = find(v);
			if (x != y) {
				S -= sze[x] * sze[y];
				res -= sze[x] * sze[y] * (S - (sze[x] + sze[y]) * (n - sze[x] - sze[y]));
				if (sze[x] > sze[y]) swap(x, y);
				fa[x] = y;
				sze[y] += sze[x];
			}
			printf("%llu\n", res);
		}
	}
	return 0;
}
