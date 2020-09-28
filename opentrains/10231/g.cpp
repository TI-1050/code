#include <bits/stdc++.h>

using namespace std;

typedef __int128 ll;

const int MAXN = 10000;
const int MAXM = 1000000;

struct Edge{
	int to, nxt, cap;
   	ll cost;
	
	Edge() {}

	Edge (int  _to, int _nxt, int _cap, ll _cost) {
		to = _to;
		nxt = _nxt;
		cap = _cap;
		cost = _cost;
	}
} edge[MAXM << 1];

int n;
int head[MAXN], tot;
int pre[MAXN], pe[MAXN];
ll dis[MAXN];
bool vis[MAXN];
int num[MAXN];
ll prize[MAXN];
ll INF = 1LL << 60;

void out(ll x) {
	if (x) {
		out(x / 10);
		printf("%d", (int)(x % 10));
	}
}

void Init() {
	tot = 0;
	memset(head, -1, sizeof head);
}

void addedge(int u,int v, int cap, ll cost) {
	edge[tot] = Edge(v, head[u], cap, cost); head[u] = tot++;
	edge[tot] = Edge(u, head[v], 0, -cost); head[v] = tot++;
}

bool SPFA(int S, int T) {
	queue<int> q;
	for (int i = 0; i <= T; ++i) {
		dis[i] = INF;
		pre[i] = -1;
		vis[i] = false;
	}
	dis[S] = 0;
	vis[S] = true;
	q.push(S);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		vis[u] = false;
		for (int i = head[u]; ~i; i = edge[i].nxt) {
			int v = edge[i].to;
			if (edge[i].cap && dis[v] > dis[u] + edge[i].cost) {
				dis[v] = dis[u] + edge[i].cost;
				pre[v] = u;
				pe[v] = i;
				if (!vis[v]) {
					vis[v] = true;
					q.push(v);
				}
			}
		}
	}
	return dis[T] < 0;
}

void solve(int S, int T) {
	ll cost = 0;
	while (SPFA(S, T)) {
		cost -= dis[T];
		for (int i = T; i != S; i = pre[i]) {
			edge[pe[i]].cap--;
			edge[pe[i] ^ 1].cap++;
		}
	}
	for (int i = 10; i >= 1; --i) {
		num[i] = cost % 1001;
		cost /= 1001;
	}
	for (int i = 1; i <= 10; ++i) {
		printf("%d%c", num[i], " \n"[i == 10]);
	}
	for (int i = 1; i <= n; ++i) {
		int res = 0;
		for (int j = head[i]; ~j; j = edge[j].nxt) {
			if (edge[j].to != S && (!edge[j].cap)) {
				res = edge[j].to - n;
				break;
			}
		}
		printf("%d%c", res, " \n"[i == n]);
	}
}

int main() {
	freopen("medals.in", "r", stdin);
	freopen("medals.out", "w", stdout);
	INF = INF * INF;
	prize[0] = 1ll;
	for (int i = 1; i <= 11; ++i) {
		prize[i] = prize[i - 1] * 1001;
	}
	while (scanf("%d", &n) != EOF) {
		Init();
		for (int i = 1, k, a, b; i <= n; ++i) {
			scanf("%d", &k);
			for (int j = 1; j <= k; ++j) {
				scanf("%d %d", &a, &b);
				addedge(i, a + n, 1, -prize[10 - b]);
			}
		}
		int S = 0, T = n + 1001;
		for (int i = 1; i <= n; ++i) {
			addedge(S, i, 1, 0);
		}
		for (int i = n + 1; i < T; ++i) {
			addedge(i, T, 1, 0);
		}
		solve(S, T);
	}
	return 0;
}
