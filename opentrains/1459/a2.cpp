#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int MAXN = 1000;
const int MAXM = 1000000;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

struct Edge {
	int to, nxt;
	ll cap, flow;
   	ll cost;
	Edge() {}
	Edge(int to, int nxt, ll cap, ll flow, ll cost) : to(to), nxt(nxt), cap(cap), flow(flow), cost(cost) {}
}edge[MAXM << 1];

int n, m;
int head[MAXN], tot;
int pre[MAXN];
ll dis[MAXN], a[MAXN], b[MAXN];
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
			Min = min(Min, 1ll * edge[i].cap - edge[i].flow);
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
	while (~scanf("%d%d", &n, &m)) {
		Init();
		for (int i = 1; i <= n; ++i) {
			scanf("%lld", a + i);
		}
		int S = n + 1, T = n + 2;
		ll sum = 0;
		a[0] = -INFLL; a[n + 1] = INFLL;
		for (int i = 0; i <= n; ++i) {
			if (a[i] < a[i + 1]) {
				addedge(i, T, a[i + 1] - a[i], 0);
			} 
			if (a[i] > a[i + 1]) {
				addedge(S, i, a[i] - a[i + 1], 0);
				sum += a[i] - a[i + 1];
			}
		}
		char op[10];
		int l, c;
		for (int i = 1; i <= m; ++i) {
			scanf("%s %d %d", op, &l, &c);  
			for (int j = 0; j + l <= n; ++j) {
				if (op[0] == '+') addedge(j + l, j, INFLL, c);
	        	else addedge(j, j + l, INFLL, c);
			}
		}
		ll cost = 0;
		if (gao(S, T, cost) < sum) {
			puts("-1");
		} else {
			printf("%lld\n", cost);
		}
	}
	return 0;
}
