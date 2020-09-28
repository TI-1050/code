#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 250010
ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a; 
}
struct frac{
    ll x,y;
	inline void sim() {
		ll g = gcd(abs(x), abs(y));
		x /= g;
		y /= g;
		if (x * y < 0) {
			x = -abs(x);
			y = abs(y);
		} else {
			x = abs(x);
			y = abs(y);
		}
	}
	frac() {}
	frac(ll x, ll y) : x(x), y(y) {sim();}
    frac operator+(const frac &u){
        ll p, q; 
        p = x * u.y + y * u.x;
        q = u.y * y;
        ll d = gcd(p, q);
        p /= d; q /= d;
        return (frac){p, q};
    }
    frac operator-(const frac &u){
        ll p, q;
        p = x * u.y - y * u.x;
        q = u.y * y;
        ll d = gcd(p, q);
        p /= d; q /= d;
        return (frac){p, q};
    }
    frac operator*(const frac &u){
        ll p, q;
        p = u.x * x;
        q = u.y * y;
        ll d = gcd(p, q); 
        p /= d; q /= d;
        return (frac){p, q};
    }
    frac operator/(const frac &u){
        ll p, q;
        p = u.y * x;
        q = u.x * y;
        ll d = gcd(p,q);
        p /= d; q /= d;
        return (frac){p,q};
    }
	bool operator < (const frac &other) const {
		return x * other.y < y * other.x;
	}
	bool operator != (const frac &other) const {
		return x * other.y != y * other.x;
	}
	bool operator <= (const frac &other) const {
		return x * other.y <= y * other.x;
	}
	bool operator >= (const frac &other) const {
		return x * other.y >= y * other.x;
	}
	bool operator == (const frac &other) const {
		return x * other.y == y * other.x;
	}
	void sqr() {
		*this = (*this) * (*this);
	}
    void print(){
		sim();
		if (x * y < 0) putchar('-');
		printf("%lld/%lld\n", abs(x), abs(y));
    }
};
struct node {
	ll a, b; 
	frac x;
	int id; 
	node() {}
	void scan(int _id) {
		scanf("%lld%lld", &a, &b);  
		id = _id;
		x = frac(b, a);
	}
	bool operator < (const node &other) const {
		return b * other.a < other.b * a;
		return x < other.x;
	}
}a[N];
int n, p[N], fp[N]; 
frac res[N];

struct BIT {
	int n;
	ll a[N << 1];
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
	ll query(int x) {
		ll res = 0;
		for (; x > 0; x -= x & -x) {
			res += a[x];
		}
		return res;
	}
	ll query(int l, int r) {
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
			if (i == 0) {
				res[i] = frac(a[p[1]].a * a[p[1]].b, a[p[1]].a + a[p[1]].b);
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
				ll Sa = A.query(pos + 1, n), Sb = B.query(1, pos - 1);
				ll p = 1ll * a[pos].a * (Sb - Sa + a[pos].b), q = a[pos].a + a[pos].b;
				ll t = gcd(p, q); p /= t; q /= t;
				printf("%lld/%lld\n", q * Sa + p, q);
			//	res[i] = frac(1ll * a[pos].a * (Sb - Sa + a[pos].b), a[pos].a + a[pos].b);
			//	res[i] = frac(Sa, 1) * res[i] + frac(res[i].y, 1);
			}
			res[i].print();
		}
	}
	return 0;
}
