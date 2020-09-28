#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 10000010
int n, l[1000010], r[1000010];
int f[N], g[N], sum[N * 3 + 10], b[N * 3 + 10], c[N * 3 + 10];

void solve() {
	ll res = 0;
	int i = 1, j, base = 10000000;
	while (i <= n) {
		j = i + 1;
		while (j <= n && f[j - 1] + g[j] >= l[j] - r[j - 1] - 1) ++j;
		--j;
		int Left = max(0, l[i] - g[i]), Right = min(1000000000 - 1, r[j] + f[j]);
		int Min = 1e9, Max = -1e9;
		sum[0] = 0;
		for (int k = Left, t = i; k <= Right; ++k) {
			int now = k - Left + 1; 
			sum[now] = sum[now - 1];
			if (k >= l[t] && k <= r[t]) {
				++sum[now];
			} else {
				--sum[now];
			}
			if (k == r[t]) ++t;
			Min = min(Min, sum[now] + base);
			Max = max(Max, sum[now] + base);
			++b[sum[now] + base];
		}
		for (int k = Max - 1; k >= Min; --k) {
			b[k] += b[k + 1];
		}
		res += b[base + 1]; 
		for (int k = Left; k <= Right; ++k) {
			int now = sum[k - Left + 1] + base;
			b[now + 1] -= c[now + 1];
		    c[now] += c[now + 1] + 1;
			c[now + 1] = 0;
			res += b[now + 1];	
		}
		Min = max(0, Min - 10);
		Max = min(30000000, Max + 10);
		for (int k = Min; k <= Max; ++k) b[k] = c[k] = 0; 
		i = j + 1;
	}
	printf("%lld\n", res);
}


int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d", l + i, r + i);
		}
		//f[]表示以第i个区间的右端点为结尾的最大区间和是多少
		f[1] = r[1] - l[1] + 1;
		for (int i = 2; i <= n; ++i) {
			f[i] = max(0, f[i - 1] - (l[i] - r[i - 1] - 1)) + r[i] - l[i] + 1;
		}
		//g[]表示以第i个区间的左端点为开头的最大区间和是多少
		g[n] = r[n] - l[n] + 1;
		for (int i = n - 1; i >= 1; --i) {
			g[i] = max(0, g[i + 1] - (l[i + 1] - r[i] - 1)) + r[i] - l[i] + 1;
		}
		solve();
	}
	return 0;
}
