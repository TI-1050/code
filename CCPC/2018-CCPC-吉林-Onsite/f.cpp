#include <bits/stdc++.h>
using namespace std;

#define N 210
#define pii pair <int, int>
#define fi first
#define se second
int n, k, v;
vector < vector <pii> > box, candy; 
int dp[N][N];

void pre(vector <pii> &box, vector <pii> &vec) {
	int f[N];
	memset(f, -1, sizeof f);
	f[0] = 0;
	for (auto it : box) {
		for (int i = v; i >= it.se; --i) {
			if (f[i - it.se] != -1) {
				f[i] = max(f[i], f[i - it.se] + it.fi);
			}
		}
	}
	for (int i = 1; i <= v; ++i) {
		if (f[i] != -1) {
			vec.emplace_back(f[i], i);
		}
	}
}

void init() {
	box.clear();
	box.resize(n + 1);
	candy.clear();
	candy.resize(n + 1); 
}
int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &k, &v); 
		init();
		for (int i = 1, a, v, c; i <= n; ++i) {
			scanf("%d%d%d", &a, &v, &c);
			box[c].emplace_back(a, v);
		}
		for (int i = 1; i <= n; ++i) if (!box[i].empty()) {
			pre(box[i], candy[i]);
		}
		memset(dp, -1, sizeof dp);
		dp[0][0] = 0; 
		for (int i = 1; i <= n; ++i) if (!candy[i].empty()) {
			for (int j = n; j >= 1; --j) {
				for (auto it : candy[i]) {
					for (int o = v; o >= it.se; --o) {
						if (dp[j - 1][o - it.se] != -1) {
							dp[j][o] = max(dp[j][o], dp[j - 1][o - it.se] + it.fi);
						}
					}
				}
			}
		}
		int res = 0;
		for (int i = k; i <= n; ++i) {
			for (int j = 1; j <= v; ++j) {
				res = max(res, dp[i][j]);
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
