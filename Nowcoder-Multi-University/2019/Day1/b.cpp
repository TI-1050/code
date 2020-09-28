#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1010
const ll p = 1e9 + 7;
int n, a[N];
ll qmod(ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) {
			res = res * base % p;
		}
		base = base * base % p;
		n >>= 1;
	}
	return res;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		ll sum = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			sum = (sum + a[i]) % p;
		}
		ll res = 1;
		for (int i = 1; i <= n; ++i) {
			res = res * 2 % p;
		}
		sum = (sum * res) % p;
		printf("%lld\n", qmod(sum, p - 2));
	}
	return 0;
}
