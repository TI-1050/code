#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll n, m, k;
ll ceil(ll x, ll y) {
	return x / y + 1;
}

int main() {
	int _T; cin >> _T;
	while (_T--) {
		scanf("%lld%lld%lld", &n, &m, &k);
		ll res = (m + 1) * k;
		res = min(res, n * (ceil(m, n - k + 1)));
		printf("%lld\n", res);
	}
	return 0;
}
