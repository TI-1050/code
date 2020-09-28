#include <bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3f
#define N 100010
#define pii pair <int, int>
#define fi first
#define se second
int n, m, q, res, kase; 
struct Graph {
	struct node {
		int to, nx;
		node() {}
		node (int to, int nx) : to(to), nx(nx) {}
	}a[6 * N];
	int head[N], pos;
	void init() {
		memset(head, 0, sizeof head);
		pos = 0;
	}
	void add(int u, int v) {
		a[++pos] = node(v, head[u]); head[u] = pos;
		a[++pos] = node(u, head[v]); head[v] = pos;
	}
}G;
#define erp(u) for (int it = G.head[u], v = G.a[it].to; it; it = G.a[it].nx, v = G.a[it].to) 
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
int d[N], que[N], top, tail;
int BFS(int s, int t) {
	for (int i = 1; i <= n; ++i) d[i] = -1;
	d[s] = 0; top = 0; tail = 0;
	que[++top] = s; 
	while (d[t] < 0) {
		int u = que[tail]; ++tail; 
		erp(u) if (d[v] < 0) {
			d[v] = d[u] + 1;
			que[++top] = v;
		}
	}
	return d[t];
}

int vis[N], dis[N];
void DFS(int u, int fa, int deep) {
	erp(u) if (v != fa) {
		if (vis[v] < kase) {
			vis[v] = kase;
			dis[v] = deep + 1;
		} else {
			dis[v] = min(dis[v], deep + 1);
		}
		if (deep < 3) {
			DFS(v, u, deep + 1);  
		}
	}
}

void DFS2(int u, int fa, int deep) {
	erp(u) if (v != fa) {
		if (vis[v] == kase) {
			res = min(res, deep + 1 + dis[v]);
		}
		if (deep < 3) {
			DFS2(v, u, deep + 1);
		}
	}
}


int work(int s, int t) {
	res = INF; vis[s] = kase; dis[s] = 0;
	DFS(s, s, 0);
	if (vis[t] == kase) res = min(res, dis[t]);   
	DFS2(t, t, 0);
	if (res == INF) {
		res = BFS(s, t);
	}
	return res;
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		G.init();
		memset(fa, 0, sizeof fa);
		kase = 0;
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d%d", &u, &v);
			G.add(u, v);
			join(u, v);
		}
		int u, v;
		scanf("%d", &q);
		while (q--) {
			++kase; 
			scanf("%d%d", &u, &v); 
			if (find(u) != find(v)) {
				puts("-1");
			} else {
				printf("%d\n", work(u, v));
			}
		}
	}
	return 0;
}
