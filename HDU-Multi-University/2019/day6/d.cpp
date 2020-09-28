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
	int a, b; 
	frac x;
	int pre, nx, id; 
	node() {}
	void scan(int _id) {
		scanf("%d%d", &a, &b);  
		nx = pre = -1;
		id = _id;
		x = frac(a, a + b);
	}
	bool operator < (const node &other) const {
		return x < other.x;
	}
}a[N];
int n, p[N]; 
frac res[N];
int t; frac x;
ll sum[2];

inline void upl(int x, int y) {
	a[x].nx = y;
}

inline void upr(int x, int y) {
	a[x].pre = y;
}

inline int getnx(int x) {
	return a[x].nx;
}

inline int getpre(int x) {
	return a[x].pre;
}

inline bool ok(frac x) {
	return x >= frac(0, 1) && x <= frac(1, 1);
}

void del(int now) {	
	upl(a[now].pre, a[now].nx);
	upr(a[now].nx, a[now].pre);
	if (now == t) {
		int it = getnx(t);
		while (it >= 1 && it <= n) {
			sum[1] -= a[it].b;
			frac tmp = frac(sum[1] - sum[0] + a[it].b, a[it].a + a[it].b);
			if (ok(tmp)) {
				t = it;
				x = tmp;
				return;
			} else {
				sum[0] += a[it].a;
			}
			it = getnx(it);
		}	
	} else if (now < t) {
		sum[1] -= a[now].b;
		int it = t;
		while (it >= 1 && it <= n) {
			sum[1] -= a[it].b;
			frac tmp = frac(sum[1] - sum[0] + a[it].b, a[it].a + a[it].b);
			if (ok(tmp)) {
				t = it;
				x = tmp;
				return;
			} else {
				sum[0] += a[it].a;
			}
			it = getnx(it);
		}
	} else {
		sum[0] -= a[now].a;
		int it = t;
		while (it >= 1 && it <= n) {
			sum[0] -= a[it].a;
			frac tmp = frac(sum[1] - sum[0] + a[it].b, a[it].a + a[it].b);
			if (ok(tmp)) {
				t = it;
				x = tmp;
				return;
			} else {
				sum[1] += a[it].b;
			}
			it = getpre(it);
		}
	}
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) a[i].scan(i);
		sort(a + 1, a + 1 + n);
		for (int i = 1; i <= n; ++i) {
			p[a[i].id] = i;
			a[i].pre = i - 1;
			a[i].nx = i + 1;  
		}
		t = -1; 
		sum[0] = sum[1] = 0;
		for (int i = 1; i <= n; ++i) {
			sum[1] += a[i].b;
		}
		for (int i = 1; i <= n; ++i) {
			sum[1] -= a[i].b;
			frac tmp = frac(sum[1] - sum[0] + a[i].b, a[i].a + a[i].b);
			if (ok(tmp)) {
				t = i;
				x = tmp;
				break;
			} else {
				sum[0] += a[i].a;
			}
		}
		for (int i = n; i > 1; --i) {
			res[i] = x * frac(a[t].a, 1) + frac(sum[0], 1);
			if (i <= 2) {
				ll A = a[p[1]].a, B = a[p[1]].b;
				res[1] = frac(B, A + B);
				break;
			} 
			del(p[i]);
		}
		for (int i = 1; i <= n; ++i)
			res[i].print();
	}
	return 0;
}
