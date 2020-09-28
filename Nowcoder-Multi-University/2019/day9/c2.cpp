#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e5 + 10;

int n, a[N];
ll f[N], g[N];

int main() {
	f[0] = g[0] = 1ll; 
	while(cin >> n) {
		f[n] = g[n] = 0ll;
		for (int i = 1; i <= n; ++i) {
			a[i] = i;
		}
		do {
			int res = 0;
			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j < i; ++j) {
					if (a[i] < a[j]) {
						res++;
					}
				}
			}
			ll ans1 = 1, ans2 = 1;
			for (int i = 1; i <= res; ++i) {
				ans1 *= 2ll;
				ans2 *= 3ll;
			}
			f[n] += ans1, g[n] += ans2;
		} while (next_permutation(a + 1, a + 1 + n));
		cout << n << " " << f[n] << " " << g[n] << " " << f[n] / f[n - 1] << " " << g[n] / g[n - 1]<< endl;
	}
	return 0;
}
