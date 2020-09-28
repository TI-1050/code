#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 3010
const ll p = 998244353;
ll f[N], C[N][N], pw[N]; 

inline void add(ll &x, ll y) {
	x += y;
	if (x >= p) x -= p;
}

ll qmod(ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) {
			res = res * base % p;
		}
		base = base * base % p;
		n >>= 1;
	}
	return res;
}


int main() {
	for (int i = 0; i < N; ++i) C[i][0] = C[i][i] = 1;
	for (int i = 1; i < N; ++i) {
		for (int j = 1; j < i; ++j) {
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % p;
		}
	}
	pw[0] = 1;
	for (int i = 1; i < N; ++i) pw[i] = pw[i - 1] * 2 % p;
	f[0] = 0;
	for (int i = 1; i < N; ++i) {
		f[i] = 1ll * i * (i - 1) % p * pw[i - 2] % p;
	   	for (int j = 0; j < i; ++j) 
			add(f[i], C[i][j] * f[j] % p);
		f[i] = f[i] * qmod(pw[i] - 1, p - 2) % p;	
	}
	for (int i = 1; i < N; ++i) add(f[i], f[i - 1]);
	int n;
	while (scanf("%d", &n) != EOF) {
		printf("%lld\n", f[n] * qmod(n, p - 2) % p);
	}
	return 0;
}
