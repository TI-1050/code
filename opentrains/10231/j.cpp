#include <bits/stdc++.h>
using namespace std;

#define pii pair <int, int>
#define fi first
#define se second
const int N = 100;
vector <vector<pii>> vec;
int n, cnt[N][N], vis[N][N];

int main() {
	freopen("snakes2.in", "r", stdin);
	freopen("snakes2.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	while (cin >> n) {
		vec.clear(); vec.resize(n + 1);
		memset(cnt, 0, sizeof cnt);
		memset(vis, 0, sizeof vis);
		for (int i = 1, m; i <= n; ++i) {
			cin >> m;
			vec[i].resize(m);
			for (auto &it : vec[i]) {
				cin >> it.fi >> it.se;
				++cnt[it.fi][it.se];
			}  
		}
		for (int i = 1; i <= n; ++i) {
			for (auto it : vec[i]) {
				if (cnt[it.fi][it.se] >= 2) {
					cout << (vis[it.fi][it.se] ? "+" : "-");
					++vis[it.fi][it.se]; 
				}
			}
			cout << "\n";
		}
	}
	return 0;
}
