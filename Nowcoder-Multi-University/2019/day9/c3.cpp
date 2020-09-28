#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e5 + 10;
const ll p = 1e9 + 7;

ll qpow(ll x, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) {
			res = res * x % p;
		}
		x = x * x % p;
		n >>= 1;
	}
	return res;
}

int n;
ll b, f[N], g[N];
int a[N];
int vis[N];

int main() {
	scanf("%d %lld", &n, &b);
	memset(vis, 0, sizeof vis);
	f[0] = 0ll;
	g[0] = 1ll;
	ll base = 1ll;
	for (int i = 1; i <= n; ++i) {
		f[i] = (f[i - 1] + base) % p;
		base = base * b % p;
	}
	for (int i = 1; i <= n; ++i) {
		g[i] = g[i - 1] * f[i] % p;
	} 
	ll res = g[n] % p;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		vis[a[i]]++;
	}
	for (int i = 0; i < N; ++i) {
		res = res * qpow(g[vis[i]], p - 2) % p;
	}
	printf("%lld\n", res % p);
	return 0;
}
