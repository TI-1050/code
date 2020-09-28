#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll n, res;
ll fac[10010], tmp[10010]; int tot; 
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
unordered_map <ll, int> used;
inline ll gao(ll n) {
	used.clear();
	res = 0; tot = 0;
	ll limit = sqrt(n);
	for (ll i = 1; i <= limit; ++i) {
		if (n % i == 0) {
			fac[++tot] = i;
			fac[++tot] = n / i; 
		}
	}
	sort(fac + 1, fac + 1 + tot);
	tot = unique(fac + 1, fac + 1 + tot) - fac - 1;
	for (int i = 1; i <= tot; ++i) used[fac[i]] = 1; 
	res = tot;
	for (int i = 1; i <= tot; ++i) {
		ll x = n - fac[i];
		limit = sqrt(x); tmp[0] = 0;  
		for (ll j = 1; j <= limit; ++j) {
			if (x % j == 0) {
				tmp[++tmp[0]] = j;
				if (j * j != x) tmp[++tmp[0]] = x / j;
			}
		}
		for (int j = 1; j <= tmp[0]; ++j) {
			if (n % tmp[j] == fac[i] && tmp[j] % fac[i] == 0) ++res;
		}
	}
	return res;
}

int main() {
//	freopen("job.in", "r", stdin);
//	freopen("job.out", "w", stdout);
//	for (int i = 1; i <= 100; ++i) printf("%d %lld\n", i, gao(i));
	while (scanf("%lld", &n) != EOF) printf("%lld\n", gao(n));
	return 0;
}
