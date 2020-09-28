#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define INFLL 0x3f3f3f3f3f3f3f3f
#define N 400010

int n;
ll S, x;
int cnt[65][2];
ll dp[65][N];

int main() {
	while (~scanf("%d %lld", &n, &S)) {
		memset(cnt, 0, sizeof cnt);
		memset(dp, 0x3f, sizeof dp);
		for (int i = 1; i <= n; ++i) {
			scanf("%lld", &x);
			for (int j = 0; j < 60; ++j) {
				cnt[j][(x >> j) & 1]++;
			}		
		}
		dp[60][0] = 0;
		for (int i = 59; ~i; --i) {
			for (int j = 0; j < N; ++j) if (dp[i + 1][j] != INFLL) {
				for (int k = 0; k < 2; ++k) {
					int now = j * 2 - cnt[i][k] + ((S >> i) & 1);
					if (now >= 0 && now < N) {
						dp[i][now] = min(dp[i][now], (dp[i + 1][j] * 2 + (k ^ 1)));
					}
				}
			}
		}
		if (dp[0][0] == INFLL) {
			dp[0][0] = -1;
		}
		printf("%lld\n", dp[0][0]);
	}
	return 0;
}
