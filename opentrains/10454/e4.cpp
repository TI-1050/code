#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 50;
int n, m, a[N][N];
//第i行第j个数字
int f[1 << 20][25];
//大于1 小于0
int g[N][N]; 
int ord[N], vec[N];
int isup[N], isdown[N];

inline bool ok(int i) {
	bool F1 = 1, F2 = 1;
	for (register int j = 2; j <= ord[0]; ++j) {
		if (a[i][ord[j]] > a[i][ord[j - 1]]) {
			F1 = 0;
		} else {
			F2 = 0;
		}
		if (F1 + F2 == 0) return 0;
	}
	return F1 | F2;
}

inline void get(int mask) {
	ord[0] = 0;
	for (register int j = 0; j < m; ++j) {
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
		isup[i] |= isdown[i];
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
	int sze, now, pre;
	for (register int mask = 1; mask < limit; ++mask) {  
		get(mask);
		vec[0] = 0;
		for (register int i = 1; i <= n; ++i) {
			if (isup[i] || ok(i)) {
				vec[++vec[0]] = i;
			}
		}
		sze = vec[0];
		for (register int i = 1; i <= sze; ++i) {
			now = vec[i]; 
			++res; 
			for (register int j = 1; j < i; ++j) {
				pre = vec[j]; 
				S = g[pre][now] & mask;
				res += f[S][pre] + 1;
				f[S][now] += f[S][pre] + 1;
			}		
		}
		for (register int i = 1; i <= sze; ++i) {
			now = vec[i]; 
			for (int j = 1; j < i; ++j) {
				pre = vec[j]; 
				S = g[pre][now] & mask;
				f[S][now] = f[S][pre] = 0;
			}		
		}
	}
	printf("%lld\n", res);
	return 0;
}
