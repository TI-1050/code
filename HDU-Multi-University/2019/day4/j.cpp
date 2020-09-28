#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll n;
ll fac[220]; int tot;
const int C = 2307;
const int S = 8;
//64位大整数随机数 
mt19937_64 rd(time(0));
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
unordered_map <ll, int> mp; 
void findfac(ll n, int c) {
	if (n == 1) return;
	if (miller_rabin(n)) {
		mp[n] = 1;
		return;
	}
	for (auto it : mp) {
		while (n % it.first == 0) {
			n /= it.first;
		}
	}
	if (n == 1) return;
	if (miller_rabin(n)) {
		mp[n] = 1;
		return;
	}
	int cnt = (int)mp.size();
	ll m = n;
	while (m == n) {
		m = pollard_rho(n, c--);
	}
	findfac(m, c);
	if (cnt > (int)mp.size()) {
		for (auto it : mp) {
			while (n % it.first == 0) {
				n /= it.first;
			}
		}
		if (n == 1) return;
		if (miller_rabin(n)) {
			mp[n] = 1;
			return;
		}
	}
	findfac(n / m, c);
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		mp.clear();
		scanf("%lld", &n);
		findfac(n, C);
		int res = 1e9;
		ll t = n;
		for (auto it : mp) {
			int tmp = 0;
			while (t % it.first == 0) {
				++tmp;
				t /= it.first;
			}
			res = min(res, tmp);
		}
		printf("%d\n", res);
	}
	return 0;
}
