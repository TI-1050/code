#include <bits/stdc++.h>
using namespace std;

#define pii pair <int, int>
#define fi first
#define se second
#define ll long long
const int N = 4e5 + 10;
struct Hash {
	int a[N], cnt;
	void init() { cnt = 0; }
	void add(int x) { a[++cnt] = x; }
	void gao() {
		sort(a + 1, a + 1 + cnt);
		cnt = unique(a + 1, a + 1 + cnt) - a - 1;
	}
	int get(int x) {
		return lower_bound(a + 1, a + 1 + cnt, x) - a; 
	}
}hx, hy;
struct node {
	int x[2], y[2];
	node() {}
	void scan() {
		scanf("%d%d%d%d", x, y, x + 1, y + 1);
		hx.add(x[0]); hx.add(x[1]);
		hy.add(y[0]); hy.add(y[1]); 
	}
}a[N];
int n;
vector <vector<pii>> add, del;

struct BIT {
	int a[N];
	void init() {
		memset(a, 0, sizeof a);
	}
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

void out(int x) { cout << x << "\n"; }

void solve() {
	bit.init();
	for (int i = 1; i <= hx.cnt; ++i) {
		for (auto it : add[i]) {
			if (bit.query(it.fi, it.se)) {
				out(1);
				return;
			}
			bit.update(it.fi, 1);
			bit.update(it.se, 1);
		}
		for (auto it : del[i]) {
			bit.update(it.fi, -1);
			bit.update(it.se, -1);
			if (bit.query(it.fi, it.se)) {
				out(1);
				return;
			}
		}
	}
	out(0);
}

int main() {
	while (scanf("%d", &n) != EOF) {
		hx.init(); hy.init();
		for (int i = 1; i <= n; ++i) a[i].scan();
		hx.gao(); hy.gao();
		add.clear(); add.resize(hx.cnt + 10);
		del.clear(); del.resize(hx.cnt + 10); 
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < 2; ++j) {
				a[i].x[j] = hx.get(a[i].x[j]);
				a[i].y[j] = hy.get(a[i].y[j]); 
			}
			add[a[i].x[0]].push_back(pii(a[i].y[0], a[i].y[1]));
			del[a[i].x[1]].push_back(pii(a[i].y[0], a[i].y[1]));
		}
		solve();
	}
	return 0;
}
