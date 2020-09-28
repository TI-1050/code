#include <bits/stdc++.h>
using namespace std;

using pII = pair <int, int>;
#define fi first
#define se second
const int N = 3e5 + 10;
const int INF = 0x3f3f3f3f;
int n, l, r, a[N], S[N], f[N];

bool cmp (const pII &x, const pII &y) {
	if (x.fi != y.fi) return x.fi < y.fi;
	return x.se > y.se;
}
struct SEG {
	struct node {
		pII a[2];
		node() {
			a[0] = a[1] = pII(-INF, INF);
		}
		node operator + (const node &other) const {
			node res = node();
			res.a[0] = max(a[0], other.a[0], cmp);
			if (a[0].fi != res.a[0].fi) res.a[1] = max(res.a[1], a[0], cmp);
			if (a[1].fi != res.a[0].fi) res.a[1] = max(res.a[1], a[1], cmp);
			if (other.a[0].fi != res.a[0].fi) res.a[1] = max(res.a[1], other.a[0], cmp);
			if (other.a[1].fi != res.a[0].fi) res.a[1] = max(res.a[1], other.a[1], cmp);
			return res;
		}
	}t[N << 2], res;
	void init() { for (int i = 0; i < N; ++i) t[i] = node(); }
	void update(int id, int l, int r, int pos, pII v) {
		if (l == r) {
			t[id].a[0] = v;
			t[id].a[1] = pII(-INF, INF);
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(id << 1, l, mid, pos, v);
		else update(id << 1 | 1, mid + 1, r, pos, v);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) {
			res = res + t[id];
			return;
		}
		int mid = (l + r) >> 1;
		if (ql <= mid) query(id << 1, l, mid, ql, qr);
		if (qr > mid) query(id << 1 | 1, mid + 1, r, ql, qr);
	}
}seg;

inline int get(int x) {
	if (!x) return 0;
	return x > 0 ? 1 : -1;
}

int main() {
//	cout << INF << endl;
	while (scanf("%d%d%d", &n, &l, &r) != EOF) {
		for (int i = 1; i <= n; ++i) f[i] = -INF;
		seg.init();
		seg.update(1, 0, n, 0, pII(0, 0));
		f[0] = 0;
		S[0] = 0;
		for (int i = 1; i <= n; ++i) { 
			scanf("%d", a + i);
			S[i] = S[i - 1] + a[i];
		}
		for (int i = 1; i <= n; ++i) {
			int L = max(i - r, 0), R = i - l;
			if (L <= R) {
				seg.res = SEG::node();
				seg.query(1, 0, n, L, R); 
				if (seg.res.a[0].fi != -INF) { 
					pII t = seg.res.a[0];
					f[i] = max(f[i], t.fi + get(S[i] - t.se));
					t = seg.res.a[1]; 
					f[i] = max(f[i], t.fi + get(S[i] - t.se)); 
				}
			} 
			seg.update(1, 0, n, i, pII(f[i], S[i]));
		//	cout << i << " " << f[i] << endl;
		}
		if (f[n] <= -INF) puts("Impossible");  
		else printf("%d\n", f[n]); 
	}
	return 0;
}
