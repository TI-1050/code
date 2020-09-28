#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200010
int n, q;
ll a[N];
ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a;
}

struct SEG {
	struct node {
		ll g; bool flag;
		node () {}
		node (ll g) : g(g) {
			flag = g == 1;
		}
		node operator + (const node &other) const {
			node res = node();
			res.g = gcd(g, other.g);
			res.flag = flag & other.flag;
			return res;
		}
	}t[N << 2];
	void build(int id, int l, int r) {
		if (l == r) {
			t[id] = node(a[l]);
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void update(int id, int l, int r, int ql, int qr) {
		if (t[id].flag) {
			return;
		}
		if (l == r) {
			t[id] = node(floor(sqrt(t[id].g)));
			return;
		}
		int mid = (l + r) >> 1;
		if (ql <= mid) update(id << 1, l, mid, ql, qr);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	ll query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) {
			return t[id].g;
		}
		int mid = (l + r) >> 1;
		ll g = 0;
		if (ql <= mid) g = gcd(g, query(id << 1, l, mid, ql, qr));
		if (qr > mid) g = gcd(g, query(id << 1 | 1, mid + 1, r, ql, qr));
		return g;
	}
}seg;

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%lld", a + i);
		}
		seg.build(1, 1, n);
		scanf("%d", &q);
		int op, l, r;
		while (q--) {
			scanf("%d%d%d", &op, &l, &r);
			switch(op) {
				case 0 :
					seg.update(1, 1, n, l, r);
					break;
				case 1 :
					printf("%lld\n", seg.query(1, 1, n, l, r));
					break;
				default :
					assert(0);
			}
		}		
	}
	return 0;
}
