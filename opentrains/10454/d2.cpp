#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll p, q, n;
ll sum_2(ll x) {
	return x * (x + 1) / 2;
}
ll gao(ll a, ll b, ll c, ll n) {
	if (a == 0) {
		return (n + 1) * (b / c);
	}
	if (a >= c || b >= c) {
		ll tmp = gao(a % c, b % c, c, n);
		return tmp + n * (n + 1) / 2 * (a / c) + (b / c) * (n + 1);
	}
	ll m = (a * n + b) / c;
	ll tmp = gao(c, c - b - 1, a, m - 1);
	return (n * m - tmp);
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%lld%lld%lld", &p, &q, &n);
		ll res = p * sum_2(n) - q * gao(p, 0, q, n);
		printf("%lld\n", res);
	}
	return 0;
}
