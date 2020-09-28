#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define ll long long
#define pii pair <int, int>
#define fi first
#define se second
ll p, n, m;
pii fac[N];
int tot;  

struct node {
	ll a[2][2];
	node() {
		memset(a, 0, sizeof a);
	}
	void set() {
		a[0][0] = a[0][1] = 1;
	}
	node operator * (const node &other) const {
		node res = node();
		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < 2; ++j) {
				for (int k = 0; k < 2; ++k) {
					res.a[i][j] = (res.a[i][j] + a[i][k] * other.a[k][j] % p) % p;
				}
			}
		}
		return res;
	}
}base, res; 

ll eular(ll n) {
	ll ans = n;
	for (int i = 2; i * i <= n; ++i) {
		if (n % i == 0) {
			ans -= ans / i;
			while (n % i == 0) 
				n /= i;
		}
	}
	if (n > 1) ans -= ans / n;
	return ans;
}

node qmod(node base, ll n) {
	node res = node(); res.set();
	while (n) {
		if (n & 1) {
			res = res * base;
		}
		base = base * base; 
		n >>= 1;
	}
	return res;
}

ll qpow(ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) {
			res = res * base;
		}
		base = base * base;
		n >>= 1;
	}
	return res;
}

void getfac(pii *fac, int &tot, ll x) {
	tot = 0;
	for (int i = 2; i * i <= x; ++i) {
		if (x % i == 0) {
			fac[++tot] = pii(i, 0);
			while (x % i == 0) {
				++fac[tot].se;
				x /= i;
			}
		}
	}
	if (x != 1) fac[++tot] = pii(x, 1);
	
}

ll calc(ll t, ll n, ll m) {
	ll res = 0;
	getfac(fac, tot, t);
	for (int j = 1; j <= min(30ll, m); ++j) {
		ll g = 1;
		for (int o = 1; o <= tot; ++o) {
			int a = fac[o].fi, b = fac[o].se;
			g *= qpow(a, b / j + (b % j != 0)); 
		}
		res += (n / g);
		if (j == 30) res += (n / g) * (m - j);
	}
	return res;
}

int main() {
	base = node();
	base.a[0][0] = 10;
	base.a[1][0] = 1;
	base.a[1][1] = 1;
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%lld%lld%lld", &p, &n, &m);
		if (p == 2 || p == 5) {
			puts("0");
		} else if (p == 3) {
			printf("%lld\n", calc(3, n, m));
		} else {	
			ll t = p - 1;  
		    getfac(fac, tot, t);	
			for (int i = 1; i <= tot; ++i) {
				for (int j = 1; j <= fac[i].se; ++j) {
					res = qmod(base, t / fac[i].fi - 1);
					if (res.a[0][0] == 0) {
						t = t / fac[i].fi;
					} else {
						break;
					}
				}
			}
			printf("%lld\n", calc(t, n, m));
		}
	}
	return 0;
}
