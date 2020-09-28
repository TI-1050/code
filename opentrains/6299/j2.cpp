#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 10, INF = 0x3f3f3f3f;
int n, q, a[N];
set <int> id;

struct BIT {
	ll a[N], b[N];
	void init() { 
		memset(a, 0, sizeof a); 
		memset(b, 0, sizeof b); 
	} 
	void update(int x, ll v) {
		ll delta = v - b[x]; 
		b[x] = v; 
		for (; x < N; x += x & -x)
			a[x] += delta;
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

struct SEG {
	int t[N << 2];
	void init() { memset(t, -0x3f, sizeof t); }
	void update(int id, int l, int r, int pos, int v) {
		if (l == r) {
			t[id] = v;
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(id << 1, l, mid, pos, v);
		else update(id << 1 | 1, mid + 1, r, pos, v);
		t[id] = max(t[id << 1], t[id << 1 | 1]);
	}
	int query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) return t[id];
		int mid = (l + r) >> 1;
		int res = -INF;
		if (ql <= mid) res = max(res, query(id << 1, l, mid, ql, qr));
		if (qr > mid) res = max(res, query(id << 1 | 1, mid + 1, r, ql, qr));
		return res;
	}
}seg;

int main() {
	scanf("%d%d", &n, &q);
	id.clear(); bit.init(); seg.init(); 
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		seg.update(1, 1, n, i, a[i]); 
		if (a[i] > 0) {
			bit.update(2 * i - 1, a[i]);
			auto pre = id.lower_bound(i);
			if (pre != id.begin()) {
				--pre;
				if (a[*pre] == a[i]) {
					int Max = -a[i];
					if (*pre < i - 1) {
						Max = max(Max, seg.query(1, 1, n, *pre + 1, i - 1));
					}
					bit.update(2 * i - 2, Max);
				}
			}
			id.insert(i);	
		}
	}
	int op, x, y;
	while (q--) {
		scanf("%d%d%d", &op, &x, &y);
		if (op == 1) {
			assert(y >= -INF);
			a[x] = y;
			seg.update(1, 1, n, x, a[x]);
			bit.update(2 * x - 1, a[x]);
			if (id.find(x) != id.end()) id.erase(x);
			auto nx = id.upper_bound(x);  
			if (nx != id.begin()) {
				auto pre = nx;
				--pre; 
				int Max = 0;
				if (a[*pre] == a[x]) {
					Max = -a[x];
					if (*pre < x - 1) {
						Max = max(Max, seg.query(1, 1, n, *pre + 1, x - 1));
					} 
				} 
				bit.update(2 * x - 2, Max);	
			}
			if (nx != id.end()) {
				int Max = 0;
				if (a[*nx] == a[x]) {
					Max = -a[x];
					if (x < *nx - 1) {
						Max = max(Max, seg.query(1, 1, n, x + 1, *nx - 1));
					}
				}
				bit.update(2 * (*nx) - 2, Max);
			}
			id.insert(x);
		} else {
			if (id.empty()) {
				printf("%d\n", seg.query(1, 1, n, x, y));
			} else {
				auto pos = id.lower_bound(x);
				if (pos == id.end() || *pos > y) {
					printf("%d\n", seg.query(1, 1, n, x, y));
					continue;
				}
				x = *pos;
				pos = id.upper_bound(y);
				--pos;
				y = *pos;
				printf("%lld\n", bit.query(2 * x - 1, 2 * y - 1)); 
			}
		}
	}
	return 0;
}
