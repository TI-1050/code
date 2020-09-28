#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll p;
const int C = 2307;
const int S = 10;
mt19937_64 rd(time(0));
ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a;
}
inline ll mul(ll x,ll y,ll mod)
{
	ll tmp=(x*y-(ll)((long double)x/mod*y+1.0e-8)*mod);
	return tmp<0 ? tmp+mod : tmp;
}

//ll mul(ll u,ll v, ll p)
//{
// return(u * v-(ll)((long double)u * v / p) * p + p ) % p;
//}
//ll mul(ll a, ll b, ll p) {
//	return (a * b - (ll)(a / (long double)p * b + 1e-3) * p + p) % p;
//}
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

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%lld", &p);
		ll n;
		for (ll i = p - 1; ; --i) {
			if (miller_rabin(i)) {
				n = i;
				break;
			}
		}
		ll res = p - 1;
		for (ll i = p - 1; i > n; --i) {
			res = mul(res, qmod(i, p - 2, p), p);
		}
		printf("%lld\n", res);
	}
	return 0;
}


