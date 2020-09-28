#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
#define INFLL 0x3f3f3f3f3f3f3f3f
int n, m;
struct node {
	ll a, b;
	node() {}
	void scan() {
		scanf("%lld%lld", &a, &b);
		b += a;
	}
	bool operator < (const node &other) const {
		return b < other.b;
	}
}a[N];
ll b[N];

struct SEG {
	struct node {
		ll cnt, sum;
		node() {
			cnt = 0;
			sum = 0; 
		}
		node (ll cnt, ll sum) : cnt(cnt), sum(sum) {}
		node operator + (const node &other) const {
			node res = node();
			res.cnt = cnt + other.cnt; 
			res.sum = sum + other.sum;
			return res;
		}
	}t[N << 2], res;
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) {
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	void update(int id, int l, int r, int pos) {
		if (l == r) {
			++t[id].cnt;
			t[id].sum += b[l];
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(id << 1, l, mid, pos);
		else update(id << 1 | 1, mid + 1, r, pos);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void query(int id, int l, int r, ll need) {
		if (l == r) {
			need -= res.sum; 
			if (need > 0) {
				res = res + node(need / b[l] + ((need % b[l]) != 0), 0);
			}
			return; 
		}
		int mid = (l + r) >> 1;
		node tmp = res; 
		tmp = t[id << 1 | 1] + tmp;
		if (tmp.sum >= need) {
			query(id << 1 | 1, mid + 1, r, need);
		} else {
			res = tmp; 
			query(id << 1, l, mid, need);
		}
	}
}seg;

int main() {
	while (scanf("%d", &n) != EOF) { 
		for (int i = 1; i <= n; ++i) {
			a[i].scan();
		}
		sort(a + 1, a + 1 + n);
		for (int i = 1; i <= n; ++i) {
			b[i] = a[i].a; 
		}
		sort(b + 1, b + 1 + n);
		m = unique(b + 1, b + 1 + n) - b - 1;
		for (int i = 1; i <= n; ++i) {
			a[i].a = lower_bound(b + 1, b + 1 + m, a[i].a) - b;
		}
		seg.build(1, 1, m);
		ll res = INFLL;
		for (int i = 1; i <= n; ++i) {
			if (seg.t[1].sum >= a[i].b - b[a[i].a]) {
				seg.res = SEG::node();
				seg.query(1, 1, m, a[i].b - b[a[i].a]);
				res = min(res, seg.res.cnt + 1);
			} 
			seg.update(1, 1, m, a[i].a);
		}
		if (res == INFLL) res = -1;
		printf("%lld\n", res);
	}
	return 0;
}
