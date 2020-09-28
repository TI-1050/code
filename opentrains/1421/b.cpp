#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 2e5 + 10;
const ll INF = 1e18;
char s[N]; int f[N], n, nx;

ll gao(char *s) {
	nx = n + 1;
	for (int i = n; i >= 1; --i) {
		f[i] = nx;
		if (s[i] == '1') nx = i;
	}
	ll tot = INF;
	for (int i = 1; i <= n; ++i) {
		tot = min(tot, 1ll * (i - 1) * 14 + (n - f[i] + 1) * 7);
		tot = min(tot, 1ll * (i - 1) * 7 + (n - f[i] + 1) * 14);
	}
	return tot;
}

int main() {
	freopen("bad.in", "r", stdin);
	freopen("bad.out", "w", stdout);
	while (scanf("%s", s + 1) != EOF) {
		n = strlen(s + 1); 
		ll res = 0;
		for (int i = 1; i <= n; ++i) res += 4 * (s[i] - '0');
		printf("%lld\n", res + gao(s));
	}
	return 0;
}
