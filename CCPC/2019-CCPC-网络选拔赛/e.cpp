#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 1e6 + 10;
const ll mod = 1e9 + 7;
int pri[N], check[N], phi[N], tot;
void init() {
	memset(check, 0, sizeof check);
	tot = 0;
	phi[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (!check[i]) {
			pri[++tot] = i;
			phi[i] = i - 1;
		} 
		for (int j = 1; j <= tot; ++j) {
			if (1ll * i * pri[j] >= N) break;
			check[i * pri[j]] = 1;
			if (i % pri[j] == 0) {
				phi[i * pri[j]] = phi[i] * pri[j];
				break;
			} else {
				phi[i * pri[j]] = phi[i] * (pri[j] - 1); 
			}
		}
	}
}

ll qpow(ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) res = res * base % mod;
		base = base * base % mod;
		n >>= 1;
	}
	return res;
}

int main() {
	init();
	ll inv2 = qpow(2, mod - 2);
	ll n, a, b;
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%lld%lld%lld", &n, &a, &b);
		ll res = 0;
		for (int i = 2; i <= n; ++i) {
			res = res + 1ll * i * phi[i] % mod;
			res %= mod;
		}
		res = res * inv2 % mod;
		printf("%lld\n", res);
	}
	return 0;
}
