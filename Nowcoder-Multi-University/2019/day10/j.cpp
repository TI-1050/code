#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 5e3 + 10;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
int n, k;
struct node {
	int w, h;
	node() {}
	node(int w, int h) : w(w), h(h) {}
	void scan() {
		scanf("%d%d", &w, &h);
	}
	bool operator < (const node &other) const {
		return h > other.h; 
	}
}a[N];
ll sum[N], f[2010]; 

struct Line {
	struct node {
		ll a, b, x;
		node() {}
		node(ll a, ll b, ll x) : a(a), b(b), x(x) {}
	}t[N * 3]; int l, r;
	void init() {
		l = 2 * N + 1000, r = l - 1;
	}
	void insert(ll a, ll b) {
		if (r < l) {
			t[--l] = node(a, b, INF);
			return;
		}
		ll x = -INF;
		while (l <= r) {
			node tmp = t[l];
			ll cross = (tmp.b - b) / (a - tmp.a);
			if (cross <= x) break;
			if (cross < t[l].x) {
				x = cross;
				break;
			} else {
				x = t[l].x;
				++l;
			}
		}
		t[--l] = node(a, b, x);
	}
	ll query(ll x) {
		if (r < l) return -INFLL * 2;
		int ql = l, qr = r, pos = -1;
		while (qr - ql >= 0) {
			int mid = (ql + qr) >> 1;
			if (t[mid].x >= x) {
				pos = mid;
				qr = mid - 1;
			} else {
				ql = mid + 1;
			}
		}
		return 1ll * t[pos].a * x + t[pos].b;
	}
}L[2010];

int main() {
	while (scanf("%d%d", &n, &k) != EOF) {
		for (int i = 1; i <= n; ++i) a[i].scan();
		sort(a + 1, a + 1 + n);
		sum[0] = 0; 
		ll tot = 0;
		for (int i = 1; i <= n; ++i) {
			sum[i] = sum[i - 1] + a[i].w;
			tot += 1ll * a[i].w * a[i].h; 
		}
		for (int i = 0; i <= k; ++i) {
			L[i].init();
		}
		for (int i = 1; i <= n; ++i) {
			memset(f, -0x3f, sizeof f); 
			f[1] = 1ll * a[i].h * sum[i];
			ll base = 1ll * a[i].h * sum[i]; 
			for (int j = k; j >= 2; --j) {
				f[j] = max(f[j], base + L[j - 1].query(a[i].h));  
				if (f[j] <= -INFLL) break; 
			}
			for (int j = 1; j <= k; ++j) {
				if (f[j] <= -INFLL) break; 
				L[j].insert(-sum[i], f[j]);
			}	
		}
		printf("%lld\n", tot - f[k]);  
	}
	return 0;
}
