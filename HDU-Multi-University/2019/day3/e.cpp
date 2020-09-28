#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 10000010
int prime[N], check[N], phi[N], tot;
void init() {
	memset(check, 0, sizeof check);
	tot = 0;
	phi[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (!check[i]) {
			prime[++tot] = i;
			phi[i] = i - 1;
		}
		for (int j = 1; j <= tot; ++j) {
			if (1ll * i * prime[j] >= N) break;
			check[i * prime[j]] = 1;
			if (i % prime[j] == 0) {
				phi[i * prime[j]] = phi[i] * prime[j];
			} else {
				phi[i * prime[j]] = phi[i] * (prime[j] - 1);
			}
		}
	}
}

int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}


ll f(int x) {
	ll res = 0;
	for (int i = 1; i <= x; ++i) {
		res += (i * i * phi[i] + i * (i == 1)) / 2; 
	}
	return res * 2;
	for (int i = 1; i <= x; ++i)
		for (int j = 1; j <= x; ++j)
			if (gcd(i, j) == 1)
				res += i * j;
	return res;
}

ll g(int x) {
	ll res = 0;
	for (int i = 1; i <= x; ++i) {
		res += 1ll * i * i * phi[i];
	}
	return res;
}

int main() {
	init();
	for (int i = 1; i <= 1000; ++i)
		if (f(i) != g(i)) {
			printf("%lld %lld\n", f(i), g(i));
		}
	return 0;
}
