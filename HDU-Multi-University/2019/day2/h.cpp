#include <bits/stdc++.h>
using namespace std;

#define N 200010
#define db double
#define INFLL 0x3f3f3f3f3f3f3f3f
#define ll long long
int n, m;
struct Dicnic {
    struct Edge {
        int to, nxt;
        db flow;

        Edge() {}
    
        Edge(int to, int nxt, db flow) : to(to), nxt(nxt), flow(flow) {}
    } edge[N << 1];
    
    int head[N], tot;
    int dep[N];
    
    void Init() {
        memset(head, -1, sizeof head);
        tot = 0;
    }
    
    void addedge(int u, int v, db w, int rw = 0) {
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
    
	db DFS(int u, db f) {
        if (u == n || f == 0) return f;
        db w, used = 0;
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
    
    db solve() {
        db ans = 0;
        while (BFS()) {
            ans += DFS(1, INFLL);
        }
        return ans;
    }
}dicnic;  

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		dicnic.Init();
		int S = 1, T = n + 2;
		n += 2;
		ll sum = 0;
		for (int i = 1, u, v, A, B, C; i <= m; ++i) {
			scanf("%d%d%d%d%d", &u, &v, &A, &B, &C);
			++u, ++v;
			db a = (A + B) * 1.0 / 2;
			db c = (B + C) * 1.0 / 2;
			db e = (A + C) * 1.0 / 2 - B; 
			dicnic.addedge(S, u, a);
		   	dicnic.addedge(S, v, a);
			dicnic.addedge(u, T, c);
			dicnic.addedge(v, T, c);
			dicnic.addedge(u, v, e);
			dicnic.addedge(v, u, e);
			sum += A + B + C;	
		}
		printf("%lld\n", (ll)round(sum - dicnic.solve()));
	}
	return 0;	
}
