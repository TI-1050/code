#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 20010
#define INFLL 0x3f3f3f3f3f3f3f3f
#define pii pair <int, int>
#define fi first
#define se second
int n, m;
int e[N][3];
vector <vector<pii>> G;

struct Dicnic {
    struct Edge {
        int to, nxt;
        ll flow;
        Edge() {}
        Edge(int to, int nxt, ll flow) : to(to), nxt(nxt), flow(flow) {}
    } edge[N << 1];
    
    int head[N], tot;
    int dep[N];
    
    void Init() {
        memset(head, -1, sizeof head);
        tot = 0;
    }
    
    void addedge(int u, int v, int w, int rw = 0) {
        edge[tot] = Edge(v, head[u], w);
        head[u] = tot++;
        edge[tot] = Edge(u, head[v], rw);
        head[v] = tot++;
    }
    
    bool BFS() {
        memset(dep, -1, sizeof dep);
        queue<int> q;
        q.push(1);
        dep[1] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = head[u]; ~i; i = edge[i].nxt) {
                if (edge[i].flow && dep[edge[i].to] == -1) {
                    dep[edge[i].to] = dep[u] + 1;
                    q.push(edge[i].to);
                }
            }
        }
        return dep[n] >= 0;
    }
    
    ll DFS(int u, ll f) {
        if (u == n || f == 0) return f;
        ll w, used = 0;
        for (int i = head[u]; ~i; i = edge[i].nxt) {
            if (edge[i].flow && dep[edge[i].to] == dep[u] + 1) {
                w = DFS(edge[i].to, min(f - used, edge[i].flow));
                edge[i].flow -= w;
                edge[i ^ 1].flow += w;
                used += w;
                if (used == f) return f;
            }
        }
        if (!used) dep[u] = -1;
        return used;
    }
    
    ll solve() {
        ll ans = 0;
        while (BFS()) {
            ans += DFS(1, INFLL);
        }
        return ans;
    }
} dicnic;

struct node {
	int u; ll w;
	node() {}
	node (int u, ll w) : u(u), w(w) {}
	bool operator < (const node &other) const {
		return w > other.w;
	}
};
ll dist[N]; bool used[N];
void Dijkstra() {
	for (int i = 1; i <= n; ++i) {
		dist[i] = INFLL;
		used[i] = 0;
	}
	dist[1] = 0;
	priority_queue <node> pq;
	pq.push(node(1, 0));
	while (!pq.empty()) {
		int u = pq.top().u; pq.pop();
		if (used[u]) continue;
		used[u] = 1;
		for (auto it : G[u]) {
			int v = it.fi, w = it.se;
			if (dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				pq.push(node(v, dist[v]));
			}
		}
	}
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		G.clear(); G.resize(n + 1);
		for (int i = 1; i <= m; ++i) {
			int &u = e[i][0], &v = e[i][1], &w = e[i][2];
			scanf("%d%d%d", &u, &v, &w);
			G[u].push_back(pii(v, w));
		}
		Dijkstra();
		dicnic.Init();
		for (int i = 1; i <= m; ++i) {
			int u = e[i][0], v = e[i][1], w = e[i][2];
			if (dist[v] == dist[u] + w) {
				dicnic.addedge(u, v, w);
			}
		}
		printf("%lld\n", dicnic.solve());
	}
	return 0;
}
