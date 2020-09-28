#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 400010
struct Hash {
	int a[N << 1], cnt;
	void init() { cnt = 0; }
	void add(int x) { a[++cnt] = x; }
	void work() {
		sort(a + 1, a + 1 + cnt);
		cnt = unique(a + 1, a + 1 + cnt) - a - 1;
	}
	int get(int x) { return lower_bound(a + 1, a + 1 + cnt, x) - a; }
}hs;
int n, m;
ll A[2], B[2], C[2], M[2];
ll L[N], R[N], X[N], Y[N];

struct SEG {
	struct node {
		int base; 
		//0表示左端点　1表示右端点
		int num[2];	
		ll sum[2];
		node() {
			num[0] = num[1] = 0;
			sum[0] = sum[1] = 0;
		}
		void add(ll x, int f) { 
			num[f] += x;
			sum[f] += 1ll * x * base;
		}
		node operator + (const node &other) const {
			node res = node();
			for (int i = 0; i < 2; ++i) {
				res.num[i] = num[i] + other.num[i];
				res.sum[i] = sum[i] + other.sum[i];
			}
			return res;
		}
	}t[N << 3], base;
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) {
			t[id].base = hs.a[l] - 1;
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	void update(int id, int l, int r, int pos, ll x, int f) {
		if (l == r) {
			t[id].add(x, f);
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(id << 1, l, mid, pos, x, f);
		else update(id << 1 | 1, mid + 1, r, pos, x, f);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	int query(int id, int l, int r, ll k, node left) {
//	    printf("## %d %d %lld\n", l, r, k)	;
		if (l == r) return hs.a[l];  
		node tmp = left + t[id << 1];
		int mid = (l + r) >> 1;
		ll pl = hs.a[mid];
		ll pr = hs.a[mid + 1] - 1; 
		ll resl = 1ll * pl * tmp.num[0] - tmp.sum[0] - (1ll * pl * tmp.num[1] - tmp.sum[1] - tmp.num[1]);
		ll resr = 1ll * pr * tmp.num[0] - tmp.sum[0] - (1ll * pr * tmp.num[1] - tmp.sum[1] - tmp.num[1]);
		if (resl >= k) {
			return query(id << 1, l, mid, k, left);
		} else if (resr < k) {
			return query(id << 1 | 1, mid + 1, r, k, tmp);
		} else {
			int ql = pl, qr = pr, res = pr;
			while (qr - ql >= 0) {
				int mid = (ql + qr) >> 1;
				ll tot = 1ll * mid * tmp.num[0] - tmp.sum[0] - (1ll * mid * tmp.num[1] - tmp.sum[1] - tmp.num[1]);
				if (tot >= k) {
					res = mid;
					qr = mid - 1;
				} else {
					ql = mid + 1;
				}
			}
			return res;
		}
	}
}seg;  

int main() {
	while (scanf("%d", &n) != EOF) {
		scanf("%lld%lld%lld%lld%lld%lld", X + 1, X + 2, A, B, C, M);
		scanf("%lld%lld%lld%lld%lld%lld", Y + 1, Y + 2, A + 1, B + 1, C + 1, M + 1);
		hs.init();
		L[1] = X[1] + 1; R[1] = Y[1] + 1; if (L[1] > R[1]) swap(L[1], R[1]); hs.add(L[1]); hs.add(R[1]);
		L[2] = X[2] + 1; R[2] = Y[2] + 1; if (L[2] > R[2]) swap(L[2], R[2]); hs.add(L[2]); hs.add(R[2]);
		for (int i = 3; i <= n; ++i) {
			X[i] = (A[0] * X[i - 1] % M[0] + B[0] * X[i - 2] % M[0] + C[0] + M[0]) % M[0];
			Y[i] = (A[1] * Y[i - 1] % M[1] + B[1] * Y[i - 2] % M[1] + C[1] + M[1]) % M[1];
			L[i] = X[i] + 1;
			R[i] = Y[i] + 1;
			if (L[i] > R[i]) swap(L[i], R[i]);
			hs.add(L[i]); hs.add(R[i]);     
		}
	//	for (int i = 1; i <= n; ++i) printf("%lld %lld\n", L[i], R[i]);  
		hs.work();
		m = hs.cnt;
		seg.build(1, 1, m);
		ll tot = 0;
		for (int i = 1; i <= n; ++i) {
			seg.update(1, 1, m, hs.get(L[i]), 1, 0);
			seg.update(1, 1, m, hs.get(R[i]), 1, 1);
			tot += R[i] - L[i] + 1;
			seg.base = SEG::node(); 
			printf("%d\n", seg.query(1, 1, m, (tot + 1) / 2, seg.base));
		}
	}
	return 0;
}
