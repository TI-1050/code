#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 2e5 + 10;

struct Edge {
	int to, nxt;
   	ll w;

	Edge() {}

	Edge(int to, int nxt, ll w): to(to), nxt(nxt), w(w) {}
}edge[N << 1];

int n;
int mark[N];
int head[N], tot;
ll f[N][3];

void Init() {
	memset(head, -1, sizeof head);
	memset(mark, 0, sizeof mark);
	tot = 0;
}

void addedge(int u, int v, ll w) {
	edge[tot] = Edge(v, head[u], w); head[u] = tot++;
	edge[tot] = Edge(u, head[v], w); head[v] = tot++;
}

void gao(int u, int pre) {
	f[u][0] = f[u][1] = f[u][2] = 0;
	for (int i = head[u]; ~i; i = edge[i].nxt) {
		int v = edge[i].to, w = edge[i].w;
		if (v == pre) continue;
		gao(v, u);
		if (mark[u]) {
			for (int c = 0; c < 3; ++c) {
				if (c != mark[u]) f[u][c] += f[v][c];
				else {
					if (mark[u] == mark[v]) f[u][c] += f[v][c] + w;
					else f[u][c] += f[v][c];
				}
			}
		} else {
			if (mark[v]) {
				if (mark[v] == 1) {
					f[u][0] += f[v][0];
					f[u][1] += f[v][1] + w;
					f[u][2] += f[v][2];	
				} else if (mark[v] == 2) {
					f[u][0] += f[v][0];
					f[u][1] += f[v][0];
					f[u][2] += f[v][2] + w;
				}
			} else {
				for (int c = 0; c < 3; ++c) {
					f[u][c] += f[v][c] + w;
				}
			}
		}
	}
}

int main() {
	while (scanf("%d", &n) != EOF) {
		Init();
		ll sum = 0;
		for (int i = 1, u, v, w; i < n; ++i) {
			scanf("%d %d %d", &u, &v, &w);
			addedge(u, v, w);
			sum += w;
		}
		for (int cas = 1, m; cas <= 2; ++cas) {
			scanf("%d", &m);
			for (int i = 1, x; i <= m; ++i) {
				scanf("%d", &x);
				mark[x] = cas;
			}
		}
		gao(1, 1);
		ll res = sum - max(f[1][0], max(f[1][1], f[1][2]));
		printf("%lld\n", res);
	}
	return 0;
}
