#include <bits/stdc++.h>
using namespace std;

#define N 1000010
#define ll long long
ll a[N];
ll n;

int main() {
	int m = 0;
	a[1] = 1;
	ll base = 0;
	for (int i = 2; i < N; ++i) {
		base += 6;
		a[i] = a[i - 1] + base;
		if (a[i] > 1e12) {
			m = i;
			break;
		}
	}
	for (int i = 1; i <= 100; ++i)
		cout << a[i] << endl;
	while (scanf("%lld", &n), n) {
		ll res = 0;
		while (n) {
			int pos = lower_bound(a + 1, a + 1 + m, n) - a;
			if (a[pos] > n) --pos;
			res += n / a[pos];
			n %= a[pos];
		}
		printf("%lld\n", res);
	}
	return 0;
}
