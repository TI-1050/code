#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 2e5 + 10;
int n, m, sze, K;
struct Hash {
	int a[N], cnt;
	void init() { cnt = 0; }
	void add(int x) { a[++cnt] = x; }
	void gao() {
		sort(a + 1, a + 1 + cnt);
		cnt = unique(a + 1, a + 1 + cnt) - a - 1;
	}
	int get(int x) { return lower_bound(a + 1, a + 1 + cnt, x) - a; }
}hx, hy;
struct qnode {
	int x, y;
	char dir[10];
	qnode() {}
	void scan() {
		scanf("%d%d%s", &x, &y, dir);
		hx.add(x);
		hy.add(y);
	}
}qrr[N];
struct node { int x, y; };
vector <vector<int>> add, del;
vector <vector<node>> qvec;
struct BIT {
	ll a[N];
	int n;
	void init(int _n) { 
		n = _n;
		memset(a, 0, sizeof (a[0]) * (n + 10));  
	};
	void update(int x, int v) {
		for (; x <= n; x += x & -x) {
			a[x] += v;	
		}
	}
	ll query(int x) {
		ll res = 0;
		for (; x > 0; x -= x & -x)
			res += a[x];
		return res;
	}
	ll query(int l, int r) {
		if (l > r) return 0;
		return query(r) - query(l - 1);
	}
}bit;

int main() {
	int _T; cin >> _T;
	while (_T--) {
		scanf("%d%d%d", &n, &m, &K);
		hx.init(); hy.init();
		hx.add(0); hx.add(n); 
		hy.add(0); hy.add(m); 
		for (int i = 1; i <= K; ++i) qrr[i].scan();
		hx.gao(); hy.gao();
		sze = max(hx.cnt, hy.cnt);
		bit.init(sze);
		add.clear(); add.resize(sze + 10);
		del.clear(); del.resize(sze + 10);
		qvec.clear(); qvec.resize(sze + 10); 
		for (int i = 1; i <= K; ++i) {
			qrr[i].x = hx.get(qrr[i].x);
			qrr[i].y = hy.get(qrr[i].y);
			int x = qrr[i].x, y = qrr[i].y, dir = qrr[i].dir[0];
			if (dir == 'L') {
				add[1].push_back(y); 
				del[x].push_back(y); 	
			} else if (dir == 'R') {
				add[x].push_back(y);
				del[hx.cnt].push_back(y);
			} else if (dir == 'U') {
				qvec[x].push_back({y, hy.cnt});
			} else {
				qvec[x].push_back({1, y});
			}
		}
		ll res = 1;
		for (int i = 1; i <= hx.cnt; ++i) {
			for (auto &it : add[i]) {
				bit.update(it, 1);
			}
			for (auto &it : qvec[i]) {
				res += bit.query(it.x, it.y);
			}
			for (auto &it : del[i]) {
				bit.update(it, -1);
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
