#include <bits/stdc++.h>
using namespace std;

#define ll long long
mt19937 rd(time(0));
ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a;
}
ll mul(ll a, ll b, ll p) {
	return (a * b - (ll)(a / (long double)p * b + 1e-3) * p + p) % p;
}
ll qmod(ll base, ll n, ll p) {
	ll res = 1;
	base %= p;
	while (n) {
		if (n & 1) {
			res = mul(res, base, p);
		}
		base = mul(base, base, p);
		n >>= 1;
	}
	return res;
}
struct Mill {
	ll n, fac[520]; int tot; 
	const int C = 2307;
	const int S = 10;
	bool check(ll a, ll n) {
		ll m = n - 1, x, y;
		int j = 0;
		while (!(m & 1)) {
			m >>= 1;
			++j;
		}
		x = qmod(a, m, n);
		for (int i = 1; i <= j; x = y, ++i) {
			y = mul(x, x, n);
			if (y == 1 && x != 1 && x != n - 1) {
				return 1;
			}
		}
		return y != 1;
	}
	bool miller_rabin(ll n) {
		if (n < 2) {
			return 0;
		} else if (n == 2) {
			return 1;
		
		} else if (! (n & 1)) {
			return 0;
		}
		for (int i = 0; i < S; ++i) {
			if (check(rd() % (n - 1) + 1, n)) {
				return 0;
			}
		}
		return 1;
	}
	ll pollard_rho(ll n, int c) {
		ll i = 1, k = 2, x = rd() % n, y = x, d;
		while (1) {
			++i; x = (mul(x, x, n) + c) % n;
			d = gcd(y - x, n);
			if (d > 1 && d < n) {
				return d;
			}
			if (y == x) {
				return n;
			}
			if (i == k) {
				y = x;
				k <<= 1;
			}
		}
	}
	void findfac(ll n, int c) {
		if (n == 1) {
			return;
		}
		if (miller_rabin(n)) {
			fac[++tot] = n;
			return;
		}
		ll m = n;
		while (m == n) {
			m = pollard_rho(n, c--);
		}
		findfac(m, c);
		findfac(n / m, c);
	}
	void gao(ll _n, vector <ll> &vec) {
		vec.clear();
		n = _n;
		tot = 0;
		findfac(n, C);
		sort(fac + 1, fac + 1 + tot); 	
		vec.push_back(1); 
		int sze;
		for (int i = 1; i <= tot; ++i) {
			if (i == 1 || fac[i - 1] % fac[i]) {
				sze = vec.size();
			} else {
				fac[i] *= fac[i - 1];
			}
			for (int j = 0; j < sze; ++j) {
				vec.push_back(fac[i] * vec[j]);
			}
		}
		sort(vec.begin(), vec.end());
	}
}mill;

ll n, res; 
inline ll calc(ll n, ll y) {
	if (y == n) return 0;
	ll x = n - y; 
  	ll res = 0;
	vector <ll> fac;
	mill.gao(x, fac);
	for (ll &it : fac) {
		res += (n % it == y && it % y == 0);
	}
	return res;
}
inline ll gao(ll n) {
	res = 0;
    vector <ll> fac; mill.gao(n, fac);
	res = fac.size();
	for (ll &it : fac) res += calc(n, it);	
	return res;
}

int main() {
	freopen("job.in", "r", stdin);
	freopen("job.out", "w", stdout);
	while (scanf("%lld", &n) != EOF) printf("%lld\n", gao(n));
	return 0;
}
