#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, a[N], b[N];

struct Cartesian_Tree {
	struct node {
		int id, val, fa;
		int son[2];
		node() {}
		node (int id, int val, int fa) : id(id), val(val), fa(fa) {
			son[0] = son[1] = 0;
		}
	}t[N];
	int root, l[N], r[N];
	void init() {
		t[0] = node(0, 0, 0);
	}
	void build(int n, int *a) {
		for (int i = 1; i <= n; ++i) {
			t[i] = node(i, a[i], 0);
		}
		for (int i = 1; i <= n; ++i) {
			int k = i - 1;
			while (t[k].val > t[i].val) {
				k = t[k].fa;
			}
			t[i].son[0] = t[k].son[1];
			t[k].son[1] = i;
			t[i].fa = k;
			t[t[i].son[0]].fa = i;
		}
		root = t[0].son[1];
	}
	int DFS(int u) {
		if (!u) return 0;
		l[t[u].id] = DFS(t[u].son[0]);
		r[t[u].id] = DFS(t[u].son[1]);
		return l[t[u].id] + r[t[u].id] + 1;
	}
}t[2];

bool check(int x) {
	t[0].init();
	t[1].init();
	t[0].build(x, a);
	t[1].build(x, b);
	t[0].DFS(t[0].root);
	t[1].DFS(t[1].root);
	for (int i = 1; i <= x; ++i) {
		if (t[0].l[i] != t[1].l[i] || t[0].r[i] != t[1].r[i]) 
			return 0;
	}
	return 1;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		for (int i = 1; i <= n; ++i) {
			scanf("%d", b + i);
		}
		int l = 1, r = n, res = -1;
		while (r - l >= 0) {
			int mid = (l + r) >> 1;
			if (check(mid)) {
				res = mid;
				l = mid + 1;
			} else {
				r = mid - 1;
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
