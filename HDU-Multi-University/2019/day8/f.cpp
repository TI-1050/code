#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define ll long long 
#define pli pair <ll, int>
#define fi first 
#define se second  
const int N = 2e5 + 10; 
const ll INF = 0x3f3f3f3f3f3f3f3f;
ll ans, a[N], b[N]; 
int n;
vector <vector<int>> G;
//f表示最大值、次大值　g表示最小值、次小值
pli f[N][2], g[N][2]; 
int d[N], fa[N];
void DFS(int u) {
	if (d[u] == 1 && u != 1) {
		f[u][0] = pli(a[u] - b[u], u);
		f[u][1] = pli(-INF, -1);
		g[u][0] = pli(a[u] - b[u], u);
		g[u][1] = pli(INF, -1);
		return; 
	} else {
		f[u][0] = f[u][1] = pli(INF, -1);
		g[u][0] = g[u][1] = pli(-INF, -1);  
	}
	for (auto v : G[u]) if (v != fa[u]) {
		fa[v] = u; 
		DFS(v);
		//最大值的转移
		if (g[v][0].fi < f[u][0].fi) { 
			f[u][1] = f[u][0];
			f[u][0] = g[v][0];   
			f[u][0].se = v;  
		} else if (g[v][0].fi < f[u][1].fi) {
			f[u][1] = g[v][0];
			f[u][1].se = v;
		}
		//最小值的转移
		if (f[v][0].fi > g[u][0].fi) {
			g[u][1] = g[u][0];
			g[u][0] = f[v][0];
			g[u][0].se = v;
		} else if (f[v][0].fi > g[u][1].fi) {
			g[u][1] = f[v][0];
			g[u][1].se = v; 
		}
	}
	for (int i = 0; i < 2; ++i) { 
		if (f[u][i].fi != INF) {
			f[u][i].fi += a[u] - b[u];
		} else {
			f[u][i].fi = INF; 
		} 
		if (g[u][i].fi != -INF) {
			g[u][i].fi += a[u] - b[u];
		} else {
			g[u][i].fi = -INF;
		}
	}
}

//0最大值， 1最小值
ll h[N][2]; 
void DFS2(int u) {
	for (auto v : G[u]) if (v != fa[u]) {
		h[v][0] = h[u][1];
		h[v][1] = h[u][0];
		if (g[u][0].se == v) {
			h[v][0] = max(h[v][0], g[u][1].fi);
		} else {
			h[v][0] = max(h[v][0], g[u][0].fi);
		}
		if (f[u][0].se == v) {
			h[v][1] = min(h[v][1], f[u][1].fi);
		} else {
			h[v][1] = min(h[v][1], f[u][0].fi);
		}
		h[v][0] += a[v] - b[v];
		h[v][1] += a[v] - b[v];
		if (d[v] == 1) {
			ans = max(ans, h[v][0]);
		} else {
			ans = max(ans, min(h[v][0], f[v][0].fi));
		}
	//    cout << v << " " << ans << endl;	
		DFS2(v);
	}
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		G.clear(); G.resize(n + 1);
		for (int i = 1; i <= n; ++i) d[i] = 0;
		for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
		for (int i = 1; i <= n; ++i) scanf("%lld", b + i);
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
			++d[u]; ++d[v];
		}
		if (n == 1) {
			printf("%lld\n", a[1] - b[1]); 
			continue;
		} else if (n == 2) {
			printf("%lld\n", a[1] + a[2] - b[1] - b[2]);
			continue;
		}
		ans = -1e18; 
		fa[1] = 0;
		DFS(1);
	    ans = f[1][0].fi;	
		if (d[1] == 1) {
			h[1][0] = h[1][1] = a[1] - b[1];
		} else {
			h[1][0] = INF;
			h[1][1] = -INF;
		}
		DFS2(1);
		printf("%lld\n", ans); 
	}
	return 0;
}
