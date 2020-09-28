#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pLL = pair<ll, ll>;
#define fi first
#define se second
const int N = 2e5 + 10;
int n, a[N], b[N];
ll L, R;
vector <ll> vec;

ll calc(ll x) {
	ll res = 0;
	for (int i = 1; i <= n; ++i) {
		res += upper_bound(b + 1, b + 1 + n, x - a[i]) - b - 1;
	}
	return res;
}

pLL get(ll bord) {
	pLL res = pLL(2e9, 1ll * n * n);
	ll l = 0, r = 2e9;
	while (r - l >= 0) {
		ll mid = (l + r) >> 1;
		ll cnt = calc(mid); 
		if (cnt >= bord) {
			res = pLL(mid, cnt);
			r = mid - 1;
		} else 
			l = mid + 1;
	}
	return res;
}

void getres(vector<ll> &vec, ll l, ll r) {
	vec.clear();
	for (int i = 1; i <= n; ++i) {
		int L = lower_bound(b + 1, b + 1 + n, l - a[i]) - b;
		int R = upper_bound(b + 1, b + 1 + n, r - a[i]) - b - 1;
		for (int j = L; j <= R; ++j) {
			vec.push_back(a[i] + b[j]);
		}
	}
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		for (int i = 1; i <= n; ++i) scanf("%d", b + i);
		sort(a + 1, a + 1 + n);
		sort(b + 1, b + 1 + n);
		L = 1ll * n * (n - 1) / 2 + 1, R = 1ll * n * (n + 1) / 2;
		pLL x = get(L), y = get(R);
		vec.clear();
		getres(vec, x.fi + 1, y.fi - 1);
		for (ll i = L; i <= x.se && vec.size() < n; ++i) vec.push_back(x.fi);
		while (vec.size() < n) vec.push_back(y.fi);
		sort(vec.begin(), vec.end());
		for (int i = 0; i < n; ++i)
			printf("%lld%c", vec[i], " \n"[i == n - 1]);
	}
	return 0;
}
