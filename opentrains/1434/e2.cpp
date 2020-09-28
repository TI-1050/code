#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define N 100010

ll a[N];
ll f[N];

int main() {
	a[1] = 1;
	ll base = 0;
	for (int i = 2; i < N; ++i) {
		base += 6;
		a[i] = a[i - 1] + base;
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
		cout << f[i] << endl;
		//cout << i << " " << f[i] << " " << (i - 1) % 6 + 1 << endl;
	}
	return 0;
}
