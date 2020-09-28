#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define N 100010
#define M 5010

int n, m;
int a[N], l[N], r[N], p[N], top;
ll f[M][M], g[M];

ll gao() {
	for (int i = 0; i <= top + 1; ++i) {
		for (int j = 0; j <= top + 1; ++j) {
			f[i][j] = 0ll;
		}
	}
	for (int i = 1; i <= top; ++i) {
		g[i] += g[i - 1];
	}
	for (int L = top; L >= 1; --L) {
		for (int R = L; R <= top; ++R) {
			f[L][R] = max(f[L][R - 1], f[L + 1][R]) + g[R] - g[L - 1];
		}
	}
	return f[1][top];
}

int main() {
	while (scanf("%d %d", &n, &m) != EOF) {
		memset(p, 0, sizeof p);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		for (int i = 1; i <= n; ++i) {
			r[a[i]] = i;
		}
		for (int i = n; i >= 1; --i) {
			l[a[i]] = i;
		} 
		for (int i = 1; i <= m; ++i) {
			p[l[i]] = i;
		}
		ll ans = 0;
		for (int i = 1; i <= n; ++i) {
			if (p[i] == 0) continue;
			top = 0;
			int L = i, nxt = 0;
			while (p[L]) {
				nxt = p[L];
				p[L] = 0;
				g[++top] = r[nxt] - l[nxt] + 1;
				L = r[nxt] + 1;
			}
			ans += gao();
		}
		printf("%lld\n", ans);
	}
	return 0;
}
