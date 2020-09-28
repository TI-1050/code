#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define db double
#define pli pair <ll, int>
#define fi first
#define se second
const int N = 2e5 + 10;
const int m = 1e5;
const db eps = 1e-8;
int n, q, h[N];

struct SEG {
	struct node {
		int num, ls, rs;
		ll sum;
		node() {
			ls = rs = 0;
			num = sum = 0;
		}
		node operator + (const node &other) const {
			node res = node();
			res.num = num + other.num;
			res.sum = sum + other.sum;
			return res;
		}
	}t[N * 50];
	int rt[N], cnt;
	void init() { cnt = 0; }
	void build(int &id, int l, int r) {
		id = ++cnt;
		t[id] = node();
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(t[id].ls, l, mid);
		build(t[id].rs, mid + 1, r);
	}
	void up(int id) {
		int ls = t[id].ls, rs = t[id].rs;
		t[id].num = t[id].sum = 0;
		if (ls) {
			t[id].num += t[ls].num;
			t[id].sum += t[ls].sum;
		}
		if (rs) {
			t[id].num += t[rs].num;
			t[id].sum += t[rs].sum;
		}
	}
	void update(int &now, int pre, int l, int r, int pos) {
		now = ++cnt;
		t[now] = t[pre];
		if (l == r) {
			++t[now].num;
			t[now].sum += l;
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(t[now].ls, t[pre].ls, l, mid, pos);
		else update(t[now].rs, t[pre].rs, mid + 1, r, pos);
		up(now);
	}
	node query(int id, int l, int r, int ql, int qr) {
		if (!id) return node();
		if (l >= ql && r <= qr) return t[id];
		int mid = (l + r) >> 1;
		node res = node();
		if (ql <= mid) res = res + query(t[id].ls, l, mid, ql, qr);
		if (qr > mid) res = res + query(t[id].rs, mid + 1, r, ql, qr);
		return res;
	}
	pli query(int tl, int tr, int ql, int qr) {
		node l = query(rt[tl], 1, m, ql, qr);
		node r = query(rt[tr], 1, m, ql, qr);
		return pli(r.sum - l.sum, r.num - l.num);
	}
}seg;

int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", h + i);
		seg.init();
		seg.build(seg.rt[0], 1, m);
		for (int i = 1; i <= n; ++i)
			seg.update(seg.rt[i], seg.rt[i - 1], 1, m, h[i]);
		for (int _q = 1, L, R, x, y; _q <= q; ++_q) {
			scanf("%d%d%d%d", &L, &R, &x, &y);
			pli tot = seg.query(L - 1, R, 1, m);
			db ave = tot.fi * 1.0 / y;
			db need = ave * x; 
			db l = 0, r = 1e5, res = 0;
			while (r - l > eps) {
				db mid = (l + r) / 2;
			//	cout << l << " " << r << mid << endl;
				pli now = seg.query(L - 1, R, ceil(mid), m);
				db cut = now.fi - 1.0 * now.se * mid;
				if (cut >= need) {
					res = mid;
					l = mid;
				} else {
					r = mid;
				}
			}
			printf("%.10f\n", res);
		}
	}
	return 0;
}
