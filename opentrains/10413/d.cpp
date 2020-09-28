#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pII = pair <int, int>;
#define fi first
#define se second
const int N = 2e5 + 10;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
int n, t[N], a[N], pre[N], sta[N]; ll f[N]; 

struct SEG {
	struct node {
		ll f, Min, lazy; 
		node() { f = Min = lazy = INFLL; }
		void up(ll x) {
			Min = f + x;
			lazy = x;
		}
		node operator + (const node &other) const {
			node res = node();
			res.f = min(f, other.f);
			res.Min = min(Min, other.Min);
			return res;
		}
	}t[N << 2];
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	void down(int id) {
		ll &lazy = t[id].lazy; 
		if (lazy == INFLL) return;
		t[id << 1].up(lazy);
		t[id << 1 | 1].up(lazy); 
		lazy = INFLL;
	}
	void update(int id, int l, int r, int ql, int qr, ll v) {
		if (ql > qr) return;
		if (l >= ql && r <= qr) {
			t[id].up(v);
			return;
		}
		int mid = (l + r) >> 1;
		down(id);
		if (ql <= mid) update(id << 1, l, mid, ql, qr, v);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr, v);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void set(int id, int l, int r, int pos, ll f) {
		if (l == r) {
			t[id].Min -= t[id].f;
			t[id].f = f;
			t[id].Min += t[id].f;
			return;
		}
		int mid = (l + r) >> 1;
		down(id);
		if (pos <= mid) set(id << 1, l, mid, pos, f);
		else set(id << 1 | 1, mid + 1, r, pos, f);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	ll query(int id, int l, int r, int ql, int qr) {
		if (ql > qr) return INFLL;
		if (l >= ql && r <= qr) return t[id].Min; 
		int mid = (l + r) >> 1;
		down(id);
		ll res = INFLL; 
		if (ql <= mid) res = min(res, query(id << 1, l, mid, ql, qr));
		if (qr > mid) res = min(res, query(id << 1 | 1, mid + 1, r, ql, qr));
		return res;
	}
}seg;

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d%d", t + i, a + i);
		*sta = 0;
		for (int i = 1; i <= n; ++i) {
			int l = 1, r = *sta, res = 0;
			while (r - l >= 0) {
				int mid = (l + r) >> 1;
				if (a[sta[mid]] >= a[i]) {
					l = mid + 1; 
					res = mid; 
				} else {
					r = mid - 1; 
				}
			}
			if (res) pre[i] = sta[res] - 1; 
			else pre[i] = -1;   
			while (*sta && a[i] >= a[sta[*sta]]) --*sta;
			sta[++*sta] = i; 
		}
	//	for (int i = 1; i <= n; ++i) cout << i << " " << pre[i] << endl;
		seg.build(1, 0, n); seg.set(1, 0, n, 0, 0); seg.update(1, 0, n, 0, 0, a[1] * 2); 
		int bored = -1; f[0] = 0;
		for (int i = 1; i <= n; ++i) {
			while (bored < i - 1 && f[bored + 1] <= t[i]) {  
				++bored;
				seg.set(1, 0, n, bored, 0);
			}
			seg.update(1, 0, n, pre[i] + 1, i - 1, a[i] * 2); 
		 //  cout << bored << " " << seg.query(1, 0, n, 0, bored) << endl; 	
			f[i] = min(seg.query(1, 0, n, 0, bored) + t[i], seg.query(1, 0, n, bored + 1, i - 1));  
		   //	cout << i << " " << seg.query(1, 0, n, 0, bored) + t[i] << " " << seg.query(1, 0, n, bored + 1, i - 1) << endl; 	
			seg.set(1, 0, n, i, f[i]); seg.update(1, 0, n, i, i, a[i + 1] * 2);   
		}
		printf("%lld\n", f[n]);
	}
	return 0;
} 
