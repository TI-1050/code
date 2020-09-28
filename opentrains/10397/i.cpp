#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e7 + 10, INF = 0x3f3f3f3f;
int pri[N], check[N];
void sieve() {
	memset(check, 0, sizeof check);
	*pri = 0;
	for (int i = 2; i < N; ++i) {
		if (!check[i]) {
			pri[++*pri] = i;
		}
		for (int j = 1; j <= *pri; ++j) {
			if (1ll * i * pri[j] >= N) break;
			check[i * pri[j]] = 1;
			if (i % pri[j] == 0) break;
		}
	}
}
ll q, n;
ll qpow(ll base, ll n, ll mod) {
	ll res = 1;
	while (n) {
		if (n & 1) res = res * base % mod;
		base = base * base % mod;
		n >>= 1;
	}
	return res;
}

bool get(int p) {
	--p;
	for (int i = 1; 1ll * i * i <= p; ++i) {
		if (p % i == 0) {
			if (qpow(q, i, p + 1) == 1) {
				if (i < n) return false;
			}
			if (qpow(q, p / i, p + 1) == 1) {
				if (p / i < n) return false;
			}
		}
	}
	return true;
}

int main() {
	sieve();
	while (scanf("%lld%lld", &q, &n) != EOF) {
		vector <int> res;
		int m = 1e7;
		for (int p = n; p <= m; ++p) if (!check[p]) {
			if (q % p && qpow(q, n, p) == 1 && get(p)) {
				res.push_back(p);
			}
		}
		int sze = res.size();
		printf("%d\n", sze);
		for (int i = 0; i < sze; ++i)
			printf("%d%c", res[i], " \n"[i == sze - 1]);
	}
	return 0;
}
