#include <bits/stdc++.h>
using namespace std;

#define N 100010
int k, n, m;
int a[N];
int pre[N], sze[N];
char s[N];
int tot;
int find(int x) {
	return pre[x] == x ? x : pre[x] = find(pre[x]);
}
void join(int u, int v) {
	u = find(u), v = find(v);
	if (u != v) {
		if (sze[u] > sze[v]) {
			swap(u, v);
		}
		pre[u] = v;
		sze[v] += sze[u];
	} else {
		++tot;
	}
}

void init() {
	tot = 0;
	for (int i = 1; i <= n; ++i) {
		pre[i] = i;
		sze[i] = 1;
	}
}
int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &k);
		scanf("%s", s + 1);
		for (int i = 1; i <= k; ++i) {
			a[i] = s[i] - '0';
		}
		scanf("%d%d", &n, &m);
		init();
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d%d", &u, &v);
			++u, ++v;
			join(u, v);
		}
		printf("%d\n", ((a[tot % k + 1] - 1) ^ 1) + 1);
	}
	return 0;
}
