#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 250010
ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a; 
}
struct node {
	int a, b, id; 
	node() {}
	void scan(int _id) {
		scanf("%d%d", &a, &b);  
		id = _id;
	}
	bool operator < (const node &other) const {
		return b * other.a < other.b * a;
	}
}a[N];
int n, p[N], fp[N]; 

struct BIT {
	int n;
	int a[N << 1];
	void init(int _n) {
		n = _n;
		for (int i = 0; i <= n; ++i)
			a[i] = 0;
	}
	void update(int x, int v) {
		for (; x < n; x += x & -x) {
			a[x] += v;
		}
	}
	int query(int x) {
		int res = 0;
		for (; x > 0; x -= x & -x) {
			res += a[x];
		}
		return res;
	}
	int query(int l, int r) {
		if (l > r) return 0;
		return query(r) - query(l - 1);
	}
}A, B;

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n); A.init(n + 10); B.init(n + 10);
		for (int i = 1; i <= n; ++i) a[i].scan(i);
		sort(a + 1, a + 1 + n);
		for (int i = 1; i <= n; ++i) {
			p[a[i].id] = i;
		}
		for (int i = 1; i <= n; ++i) {
			A.update(p[i], a[p[i]].a);
			B.update(p[i], a[p[i]].b); 
			ll x, y, t;
			if (i == 1) {
				x = a[p[1]].a * a[p[1]].b, y = a[p[1]].a + a[p[1]].b;
				t = gcd(x, y); x /= t; y /= t; 
			} else {
				int l = 1, r = n, pos = -1;
				while (r - l >= 0) {
					int mid = (l + r) >> 1;
					if (B.query(1, mid) >= A.query(mid + 1, n)) { 
						r = mid - 1;  
						pos = mid;
					} else {
						l = mid + 1;
					}
				}
				int Sa = A.query(pos + 1, n), Sb = B.query(1, pos - 1); 
			    x = a[pos].a * (Sb - Sa + a[pos].b), y = a[pos].a + a[pos].b;
				t = gcd(x, y); x /= t; y /= t;
				x = y * Sa + x; 	
			}
			printf("%lld/%lld\n", x, y);
		}
	}
	return 0;
}
