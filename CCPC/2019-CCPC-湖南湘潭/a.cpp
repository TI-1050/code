#include <bits/stdc++.h>

using namespace std;

const int maxn = 510 * 510;
const int maxM = 1e6 + 10;
const int INF = 0x3f3f3f3f;

struct node{
	int x, y;
}a[maxn];

struct Edge{
	int to, nxt, cap, flow, cost;
}edge[maxM << 1];

int head[maxn], tot;
int pre[maxn], dis[maxn];
bool isAdd[maxn];
bool vis[maxn];
int N;

void Init(int n) {
	N = n;
	tot = 0;
	memset(head, -1, sizeof head);
}

void addedge(int u, int v, int cap, int cost) {
	edge[tot].to = v;
	edge[tot].cap = cap;
	edge[tot].cost = cost;
	edge[tot].flow = 0;
	edge[tot].nxt = head[u];
	head[u] = tot++;

	edge[tot].to = u;
	edge[tot].cap = 0;
	edge[tot].cost = -cost;
	edge[tot].flow = 0;
	edge[tot].nxt = head[v];
	head[v] = tot++;
}

bool SPFA(int s,int t) {
	queue<int>q;
	for (int i = 0; i < N; ++i) {
		dis[i] = INF;
		vis[i] = false;
		pre[i] = -1;
	}
	dis[s] = 0;
	vis[s] = true;
	q.push(s);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		vis[u] = false;
		for (int i = head[u]; ~i; i = edge[i].nxt) {
			int v = edge[i].to;
			if(edge[i].cap > edge[i].flow && dis[v] > dis[u] + edge[i].cost) {
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

int minCostMaxflow(int s, int t, int &cost) {
	int flow = 0;
	cost = 0;
	while(SPFA(s, t)) {
		int Min = INF;
		for (int i = pre[t]; ~i; i = pre[edge[i ^ 1].to]) {
			if(Min > edge[i].cap - edge[i].flow) {
				Min = edge[i].cap - edge[i].flow;
			}
		}
		for (int i = pre[t]; ~i; i = pre[edge[i ^ 1].to]) {
			edge[i].flow += Min;
			edge[i ^ 1].flow -= Min;
			cost += edge[i].cost * Min;			
		}
		flow += Min;
		for (int i = head[t]; ~i; i = edge[i].nxt) if(!isAdd[edge[i].to] && edge[i].cap == 1) {
			addedge(edge[i].to, t, 1, -edge[i].to);
			isAdd[edge[i].to] = 1;
		}
	}
	return flow;
}

int n, m;
map<int, vector<int> >mp1, mp2;
map<int, int>id1, id2;

int main() {
	scanf("%d", &n);
	int S = 0, T = n * 3 + 2;
	int cnt = n;
	for (int i = 1; i <= n; ++i) {
		scanf("%d %d", &a[i].x, &a[i].y);
		mp1[a[i].x].push_back(i);
		mp2[a[i].y].push_back(i);
	}
	scanf("%d", &m);
	Init(n * 3 + 2);
	for (int i = 1; i <= m; ++i) {
		char op;
		int x, k;
		scanf(" %c %d %d", &op, &x, &k);
		if(op == 'R') {
			if(mp1[x].size() == 0) continue;
			if(id1.find(x) == id1.end()) {
				id1[x] = ++cnt;
			}
			int id = id1[x];
			addedge(S, id, k, 0);
			for (auto &it : mp1[x]) {
				addedge(id, it, 1, 0);
			}
		} else {
			if(mp2[x].size() == 0) continue;
			if(id2.find(x) == id2.end()) {
				id2[x] = ++cnt;
			}
			int id = id2[x];
			addedge(S, id, k, 0);
			for (auto &it : mp2[x]) {
				addedge(id, it, 1, 0);
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		addedge(i, T, 1, 0);
	}
	int cost = 0;
	int flow = minCostMaxflow(S, T, cost);
	printf("%d\n", cost);
	return 0;
}
