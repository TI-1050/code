#include <bits/stdc++.h>
using namespace std;

#define N 1010
#define INF 0x3f3f3f3f
int n, m, S, T, K;
struct Graph {
	struct node {
		int to, nx, w;
		node() {}
		node (int to, int nx, int w) : to(to), nx(nx), w(w) {}
	}a[N << 1];
	int head[N], pos;
	void init() {
		pos = 0;
		memset(head, -1, sizeof head);
	}
	void add(int u, int v, int w) {
		a[pos] = node(v, head[u], w); head[u] = pos++; 
		a[pos] = node(u, head[v], w); head[v] = pos++; 
	}
}G;
#define erp(u) for (int it = G.head[u], v = G.a[it].to, w = G.a[it].w; ~it; it = G.a[it].nx, v = G.a[it].to, w = G.a[it].w)

struct node {
	int u, w, k;
	node() {}
	node(int u, int w, int k) : u(u), w(w), k(k) {}
	bool operator < (const node &other) const {
		return w > other.w; 
	}
};

int dist[N][N], used[N][N]; 
void Dijkstra() {
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j <= K; ++j) {
			dist[i][j] = INF;
			used[i][j] = 0;
		}
	dist[S][0] = 0;
	priority_queue <node> pq;
	pq.push(node(S, dist[S][0], 0));
	while (!pq.empty()) {
		int u = pq.top().u, k = pq.top().k; pq.pop();
		if (used[u][k]) continue;
		if (u == T) break;
		used[u][k] = 1;
		erp(u) if (dist[v][k] > dist[u][k] + w) {
			dist[v][k] = dist[u][k] + w;
			pq.push(node(v, dist[v][k], k));
		}
		if (k < K) {
			erp(u) if (dist[v][k + 1] > dist[u][k]) {
				dist[v][k + 1] = dist[u][k];
				pq.push(node(v, dist[v][k + 1], k + 1));
			}
		}
	}
	int res = INF;
	for (int i = 0; i <= K; ++i) res = min(res, dist[T][i]);
	printf("%d\n", res);
}

int main() {
	while (scanf("%d%d%d%d%d", &n, &m, &S, &T, &K) != EOF) {
		G.init();
		for (int i = 1, u, v, w; i <= m; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			if (u == v) continue; 
			G.add(u, v, w);
		}
		Dijkstra();
	}
	return 0;
}
