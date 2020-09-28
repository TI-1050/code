#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 50;
int n, m, a[N][N];
//第i行第j个数字
int f[1 << 20][21];
int vis[1 << 20][21];
//大于1 小于0
int g[N][N]; 
int ord[N], vec[N];
int isup[N], isdown[N];

bool ok(int i) {
	if (isup[i] || isdown[i]) return 1;
	bool F1 = 1, F2 = 1;
	for (int j = 2; j <= ord[0]; ++j) {
		if (a[i][ord[j]] > a[i][ord[j - 1]]) {
			F1 = 0;
		} else {
			F2 = 0;
		}
		if (F1 + F2 == 0) return 0;
	}
	return F1 or F2;
}

void get(int mask) {
	ord[0] = 0;
	for (int j = 0; j < m; ++j) {
		if ((mask >> j) & 1) {
			ord[++ord[0]] = j + 1;
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	ll res = 0;
	int limit = 1 << m, S;  
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			scanf("%d", a[i] + j);
	for (int i = 1; i <= n; ++i) {
		isup[i] = 1; isdown[i] = 1;
		for (int j = 2; j <= m; ++j) {
			if (a[i][j] > a[i][j - 1]) {
				isdown[i] = 0;
			} else {
				isup[i] = 0;
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			S = 0;
			for (int k = m; k >= 1; --k) {
				S = S * 2 + (a[j][k] > a[i][k]);
			}
			g[i][j] = S;
		}
	}
	for (int mask = 1; mask < limit; ++mask) {
		get(mask);
		vec[0] = 0;
		for (int i = 1; i <= n; ++i) {
			if (ok(i)) {
				vec[++vec[0]] = i;
			}
		}
		int sze = vec[0], now, pre;  
		for (int i = 1; i <= sze; ++i) {
			now = vec[i]; 
			++res; 
			for (int j = 1; j < i; ++j) {
				pre = vec[j]; 
				S = g[pre][now] & mask;
				if (vis[S][pre] != mask) {
					vis[S][pre] = mask;
					f[S][pre] = 0;
				} 
				if (vis[S][now] != mask) {
					vis[S][now] = mask;
					f[S][now] = 0;
				}
				res += f[S][pre] + 1;
				f[S][now] += f[S][pre] + 1;
			}		
		}
	//	for (int i = 1; i <= sze; ++i) {
	//		now = vec[i]; 
	//		for (int j = 1; j < i; ++j) {
	//			pre = vec[j]; 
	//			S = g[pre][now] & mask;
	//			f[now][S] = f[pre][S] = 0;
	//		}		
	//	}
	}
	printf("%lld\n", res);
	return 0;
}
