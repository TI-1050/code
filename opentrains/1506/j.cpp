#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 510;

struct Dicnic {
	static const int M = 2e6 + 10;
	static const int N = 510;
	struct Edge {
		int to, nxt, flow;
		Edge () {}
		Edge (int _to, int _nxt, int _flow) {
			to = _to;
			nxt = _nxt;
			flow = _flow;
		}
	} edge[M];

	int S, T;
	int head[N], tot;
	int dep[N];

	void Init() {
		memset(head, -1, sizeof head);
		tot = 0;
	}

	void set(int _S, int _T) {
		S = _S;
		T = _T;
	}

	void addedge(int u, int v, int w, int rw = 0) {
		edge[tot] = Edge(v, head[u], w); head[u] = tot++;
		edge[tot] = Edge(u, head[v], rw); head[v] = tot++;
	}

	bool BFS() {
		memset(dep, -1, sizeof dep);
		queue<int>q;
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

	int DFS(int u, int f) {
		if (u == T || f == 0) return f;
		int w, used = 0;
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
	
	int solve() {
		int ans = 0;
		while (BFS()) {
			ans += DFS(S, INF);
		}
		return ans;
	}
}dicnic;

struct Hash {
	int a[MAXN], cnt;

	void Init() {
		cnt = 0;
	}

	void add(int x) {
		a[++cnt] = x;
	}

	void work() {
		sort(a + 1, a + 1 + cnt);
		cnt = unique(a + 1, a + 1 + cnt) - a - 1;
	}

	int get(int x) {
		return lower_bound(a + 1, a + 1 + cnt, x) - a - 1;
	}
}ha;

struct node {
	int p, k, c;

	void input() {
		scanf("%d %d %d", &p, &k, &c);
	}
}a[MAXN];

int n, m;

int main() {
	while (scanf("%d %d", &n, &m) != EOF) {
		dicnic.Init();
		ha.Init();
		int sum = 0;
		for (int i = 1; i <= n; ++i) {
			a[i].input();
			ha.add(a[i].p);ha.add(a[i].p + 1);
			ha.add(a[i].k - 1); ha.add(a[i].k); 
			sum += a[i].c;
		}
		ha.work();ha.add(ha.a[ha.cnt] + 1);
		int S = 0, T = n + ha.cnt + 1;
		dicnic.set(S, T);
		for (int i = 1; i < ha.cnt; ++i) {
			dicnic.addedge(n + i, T, (ha.a[i + 1] - ha.a[i]) * m);
		}
		for (int i = 1; i <= n; ++i) {
			dicnic.addedge(S, i, a[i].c);
			for (int j = 1; j < ha.cnt; ++j) {
				if (ha.a[j] >= a[i].p && ha.a[j + 1] <= a[i].k) {
					dicnic.addedge(i, j + n, ha.a[j + 1] - ha.a[j]);
				}
			}
		}
		int flow = dicnic.solve();
		sum -= flow;
		puts(sum ? "NO" : "YES");
	}	
	return 0;
}
