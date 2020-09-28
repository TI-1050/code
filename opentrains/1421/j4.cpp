#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll n, res;
inline int check(ll n, ll x, ll m) { 
	if (n % x == m && x % m == 0) return 1;
	return 0;
}
inline ll calc(ll n, ll y) {
	ll x = n - y; 
	ll limit = sqrt(x);  
  	ll res = 0;
	for (ll j = 1; j <= limit; ++j) {
		if (x % j == 0) { 
			res += check(n, j, y);  
			if (j * j != x) res += check(n, x / j, y);
		}
	}
	return res;
}
inline ll gao(ll n) {
	res = 0; 
	ll limit = sqrt(n);
	for (ll i = 1; i <= limit; ++i) {
		if (n % i == 0) {
			res += calc(n, i) + 1;
			if (i * i != n) res += calc(n, n / i) + 1;
		}
	}
	return res;
}

int main() {
//	freopen("job.in", "r", stdin);
//	freopen("job.out", "w", stdout);
//	cout << gao(5);
//	for (int i = 1; i <= 100; ++i) printf("%d %lld\n", i, gao(i));
	while (scanf("%lld", &n) != EOF) printf("%lld\n", gao(n));
	return 0;
}
