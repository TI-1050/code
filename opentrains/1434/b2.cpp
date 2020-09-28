#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair <int, int>
#define fi first
#define se second
const int N = 5e5 + 10;
int n, m, d[N];
struct node {
	int a, b, c, has;
	node() {}
	node(int a, int b, int c) : a(a), b(b), c(c) { 
		has = 1; 
	}
	bool operator < (const node &other) const {
		return c < other.c;
	}
}e[N];

int fa[N], sze[N];
vector < vector <int> > G;
vector < vector <int> > vec; 
int find(int x) {
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void merge(int x, int y, int c) {
	x = find(x), y = find(y);
	if (x == y) {
		vec[x].push_back(c);
	} else if (x != y) {
		if (vec[x].size() > vec[y].size()) swap(vec[x], vec[y]);
		fa[x] = y; 
		for (auto it : vec[x]) vec[y].push_back(it);
		vec[y].push_back(c);
		sze[y] += sze[x]; 
	}
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		vec.clear(); vec.resize(n + 1);
		G.clear(); G.resize(n + 1);
		for (int i = 1; i <= n; ++i) fa[i] = i, sze[i] = 1, d[i] = 0;   
		for (int i = 1, a, b, c; i <= m; ++i) {
			scanf("%d%d%d", &a, &b, &c);
			e[i] = node(a, b, c);  
			G[a].push_back(i);
			G[b].push_back(i);  
			++d[a]; ++d[b]; 
		} 
		ll res = 0;
		set <pii> se;
		for (int i = 1; i <= n; ++i) se.insert(pii(d[i], i));
		while (!se.empty()) { 
			pii t = *se.begin(); se.erase(se.begin());
			if (t.fi > 1) break;
			--t.fi;
			for (auto it : G[t.se]) {
				if (e[it].has == 0) continue;
				int u = e[it].a, v = e[it].b, c = e[it].c;
				if (u != t.fi) swap(u, v);
				if (c < 0) res += c; 
				e[it].has = 0;
				se.erase(pii(d[v], v));
				--d[v];
				se.insert(pii(d[v], v));
			}
		}
		for (int i = 1; i <= m; ++i) if (e[i].has) {
			merge(e[i].a, e[i].b, e[i].c);
		}
		for (int i = 1; i <= n; ++i) if (fa[i] == i) {
			sort(vec[i].begin(), vec[i].end());
			int _n = sze[i], _m = vec[i].size();
		//	cout << i << " " << _n << " " << _m << endl;
			for (int j = 0; j < _m - _n + 1; ++j) {
				res += vec[i][j];
			}
			for (int j = _m - _n + 1; j < _m; ++j) {
				if (vec[i][j] < 0) res += vec[i][j];
				else break;
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
