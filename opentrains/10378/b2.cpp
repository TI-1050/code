#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 1e5 + 10;

struct Edge {
	int to, nxt, w;
	
	Edge() {}

	Edge(int to, int nxt, int w): to(to), nxt(nxt), w(w) {}
}edge[N << 1];

int k, b, s;
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

void pre() {
	for (int i = 1, x; i <= k; ++i) {
		int l = b + (i - 1) * s, r = b + i * s - 1;
		scanf("%d", &x);
		addedge(l - 1, r, -x);
		addedge(r, l - 1, x);
		Max = max(Max, r);
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
					if (vis[v] > Max + 1) return false;
				}
			}
		}
	}
	return true;
}

int main() {
	while (scanf("%d %d %d", &k, &b, &s) != EOF) {
		Init();
		pre();
		scanf("%d %d %d", &k, &b, &s);
		pre();
		for (int i = 1; i <= Max; ++i) addedge(i - 1, i, 0);
		puts(solve() ? "Yes" : "No");
	}
	return 0;
}
