#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 2000010
const ll p = 1e9 + 7;
int n, m, k;
int f[N];

void DFS(vector <int> &vec, int i, int x, int p) {
	if (i < (int)vec.size()) {
		DFS(vec, i + 1, x, p);
		DFS(vec, i + 1, x ^ vec[i], -p);
	} else {
		f[x] += p;
	}
}

void FWT(int *x, int len) {
	for (int i = 2; i <= len; i <<= 1) {
		int step = i >> 1;
		for (int j = 0; j < len; j += i) {
			for (int k = j; k < j + step; ++k) {
				ll a = x[k], b = x[k + step];
				x[k] = (a + b) % p;
				x[k + step] = (a - b + p) % p;
			}
		}
	}
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
	while (scanf("%d%d%d", &n, &m, &k) != EOF) {
		for (int i = 0; i < 1 << k; ++i) f[i] = 0;
		for (int i = 1; i <= n; ++i) {
			vector <int> a(m);
			for (auto &it : a) scanf("%d", &it);
			DFS(a, 0, 0, 1);
		}
		FWT(f, 1 << k);
		ll res = 0;
		ll three = 1;
		ll inv = qmod(qmod(2, m), p - 2);
		for (int i = 0; i < 1 << k; ++i) {
			res ^= 1ll * f[i] * three % p * inv % p;
			three = three * 3 % p;
		}
		printf("%lld\n", res);
	}
	return 0;
}
