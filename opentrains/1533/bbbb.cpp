#include <bits/stdc++.h>

using namespace std;

#define N 5010

int n;
int arr[N];
int dp[N][N];

int main() {
	while (~scanf("%d", &n)) {
		memset(dp, 0, sizeof dp);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", arr + i);
		}
		for (int i= 1; i <= n; ++i) {
			for (int j = 1; j < i; ++j) {
				dp[i][j] = 2;
			}
		}
		sort(arr + 1, arr +  1 + n);
		int ans = 2;
		for (int i = 1; i <= n; ++i) {
			int k = i - 2;
			for (int j = i - 1; j >= 2; --j) {
				if (k >= j) k = j - 1;
				while (k >= 1 && arr[i] - arr[j] > arr[j] - arr[k]) {
					--k;
				}
				if (k >= 1 && arr[j] * 2 == arr[i] + arr[k]) {
					dp[i][j] = max(dp[i][j], dp[j][k] + 1);
					ans = max(ans, dp[i][j]);
				}
			}
		}
		printf("%d\n", ans);
	}
}
