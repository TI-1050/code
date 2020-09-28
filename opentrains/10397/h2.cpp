#include <bits/stdc++.h>
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0)
void err() { cout << "\033[39;0m" << endl; }
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
using ll = long long;
const int N = 2e5 + 10;
int n, m, q, a[N], d[N]; ll S[N];
struct Hash {
	vector <int> a;
	void init() { a.clear(); }
	void add(int x) { a.push_back(x); }
	void gao() { sort(a.begin(), a.end()); a.erase(unique(a.begin(), a.end()), a.end()); }
	int get(int x) { return lower_bound(a.begin(), a.end(), x) - a.begin() + 1; }
}hs;

int rt[N];
struct SEG {
	struct node {
		int ls, rs, cnt;
		ll tot;
		node() { ls = rs = cnt = tot = 0; }
	}t[N * 50];
	int tot;
	void init() { tot = 0; t[0] = node(); }
	int ls(int id) { return t[id].ls; }
	int rs(int id) { return t[id].rs; }
	int newnode() {
		++tot;
		t[tot] = node();
		return tot;
	} 
	void up(int id) {
		int ls = t[id].ls, rs = t[id].rs;
		t[id].cnt = 0;
		t[id].tot = 0;
		if (ls) t[id].cnt += t[ls].cnt, t[id].tot += t[ls].tot;
		if (rs) t[id].cnt += t[rs].cnt, t[id].tot += t[rs].tot;
	}
	void build(int &rt, int l, int r) {
		rt = newnode();
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(t[rt].ls, l, mid);
		build(t[rt].rs, mid + 1, r);
	}
	void update(int &now, int pre, int l, int r, int pos, int v) {
		now = newnode();
		t[now] = t[pre];
		if (l == r) {
			t[now].cnt += v;
			t[now].tot += 1ll * hs.a[l - 1] * v;
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(t[now].ls, t[pre].ls, l, mid, pos, v);
		else update(t[now].rs, t[pre].rs, mid + 1, r, pos, v);
		up(now);
	}
	ll query(int rt_l, int rt_r, int l, int r, int k) {
		if (!k) return 0;
		if (l == r) return 1ll * k * hs.a[l - 1];
		int mid = (l + r) >> 1;
		if (t[rs(rt_r)].cnt - t[rs(rt_l)].cnt <= k) {
			return t[rs(rt_r)].tot - t[rs(rt_l)].tot + query(t[rt_l].ls, t[rt_r].ls, l, mid, k - t[rs(rt_r)].cnt + t[rs(rt_l)].cnt);
		} else {
			return query(t[rt_l].rs, t[rt_r].rs, mid + 1, r, k);
		}
	}
}seg;

int main() {
	while(scanf("%d", &n) != EOF) {
		S[0] = 0;
		for (int i = 1; i <= n; ++i) scanf("%d", a + i), S[i] = S[i - 1] + 2 * a[i];
		for (int i = 1; i <= n; ++i) scanf("%d", d + i);
		hs.init();
		for (int i = 1; i <= n; ++i) hs.add(d[i] - a[i]);
		hs.gao();
		m = hs.a.size();
		memset(rt, 0, sizeof rt);
		seg.build(rt[0], 1, m);
		for (int i = 1; i <= n; ++i) {
		//	dbg(i, d[i] - a[i], hs.get(d[i] - a[i]));
			seg.update(rt[i], rt[i - 1], 1, m, hs.get(d[i] - a[i]), 1);
		}
	//	dbg(seg.query(rt[0], rt[6], 1, m, 2));
		scanf("%d", &q);
		for (int _q = 1; _q <= q; ++_q) {
			int l, r; scanf("%d%d", &l, &r);
			int thr = (r - l + 1) / 3;
	//		dbg(_q, seg.query(rt[l - 1], rt[r], 1, m, thr * 2), seg.query(rt[l - 1], rt[r], 1, m, thr));
			ll res = S[r] - S[l - 1] + seg.query(rt[l - 1], rt[r], 1, m, thr * 2) + seg.query(rt[l - 1], rt[r], 1, m, thr);
			if (res % 2) printf("%lld.5\n", res / 2);
			else printf("%lld\n", res / 2);
		}
	}
	return 0;
}
