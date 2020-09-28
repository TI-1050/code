#include <bits/stdc++.h>

using namespace std;

const int N = 5e3 + 10;
const int M = 2e5 + 10;

struct Edge {
	int to, nxt;

	Edge() {}

	Edge(int to, int nxt): to(to), nxt(nxt) {}
} edge[M << 1];

int head[N], tot;

void Init() {
	tot = 0;
	memset(head, -1, sizeof head);
}

void addedge(int u, int v) {
	edge[tot] = Edge(v, head[u]); head[u] = tot++;
}

struct node {
	string name;
	int version;

	node() {}

	node(string name, int version): name(name), version(version) {}

	bool operator < (const node &other) const {
		if (name == other.name) return version < other.version;
		else return name < other.name;
	}
};

int n, k;
string app[N];
map<string, int> mp;
vector<vector<node> > G;
vector<vector<int>> version;
map<node, int> has;
int vis[N];
int linker[N];
bool used[M];
int res[N];
int uN;

bool DFS(int u) {
	for (int i = head[u]; ~i; i = edge[i].nxt) {
		int v = edge[i].to;
		if (!used[v]) {
			used[v] = true;
			if (linker[v] == -1 || DFS(linker[v])) {
				linker[v] = u;
				return true;
			}
		}
	}
	return false;
}

int gao() {
	int res = 0;
	memset(linker, -1, sizeof linker);
	for (int u = 1; u <= uN; ++u) {
		if (vis[u]) {
			res++;
			continue;
		}
		memset(used, false, sizeof used);
		if (DFS(u)) res++;
	}
	return res;
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	while (cin >> n) {
		Init();
		has.clear();
		memset(vis, 0, sizeof vis);
		version.clear();
		version.resize(n + 1);
		for (int i = 1, m, v; i <= n; ++i) {
			cin >> app[i];
			mp[app[i]] = i;
			cin >> m;
			for (int j = 1; j <= m; ++j) {
				cin >> v;
				version[i].push_back(v);
			}
		}
		cin >> k;
		G.clear();
		G.resize(k + 1);
		for (int i = 1, m, v; i <= k; ++i) {
			cin >> m;
			for (int j = 1; j <= m; ++j) {
				string name;
				cin >> name >> v;
				G[i].push_back(node(name, v));
				addedge(mp[name], i + n);
				has[node(name, v)]++;
			}
		}
		for (int i = 1; i <= n; ++i) {
			bool F = false;
			for (auto &v : version[i]) {
				if (has.count(node(app[i], v)) == 0) {
					F = true;
					res[i] = v;
					break;
				}
			}
			if (F) {
				vis[i] = 1;
			}
		}
		uN = n;
		int S = gao();
		if (S != n) {
			puts("No");
		} else {
			puts("Yes");
			for (int i = 1; i <= k; ++i) {
				if (linker[i + n] != -1) {
					for (auto it : G[i]) {
						if (mp[it.name] == linker[i + n]) {
							res[linker[i + n]] = it.version;
							break;
						}
					}
				}
			}
			for (int i = 1; i <= n; ++i) {
				printf("%d%c", res[i],  " \n"[i == n]);
			}
		}
	}
	return 0;
}
