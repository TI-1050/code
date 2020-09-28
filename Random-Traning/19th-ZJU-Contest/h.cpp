#include <bits/stdc++.h>
using namespace std;

/*
   1.找出所有桥，注意处理重边
   2.去掉所有桥，缩点
   3.遍历所有桥，如果桥是重边，将桥连接的两个点并起来
   4.加入所有桥，建树
   

   判断：
   1.先判联通性，不连通，直接No
   2.再判断u和v或者w是否在同一个联通快
   3.再判断树上两条简单路径是否有交

*/
#define ll long long
#define N 200010
struct Edge {
	struct node {
		int to, nx;
		bool cut;
		node () {}
		node (int to, int nx) : to(to), nx(nx) {
			cut = false;
		}
	}a[N << 1];
	int head[N], pos;
	void init(int n) {
		for (int i = 0; i <= n; ++i) {
			head[i] = -1;
		}
		pos = 0;
	}
	void add(int u, int v) {
		a[pos] = node(v, head[u]); head[u] = pos++;
		a[pos] = node(u, head[v]); head[v] = pos++;
	}
}G[2];
#define erp(G, u) for (int it = G.head[u], v = G.a[it].to, cut = G.a[it].cut; ~it; it = G.a[it].nx, v = G.a[it].to, cut = G.a[it].cut)

int Low[N], DFN[N], Stack[N];
int Index, Top;
bool Instack[N];
void Tarjan(int u, int fa) {
	Low[u] = DFN[u] = ++Index;
	Stack[Top++] = u;
	Instack[u] = true;
	erp(G[0], u) if (v != fa) {
		if (!DFN[v]) {
			Tarjan(v, u);
			if (Low[u] > Low[v]) {
				Low[u] = Low[v];
			}
			if (Low[v] > DFN[u]) {
				G[0].a[it].cut = true;
				G[0].a[it ^ 1].cut = true;
			}
		} else if (Low[u] > DFN[v]) {
			Low[u] = DFN[v];
		}
	}
	Instack[u] = false;
	Top--;
}

int n, m, q;
int id[N], id_cnt;
map <ll, int> used, ismuledge;
bool Hash(int u, int v) {
	if (u > v) {
		swap(u, v);
	}
	ll t = 1ll * u * n + v;
	if (used.find(t) != used.end()) {
		ismuledge[t] = 1;
		return 0;
	} else {
		used[t] = 1;
		return 1;
	}
}
bool ismul(int u, int v) {
	if (u > v) {
		swap(u, v);
	}
	ll t = 1ll * u * n + v;
	if (ismuledge.find(t) != ismuledge.end()) {
		return 1;
	} else {
		return 0;
	}
}

int pre[N];
int find(int x) {
	return pre[x] == 0 ? x : pre[x] = find(pre[x]);
}
void join(int x, int y) {
	int fx = find(x), fy = find(y);
	if (fx != fy) {
		pre[fx] = fy;
	}
}

int fa[N], top[N], deep[N], sze[N], son[N], rt[N];
void DFS(int u) {
	sze[u] = 1;
	erp(G[1], u) if (v != fa[u]) {
		fa[v] = u;
		deep[v] = deep[u] + 1;
		rt[v] = rt[u];
		DFS(v);
		sze[u] += sze[v];
		if (!son[u] || sze[v] > sze[son[u]]) {
			son[u] = v;
		}
	}
}
void gettop(int u, int sp) {
	top[u] = sp;
	if (!son[u]) {
		return;
	}
	gettop(son[u], sp);
	erp(G[1], u) if (v != son[u] && v != fa[u]) {
		gettop(v, v);
	}
}
int lca(int u, int v) {
	while (top[u] != top[v]) {
		if (deep[top[u]] < deep[top[v]]) {
			swap(u, v);
		}
		u = fa[top[u]];
	}
	if (deep[u] > deep[v]) {
		swap(u, v);
	}
	return u;
}
bool ok(int a, int b, int c) {
	int t[] = {
		a, lca(a, c), lca(a, b), lca(b, c),
	};
	sort(t, t + 4, [](int x, int y) {
		return deep[x] < deep[y];		
	});
	if (t[2] == a && t[3] == a) {
		return true;
	} else {
		return false;
	}
}

void init(int n) {
	G[0].init(n); G[1].init(n);
	used.clear(); ismuledge.clear();
	for (int i = 0; i <= n; ++i) {
		Instack[i] = 0;
		son[i] = 0;
		fa[i] = -1;
		id[i] = -1;
		DFN[i] = 0;
		pre[i] = 0;
	}
	Index = Top = id_cnt = 0;
}
int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &m, &q); init(n);
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d%d", &u, &v);
			if (u == v) {
				continue;
			} else if (Hash(u, v)) {
				G[0].add(u, v);
			}
		}
		for (int i = 1; i <= n; ++i) if (!DFN[i]) {
			Tarjan(i, i);
		}
		for (int u = 1; u <= n; ++u) {
			erp(G[0], u) if (!cut || (cut && ismul(u, v))) {
				join(u, v); 
			}
		}
		for (int i = 1; i <= n; ++i) if (find(i) == i) {
			id[i] = ++id_cnt;
		}  
		for (int i = 1; i <= n; ++i) {
			id[i] = id[find(i)];
		}
		for (int u = 1; u <= n; ++u) {
			erp(G[0], u) if (cut && u <= v && !ismul(u, v)) {
				G[1].add(id[u], id[v]);
			}
		}
		for (int i = 1; i <= id_cnt; ++i) if (fa[i] == -1) {
			fa[i] = i;
			rt[i] = i;
			DFS(i);
			gettop(i, i);
		}
		for (int i = 1, u, v, w; i <= q; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			u = id[u], v = id[v], w = id[w];
			if (rt[u] != rt[v] || rt[u] != rt[w]) {
				puts("No");
			} else if (u == v || u == w) {
				puts("Yes");
			} else if (v == w) {
				puts("No");
			} else {
				puts(ok(u, v, w) ? "Yes" : "No");
			}
		}
	}
	return 0;
}
