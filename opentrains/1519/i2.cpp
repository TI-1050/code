#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define fi first
#define se second
const int N = 5e3 + 10, INF = 0x3f3f3f3f;
int n, V, num, w[N], f[N][N], g[N][N], cnt[N];

int gao1() {
	memset(f, 0x3f, sizeof f);
	f[0][0] = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= V; ++j) f[i][j] = f[i - 1][j];
		for (int j = V; j >= w[i]; --j) {
			f[i][j] = min(f[i][j], f[i - 1][j - w[i]] + 1);
		}
	}
	return f[n][V];
}

void gao2() {
	memset(g, 0x3f, sizeof g);
	g[n + 1][0] = 0;
	for (int i = n; i >= 1; --i) {
		for (int j = 0; j <= V; ++j) g[i][j] = g[i + 1][j];
		for (int j = V; j >= w[i]; --j) {
			g[i][j] = min(g[i][j], g[i + 1][j - w[i]] + 1);
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= V; ++j) {
			if (f[i][j] == (num + 1) / 2 && g[i + 1][V - j] == num / 2) {
				printf(" %d", w[i]);
				return;
			}
		}
	}
}

void gao3() {
	memset(f, 0x3f, sizeof f);
	f[0][0] = 0;
	memset(cnt, 0, sizeof cnt);
	for (int i = 1; i <= n; ++i) ++cnt[w[i]];
	vector <int> A, B; 
	for (int i = 1; i <= V; ++i) if (cnt[i]) A.push_back(i);
	int res = 0;
	while (!A.empty()) {
		B.clear();
		++res;
		for (auto &it : A) {
			for (int j = V; j >= it; --j)
				f[0][j] = min(f[0][j], f[0][j - it] + 1);
			--cnt[it];
			if (cnt[it]) B.push_back(it);
		}
		if (f[0][V] == num) {
			printf(" %d", res);
			return;
		}
		A = B;
	}
}

void gao4() {
	memset(f, 0x3f, sizeof f);
	memset(g, 0x3f, sizeof g);
	f[0][0] = 0, g[0][0] = INF;
	int res = INF;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= V; ++j) f[i][j] = f[i - 1][j], g[i][j] = g[i - 1][j]; 
		for (int j = V; j >= w[i]; --j) {
			if (f[i - 1][j - w[i]] + 1 < f[i][j] || (f[i - 1][j - w[i]] + 1 == f[i][j] && min(g[i - 1][j - w[i]], w[i]) > g[i][j])) {
				f[i][j] = f[i - 1][j - w[i]] + 1;
				g[i][j] = min(g[i - 1][j - w[i]], w[i]); 
			}
		}
		if (f[i][V] == num) res = min(res, w[i] - g[i][V]);
	}	
	printf(" %d", res);
}

int main() {
	while (scanf("%d%d", &n, &V) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", w + i);
		sort(w + 1, w + 1 + n);
		num = gao1();
		if (num > n) {
			puts("-1");
			continue;
		}
		printf("%.10f", V * 1.0 / num);
		gao2();
		gao3();
		gao4();
		puts("");
	}
	return 0;
}
