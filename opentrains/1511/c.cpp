#include <bits/stdc++.h>
using namespace std;

inline void chmax(int &x, int y) { if (x < y) x = y; }
const int N = 2e5 + 10;
int n, f[N];
struct node {
	int x, y, id;
	bool isleft;
	node() {}
	node(int x, int y, int id) : x(x), y(y), id(id) { isleft = false; } 
	bool operator < (const node &other) const {
		if (x == other.x) return y > other.y;
		return x < other.x;
	}
}a[N], ta[N];

struct Hash {
	int a[N << 1];
	int tot;

	void Init() {
		tot = 0;
	}

	void add(int x) {
		a[++tot] = x;
	}

	void gao() {
		sort(a + 1, a + 1 + tot);
		tot = unique(a + 1, a + 1 + tot) - a - 1;
	}

	int get(int x) {
		return lower_bound(a + 1, a + 1 + tot, x) - a;
	}
}ha;

struct BIT {
	int a[N];
	void update(int x, int v) {
		for (; x < N; x += x & -x)
			a[x] = max(a[x], v);
	}
	int query(int x) {
		int res = 0;
		for (; x > 0; x -= x & -x)
			res = max(res, a[x]);
		return res;
	}
	void clear(int x) {
		for (; x < N; x += x & -x)
			a[x] = 0;
	}
}bit;

void gao(int l, int r) {
	if (l == r) {
		chmax(f[a[l].id], 1);
		return;
	}
	int mid = (l + r) >> 1;
	gao(l, mid); 
	for (int i = l; i <= r; ++i) {
		ta[i] = a[i];
		if (i <= mid) ta[i].isleft = true;
		else ta[i].isleft = false;
	}	
	sort(ta + l, ta + r + 1);
	for (int i = l; i <= r; ++i) {
		if (ta[i].isleft) bit.update(ta[i].y, f[ta[i].id]);
		else chmax(f[ta[i].id], bit.query(ta[i].y - 1) + 1);
	}
	for (int i = l; i <= r; ++i)
		if (ta[i].isleft)
			bit.clear(ta[i].y);
	gao(mid + 1, r);
}


int main() {
	int _T; cin >> _T;
	while (_T--) {
		scanf("%d", &n);
		memset(f, 0, sizeof (f[0]) * (n + 10));
		ha.Init();
		for (int i = 1, x; i <= n; ++i) {
			scanf("%d", &x);
			a[i] = node(x, 0, i);	
		}
		for (int i = 1, y; i <= n; ++i) {
			scanf("%d", &y);
			ha.add(y);
			a[i].y = y;
		}
		ha.gao();
		for (int i = 1; i <= n; ++i) {
			a[i].y = ha.get(a[i].y);
		}
		gao(1, n);
		printf("%d\n", *max_element(f + 1, f + 1 + n));
	}
	return 0;
}
