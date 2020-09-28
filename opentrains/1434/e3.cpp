#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

//#define N 2000010
#define N 1010

ll n;
ll a[N];
ll f[N];
map<ll, int> mp;

int gao(ll n) {
	ll tmp = (n - 1) % 6 + 1;
	if (tmp >= 3)  {
		return tmp;
	}
	if (tmp == 1) {
		if (mp.find(n) != mp.end()) return 1;
		else return 7;
	} else {
		for (auto it : mp) {
			if (mp.find(n - it.first) != mp.end()) {
				return 2;
			}
		}
		return 8;
	}
}

int main() {
	a[1] = 1;
	ll base = 0;
	mp[1] = 1;
	for (int i = 2; i < N; ++i) {
		base += 6;
		a[i] = a[i - 1] + base;
		if (a[i] > 1e12) break;
		mp[a[i]] = 1;
	}
	memset(f, 0x3f, sizeof f);
	f[0] = 0;
	ll res=  0;
	for (int i = 1; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (j - a[i] >= 0) {
				f[j] = min(f[j], f[j - a[i]] + 1);
			}
		}
	}
	for (int i = 1; i < N; ++i) {
		if (gao(i) != f[i]) {
			cout << i << " " << f[i] << " " << gao(i) << endl;
			break;
		}
	}


//	while (~scanf("%lld", &n)) {
//		if (n == 0) return 0;
//		printf("%d\n", gao());
//	}
	return 0;
}
