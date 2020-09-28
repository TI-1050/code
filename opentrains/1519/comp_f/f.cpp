#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
int n, m, q, ans[N]; 
struct Hash {
	int a[N];
	void init() { memset(a, 0, sizeof a); }
	void add(int x) { a[++*a] = x; }
	void gao() { sort(a + 1, a + 1 + *a); *a = unique(a + 1, a + 1 + *a) - a - 1; } 
	int get(int x) { return lower_bound(a + 1, a + 1 + *a, x) - a; }
}hy;
struct qnode { 
	int op, id, x, y[2];
	qnode() {}
	qnode(int op, int id, int x, int y1, int y2) : op(op), id(id), x(x) {
		y[0] = y1; y[1] = y2;
	}
	bool operator < (const qnode &other) const {
		if (x != other.x) return x < other.x;
		return abs(op) < abs(other.op);
	}
}qrr[N];
struct BIT {
	int a[N];
	void init() { memset(a, 0, sizeof a); }
	void update(int x, int v) {
		for (; x < N; x += x & -x)
			a[x] += v;
	}
	int query(int x) {
		int res = 0;
		for (; x > 0; x -= x & -x)
			res += a[x];
		return res;
	}
	int query(int l, int r) {
		if (l > r) return 0;
		return query(r) - query(l - 1);
	}
}bit;

int main() {
	while (scanf("%d", &n) != EOF) {
		m = 0;
		memset(ans, 0, sizeof ans);
		for (int i = 1, x, y; i <= n; ++i) {
			scanf("%d%d", &x, &y);
			qrr[++m] = qnode(0, 0, x + y, x - y, x - y); 							
		}
		scanf("%d", &q);
		for (int i = 1, a, b, x, y, d; i <= q; ++i) {
			scanf("%d%d%d", &a, &b, &d);
			x = a + b, y = a - b;
			qrr[++m] = qnode(-1, i, x - d - 1, y - d, y + d);
			qrr[++m] = qnode(1, i, x + d, y - d, y + d);
		}
		hy.init();
		for (int i = 1; i <= m; ++i) hy.add(qrr[i].y[0]), hy.add(qrr[i].y[1]);
		hy.gao();
		for (int i = 1; i <= m; ++i) for (int j = 0; j < 2; ++j) qrr[i].y[j] = hy.get(qrr[i].y[j]);
		bit.init();
		sort(qrr + 1, qrr + 1 + m);
		for (int i = 1; i <= m; ++i) {
			if (qrr[i].op == 0) {
				bit.update(qrr[i].y[0], 1);
			} else {
				ans[qrr[i].id] += qrr[i].op * bit.query(qrr[i].y[0], qrr[i].y[1]);
			}
		}
		for (int i = 1; i <= q; ++i)
			printf("%d\n", ans[i]);
	}
	return 0;
}
