#include <bits/stdc++.h>
using namespace std;
using pII = pair <int, int>;
#define fi first
#define se second
const int N = 1e6 + 10, ALP = 26;
char s[N], t[N];
int n, m, f[N][ALP], nx[ALP];
pII g[N];

bool operator < (const pII &x, const pII &y) {
	if (x.fi != y.fi) return x.fi < y.fi;
	return x.se > y.se;
}

int main() {
	int _T; cin >> _T;
	while (_T--) {
		scanf("%s%s", s + 1, t + 1);
		n = strlen(s + 1), m = strlen(t + 1);
		for (int i = 0; i < 26; ++i) f[n + 1][i] = nx[i] = n + 1;
		for (int i = n; i >= 0; --i) {
			for (int j = 0; j < ALP; ++j)
				f[i][j] = nx[j];
			if (i) nx[s[i] - 'a'] = i;
		}
		g[0] = pII(0, 0);
		int res = 0; 
		for (int i = 1; i <= m; ++i) {
			int ch = t[i] - 'a';
			g[i] = pII(0, 0);
			for (int j = 0; j < i; ++j) {
				int p = g[j].se;
				if (p < n + 1 && f[p][ch] < n + 1) {
					g[i] = max(g[i], pII(g[j].fi + 1, f[p][ch]));
				}
			}
			res = max(res, g[i].fi);
		}
		printf("%d\n", res);
	}
	return 0;
}
