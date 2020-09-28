#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll n, x0, a, b, p, v;
int q;

inline ll qmod(ll base, ll n, ll p) {
	ll res = 1;
	while (n) {
		if (n & 1) res = res * base % p;
		base = base * base % p;
		n >>= 1;
	}
	return res;
}

inline ll inv(ll x, ll p) {
	return qmod(x, p - 2, p);
}

inline void out(int x) {
	if (x < n) printf("%d\n", x);
	else puts("-1");
}

struct Hash {
	static const int MOD = 1999997;
	static const int N = 1e6;
	int head[MOD + 10], nx[N], top; 
	int hs[N], id[N];
	void init() {
		memset(head, -1, sizeof head); 
		top = 0;
	}
	void insert(int x, int y) {
		int k = x % MOD;
		hs[top] = x; id[top] = y; nx[top] = head[k]; head[k] = top++;
	}
	int find(int x) {
		int k = x % MOD;
		for (int i = head[k]; i != -1; i = nx[i]) {
			if (hs[i] == x) {
				return id[i]; 
			}
		}
		return -1;
	}
}hs;

struct BSGS {
	ll V, m, lim, n;
	inline ll getsqrt(ll n) {
		//适当更改块的大小和Hash的块的大小
		ll x = (ll)pow(n, 2.0 / 3);
		return x;
	}
	inline void init(ll a, ll _n) {
		n = _n;
		hs.init();
		m = getsqrt(n);
		lim = n / m + 1;
		V = inv(qmod(a, m, n), n);
		hs.insert(1, 0);
		ll e = 1;
		for (int i = 1; i < m; ++i) {
			e = e * a % n;
			if (hs.find(e) == -1) {
				hs.insert(e, i);
			}
		}	
	}
	//a^x = b % n
	//需要保证gcd(a, n) = 1, 即存在逆元
	//如果有解输出的是最小的正整数解，否则输出-1
	inline ll cal(ll b) { 
		if (b == 1) return 0; 
		for (int i = 0; i < lim; ++i) { 
			int j = hs.find(b);
			if (j != -1) return 1ll * i * m + j;
			b = V * b % n;
		}
		return -1;
	}
}bsgs;

//a^n = (a - 1)v + b / ((a - 1)x0 + b)
void solve() {
	scanf("%lld%lld%lld%lld%lld", &n, &x0, &a, &b, &p);
	scanf("%d", &q);
	if (a == 0) {
		while (q--) {
			scanf("%lld", &v);
			if (v == x0) {
				out(0);
			} else if (v == b) {
				out(1);
			} else {
				out(-1);
			}
		}
		return;
	}
	if (a == 1) {
		if (b == 0) {
			while (q--) {
				scanf("%lld", &v);
				if (v == x0) {
					out(0);
				} else {
					out(-1);
				}
			}
		} else {
			while (q--) {
				scanf("%lld", &v); 
				v = (v - x0 + p) % p;
				ll res = v * inv(b, p) % p;
				out(res);
			}
		}
		return;
	}
	ll Inv = ((a - 1) * x0 + b) % p;
   	if (inv == 0) {
		while (q--) {
			scanf("%lld", &v);
			if (((a - 1) * v + b) % p == 0) {
				out(0);
			} else {
				out(-1);
			}
		}
		return;
	}
	Inv = inv(Inv, p);
	bsgs.init(a, p); 
    while (q--) {
		scanf("%lld", &v);
		if (v == x0) {
			out(0);
		} else {
			ll B = ((a - 1) * v + b) % p * Inv % p;
			out(bsgs.cal(B));
		}
	}	
}

int main() {
	int T; scanf("%d", &T);
	while (T--) solve();
	return 0;
}
