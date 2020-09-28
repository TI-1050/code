#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1000010
const ll p = 1e9 + 7;
ll n, m, k, inv2, invk;
ll f[N], g[N], fac[N], inv[N];
ll qmod(ll base, ll n) {
	base %= p;
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
}

#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef pair<int, int> PII;
const ll mod = 1000000007;
ll powmod(ll a, ll b) { ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) { if (b & 1)res = res * a%mod; a = a * a%mod; }return res; }
// head
 
int _;
namespace linear_seq {
	ll res[N], base[N], _c[N], _md[N];
 
	vector<int> Md;
	void mul(ll *a, ll *b, int k) {
		rep(i, 0, k + k) _c[i] = 0;
		rep(i, 0, k) if (a[i]) rep(j, 0, k) _c[i + j] = (_c[i + j] + a[i] * b[j]) % mod;
		for (int i = k + k - 1; i >= k; i--) if (_c[i])
			rep(j, 0, SZ(Md)) _c[i - k + Md[j]] = (_c[i - k + Md[j]] - _c[i] * _md[Md[j]]) % mod;
		rep(i, 0, k) a[i] = _c[i];
	}
	int solve(ll n, VI a, VI b) { // a 系数 b 初值 b[n+1]=a[0]*b[n]+...
								  //        printf("%d\n",SZ(b));
		ll ans = 0, pnt = 0;
		int k = SZ(a);
		assert(SZ(a) == SZ(b));
		rep(i, 0, k) _md[k - 1 - i] = -a[i]; _md[k] = 1;
		Md.clear();
		rep(i, 0, k) if (_md[i] != 0) Md.push_back(i);
		rep(i, 0, k) res[i] = base[i] = 0;
		res[0] = 1;
		while ((1ll << pnt) <= n) pnt++;
		for (int p = pnt; p >= 0; p--) {
			mul(res, res, k);
			if ((n >> p) & 1) {
				for (int i = k - 1; i >= 0; i--) res[i + 1] = res[i]; res[0] = 0;
				rep(j, 0, SZ(Md)) res[Md[j]] = (res[Md[j]] - res[k] * _md[Md[j]]) % mod;
			}
		}
		rep(i, 0, k) ans = (ans + res[i] * b[i]) % mod;
		if (ans<0) ans += mod;
		return ans;
	}
	VI BM(VI s) {
		VI C(1, 1), B(1, 1);
		int L = 0, m = 1, b = 1;
		rep(n, 0, SZ(s)) {
			ll d = 0;
			rep(i, 0, L + 1) d = (d + (ll)C[i] * s[n - i]) % mod;
			if (d == 0) ++m;
			else if (2 * L <= n) {
				VI T = C;
				ll c = mod - d * powmod(b, mod - 2) % mod;
				while (SZ(C)<SZ(B) + m) C.pb(0);
				rep(i, 0, SZ(B)) C[i + m] = (C[i + m] + c * B[i]) % mod;
				L = n + 1 - L; B = T; b = d; m = 1;
			}
			else {
				ll c = mod - d * powmod(b, mod - 2) % mod;
				while (SZ(C)<SZ(B) + m) C.pb(0);
				rep(i, 0, SZ(B)) C[i + m] = (C[i + m] + c * B[i]) % mod;
				++m;
			}
		}
		return C;
	}
	int gao(VI a, ll n) {
		VI c = BM(a);
		c.erase(c.begin());
		rep(i, 0, SZ(c)) c[i] = (mod - c[i]) % mod;
		return solve(n, c, VI(a.begin(), a.begin() + SZ(c)));
	}
};
 
int main() {
	m = 1000000;
	fac[0] = 1;
	for (int i = 1; i < N; ++i) fac[i] = 1ll * fac[i - 1] * i % p; 
	inv[m] = qmod(fac[m], p - 2);
	for (int i = m; i >= 1; --i) inv[i - 1] = inv[i] * i % p;
	inv2 = 5e8 + 4;
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%lld%lld", &k, &n);
		invk = qmod(k, p - 2);
		if (n == -1) { 
			printf("%lld\n", 2 * qmod(k + 1, p - 2) % p);
			continue;
		}
		for (int i = 1; i <= m; ++i) f[i] = 0;
		f[0] = 1; g[0] = 1;
		for (int i = 1; i <= m; ++i) {
			if (i > k) {
				add(f[i], invk * (g[i - 1] - g[i - k - 1] + p) % p);
			} else {
				add(f[i], invk * g[i - 1] % p);
			}
			g[i] = (g[i - 1] + f[i]) % p;
		}
		vector <int> vec;
		for (int i = 0; i <= 2 * k; ++i) vec.push_back(f[i]);
		printf("%d\n", linear_seq::gao(vec, n));
	}
	return 0;
}
