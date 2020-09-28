#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 2010
#define M 10010
int n, m, a[N], b[N], cnt[M];
int prime[M], check[M], tot;
void init() {
	tot = 0;
	memset(check, 0, sizeof check);
	for (int i = 2; i < N; ++i) {
		if (!check[i]) {
			prime[++tot] = i;
		}
		for (int j = 1; j <= tot; ++j) {
			if (1ll * i * prime[j] >= N) break;
			check[i * prime[j]] = 1;
			if (i % prime[j] == 0) break;
		}
	}
}

ll f(int x) {
	return x * (x - 1) / 2;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		memset(cnt, 0, sizeof cnt);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			++cnt[a[i]];
			b[i] = a[i];	
		}
		m = n;
		sort(b + 1, b + 1 + m);
		m = unique(b + 1, b + 1 + m) - b - 1;
		ll res = 0;
		//枚举腰
		for (int i = 1; i <= m; ++i) {
			//3 + 1
			if (cnt[b[i]] >= 3) {
				for (int j = 1; j <= m; ++j) if (i != j) {
					if (__gcd(b[i], b[j]) == 1) {
						++res;
					}
				}
			}
			if (cnt[b[i]] >= 2) {
				//2 + 2
				for (int j = 1; j < i; ++j) if (i != j) {
					if (__gcd(b[i], b[j]) == 1 && cnt[b[j]] >= 2) {
						++res; 
					}
				}
				//2 + 1 + 1
				//两边不互质
				for (int j = 1; j <= tot; ++j) {  
					int base = (__gcd(b[i], prime[j]) == 1 && cnt[prime[j]] >= 1);  
					for (int k = prime[j] + prime[j]; k <= 10000; k += prime[j]) {
						if (k == b[i] || cnt[k] <= 0) continue;
						res += base;
						base += (__gcd(b[i], k) == 1);
					}
				}
				//两边互质
				res += f(m - 1);
				for (int j = 1; j <= tot; ++j) {
					int tmp = 0;
					for (int k = prime[j]; k <= 10000; k += prime[j]) {
						if (cnt[k] >= 1 && k != b[i]) ++tmp;
					}
					res -= f(tmp);
				}
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
