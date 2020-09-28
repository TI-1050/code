#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e5 + 10;
const ll p = 1e9 + 7;

ll qpow(ll x, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) res = res * x % p;
		x = x *x % p;
		n >>= 1;
	}
	return res;
}

int n;
ll b, f[N], g[N];
int cnt[N];

int main() {
	cin.tie(0), cout.tie(0);
	cin >> n >> b;
	ll base = 1;
	for (int i = 1; i <= n; ++i) {
		f[i] = (f[i - 1] + base) % p;
		base = base * b % p;
	}
	g[0] = 1ll;
	for (int i = 1; i <= n; ++i) g[i] = g[i - 1] * f[i] % p;
	ll res = g[n];
	for (int i = 1, x; i <= n; ++i) {
		cin >> x;
		cnt[x]++;
	}
	for (int i = 0; i < N; ++i) {
		res = res * qpow(g[cnt[i]], p - 2) % p;
	}
	cout << res << "\n";
	return 0;
}
