#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
const int INF = 0x3f3f3f3f;
int n, a[N], f[N], res;

struct SEG {
	int t[N << 2];
	void init() { memset(t, 0x3f, sizeof t); }
	void update(int id, int l, int r, int pos, int v) {
		if (l == r) {
			t[id] = v;
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(id << 1, l, mid, pos, v);
		else update(id << 1 | 1, mid + 1, r, pos, v);
		t[id] = min(t[id << 1], t[id << 1 | 1]);
	}
	int query(int id, int l, int r, int ql, int qr) {
		if (ql > qr) return INF;
		if (l >= ql && r <= qr) return t[id];
		int mid = (l + r) >> 1;
		int res = INF;
		if (ql <= mid) res = min(res, query(id << 1, l, mid, ql, qr));
		if (qr > mid) res = min(res, query(id << 1 | 1, mid + 1, r, ql, qr));
		return res;
	}
}seg;

int gao() {
	seg.init();
	memset(f, 0x3f, sizeof f);
	f[n] = 0;
	seg.update(1, 1, n, n, 0);
	for (int i = n - 1; i >= 1; --i) {
		int l = i + 1, r = min(i + a[i], n);
		f[i] = min(f[i], seg.query(1, 1, n, l, r) + 1);
		seg.update(1, 1, n, i, f[i]);
	}
	int res = f[1];
	for (int i = 2; i <= n; ++i) {
		int l = max(1, i - a[i]), r = i - 1;
		f[i] = min(f[i], seg.query(1, 1, n, l, r) + 1);
		seg.update(1, 1, n, i, f[i]);
		res = max(res, f[i]);
	}
	return res;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		res = gao();
		reverse(a + 1, a + 1 + n);
		res = max(res, gao());
		printf("%d\n", res);
	}
	return 0;
}
