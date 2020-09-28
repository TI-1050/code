#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 300010
#define pii pair <int, int>
#define fi first
#define se second
int n, a[N];
pii b[N]; 
ll S[N];

struct Cartesian_Tree {
	struct node {
		int id, val, fa;
		int son[2];
		node() {}
		node (int id, int val, int fa) : id(id), val(val), fa(fa) {
			son[0] = son[1] = 0;
		}
		bool operator < (const node &other) const {
			return id < other.id;
		}
	}t[N];
	int root;
	void init() {
		t[0] = node(0, 1e9, 0);
	}
	void build(int n, int *a) {
		for (int i = 1; i <= n; ++i) {
			t[i] = node(i, a[i], 0);
		}
		for (int i = 1; i <= n; ++i) {
			int k = i - 1;
			while (t[k].val < t[i].val) {
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
		int lsze = DFS(t[u].son[0]);
		int rsze = DFS(t[u].son[1]);
		b[t[u].id].fi = lsze;
		b[t[u].id].se = rsze; 
		return lsze + rsze + 1; 
	}
}CT;

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		S[0] = 0;
		for (int i = 1; i <= n; ++i) scanf("%d", a + i), S[i] = S[i - 1] + a[i];
		CT.init();
		CT.build(n, a);
		CT.DFS(CT.root);
		ll res = 0;
		for (int i = 1; i <= n; ++i) {
			int l = i - b[i].fi, r = i + b[i].se;
		//	cout << i << " " << l << " " << r << endl;
			//枚举左边
			if (i - l <= r - i) {
				for (int j = l; j <= i; ++j) {
					int ql = i, qr = r, pos = -1;
					while (qr - ql >= 0) {
						int mid = (ql + qr) >> 1;
						if (S[mid] - S[j - 1] - a[i] >= a[i]) {
							pos = mid;
							qr = mid - 1;
						} else {
							ql = mid + 1; 
						}
					}
					if (pos != -1) {
						res += r - pos + 1;
					}
				}
			} else {
				for (int j = i; j <= r; ++j) {
					int ql = l, qr = i, pos = -1;
					while (qr - ql >= 0) {
						int mid = (ql + qr) >> 1; 
						if (S[j] - S[mid - 1] - a[i] >= a[i]) {
							pos = mid;
							ql = mid + 1;
						} else {
							qr = mid - 1; 
						}
					}
					if (pos != -1) {
						res += pos - l + 1; 
					}
				}
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
