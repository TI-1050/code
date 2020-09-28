#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define N 40

int n, m;
int v[N][N];
int vis[N];
ll ans;
vector<int> v1, v2;

void DFS(int pos, int cnt) {
	if (pos > n) {
		if (cnt) {
			return ;
		}
		ll res = 0;
		for (auto i : v1) {
			for (auto j : v2) {
				res += v[i][j];
			}
		}
		ans = max(ans, res);
		return;
	}
	// 1
	if (cnt == n - pos + 1) {
		v1.push_back(pos);
		DFS(pos + 1, cnt - 1);
		v1.pop_back();
		return ;
	}
	if (cnt) {
		v1.push_back(pos);
		DFS(pos + 1, cnt - 1);
		v1.pop_back();
	}
	//0
	v2.push_back(pos);
	DFS(pos + 1, cnt);
	v2.pop_back();
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
