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
    frac operator+(const frac &u){
        ll p,q;
        p=x*u.y+y*u.x;
        q=u.y*y;
        ll d=__gcd(p,q);
        p/=d; q/=d;
        return (frac){p,q};
    }
    frac operator-(const frac &u){
        ll p,q;
        p=x*u.y-y*u.x;
        q=u.y*y;
        ll d=__gcd(p,q);
        p/=d; q/=d;
        return (frac){p,q};
    }
    frac operator*(const frac &u){
        ll p,q;
        p=u.x*x;
        q=u.y*y;
        ll d=__gcd(p,q);
        p/=d; q/=d;
        return (frac){p,q};
    }
    frac operator/(const frac &u){
        ll p,q;
        p=u.y*x;
        q=u.x*y;
        ll d=__gcd(p,q);
        p/=d; q/=d;
        return (frac){p,q};
    }
	void sqr() {
		*this = (*this) * (*this);
	}
    void print(){
        if (y==1) printf("%lld\n",x);
        else printf("%lld/%lld\n",x,y);
    }
};

ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a; 
}

int main() {
	while (scanf("%d%lld", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
		sort(a + 1, a + 1 + n, [&](ll x, ll y){
			return x > y;		
		});
		ll k = m;
	    ll ans = 0;	
		for (int i = 1; i <= n; ++i) {
			if (i < n && (1ll * i * (a[i] - a[i + 1])) <= k) {
				k -= 1ll * i * (a[i] - a[i + 1]);  
			} else {
				ans = 1ll * (i * a[i] - k) * (i * a[i] - k);
				for (int j = i + 1; j <= n; ++j) {
					ans += 1ll * i * a[j] * a[j]; 
				}
				ll q = 1ll * i * m * m;
				ll G = gcd(ans, q);
				ans /= G; q /= G; 
				if (q == 1) printf("%lld\n", ans);
				else printf("%lld/%lld\n", ans, q);
				break;
			}
		}
	}
	return 0;
}
