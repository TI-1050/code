#include <bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3f
//点数
#define N 4010

struct edge {
    int to, capacity, cost, rev;
    edge() {}
    edge(int to, int _capacity, int _cost, int _rev) : to(to), capacity(_capacity), cost(_cost), rev(_rev) {}
};

//时间复杂度O(F*ElogV)(F是流量, E是边数, V是顶点数)
struct Min_Cost_Max_Flow {
    int V, H[N + 5], dis[N + 5], PreV[N + 5], PreE[N + 5];
    vector<edge> G[N + 5];

    //调用前初始化
    void Init(int n) {
        V = n;
        for (int i = 0; i <= V; ++i)G[i].clear();
    }

    //加边
    void addedge(int from, int to, int cap, int cost) {
        G[from].push_back(edge(to, cap, cost, G[to].size()));
        G[to].push_back(edge(from, 0, -cost, G[from].size() - 1));
    }

    //flow是自己传进去的变量，就是最后的最大流，返回的是最小费用
    int Min_cost_max_flow(int s, int t, int f, int &flow) {
        int res = 0;
        fill(H, H + 1 + V, 0);
        while (f) {
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
            fill(dis, dis + 1 + V, INF);
            dis[s] = 0;
            q.push(pair<int, int>(0, s));
            while (!q.empty()) {
                pair<int, int> now = q.top();
                q.pop();
                int v = now.second;
                if (dis[v] < now.first)continue;
                for (int i = 0, sze = (int)G[v].size(); i < sze; ++i) {
                    edge &e = G[v][i];
                    if (e.capacity > 0 && dis[e.to] > dis[v] + e.cost + H[v] - H[e.to]) {
                        dis[e.to] = dis[v] + e.cost + H[v] - H[e.to];
                        PreV[e.to] = v;
                        PreE[e.to] = i;
                        q.push(pair<int, int>(dis[e.to], e.to));
                    }
                }
            }
            if (dis[t] == INF)break;
            for (int i = 0; i <= V; ++i)H[i] += dis[i];
            int d = f;
            for (int v = t; v != s; v = PreV[v])d = min(d, G[PreV[v]][PreE[v]].capacity);
            f -= d;
            flow += d;
            res += d * H[t];
            for (int v = t; v != s; v = PreV[v]) {
                edge &e = G[PreV[v]][PreE[v]];
                e.capacity -= d;
                G[v][e.rev].capacity += d;
            }
        }
        return res;
    }

    int Max_cost_max_flow(int s, int t, int f, int &flow) {
        int res = 0;
        fill(H, H + 1 + V, 0);
        while (f) {
            priority_queue<pair<int, int>> q;
            fill(dis, dis + 1 + V, -INF);
            dis[s] = 0;
            q.push(pair<int, int>(0, s));
            while (!q.empty()) {
                pair<int, int> now = q.top();
                q.pop();
                int v = now.second;
                if (dis[v] > now.first)continue;
                for (int i = 0, sze = (int)G[v].size(); i < sze; ++i) {
                    edge &e = G[v][i];
                    if (e.capacity > 0 && dis[e.to] < dis[v] + e.cost + H[v] - H[e.to]) {
                        dis[e.to] = dis[v] + e.cost + H[v] - H[e.to];
                        PreV[e.to] = v;
                        PreE[e.to] = i;
                        q.push(pair<int, int>(dis[e.to], e.to));
                    }
                }
            }
            if (dis[t] == -INF)break;
            for (int i = 0; i <= V; ++i)H[i] += dis[i];
            int d = f;
            for (int v = t; v != s; v = PreV[v])d = min(d, G[PreV[v]][PreE[v]].capacity);
            f -= d;
            flow += d;
            res += d * H[t];
            for (int v = t; v != s; v = PreV[v]) {
                edge &e = G[PreV[v]][PreE[v]];
                e.capacity -= d;
                G[v][e.rev].capacity += d;
            }
        }
        return res;
    }
} MCMF;

int n, k, s1, s2, t, a[N], flow;

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &k);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		s1 = 0, s2 = 1, t = 2 * n + 2;
		MCMF.Init(t);
		MCMF.addedge(s1, s2, k, 0);
		for (int i = 1; i <= n; ++i) {
			MCMF.addedge(s2, i << 1, 1, 0);
			MCMF.addedge(i << 1, i << 1 | 1, 1, -a[i]);
			MCMF.addedge(i << 1 | 1, t, 1, 0);
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j < i; ++j) {
				if (a[j] <= a[i]) {
					MCMF.addedge(j << 1 | 1, i << 1, 1, 0); 
				}
			}
		}
		printf("%d\n", -MCMF.Min_cost_max_flow(s1, t, INF, flow));
	}
    return 0;
}
