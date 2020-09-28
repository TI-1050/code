#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define N 40

int n, m;
int v[N][N];
int vis[N];
ll ans;

void DFS(int pos, int cnt) {
	if (pos > n) {
		if (cnt) {
			return ;
		}
		ll res = 0;
		for (int i = 1; i <= n; ++i) {
			if (!vis[i]) {
				continue;
			}
			for (int j = 1; j <= n; ++j) {
				if (vis[j]) {
					continue;
				}
				res += v[i][j];
			}
		}
		ans = max(ans, res);
		return;
	}
	// 1
	if (cnt == n - pos + 1) {
		vis[pos] = 1;
		DFS(pos + 1, cnt - 1);
		return ;
	}
	if (cnt) {
		vis[pos] = 1;
		DFS(pos + 1, cnt - 1);
	}
	//0
	vis[pos] = 0;
	DFS(pos + 1, cnt);
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
	DFS(1, m);
	printf("%lld\n", ans);
	return 0;	
}
