#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a; 
}
struct frac{
    ll x,y;
	void sim() {
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
		printf("%lld/%lld", abs(x), abs(y));
    }
};

const int N = 2e5 + 10;
int n;
ll C;
struct node {
	int a, b;
	frac x;
	void scan() {
		scanf("%d%d", &a, &b);
		x = frac(-b, a); 
	}
	bool operator < (const node &other) const {
		return x < other.x;
	}
}a[N];
frac res[N << 1]; int cnt = 0; 

void solve() {
	cnt = 0;
	ll suma[2] = {0, 0}, sumb[2] = {0, 0};
	for (int i = 1; i <= n; ++i) {
		suma[1] += a[i].a;
		sumb[1] += a[i].b;
	}
	for (int i = 1, j; i < n; i = j + 1) {
		for (j = i; j < n; ++j) {
			if (a[i].x != a[j + 1].x) break;
		}
		j = min(j, n - 1);
		for (int k = i; k <= j; ++k) {
			suma[1] -= a[k].a;
			sumb[1] -= a[k].b;
			suma[0] += a[k].a;
			sumb[0] += a[k].b;
		}
		if (suma[0] - suma[1] == 0 && sumb[0] - sumb[1] == C) {
			puts("-1");
			return;
		}  
		if (suma[1] == suma[0]) continue;
		frac x = frac(C - sumb[0] + sumb[1], suma[0] - suma[1]);
		if (x >= a[i].x) {
			if (j + 1 < n) {
				if (x < a[j + 1].x) {
					res[++cnt] = x;
				}
			} else {
				res[++cnt] = x;
			}
		}
	}
	sort(res + 1, res + 1 + cnt);
	cnt = unique(res + 1, res + 1 + cnt) - res - 1;
	printf("%d", cnt);
	for (int i = 1; i <= cnt; ++i) {
		putchar(' ');
		res[i].print();
	}
	puts("");
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%lld", &n, &C);
		for (int i = 1; i <= n; ++i) a[i].scan();
		++n; a[n].a = a[n].b = 0; a[n].x = frac(-2e9, 1);
		sort(a + 1, a + 1 + n);
		++n; a[n].a = a[n].b = 0; a[n].x = frac(2e9, 1);
		solve();	
	}
	return 0;	
}
