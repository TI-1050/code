#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int MAXN = 1100;
const int MAXM = 1100000;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

struct Edge {
	int to, nxt;
	ll cap, flow, cost;
	Edge() {}
	Edge(int to, int nxt, ll cap, ll flow, ll cost) : to(to), nxt(nxt), cap(cap), flow(flow), cost(cost) {}
}edge[MAXM << 1];

int n, m;
int a[MAXN], b[MAXN];
int head[MAXN], tot;
int pre[MAXN];
ll dis[MAXN];
bool vis[MAXN];

void Init() {
	tot = 0;
	memset(head, -1, sizeof head);
}

void addedge(int u,int v,ll cap, ll cost) {
	edge[tot] = Edge(v, head[u], cap, 0, cost); head[u] = tot++;
	edge[tot] = Edge(u, head[v], 0, 0, -cost); head[v] = tot++;
}

bool SPFA(int s,int t) {
	queue<int>q;
	for (int i = 0; i <= n + 2; ++i) {
		dis[i] = INFLL;
		vis[i] = false;
		pre[i] = -1;
	}
	dis[s] = 0;
	q.push(s);
	vis[s] = true; 
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		vis[u] = false;
		for (int i = head[u]; ~i; i = edge[i].nxt) {
			int v = edge[i].to;
			if (edge[i].cap > edge[i].flow && dis[v] > dis[u] + edge[i].cost) {
				dis[v] = dis[u] + edge[i].cost;
				pre[v] = i;
				if(!vis[v]) {
					vis[v] = true;
					q.push(v);
				}
			}	
		}
	}
	return pre[t] != -1;
}

ll gao(int s, int t, ll &cost) {
	ll flow = 0;
	cost = 0;
	while (SPFA(s, t)) {
		ll Min = INFLL;
		for (int i = pre[t]; ~i; i = pre[edge[i ^ 1].to]) {
			Min = min(Min, edge[i].cap - edge[i].flow);
		}
		for (int i = pre[t]; ~i; i = pre[edge[i ^ 1].to]) {
			edge[i].flow += Min;
			edge[i ^ 1].flow -= Min;
			cost += edge[i].cost * Min;
		}
		flow += Min;
	}
	return flow;
}

int main() {
	while (~scanf("%d %d", &n, &m)) {
		Init();
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		int S = 0, T = n + 2;
		ll sum = 0; 
		addedge(n + 1, T, INFLL, 0);
		addedge(1, T, INFLL, 0);
		for (int i = 2; i <= n; ++i) {
			b[i] = a[i] - a[i - 1];
			if (b[i] < 0) {
				addedge(S, i, -b[i], 0);
				sum += -b[i];
			} else if (b[i] > 0) {
				addedge(i, T, b[i], 0);
			}
		}
		char op[10];
		int l, c;
		for (int i = 1; i <= m; ++i) {
			scanf(" %s %d %d", op, &l, &c);  
			if (op[0] == '+') {
				for (int j = n + 1; j - l >= 1; --j) {
					addedge(j, j - l, INFLL, c);
				}
			} else {
				for (int j = 1; j + l <= n + 1; ++j) {
					addedge(j, j + l, INFLL, c);
				}
			}
		}
		ll cost = 0;
		ll flow = gao(S, T, cost);
		if (flow < sum) {
			puts("-1");
		} else {
			printf("%lld\n", cost);
		}
	}
	return 0;
}
