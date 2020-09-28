#include <bits/stdc++.h>
using namespace std;

const int N = 2e3 + 10;
const int INF = 0x3f3f3f3f;
int n, m, s, f[55][N], id[N]; char G[N][N];
struct node {
	char ch;
	int a, b, c, d;
	void scan(int i) { scanf(" %c%d%d%d%d", &ch, &a, &b, &c, &d); id[(int)ch] = i; }
	int get(int s) { return (a * s + b) % c + d; }
}a[N];
inline void chmin(int &x, int y) { if (x > y) x = y; }
int dis[N], used[N];
struct qnode {
	int u, w;
	qnode() {}
	qnode(int u, int w) : u(u), w(w) {}
	bool operator < (const qnode &other) const {
		return w > other.w;
	}
};
void Dijkstra() {
	for (int i = 1; i <= n; ++i) {
		dis[i] = INF; 
		used[i] = 0;
	}
	dis[1] = s;
	priority_queue <qnode> pq;
	pq.push(qnode(1, dis[1]));
	while (!pq.empty()) {
		int u = pq.top().u; pq.pop();
		if (used[u]) continue;
		used[u] = 1;
		for (int v = 1; v <= n; ++v) {
			if (G[u][v] == '.') continue;
			int Id = id[(int)G[u][v]];
		    int w = f[Id][dis[u] % a[Id].c];
			if (dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				pq.push(qnode(v, dis[v]));
			}	
		}
	}
	if (dis[n] == INF) dis[n] = -1;
	else dis[n] -= s;
	printf("%d\n", dis[n]);
}

int main() {
	while (scanf("%d%d%d", &n, &m, &s) != EOF) {
		for (int i = 1; i <= m; ++i) a[i].scan(i);
		for (int i = 1; i <= n; ++i) scanf("%s", G[i] + 1);
		for (int i = 1; i <= m; ++i) {
			for (int j = 0; j < a[i].c; ++j) {
				f[i][j] = a[i].get(j);
				for (int k = 0, o = j; k < a[i].c; ++k, o = (o + 1) % a[i].c) {
					chmin(f[i][j], a[i].get(o) + k);
				}
			}
		}
		Dijkstra();
	}
	return 0;
}
