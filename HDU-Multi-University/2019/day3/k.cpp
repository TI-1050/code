#include <bits/stdc++.h>
using namespace std;

#define N 200010
#define INF 0x3f3f3f3f 
#define pii pair <int, int>
#define fi first
#define se second
int n;
vector <vector<pii>> G;
pii res;
//f表示没有删边
//g表示删了一条边
pii f[N][3];
int g[N][3], h[N][3];

int fa[N], d[N];   
void DFS(int u) {
	for (auto it : G[u]) {
		int v = it.fi, w = it.se;  
		if (v == fa[u]) continue;    
		d[v] = w;
		fa[v] = u;
		DFS(v);

		//f的转移
		if (f[v][0].fi + w > f[u][0].fi) {
			f[u][2] = f[u][1];
			f[u][1] = f[u][0];
			f[u][0] = f[v][0];
			f[u][0].fi += w;
			f[u][0].se = v; 
		} else if (f[v][0].fi + w > f[u][1].fi) {
			f[u][2] = f[u][1];
			f[u][1] = f[v][0];
			f[u][1].fi += w;
			f[u][1].se = v;
		} else if (f[v][0].fi + w > f[u][2].fi) {
			f[u][2] = f[v][0];
			f[u][2].fi += w;
			f[u][2].se = v;
		}
	}
	g[u][0] = min(f[f[u][0].se][0].fi, max(f[f[u][0].se][1].fi, g[f[u][0].se][0]) + d[f[u][0].se]);
	g[u][1] = min(f[f[u][1].se][0].fi, max(f[f[u][1].se][1].fi, g[f[u][1].se][0]) + d[f[u][1].se]);	 
}

void DFS2(int u) {
	pii tmp = pii(min(max(f[u][0].fi, h[u][1]), max(h[u][0], max(g[u][0], f[u][1].fi))), u);
//	cout << tmp.fi << " " << tmp.se << endl;
	res = min(res, tmp);
	for (auto it : G[u]) {
		int v = it.fi;
		int w = it.se; 
		if (v == fa[u]) continue;
		if (f[u][0].se == v) {
			h[v][0] = max(h[u][0], f[u][1].fi) + w; 
			h[v][1] = max(h[u][0], max(f[u][2].fi, g[u][1])) + w;
			h[v][1] = min(h[v][1], max(h[u][1], f[u][1].fi) + w); 
			h[v][1] = min(h[v][1], max(h[u][0], f[u][1].fi));     
		} else {
			h[v][0] = max(h[u][0], f[u][0].fi) + w;
			if (f[u][1].se == v) {
				h[v][1] = max(h[u][0], max(f[u][2].fi, g[u][0])) + w; 
			} else {
				h[v][1] = max(h[u][0], max(f[u][1].fi, g[u][0])) + w; 
			}
			h[v][1] = min(h[v][1], max(h[u][0], f[u][0].fi));
			h[v][1] = min(h[v][1], max(h[u][1], f[u][0].fi) + w);
		}
		DFS2(v);
	}
}
	
void init() {
	G.clear(); G.resize(n + 1);
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < 3; ++j) {
			f[i][j] = pii(0, 0);
			g[i][j] = h[i][j] = 0;
		}
	}
}
int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n); init();
		for (int i = 1, u, v, w; i < n; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			G[u].push_back(pii(v, w));
			G[v].push_back(pii(u, w));
		}
		res = pii(INF, INF);
		fa[1] = 1;  
		DFS(1);
		DFS2(1);
		printf("%d %d\n", res.se, res.fi);
	}
	return 0;
}
