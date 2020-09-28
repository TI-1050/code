#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 1e5 + 10;

struct Edge {
	int to, nxt, w;
	
	Edge() {}

	Edge(int to, int nxt, int w): to(to), nxt(nxt), w(w) {}
}edge[N << 1];

int k[2], b[2], s[2];
int Max;
int head[N], tot;
int vis[N], inq[N];
ll dis[N];

void Init() {
	memset(head, -1, sizeof head);
	tot = Max = 0;
}

void addedge(int u, int v, int w) {
	edge[tot] = Edge(v, head[u], w); head[u] = tot++;
}

void pre(int k, int b, int s) {
	for (int i = 1, x; i <= k; ++i) {
		int l = b + (i - 1) * s, r = b + i * s - 1;
		scanf("%d", &x);
		addedge(l - 1, r, -x);
		addedge(r, l - 1, x);
		Max = max(Max, r + 1);
	}
}

bool solve() {
	memset(vis, 0, sizeof vis);
	memset(inq, 0, sizeof inq);
	memset(dis, 0x3f, sizeof dis);
	queue<int> q;
	q.push(0);
	dis[0] = 0, vis[0] = 1, inq[0] = 1;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		inq[u] = 0;
		for (int i = head[u]; ~i; i = edge[i].nxt) {
			int v = edge[i].to, w = edge[i].w;
			if (dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				if (!inq[v]) {
					inq[v] = 1;
					q.push(v);
					++vis[v];
					if (vis[v] > Max + 5) return false;
				}
			}
		}
	}
	return true;
}

int main() {
	while (scanf("%d %d %d", k, b, s) != EOF) {
		Init();
		pre(k[0], b[0], s[0]);
		scanf("%d %d %d", k + 1, b + 1, s + 1);
		pre(k[1], b[1], s[1]);
		for (int i = 1; i <= Max; ++i) addedge(i - 1, i, 0);
		addedge(0, b[0] - 1, 0);
		addedge(b[0] - 1, 0, 0);
		addedge(0, b[1] - 1, 0);
		addedge(b[1] - 1, 0, 0);
		addedge(Max, b[0] + k[0] * s[0] - 1, 0);
		addedge(Max, b[1] + k[1] * s[1] - 1, 0);
		addedge(b[0] + k[0] * s[0] - 1, Max, 0);
		addedge(b[1] + k[1] * s[1] - 1, Max, 0);
		puts(solve() ? "Yes" : "No");
	}
	return 0;
}
