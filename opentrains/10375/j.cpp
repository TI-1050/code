#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define pii pair <int, int>
#define fi first
#define se second
int n, m, q, u, v;
vector <vector<int>> G;
int fa[N];
int find(int x) {
	return fa[x] == 0 ? x : fa[x] = find(fa[x]);
}
void join(int x, int y) {
	int fx = find(x), fy = find(y);
	if (fx != fy) {
		fa[fx] = fy;
	}
}
map <pii, int> mp;
int used[N];  
vector <int> vec;
int BFS(int s, int t) {
	for (auto it : vec) used[it] = 0;
    vec.clear();	
	queue <pii> q;
	q.push(pii(s, 0));
	used[s] = 1; 
	vec.push_back(s);
	while (!q.empty()) {
		pii u = q.front(); q.pop();
		if (u.fi == t) {
			return u.se;
		}
		for (auto v : G[u.fi]) {
			if (!used[v]) {
				used[v] = 1;
				vec.push_back(v);
				q.push(pii(v, u.se + 1));
			}
		}
	}
}

int work(int s, int t) {
	
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		G.clear(); G.resize(n + 1);
		mp.clear();
		memset(used, 0, sizeof used);
		memset(fa, 0, sizeof fa);
		for (int i = 1; i <= m; ++i) {
			scanf("%d%d", &u, &v); 
			G[u].push_back(v);  
			G[v].push_back(u); 
			join(u, v);
		}
		scanf("%d", &q);
		while (q--) {
			scanf("%d%d", &u, &v);
			if (u == v) {
				puts("0");
			} else if (find(u) != find(v)) {
				puts("-1");
			} else {
				if (u > v) swap(u, v);
				if (mp.find(pii(u, v)) == mp.end()) {
					mp[pii(u, v)] = BFS(u, v);			
				} 
				printf("%d\n", mp[pii(u, v)]);
			}
		}
	}
	return 0;
}
