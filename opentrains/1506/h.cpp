#include <bits/stdc++.h>
using namespace std;

#define pii pair <int, int>
#define fi first
#define se second
#define ll long long
const int N = 1e6 + 10;
int pri[N], check[N], ptot, mu[N];
ll f[N], g[N];
void init() {
	ptot = 0;
	mu[1] = 1;
	f[1] = 0;
	for (int i = 2; i < N; ++i) {
		if (!check[i]) {
			pri[++ptot] = i;
			mu[i] = -1;
			f[i] = 1;
		} 
		for (int j = 1; j <= ptot; ++j) {
			if (1ll * i * pri[j] >= N) break;
			check[i * pri[j]] = 1;
			if (i % pri[j] == 0) {
				mu[i * pri[j]] = 0;
				f[i * pri[j]] = f[i];
				break;
			} else {
				mu[i * pri[j]] = -mu[i];
				f[i * pri[j]] = f[i] + 1;
			}
		}
	}
	for (int i = 1; i < N; ++i) {
		for (int j = i; j < N; j += i) {
			g[j] += 1ll * mu[i] * f[j / i]; 
		}
	}
	for (int i = 1; i < N; ++i) f[i] += f[i - 1], g[i] += g[i - 1];
}
map <pii, ll> mp;
int n, m;
inline ll gao(int n, int m) {
	if (mp.find(pii(n, m)) != mp.end()) {
		return mp[pii(n, m)];
	}
	ll res = 0;
	for (int i = 1, j; i <= n; i = j + 1) {
		j = min(n / (n / i), m / (m / i));
		res += 1ll * (n / i) * (m / i) * (g[j] - g[i - 1]);
	}
	return mp[pii(n, m)] = res;
}

int main() {
	init();
	mp.clear();
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%d%d", &n, &m);
		ll res = gao(m, m) - 2ll * gao(n - 1, m) + gao(n - 1, n - 1);
		res -= f[m] - f[n - 1];
		res /= 2;
		printf("%lld\n", res);
		fflush(stdout);
	}
	return 0;
}
