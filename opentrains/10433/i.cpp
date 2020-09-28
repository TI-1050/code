#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e6 + 10;
const ll mod = 1ll << 31;
int pri[N], check[N]; ll a[N];
void sieve() {
	memset(check, 0, sizeof check);
	*pri = 0;
	for (int i = 2; i < N; ++i) {
		if (!check[i]) pri[++*pri] = i;
		for (int j = 1; j <= *pri; ++j) {
			if (1ll * i * pri[j] >= N) break;
			check[i * pri[j]] = 1;
			if (i % pri[j] == 0) break;
		}
	}
}
ll ex_gcd(ll a, ll b, ll &x, ll &y) {
	if (a == 0 && b == 0) return -1;
	if (b == 0) { x = 1; y = 0; return a; }
	ll d = ex_gcd(b, a % b, y, x);
	y -= a / b * x;
	return d;
}
ll inv(ll a, ll n) {
	ll x, y;
	ll d = ex_gcd(a, n, x, y);
	if (d == 1) return (x % n + n) % n;
	return -1;
}
inline void f5() { fflush(stdout); }
unordered_map <int, int> mp;
mt19937 rnd(time(0));

int main() {
	sieve();
	int n;
	while (scanf("%d", &n) != EOF) {
		for (int i = 2; i <= n + 1; ++i) printf("%d%c", pri[i], " \n"[i == n + 1]); f5();
		for (int i = 1; i <= n / 2; ++i) scanf("%lld", a + i);
		shuffle(pri + 2, pri + n + 2, rnd);
		mp.clear();
		for (int i = 2; i <= n + 1; ++i) {
			for (int j = 1; j <= n / 2; ++j) {
				int x = a[j] * inv(pri[i], mod) % mod;
				++mp[x];
				if (mp[x] > 2) {
					printf("%d\n", x);
					f5();
					return 0;
				}
			}
		}
		int Max = -1, pos = -1;
		for (auto &it : mp) {
			if (it.second > Max) {
				Max = it.second;
				pos = it.first;
			}
		}	
		printf("%d\n", pos); f5();
	}
	return 0;
}
