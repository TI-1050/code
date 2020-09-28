#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll p = 998244353;

const int N = 1e7 + 10;
const int M = 3010;

ll inv[N], fac[N];

ll qpow(ll x, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) res = res * x % p;
		x = x * x % p;
		n >>= 1;
	}
	return res;
}

void Init() {
	fac[0] = 1ll;
	for (int i = 1; i < N; ++i) {
		fac[i] = fac[i - 1] * i % p;
	}
	inv[N - 1] = qpow(fac[N - 1], p - 2);
	for (int i = N - 1; i >= 1; --i) {
		inv[i - 1] = inv[i] * i % p;
	}
}

ll C(int n, int m) {
	if (n < m) return 0ll;
	return fac[n] * inv[m] % p * inv[n - m] % p;
}

struct node {
	int t, p;

	void input() {
		scanf("%d %d", &t, &p);
	}
	
	bool operator < (const node &other) const {
		return p < other.p;
	}
}q[M];

int L, d, m;
ll f[N], g[N];

ll F(int t, int p) {
	if (p < d * t) return 0ll;
	if (p - (d - 1) * t < 1) return 0ll;
	return C(p - (d - 1) * t - 1, t - 1);
}

int main() {
	Init();
	while (scanf("%d %d %d", &L, &d, &m) != EOF) {
		for (int i = 1; i <= m; ++i) {
			q[i].input();
		}
		sort(q + 1, q + 1 + m);
		memset(f, 0, sizeof f);
		f[0] = 1;
		g[0] = 1;
		int pos = 1;
		for (int i = 1; i <= L; ++i) {
			if (i >= d) {
				f[i] = g[i - d];
			}
			while (pos <= m && i == q[pos].p) {
				f[i] = (f[i] - F(q[pos].t, q[pos].p) + p) % p;
				for (int j = 1; j < pos; ++j) {
					if (q[j].t < q[pos].t )
						f[i] = (f[i] + F(q[pos].t - q[j].t, q[pos].p - q[j].p)) % p;
				}
				++pos;
			}
			g[i] = (f[i] + g[i - 1]) % p;
		}
	//	for (int i = 1; i <= L; ++i) {
	//		cout << i << " " << f[i] << endl;
	//	}
		ll res = f[L];
		printf("%lld\n", res);

	}
	return 0;
}
