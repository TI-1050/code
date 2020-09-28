#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 10010
int n;
ll a[N], m;

struct frac{
    ll x,y;
	frac() {}
	frac(ll x, ll y) : x(x), y(y) {}
	ll gcd(ll a, ll b) {
		return b ? gcd(b, a % b) : a; 
	}
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
	void sqr() {
		*this = (*this) * (*this);
	}
    void print(){
		y == 1 ?
			printf("%lld\n", x) :
			printf("%lld/%lld\n", x, y);
    }
};

int main() {
	while (scanf("%d%lld", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
		sort(a + 1, a + 1 + n, [&](ll x, ll y){
			return x > y;		
		});
		ll k = m;
		frac ans = frac(0, 1);
		for (int i = 1; i <= n; ++i) {
			if (i < n && (1ll * i * (a[i] - a[i + 1])) <= k) {
				k -= 1ll * i * (a[i] - a[i + 1]);  
			} else {
				ans = ans + frac(1ll * (i * a[i] - k) * (i * a[i] - k), 1ll * i * m * m);
				for (int j = i + 1; j <= n; ++j) {
					ans = ans + frac(1ll * a[j] * a[j], m * m); 
				}
				ans.print();
				break;
			}
		}
	}
	return 0;
}
