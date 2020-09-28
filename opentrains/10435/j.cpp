#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 300010
#define pii pair <int, int>
#define fi first
#define se second
int n, a[N];
pii b[N];
ll L, R;
vector <ll> res;

struct Cartesian_Tree {
	struct node {
		int id, val, fa;
		int son[2];
		node() {}
		node (int id, int val, int fa) : id(id), val(val), fa(fa) {
			son[0] = son[1] = 0;
		}
	}t[N];
	int root;
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
		int lsze = 0, rsze = 0;
		if (t[u].son[0]) {
			lsze = DFS(t[u].son[0]);
		}
		if (t[u].son[1]) {
			rsze = DFS(t[u].son[1]);
		}
		b[t[u].id] = pii(lsze, rsze);
		return lsze + rsze + 1; 
	}
	void print(int u) {
		if (!u) return;
		print(t[u].son[0]);
		printf("%d %d %d\n", u, t[u].id, t[u].val);
		print(t[u].son[1]);
	}
}CT;

ll f(ll l, ll r) {
	if (l > r) return 0;
	return (r + l) * (r - l + 1) / 2;
}

//得到面积小于等于x的个数
ll getcnt(ll x) {
	ll res = 0;
	for (int i = 1; i <= n; ++i) {
		ll len = x / a[i]; 
	    if (len <= 0) continue;
//	    cout << len << endl;	
		if (len - b[i].se <= 0) {
			res += f(max(1ll, len - b[i].fi), len);
		} else {
			res += 1ll * min(len - b[i].se, 1ll * b[i].fi + 1) * (b[i].se + 1);  
			if (len <= b[i].fi + b[i].se + 1) {
				res += f(max(1ll, len - b[i].fi), b[i].se);
			}
		}
//		cout << res << endl;
	}
	return res;
}

ll get(ll x) {
	ll l = 1, r = 1e15, res = -1;
	while (r - l >= 0) {
		ll mid = (l + r) >> 1;
//		cout << mid << " " << getcnt(mid) << endl;
		if (getcnt(mid) >= x) {
			r = mid - 1;
			res = mid;
		} else {
			l = mid + 1;
		}
	}
	return res;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		CT.init(); CT.build(n, a);
		CT.DFS(CT.root);
	//    for (int i = 1; i <= n; ++i) {
	//		printf("%d %d %d\n", i, b[i].fi, b[i].se);
	//	}	
		scanf("%lld%lld", &L, &R);
		ll QL = get(L) + 1, QR = get(R) - 1;
		res.clear();
		if (QL <= QR) {
			for (int i = 1; i <= n; ++i) {
				ll len = QL / a[i] + (QL % a[i] != 0), low = max(1ll, len - b[i].se);
				for (ll j = low; j <= b[i].fi + 1; ++j) {
					if (1ll * a[i] * j > QR) break;
					ll _low = max(0ll, len - j); 
					for (ll k = _low; k <= b[i].se; ++k) {
						if (1ll * a[i] * (j + k) > QR) break;
						res.push_back(1ll * a[i] * (j + k));
					}	
				}
			}
		}
		ll m = R - L + 1;
		ll cnt = getcnt(QL - 1) - L + 1;
		while (cnt > 0) {
			--cnt;
			res.push_back(QL - 1);
		}
		while ((int)res.size() <= m) {
			res.push_back(QR + 1);
		}
		sort(res.begin(), res.end());
		for (int i = 0; i < m; ++i) {
			printf("%lld%c", res[i], " \n"[i == m - 1]);
		//	assert(res[i] >= QL - 1 && res[i] <= QR + 1);
		}
	}
	return 0;
}
