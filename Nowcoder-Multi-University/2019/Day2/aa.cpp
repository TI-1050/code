#include <bits/stdc++.h>

using namespace std;

#define N 100

int n, m;
int vis[N];
double dp[N];

void DFS(int pos, int cnt, double p) {
	if (cnt > 25) return ;
	for (int i = 0; i < n; ++i) {
		if (!vis[i]) {
			int l = (pos - 1 + n) % n;
			int r = (pos + 1) % n;
			vis[l]++;
			DFS(l, cnt + 1, p * 0.5);
			vis[l]--;
			vis[r]++;
			DFS(r, cnt + 1, p * 0.5);
			vis[r]--;
			return ;
		}
	}
	dp[pos] += p;
}

int main() {
	while (~scanf("%d %d", &n, &m)) {
		memset(vis, 0, sizeof vis);
		memset(dp, 0, sizeof dp);
		vis[0] = 1;
		DFS(0, 0, 1.0);
		cout << dp[m] << endl;	
	}
	return 0;
}
