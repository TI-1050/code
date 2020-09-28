#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 1e5 + 10;
int n, m, f[N][26], nx[26];
char s[N], t[N];

int main() {
	while (scanf("%s%s", s + 1, t + 1) != EOF) {
		n = strlen(s + 1), m = strlen(t + 1);
		for (int i = 0; i < 26; ++i) nx[i] = n + 1;
		for (int i = n; i >= 0; --i) {
			for (int j = 0; j < 26; ++j) {
				f[i][j] = nx[j];
			}
			if (i) nx[s[i] - 'a'] = i;
		}
		ll res = 0;
		for (int i = 1; i <= n; ++i) {
			int now = i - 1;
			for (int j = 1; j <= m && now <= n; ++j) now = f[now][t[j] - 'a'];
			res += max(0, n - now + 1);
		}
		printf("%lld\n", res);
	}
	return 0;
}
