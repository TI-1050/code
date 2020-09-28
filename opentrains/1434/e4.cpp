#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define N 2000010
//#define N 1010

int m;
ll n;
ll a[N];
map<ll,int> h;
map<ll, int> mp;

int gao() {
	if (h.find(n) != h.end()) return h[n];
	ll tmp = (n - 1) % 6 + 1;
	if (tmp >= 3)  {
		h[n] = tmp;
		return tmp;
	}
	if (tmp == 1) {
		if (mp.find(n) != mp.end()) {
			h[n] = 1;
			return 1;
		} else {
			h[n] = 7;
			return 7;
		}
	} else {
		int l = 1, r = m;
		while (r - l >= 0) {
			if (a[l] + a[r] == n) {
				h[n] = 2;
				return 2;
			}
			if (a[l] + a[r] > n) {
				--r;
			} else {
				++l;
			}
		}	
		h[n] = 8;
		return 8;
	}
}

int main() {
	a[1] = 1;
	ll base = 0;
	mp[1] = 1;
	m = 1;
	for (int i = 2; i < N; ++i) {
		base += 6;
		a[i] = a[i - 1] + base;
		if (a[i] > 1e12) break;
		++m;
		mp[a[i]] = 1;
	}

	while (~scanf("%lld", &n)) {
		if (n == 0) return 0;
		printf("%d\n", gao());
	}
	return 0;
}
