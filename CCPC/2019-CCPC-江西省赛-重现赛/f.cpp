#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 110
int n;
char s[N];
int cnt[220];

int main() {
	while (scanf("%d", &n) != EOF) {
		scanf("%s", s + 1);
		memset(cnt, 0, sizeof cnt);
		for (int i = 1; i <= n; ++i) ++cnt[s[i]];
		if (!cnt['a'] || !cnt['v'] || !cnt['i'] || !cnt['n']) {
			puts("0/1");
		} else {
			ll a = 1ll * cnt['a'] * cnt['v'] * cnt['i'] * cnt['n'];
			ll b = 1ll * n * n * n * n;
			ll G = __gcd(a, b);
			a /= G;
			b /= G;
			printf("%lld/%lld\n", a, b);
		}
	}
	return 0;
}
