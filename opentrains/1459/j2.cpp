#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define N 210
#define INF 0x3f3f3f3f

int n, m, b;
vector<int> G[N];
int step;

int main() {
	srand(time(NULL));
	n = 200;
	cin >> m;
	for (int i = 1, u, v; i <= m; ++i) {
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	ll res = 0;
	int limit = 100;
	for (int cas = 1; cas <= limit; ++cas) {
		step = 0;
		int now = 1;
		while (true) {
			if (now == n || step > 10000000) break;
			int nxt = rand() % G[now].size();
			now = G[now][nxt];
			step++;
		}
		res += step;
	}
	cout << res / 100.0 << endl;
	return 0;
}
