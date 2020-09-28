#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int N = 2e5 + 10;
const ll M = 1e6;
int n, m; ll mod, lst;

//6 digits
ll getdb() {
	char s[30];
	scanf("%s", s);
	ll a = 0, b = 0;
	int i = 0, j = 0;
	for (; s[i]; ++i) {
		if (s[i] == '.') break;
		a = a * 10 + s[i] - '0';
	}
	int len = strlen(s);
	for (++i, j = 0; j < 6; ++i, ++j) {
		if (i >= len) b = b * 10;
		else b = b * 10 + s[i] - '0';
	}
	return a * M + b;
}

using pLL = pair <ll, ll>;
#define fi first
#define se second
struct SEG {
	struct node {
		int ls, rs;
		// fi sum[0] se sum[1]
		pLL sum, lazy;
		node() {
			ls = rs = 0;
			sum = lazy = pLL(0, 0);
		}
		void up(pLL x) {
			sum.fi += x.fi, sum.se += x.se;
			lazy.fi += x.fi, lazy.se += x.se;
		}
	}t[N * 33];
	int tot, rt;
	inline void init() { tot = 0; rt = newnode(); }
	inline int newnode() {
	//	assert(tot < N * 33);
		++tot;
		t[tot] = node();
		return tot;
	}
	void down(int id) {
		pLL &lazy = t[id].lazy;
		int &ls = t[id].ls, &rs = t[id].rs;
		if (!ls) ls = newnode();
		if (!rs) rs = newnode();
		t[ls].up(lazy);
		t[rs].up(lazy);
		lazy = pLL(0, 0);
	}
	void update(int &id, ll l, ll r, ll ql, ll qr, pLL v) {
		if (!id) id = newnode();
		if (l >= ql && r <= qr) {
			t[id].up(v);
			return;
		}
		ll mid = (l + r) >> 1;
		down(id);
		if (ql <= mid) update(t[id].ls, l, mid, ql, qr, v);
		if (qr > mid) update(t[id].rs, mid + 1, r, ql, qr, v);
	}
	pLL query(int id, ll l, ll r, ll pos) {
		if (!id) return pLL(0, 0);
		if (l == r) return t[id].sum;
		ll mid = (l + r) >> 1;
		down(id);
		if (pos <= mid) return query(t[id].ls, l, mid, pos);
		else return query(t[id].rs, mid + 1, r, pos);
	}
}seg;

int main() {
	while (scanf("%d", &n) != EOF) {
		mod = 1ll * n * M;
		lst = 0;
		m = 0;
		seg.init();
		int op;
		for (int i = 1; i <= n * 2; ++i) {
			scanf("%d", &op);
			if (op == 0) {
				ll C = (getdb() + lst) % mod, R = getdb();
				ll l = max(0ll, C - R), r = min(mod, C + R);
				seg.update(seg.rt, 0, mod, l, r, pLL(1ll * m, 1));
				++m;
			} else {
				ll x = (getdb() + lst) % mod;
				pLL tmp = seg.query(seg.rt, 0, mod, x);
				lst = (lst + tmp.fi * M % mod) % mod;
				printf("%lld\n", tmp.se);
			}
		}
	}
	return 0;
}
