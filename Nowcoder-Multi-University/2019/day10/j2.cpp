#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 5e3 + 10;
const int INF = 0x3f3f3f3f;
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
ll sum[N], f[N]; 

struct Line {
	struct node {
		ll a, b, x;
		node() {}
		node(ll a, ll b, ll x) : a(a), b(b), x(x) {}
	}t[N * 3]; int l, r, pos;
	void init() {
		l = N * 3 - 10, r = l - 1;
		pos = r; 
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
		while (l < pos && t[pos - 1].x >= x) --pos;
		return 1ll * t[pos].a * x + t[pos].b;
	}
}L;

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
		L.init();
		for (int i = 1; i <= n; ++i) {
			f[i] = 1ll * a[i].h * sum[i];
			L.insert(-sum[i], f[i]);
		}
		for (int o = 2; o <= k; ++o) {
			for (int i = 1; i <= n; ++i) {
				ll base = a[i].h * sum[i];
			    f[i] = base + L.query(a[i].h);	
			}
			L.init();
			for (int i = 1; i <= n; ++i) {
				L.insert(-sum[i], f[i]);
			}
		}
		printf("%lld\n", tot - f[n]);  
	}
	return 0;
}
