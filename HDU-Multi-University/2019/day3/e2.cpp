#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 5000010
const ll p = 1e9 + 7;
ll n; int k;
bool check[N];
int prime[N], ptot;
ll phi[N], sp[N];
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

void add(ll &x, ll y) {
	x += y;
	if (x >= p) x -= p;
	else if (x < 0) {
		x += p;
	}
}

//线性筛
void init() { 
	memset(check, 0, sizeof check);
	phi[1] = 1;
	ptot = 0;
	for (int i = 2; i < N; ++i) {
		if (!check[i]) {
			prime[++ptot] = i;
			phi[i] = i - 1;
			sp[ptot] = qmod(i, k);
		}
		for (int j = 1; j <= ptot; ++j) {
			if (1ll * i * prime[j] >= N) break;
			check[i * prime[j]] = 1;
			if (i % prime[j] == 0) {
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			} else {
				phi[i * prime[j]] = phi[i] * (prime[j] - 1);
			}
		}
	}
	for (int i = 1; i <= ptot; ++i) {
		add(sp[i], sp[i - 1]);
	}
	for (int i = 1; i < N; ++i) {
		phi[i] = (phi[i - 1] + 1ll * i * i % p * phi[i] % p) % p;
	}
}

//拉格朗日差值
struct Lagrange { 
	static const int SIZE = 220;
	ll f[SIZE], fac[SIZE], inv[SIZE], pre[SIZE], suf[SIZE];
	int n;
	void init(int _n) {
		n = _n + 1;
		fac[0] = 1;
		for (int i = 1; i < SIZE; ++i) fac[i] = fac[i - 1] * i % p;
	    inv[SIZE - 1] = qmod(fac[SIZE - 1], p - 2);
		for (int i = SIZE - 1; i >= 1; --i) inv[i - 1] = inv[i] * i % p;
		//设置f初值，可以根据需要修改
		f[0] = 0;
		for (int i = 1; i <= n; ++i)
			f[i] = (f[i - 1] + qmod(i, n - 1)) % p;
	}
	ll cal(ll x) {
		if (x <= n) return f[x];
		pre[0] = x % p;
		for (int i = 1; i <= n; ++i) pre[i] = pre[i - 1] * ((x - i) % p) % p;
		suf[n] = (x - n) % p;
		for (int i = n - 1; i >= 0; --i) suf[i] = suf[i + 1] * ((x - i) % p) % p;
		ll res = 0;
		for (int i = 0; i <= n; ++i) {
			ll tmp = f[i] * inv[n - i] % p * inv[i] % p;
			if (i) tmp = tmp * pre[i - 1] % p;
			if (i < n) tmp = tmp * suf[i + 1] % p;
			if ((n - i) & 1) tmp = p - tmp;
			add(res, tmp); 
		}
		return res;
	}
}lagrange; 

//Min25筛
struct Min25 {
	static const int SIZE = 4e5 + 10;
	ll w[SIZE], g[SIZE], n;
	ll id1[SIZE], id2[SIZE], m, blk;
	void go(ll n) {
		this->n = n;
		m = 0;
		blk = sqrt(n); 
		for (ll i = 1, j; i <= n; i = j + 1) {
			j = n / (n / i);
			w[++m] = n / i;  
			g[m] = (lagrange.cal(w[m]) + p - 1) % p;
			if (w[m] <= blk) id1[w[m]] = m;
			else id2[n / w[m]] = m;
		}
		int tot = lower_bound(prime + 1, prime + 1 + ptot, blk) - prime;
		for (int j = 1; j <= tot; ++j) {
			for (int i = 1; i <= m && 1ll * prime[j] * prime[j] <= w[i]; ++i) {
				int id = (w[i] / prime[j] <= blk) ? id1[w[i] / prime[j]] : id2[n / (w[i] / prime[j])];
				add(g[i], (p - (sp[j] - sp[j - 1]) * (g[id] - sp[j - 1]) % p) % p);
				g[i] = (g[i] + p) % p;
			}
		}
	}
	inline ll get(ll x) {
		if (x <= blk) return g[id1[x]];
		else return g[id2[n / x]];
	}
}min25;

//杜教筛
struct DLS {
	unordered_map <ll, ll> mp;
	ll inv2, inv6;
	void init() {
		mp.clear();
		inv2 = qmod(2, p - 2);
		inv6 = qmod(6, p - 2);
	}	
	inline ll sum_3 (ll n) {
		n %= p;
		return n * n % p * inv2 % p * (n + 1) % p * (n + 1) % p * inv2 % p;
	}
	inline ll sum_2 (ll n) {
		n %= p;
		return n * (n + 1) % p * (2 * n + 1) % p * inv6 % p;
	}
	ll go(ll n) {
		if (n < N) return phi[n];
		if (mp.count(n)) return mp[n];
		ll res = sum_3(n);
		for (ll i = 2, j; i <= n; i = j + 1) {
			j = n / (n / i);
			add(res, p - (sum_2(j) - sum_2(i - 1)) % p * go(n / i) % p);
			res = (res + p) % p;
		}
		return mp[n] = res;
	} 
}dls;

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%lld%d", &n, &k); ++k;
		init();
		lagrange.init(k);
		min25.go(n);
		dls.init();
		ll res = 0;
		for (ll i = 1, j; i <= n; i = j + 1) {
			j = n / (n / i);
			add(res, (min25.get(j) - min25.get(i - 1)) % p * dls.go(n / i) % p);
			res = (res + p) % p;
		}
		printf("%lld\n", res);
	}
	return 0;
}
