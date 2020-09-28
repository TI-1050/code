#include <bits/stdc++.h>
using namespace std;
	
typedef long long ll;
mt19937 rd(time(NULL));
const ll inv2 = 5e8 + 4;
ll w, b, c, p;
struct num { ll x, y; };
num mul(num a, num b, ll p) {
	num ans = {0, 0};
	ans.x = ((a.x * b.x % p + a.y * b.y % p * w % p) % p + p) % p;
	ans.y = ((a.x * b.y % p + a.y * b.x % p) % p + p) % p;
	return ans;
}
ll qpow(ll base, ll n, ll p) {
	ll res = 1;
	while (n) {
		if (n & 1) {
			res = res % p * base % p;
	//		cout << res << endl;
		}
		base = base % p * base % p;
		n >>= 1;
	}
	return res % p;
}
ll qpow(num base, ll n, ll p) {
	num res = {1, 0};
	while (n) {
		if (n & 1) res = mul(res, base, p);
		base = mul(base, base, p);
		n >>= 1;
	}
	return res.x % p;
}

ll gao(ll n, ll p) {
	n %= p; n = (n + p) % p;
	if (!n) return 0;
	if (p == 2) return n;
	if (qpow(n, (p - 1) / 2, p) == p - 1) return -1;
	ll a;
	while (1) {
		a = rd() % p;
	//	cout << a << endl;
		w = ((a * a % p - n) % p + p) % p;
	//	cout << w << " " << (p - 1) / 2 << " " << qpow(w, (p - 1) / 2, p) << endl;
		if (qpow(w, (p - 1) / 2, p) == p - 1) break;	
	}
	num x = {a, 1};
	return qpow(x, (p + 1) / 2, p); 
}

int main() {
	p = 1e9 + 7;
	int _T; cin >> _T;
	while (_T--) {
		scanf("%lld%lld", &b, &c);
		ll A = gao(b * b - c * 4, p), B, x = -1, y = -1;
		if (A == -1) puts("-1 -1");
		else {
			B = p - A;
			x = (b + A) * inv2 % p;
			y = (b - x + p) % p;
			if (x > y) { x = y = -1; }
			if (x == -1 && y == -1) {
				x = (b + B) * inv2 % p;
				y = (b - x + p) % p;
			}
			printf("%lld %lld\n", x, y);
		}
	}
	return 0;
}
