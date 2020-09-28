#include <bits/stdc++.h>
using namespace std;

#define N 5010
#define ll long long
ll n;
int prime[N], check[N], tot;
void init() {
	memset(check, 0, sizeof check);
	tot = 0;
	for (int i = 2; i < N; ++i) {
		if (!check[i]) {
			prime[++tot] = i;
		}
		for (int j = 1; j <= tot; ++j) {
			if (i * prime[j] >= N) break;
			check[i * prime[j]] = 1;
			if (i % prime[j] == 0) break; 
		}
	}
}

bool f(ll x, int op) {
	if (op == 1) return 1;
	ll mid = pow(x, 1.0 / op);
	for (ll i = max(1ll, mid - 10); i <= min(x, mid + 10); ++i) {
		ll t = 1;
		for (int j = 0; j < op; ++j) {
			t *= i;
		}
		if (t == x) return 1;
	}
	return 0;
}

int main() {
	init();
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%lld", &n);
		int res = 1e9;
		for (int i = 1; i <= tot; ++i) {
			int x = prime[i];
			if (n % x == 0) {
				int tmp = 0;
				while (n % x == 0) {
					++tmp;
					n /= x;
				}
				res = min(res, tmp);
			}
		}
		if (n != 1) {
			for (int i = 4; i >= 1; --i) {
				if (f(n, i)) {
					res = min(res, i);
					break;
				}
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
