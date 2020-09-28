#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll n;
int calc(ll l, ll r, ll x) {
	int limit = sqrt(x);
	int res = 0;
	for (int i = 1; i <= limit; ++i) {
		if (x % i == 0) {
			if (l <= i && i >= r) ++res;
			if (1ll * i * i != x && x / i <= r && x / i >= l) ++res;
		}		
	}	
	return res; 
}

ll gao(ll n) {
	ll res = 0;
	for (ll i = 1, j; i <= n; i = j + 1) {
		j = n / (n / i); 
		if (n % j == 0 || (j % (n % j)) == 0) ++res;
		if (i < j) res += calc(n % (j - 1), n % i, j);
		printf("# %lld %lld\n", i, j);
		for (ll k = j - 1; k >= i; --k) {
			printf("%lld %lld\n", k, n % k);
		}
	//	cout << i << " " << j << " " << res << endl; 
	}
	return res;
}

int main() {
	gao(100);
//	for (int i = 1; i <= 100; ++i) printf("%d %lld\n", i, gao(i));
	while (scanf("%lld", &n) != EOF) {
		printf("%lld\n", gao(n)); 
	}
	return 0;
}
