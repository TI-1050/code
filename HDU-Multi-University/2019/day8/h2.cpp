#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 1e4 + 10;
int n, m, k;
struct Graph {
	struct node {
		int to, nx, w;
		node() {}
		node(int to, int nx, int w) : to(to), nx(nx), w(w) {}
	}a[N << 1];
	int head[N], pos;
	void init(int n) {
		pos = 0;
		memset(head, 0, sizeof (head[0]) * (n + 1));
	}
	void add(int u, int v, int w) {
		a[++pos] = node(v, head[u], w); head[u] = pos;
		a[++pos] = node(u, head[v], w); head[v] = pos; 
	} 
}G;
#define erp(u) for (int it = G.head[u], v = G.a[it].to, w = G.a[it].w; it; it = G.a[it].nx, v = G.a[it].to, w = G.a[it].w) 

int vis[N], mx, ans;
void gao(int u, int cur, int res) {
	if (cur == k) {
		ans = max(ans, res);
		return;
	}
//	printf("%d %d %d\n", u, cur, res);
	if (res + (k - cur) * mx < ans) return;
	erp(u) if (!vis[v]) {
		vis[v] = 1;
		gao(v, cur + 1, res + w);
		vis[v] = 0;
	}
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &m, &k);
		G.init(n);
		mx = 0;
		for (int i = 1, u, v, w; i <= m; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			mx = max(mx, w);
			G.add(u, v, w);
		}
		ans = -1;
		memset(vis, 0, sizeof (vis[0]) * (n + 1));
		for (int i = 1; i <= n; ++i) {
			vis[i] = 1;
			gao(i, 1, 0);
			vis[i] = 0;
		//	cout << i << " " << ans << endl;	
		}
		if (ans == -1) puts("impossible");
		else printf("%d\n", ans);
	}
	return 0;
}
