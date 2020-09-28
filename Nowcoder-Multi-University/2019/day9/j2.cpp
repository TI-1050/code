#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e6 + 10;

struct node {
	int l, r, mid;

	void input() {
		scanf("%d %d", &l, &r);
		l <<= 1, r <<= 1;
		mid = (l + r) >> 1;
	}
}a[N];

struct Hash {
	int a[N], cnt;

	void Init() {
		cnt = 0;
	}

	void add(int x) {
		a[++cnt] = x;
	}

	void gao() {
		sort(a + 1, a + 1 + cnt);
		cnt = unique(a + 1, a + 1 + cnt) - a - 1;	
	}

	int get(int x) {
		return lower_bound(a + 1, a + 1 + cnt, x) - a;
	}
}hs;

int n;
vector< vector<node> >l, r, mid;

int main() {
	while (~scanf("%d", &n)) {
		hs.Init();
		for (int i = 1; i <= n; ++i) {
			a[i].input();
			hs.add(a[i].l);
			hs.add(a[i].r);
			hs.add(a[i].mid);
		}
		hs.gao();
		l.clear(); l.resize(hs.cnt + 1);
		r.clear(); r.resize(hs.cnt + 1);
		mid.clear(); mid.resize(hs.cnt + 1);
		for (int i = 1; i <= n; ++i) {
			l[hs.get(a[i].l)].push_back(a[i]);
			r[hs.get(a[i].r)].push_back(a[i]);
			mid[hs.get(a[i].mid)].push_back(a[i]);
		}
		ll res = 0;
		ll up_num = 0, sum_up = 0, down_num = 0, sum_down = 0;
		for (int i = 1; i <= hs.cnt; ++i) {
			int x = hs.a[i];
			for (auto it : l[i]) {
				down_num++;
				sum_down += it.l;
			}
			for (auto it : r[i]) {
				up_num--;
				sum_up -= it.r;
			}
			for (auto it : mid[i]) {
				down_num--;
				sum_down -= it.l;
				up_num++;
				sum_up += it.r;
			}
			res = max(res, (down_num * x - sum_down + sum_up - up_num * x) * 2ll);
		}
		printf("%lld\n", res / 2);
	}
	return 0;
}
