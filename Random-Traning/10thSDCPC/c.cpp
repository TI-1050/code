#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n, k;
char s[N];

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &k);
		scanf("%s", s + 1);
		ll x = 0, y = 0;
		ll res = 0;
		for (int i = 1; i <= n; ++i) {
			if (s[i] == 'L') {
				--x; 
			} else if (s[i] == 'R') {
				++x;
			} else if (s[i] == 'U') {
				--y;
			} else if (s[i] == 'D') {
				++y;
			}
			res = max(res, abs(x) + abs(y));
		}
		ll tmp = 1ll * (k - 1) * (abs(x) + abs(y));
		res = max(res, tmp);
		ll nx = 1ll * (k - 1) * x, ny = 1ll * (k - 1) * y;
		for (int i = 1; i <= n; ++i) {
			if (s[i] == 'L') {
				--nx;
			} else if (s[i] == 'R') {
				++nx;
			} else if (s[i] == 'U') {
				--ny;
			} else if (s[i] == 'D') {
				++ny;
			}
			res = max(res, abs(nx) + abs(ny));
		}
		printf("%lld\n", res);
	}
	return 0;
}
