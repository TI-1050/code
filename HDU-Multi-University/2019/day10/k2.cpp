#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 3e5 + 10;
const int M = 25;
const int INF = 0x3f3f3f3f;
int n, k, a[N], f[N], g[N], id[N], lz[N], rz[N];

struct Cartesion_Tree {
	struct node {
		int id, val, fa;
		int son[2];
		node() {}
		node(int id, int val, int fa) : id(id), val(val), fa(fa) {
			son[0] = son[1] = 0;
		}
		bool operator < (const node &other) const {
			return val > other.val; 
		}
	}t[N];
	int root;
	void init() {
		t[0] = node(0, INF, 0);
	}
	void build(int n, int *a) {
		for (int i = 1; i <= n; ++i) t[i] = node(i, a[i], 0);
		for (int i = 1; i <= n; ++i) {
			int k = i - 1;
			while (t[i] < t[k]) k = t[k].fa;
			t[i].son[0] = t[k].son[1];
			t[k].son[1] = i;
			t[i].fa = k;
			t[t[i].son[0]].fa = i;
		}
		root = t[0].son[1];
	}
	int DFS(int u) {
		if (!u) return 0;
		lz[u] = DFS(t[u].son[0]);
		rz[u] = DFS(t[u].son[1]);
		return lz[u] + rz[u] + 1;
	}
}CT;

struct RMQ {
	int Max[N][M], Min[N][M], mm[N];
	void init(int n, int *b, int *c) {
		mm[0] = -1;
		for (int i = 1; i <= n; ++i) {
			mm[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
			Max[i][0] = b[i];
			Min[i][0] = c[i];
		}
		for (int j = 1; j <= mm[n]; ++j) {
			for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
				Max[i][j] = max(Max[i][j - 1], Max[i + (1 << (j - 1))][j - 1]);
				Min[i][j] = min(Min[i][j - 1], Min[i + (1 << (j - 1))][j - 1]);
			}
		}
	}
	inline int queryMax(int x, int y) {
		int k = mm[y - x + 1];
		return max(Max[x][k], Max[y - (1 << k) + 1][k]);
	}
	inline int queryMin(int x, int y) {
		int k = mm[y - x + 1];
		return min(Min[x][k], Min[y - (1 << k) + 1][k]); 
	}
}rmq;

int main() {
	int _T; cin >> _T;
	while (_T--) {
		scanf("%d%d", &n, &k);
		for (int i = 1; i <= n; ++i) id[i] = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			f[i] = id[a[i]];
			id[a[i]] = i;
		}
		for (int i = 1; i <= n; ++i) id[i] = n + 1;
		for (int i = n; i >= 1; --i) {
			g[i] = id[a[i]];
			id[a[i]] = i;	
		}
		CT.init(); CT.build(n, a);
		CT.DFS(CT.root);
		rmq.init(n, f, g); 
		ll res = 0; 
		for (int i = 1; i <= n; ++i) {
			int l = i - lz[i], r = i + rz[i];
			if (r - i > i - l) {
				int ql = i, qr = r, pos = ql;
				while (qr - ql >= 0) {
					int mid = (ql + qr) >> 1;
					if (rmq.queryMin(i, mid) > mid) {
						pos = mid;
						ql = mid + 1;
					} else {
						qr = mid - 1;
					}
				}
				r = pos;
				for (int j = i; j >= l; --j) {
					r = min(r, g[j] - 1);
					if (r < i) break;
					res += max(0, r - max(i, (a[i] + j - k - 1)) + 1);
				}	
			} else {
				int ql = l, qr = i, pos = qr;
				while (qr - ql >= 0) {
					int mid = (ql + qr) >> 1;
					if (rmq.queryMax(mid, i) < mid) {
						pos = mid;
						qr = mid - 1;
					} else {
						ql = mid + 1; 
					}
				}
				l = pos;
				for (int j = i; j <= r; ++j) {
					l = max(l, f[j] + 1);
					if (l > i) break;
					res += max(0, min(i, (k + j + 1 - a[i])) - l + 1);
				}
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
