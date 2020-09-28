#include <bits/stdc++.h>
using namespace std;

const int N = 510;
int n;
map<string, int> mp; int tot;
string s[2][N];
int getid(string s) {
	if (mp.count(s)) return mp[s];
	mp[s] = ++tot;
	return mp[s];
}

vector <vector<int>> G;
int d[N];
bool gao(int n) {
	memset(d, 0, sizeof d);
	G.clear(); G.resize(tot + 1);
	for (int i = 1; i <= n; ++i) {
		int u = getid(s[0][i]), v = getid(s[1][i]);
		++d[v];
		G[u].push_back(v);
	}
	int cnt = 0;
	queue <int> que; 
	for (int i = 1; i <= tot; ++i) if (!d[i]) que.push(i);
	while (!que.empty()) {
		int u = que.front(); que.pop();
		++cnt;
		for (auto &v : G[u]) {
			if (--d[v] == 0) {
				que.push(v);
			}
		}
	}
	return cnt != tot;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	while (cin >> n) {
		mp.clear(); tot = 0;
		for (int i = 1; i <= n; ++i) {
			cin >> s[0][i] >> s[1][i];
			getid(s[0][i]); getid(s[1][i]);
		}
		bool flag = 0;
		for (int i = 1; i <= n; ++i) {
			if (gao(i)) {
				cout << s[0][i] << " " << s[1][i] << "\n";
				flag = 1;
				break;
			}
		}
		if (!flag) cout << 0 << "\n";
	}
	return 0;
}
