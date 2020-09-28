#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define N 40

int n, m;
int v[N][N];
ll ans, tnow;
int arr[N], brr[N];

inline void calc() {
	ll res = 0;
	for (register int i = 1; i <= m; ++i) {
		for (register int j = 1; j <= m; ++j) {
			res += v[arr[i]][brr[j]];
		}
	}
	ans = max(ans, res);
}

void DFS(int pos, int cnt, int cntB, ll now) {
	// 1
	if (cnt == n - pos + 1) {
		int tmp = arr[0];
		tnow = now;
		for (register int i = pos; i <= n; ++i) {
			arr[++arr[0]] = i;
			for (int j = 1; j <= m; ++j) {
				tnow += v[i][brr[j]];
			}
		}
		ans = max(ans, tnow);   
		arr[0] = tmp;
		return;
	}
	if (cntB == n - pos + 1) {
		int tmp = brr[0];
		tnow = now;
		for (register int i = pos; i <= n; ++i) {
			brr[++brr[0]] = i;
			for (int j = 1; j <= m; ++j) {
				tnow += v[i][arr[j]];
			}
		}
		ans = max(ans, tnow);
		brr[0] = tmp;
		return;
	}
	if (cnt) {
		arr[++arr[0]] = pos;
		tnow = now;
		for (int j = 1; j <= brr[0]; ++j) {
			tnow += v[pos][brr[j]];
		}
		if (pos < n) {
			DFS(pos + 1, cnt - 1, cntB, tnow);
		} else {
			ans = max(ans, tnow);
		}
		--arr[0];
	}
	if (cntB) {
		brr[++brr[0]] = pos;
		tnow = now;
		for (int j = 1; j <= arr[0]; ++j) {
			tnow += v[arr[j]][pos];
		}
		if (pos < n) {
			DFS(pos + 1, cnt, cntB - 1, tnow);
		} else {
			ans = max(ans, tnow);
		}
		--brr[0];
	}
}

int main() {
	scanf("%d", &n);
	m = n;
	n <<= 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			scanf("%d", &v[i][j]);
		}
	}
	DFS(1, m, m, 0ll);
	printf("%lld\n", ans);
	return 0;	
}
