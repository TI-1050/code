#include <bits/stdc++.h>

using namespace std;

#define N 5010

int n;
int arr[N];
int dp[N][N];

int main() {
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", arr + i);
		}
		for (int i= 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				dp[i][j] = 2;
			}
		}
		sort(arr + 1, arr +  1 + n);
		int ans = 2;
		for (int i = 1; i <= n; ++i) {
			int j = i - 1, k = i - 2;
			while (j > k && k >= 1) {
				if (arr[j] * 2 > arr[i] + arr[k]) {
					--j;
				} else if (arr[j] * 2 < arr[i] + arr[k]) {
					--k;
				} else {
					dp[i][j] = max(dp[i][j], dp[j][k] + 1);
					ans = max(ans, dp[i][j]);
					--j;
				}
			}
		}
		printf("%d\n", ans);
	}
}
