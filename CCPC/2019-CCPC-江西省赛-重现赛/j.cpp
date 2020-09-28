#include <bits/stdc++.h>
using namespace std;

#define N 1100
#define ll long long
int n, a[N];
ll m, lcm;

void solve() {
	ll one = 0;
	for (int i = 1; i <= n; ++i) {
		one += lcm / a[i];
	}
	if (m % one) {
		puts("No");
		return;
	}
	ll cur = m / one;
	puts("Yes");
	for (int i = 1; i <= n; ++i) printf("%lld%c", cur * (lcm / a[i]), " \n"[i == n]);
}

int main() {
	while (scanf("%d%lld", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		lcm = a[1]; 
		for (int i = 2; i <= n; ++i) {
			lcm = lcm * a[i] / __gcd(lcm, 1ll * a[i]);
		}
		solve();
	}
	return 0;
}
