#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 1e5 + 10;
int pri[N], check[N], ptot;
void init() {
	memset(check, 0, sizeof check);
	ptot = 0;
	for (int i = 2; i < N; ++i) {
		if (!check[i]) {
			pri[++ptot] = i;
		}
		for (int j = 1; j <= ptot; ++j) {
			if (1ll * i * pri[j] >= N) break;
			check[i * pri[j]] = 1;
			if (i % pri[j] == 0) {
				break;
			}
		}
	}
}
int n;
ll f[N];

int main() {
	freopen("fourprimes.in", "r", stdin); 
	freopen("fourprimes.out", "w", stdout); 
	init();
	while (scanf("%d", &n) != EOF) {
		memset(f, 0, sizeof f);
		for (int i = 1; i <= ptot; ++i) {
			if (pri[i] + pri[i] <= n) {
				f[pri[i] + pri[i]] += 1;
			}
			for (int j = 1; j < i && pri[i] + pri[j] <= n; ++j) {
				f[pri[i] + pri[j]] += 2;
			}
		}
		ll res = 0;
		for (int i = 1; i <= n; ++i) {
			res += f[i] * f[n - i];
		}
		printf("%lld\n", res);
	}
	return 0;
}
