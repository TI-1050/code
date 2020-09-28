#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200010
int n, q, c[N];
ll res[N];
vector <vector<int>> G;
set <int> se[N];

int fa[N], deep[N], sze[N], son[N], top[N], in[N], fin[N], cnt;  
void DFS(int u) {
	for (auto v : G[u]) if (v != fa[u]) {
		fa[v] = u;
		deep[v] = deep[u] + 1;
		DFS(v);
		sze[u] += sze[v];
		if (!son[u] || sze[v] > sze[son[u]]) {
			son[u] = v;   
		}
	}
}
void gettop(int u, int tp) {
	top[u] = tp;
	in[u] = ++cnt;  
	fin[cnt] = u;
	if (!son[u]) return;
	gettop(son[u], tp);
	for (auto v : G[u]) {
		if (v != fa[u] && v != son[u]) {
			gettop(v, v); 
		}
	}
}
int lca(int u, int v) {
	while (top[u] != top[v]) {
		if (deep[top[u]] < deep[top[v]]) {
			swap(u, v);
		}
		u = fa[top[u]];
	}
	if (deep[u] > deep[v]) swap(u, v);
	return u;
}

int dis(int u, int v) {
	return deep[u] + deep[v] - 2 * deep[lca(u, v)];
}

void add(int k, int u) {
	se[k].insert(in[u]);
	int sze = (int)se[k].size();
	if (sze == 1) return;
	//如果原来只有一个点
	if (sze == 2) {
		auto pos = se[k].begin();
		auto nx = next(pos);
		res[k] += 2 * dis(fin[*pos], fin[*nx]);  
	} else {
		auto pos = se[k].lower_bound(in[u]);
	    auto nx = next(pos);	
		//加入的点是第一个点
		if (pos == se[k].begin()) {
			auto End = se[k].rbegin();
			res[k] -= dis(fin[*nx], fin[*End]);   
			res[k] += dis(fin[*pos], fin[*End]);
			res[k] += dis(fin[*pos], fin[*nx]);    
		//加入的点是最后一个点  
		} else if (nx == se[k].end()) {
			auto Begin = se[k].begin();
			auto pre = prev(pos);
			res[k] -= dis(fin[*pre], fin[*Begin]); 
			res[k] += dis(fin[*pos], fin[*pre]);
		    res[k] += dis(fin[*pos], fin[*Begin]);	
		//加入的点是中间点 
		} else {
			auto pre = prev(pos);
			res[k] -= dis(fin[*pre], fin[*nx]);
			res[k] += dis(fin[*pre], fin[*pos]);
			res[k] += dis(fin[*pos], fin[*nx]);
		}
	}
}

void del(int k, int u) {
	int sze = (int)se[k].size();
	//如果此时只有一个点 
	if (sze <= 2) {
		res[k] = 0;
		se[k].erase(in[u]);
	} else {
		auto pos = se[k].lower_bound(in[u]);
		auto nx = next(pos);
		//删除的点是第一个点
		if (pos == se[k].begin()) {
			auto End = se[k].rbegin();
			res[k] -= dis(fin[*pos], fin[*End]);
			res[k] -= dis(fin[*pos], fin[*nx]);
			res[k] += dis(fin[*nx], fin[*End]);
		//删除的点是最后一个点
		} else if (nx == se[k].end()) {
			auto Begin = se[k].begin();
			auto pre = prev(pos);    
			res[k] -= dis(fin[*pos], fin[*pre]);
			res[k] -= dis(fin[*pos], fin[*Begin]);
			res[k] += dis(fin[*pre], fin[*Begin]);
		//删除的点是中间点
		} else {
			auto pre = prev(pos);
			res[k] -= dis(fin[*pre], fin[*pos]);
			res[k] -= dis(fin[*pos], fin[*nx]);
			res[k] += dis(fin[*pre], fin[*nx]);
		}
		se[k].erase(in[u]);  
	}
}


void init() {
	cnt = 0;
	G.clear(); G.resize(n + 1);
	memset(son, 0, sizeof son);
	memset(res, 0, sizeof res);
	for (int i = 1; i <= 100000; ++i) {
		se[i].clear();
	}
}
int main() {
	while (scanf("%d", &n) != EOF) {
		init();
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		for (int i = 1; i <= n; ++i) {
			scanf("%d", c + i);
		}
		DFS(1);	gettop(1, 1);
		for (int i = 1; i <= n; ++i) {
			add(c[i], i);
		}
		scanf("%d", &q);
		char op[10]; int x, y;
		while (q--) {
			scanf("%s%d", op, &x);
			switch(op[0]) {
				case 'U' :
					scanf("%d", &y);
					del(c[x], x);
					c[x] = y; 
					add(c[x], x);		
					break;
				case 'Q' :
					if (se[x].empty()) puts("-1");
					else {
						printf("%lld\n", res[x] / 2);
					}
					break;
				default :
					assert(0);
			}
		}
	}
	return 0;
}
