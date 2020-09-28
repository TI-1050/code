#include <cstdio>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <cmath>
#include <climits>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <stack>
#include <set>
#include <list>
#include <bitset>
#include <numeric>
#include <sstream>
#include <iomanip>
#include <limits>
using namespace std;

const int N = 5e4 + 10;
typedef long long ll;
ll r, s, t, m, p, q, n;
int pri[N], check[N];
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
ll qpow(ll base, ll n, ll mod) {
	ll res = 1;
	while (n) {
		if (n & 1) res = res * base % mod;
	    base = base * base % mod;
		n >>= 1;	
	}
	return res;
}
ll ex_gcd(ll a, ll b, ll &x, ll &y) {
	if (!a && !b) return -1;
	if (!b) { x = 1; y = 0; return a; }
	ll d = ex_gcd(b, a % b, y, x);
	y -= a / b * x;
	return d;	
}
ll inv(ll a, ll n) {
	ll x = 0, y = 0;
	ll d = ex_gcd(a, n, x, y);
	if (d == 1) return (x % n + n) % n;
	return -1;
}

int main() {
	sieve();
	while (scanf("%lld%lld%lld", &r, &s, &m) != EOF) {
	//	for (int i = 1; i <= *pri; ++i) {
	//		p = pri[i];
	//		if (r % p == 0) {
	//			if (check[r / p] == 0) {
	//				q = r / p;
	//				break;
	//			}
	//		}
	//	}
	//	cout << p << " " << q << endl;
	//	ll phi = (p - 1) * (q - 1);
	//	t = inv(s, phi);
	//	cout << s << " " << t << endl;
		printf("%lld\n", qpow(m % r, s, r));
	}
	return 0;
}
