#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define INFLL 0x3f3f3f3f3f3f3f3f
struct Dicnic {
	static const int M = 2e6 + 10;
	static const int N = 1e5 + 10;
    struct Edge {
        int to, nxt;
        ll flow;
        Edge() {}
        Edge(int to, int nxt, ll flow) : to(to), nxt(nxt), flow(flow) {}
    } edge[M];
	int n, S, T;
    int head[N], tot;
    int dep[N];
    void init(int n, int S, int T) {
		this->n = n;
		this->S = S;
		this->T = T;
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
        q.push(S);
        dep[S] = 1;
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
        return dep[T] >= 0;
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
            ans += DFS(S, INFLL);
        }
        return ans;
    }
}dicnic;

#define N 5010
int n, a[N];
bool isleft[N];
bool ispow2(int x) {
	return x && (x & (x - 1)) == 0;
}
int getbit(int x) {
	int res = 0;
	while (x) {
		res += x % 2;
		x /= 2;
	}
	return res & 1;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		int S = 0, T = n + 1; 
		dicnic.init(n + 1, S, T);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			isleft[i] = getbit(a[i]);
			if (isleft[i]) dicnic.addedge(S, i, 1);
			else dicnic.addedge(i, T, 1);
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j < i; ++j) {
				if (ispow2(a[i] ^ a[j])) {
					if (isleft[i]) dicnic.addedge(i, j, 1);
					else dicnic.addedge(j, i, 1);
				}
			}
		}
		//最大独立集点数 = N - 最大匹配数
		int num = n - dicnic.solve();
		vector <int> res;
		for (int i = 1; i <= n; ++i) {
			if (isleft[i]) {
				if (dicnic.dep[i] != -1) {
					res.push_back(a[i]);
				}
			} else {
				if (dicnic.dep[i] == -1) {
					res.push_back(a[i]); 
				}
			}
		}
		printf("%d\n", num);
		for (int i = 0; i < num; ++i)
			printf("%d%c", res[i], " \n"[i == num - 1]);
	}
	return 0;
}
