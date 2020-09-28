#include <bits/stdc++.h>
using namespace std;

#define ll long long
const ll mod = 1e9 + 7;
ll qmod(ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) res = res * base % mod;
		base = base * base % mod;
		n >>= 1;
	}
	return res;
}
ll inv(ll x) {
	return qmod(x, mod - 2);
}

int main() {
	ll a, b;
	while (cin >> a >> b) {
		cout << a * inv(b) % mod << endl;
	}
	return 0;
}
