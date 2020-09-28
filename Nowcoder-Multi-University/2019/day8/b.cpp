#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 1e5 + 10;
int n, a[N], pre[N];
ll f(int n) {
	return 1ll * n * (n + 1) / 2;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		ll res = 1ll * 100000 * f(n);
		memset(pre, 0, sizeof pre);
		for (int i = 1; i <= n; ++i) {
			res -= f(i - pre[a[i]] - 1);
			pre[a[i]] = i;
		}
		for (int i = 1; i <= 100000; ++i) res -= f(n - pre[i]); 
		cout << res << "\n";
	}
	return 0;
}
