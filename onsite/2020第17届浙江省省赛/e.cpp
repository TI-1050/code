#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define dbg(x...) do { cout << #x << " -> "; err(x); } while (0)
void err() { cout << endl; }
template <class T, class... Ts> 
void err(const T& arg, const Ts&... args) {
	cout << arg << ' '; err(args...);
}

const int N = 1e5 + 10;
int n, m, q;
int a[N], t[N];
ll f[N];

struct Hash {
	int a[N];
	void init() { *a = 0; }
	int size() { return *a; }
	void add(int x) { a[++*a] = x; }
	void gao() {
		sort(a + 1, a + 1 + *a);
		*a = unique(a + 1, a + 1 + *a) - a - 1;
//		cout << *a << endl;
	} 
	int get(int x) {
		return lower_bound(a + 1, a + 1 + *a, x) - a;
	}
}hs;

struct SEG {
	struct node {
		int ls, rs, sum;
		ll S;
		void init() {
			ls = rs = sum = 0;
			S = 0;
		}
	}t[N * 50];
	int tot;
	ll res;
	void init() { tot = 0; t[tot].init(); }
	int newnode() {
		++tot;
		t[tot].init();
		return tot;
	}
	void build(int &id, int l, int r) {
		if (!id) id = newnode();
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(t[id].ls, l, mid);
		build(t[id].rs, mid + 1, r);
	}
	void update(int &rt, int l, int r, int pos, int v) {
		int now = newnode();
		t[now] = t[rt];
		t[now].sum += v;
		t[now].S += 1ll * hs.a[pos] * v;
		if (l == r) {
			rt = now;
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(t[now].ls, l, mid, pos, v);
		else update(t[now].rs, mid + 1, r, pos, v);
		rt = now;
	}
	void query(int l_rt, int r_rt, int l, int r, int k) {
		if (l == r) {
//			dbg(k, hs.a[l], res);
			res += 1ll * k * hs.a[l];
			return;
		}	
		int mid = (l + r) >> 1;
		int lsum = t[t[l_rt].rs].sum, rsum = t[t[r_rt].rs].sum;
		if (rsum - lsum >= k) {
			l_rt = t[l_rt].rs;
			r_rt = t[r_rt].rs;
			query(l_rt, r_rt, mid + 1, r, k);
		} else {
			ll lS = t[t[l_rt].rs].S, rS = t[t[r_rt].rs].S;
			res += rS - lS;
//			dbg(lsum, rsum, lS, rS, res);
			l_rt = t[l_rt].ls;
			r_rt = t[r_rt].ls;
			query(l_rt, r_rt, l, mid, k - (rsum - lsum));
		}
	}
}seg;

int main() {
	f[0] = 0;
	for (int i = 1; i < N; ++i) {
		f[i] = f[i - 1] + 1ll * i * i;
	}
	int _T; scanf("%d", &_T);
	while(_T--) {
		scanf("%d", &n);
		hs.init();
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			hs.add(a[i]);	
		}
		hs.gao();
		m = hs.size();
//		dbg(m);
//		for (int i = 1; i <= m; ++i) dbg(i, hs.a[i]);
		seg.init();
		t[0] = 0;
		seg.build(t[0], 1, m);
		for (int i = 1; i <= n; ++i) {
			t[i] = t[i - 1];
//			dbg(i, hs.get(a[i]));
			seg.update(t[i], 1, m, hs.get(a[i]), 1);
		}
		scanf("%d", &q);
		for (int i = 1, l, r, k; i <= q; ++i) {
			scanf("%d%d%d", &l, &r, &k);
			ll res = f[r - l + 1];
			seg.res = 0;
			seg.query(t[l - 1], t[r], 1, m, k);
			res += seg.res;
			printf("%lld\n", res);
		}
	}
	return 0;
}
