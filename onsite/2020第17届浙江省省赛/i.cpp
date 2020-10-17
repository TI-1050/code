#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, tot;
int fa[N], sze[N], num[N];
map<int , int> mp;

int get(int x) {
	if (mp.count(x)) return mp[x];
	mp[x] = ++tot;
	return tot;
}

int find(int x) {
	return x == fa[x] ? fa[x] : fa[x] = find(fa[x]);
}

void Union(int x, int y) {
	x = find(x), y = find(y);
	if (x != y) {
		if (sze[x] > sze[y]) swap(x, y);
		fa[y] = x;
		sze[x] += sze[y];
	}
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			sze[i] = 1, num[i] = 0, fa[i] = i;
		}
		tot = 0;
		mp.clear();
		for (int i = 1, u, v; i <= n; ++i) {
			scanf("%d %d", &u, &v);
			u = get(u), v = get(v);
			Union(u, v);
		}
		for (int i = 1; i <= n; ++i) {
			num[find(i)]++;
		}
		int res = 0;
		for (int i = 1; i <= n; ++i) res = max(res, num[i]);
		printf("%d\n", res);
	}
	return 0;
}
