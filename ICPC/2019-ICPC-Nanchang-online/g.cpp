#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 10000010
const int p = 1 << 30;
int inv2, inv6;
int prime[N];
bool check[N];
int f[N], g[N], h[N];
int mu[N], phi[N];
void init() {
	/*
	memset(check, 0, sizeof check);
	prime[0] = 0;
	f[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (!check[i]) {
			prime[++prime[0]] = i;
			f[i] = i * i * i * (i - 1) - 1;
			g[i] = i * i * i; 
			h[i] = i;
		}
		for (int j = 1; j <= prime[0]; ++j) {
			if (1ll * i * prime[j] >= N) break;
			check[i * prime[j]] = 1;
			if (i % prime[j] == 0) { 
				g[i * prime[j]] = g[i] * prime[j] * prime[j] * prime[j] * prime[j];
				h[i * prime[j]] = h[i] * prime[j];
				f[i * prime[j]] = f[i / h[i]] * (h[i * prime[j]] - h[i]) * (prime[j] - 1); 
				break;
			} else {
				f[i * prime[j]] = f[i] * f[prime[j]];
				g[i * prime[j]] = prime[j] * prime[j] * prime[j];
			  	h[i * prime[j]] = prime[j];	
			}
		}
	}
	*/

	memset(check, 0, sizeof check);
	prime[0] = 0;
	mu[1] = 1, phi[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (!check[i]) {
			prime[++prime[0]] = i;
			mu[i] = -1;
			phi[i] = i - 1;
		}
		for (int j = 1; j <= prime[0]; ++j) {
			if (1ll * i * prime[j] >= N) {
				break;
			}
			check[i * prime[j]] = 1;
			if (i % prime[j] == 0) {
				mu[i * prime[j]] = 0;
				phi[i * prime[j]] = phi[i] * prime[j];
			} else {
				mu[i * prime[j]] = -mu[i];
				phi[i * prime[j]] = phi[i] * (prime[j] - 1);
			}
		}
	}
	memset(f, 0, sizeof f);
	for (int i = 1; i < N; ++i) {
		for (int j = i; j < N; j += i) {
			f[j] += phi[j / i] * mu[i] * j * j * j;
		}
	}
	for (int i = 2; i < N; ++i) {
		f[i] += f[i - 1];
	}
}

int F(int x) {
	int a = x, b = x + 1;
	if (a % 2 == 0) {
		a /= 2;
	} else if (b % 2 == 0) {
		b /= 2;
	} else {
		assert(0);
	}
	return a * b;
}

int S(int x) {
	int a = x, b = x + 1, c = 2 * x + 1;
	if (a % 2 == 0) {
		a /= 2;
	} else if (b % 2 == 0) {
		b /= 2;
	} else if (c % 2 == 0) {
		c /= 2;
	} else {
		assert(0);
	}

	if (a % 3 == 0) {
		a /= 3;
	} else if (b % 3 == 0) {
		b /= 3;
	} else if (c % 3 == 0) {
		c /= 3;
	} else {
		assert(0);
	}

	return a * b * c;
}

int main() {
	init(); 
	int T; scanf("%d", &T);
	while (T--) {
		int n; scanf("%d", &n);
		int res = 0;
		for (int i = 1, j; i <= n; i = j + 1) {
			j = n / (n / i);
			res += (n / i) * F(n / i) * S(n / i) * (f[j] - f[i - 1]);
		}
		printf("%d\n", (res % p + p) % p);
	}
	return 0;
}
