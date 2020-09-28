#include <bits/stdc++.h>
using namespace std;
 
#define N 200010
int n, C, q, f[N], g[N], h[N], num[N];
vector <int> G[N];
 
int fa[N], sze[N], son[N], top[N], p[N], cnt;
void DFS(int u)
{
	sze[u] = 1;
	for (auto v : G[u]) if (v != fa[u])
	{
		fa[v] = u;
		DFS(v);
		sze[u] += sze[v];
		if (!son[u] || sze[v] > sze[son[u]])
			son[u] = v;
	}
}
 
void gettop(int u, int sp)
{
	top[u] = sp;  
	p[u] = ++cnt;
	if (son[u] == 0)
		return;
	gettop(son[u], sp);
	for (auto v : G[u]) if (v != fa[u] && v != son[u])
		gettop(v, v);
}
 
void calc(int c, int tot, int vis)
{
	if (c == 0) return;
	--g[num[c]];
	num[c] += vis * tot;
	++g[num[c]];
}
 
void add(int l, int r, int c)
{
	int Max = 0, color = -1;
	for (int i = l; i <= r; i = f[i] + 1)
	{
		Max = f[i]; 
		color = h[i];
		int nx = min(r, f[i]); 
		calc(h[i], nx - i + 1, -1);
		h[i] = c;
		calc(h[i], nx - i + 1, 1);
	}
	f[l] = r; 
	if (Max > r) 
	{
		f[r + 1] = Max;
		h[r + 1] = color;	
	}
}
 
void work(int u, int c)
{
	while (top[u] != 1)
	{
		
		add(p[top[u]], p[u], c);
		u = fa[top[u]];	  
	}
	if (u == 1) return;
	add(p[son[1]], p[u], c);
}
 
int main()
{
	while (scanf("%d%d%d", &n, &C, &q) != EOF)
	{
		memset(num, 0, sizeof num); 
		memset(h, 0, sizeof h);
		memset(g, 0, sizeof g);
		memset(son, 0, sizeof son); 
		cnt = 0;
	    g[0] = C; 	
		for (int i = 1; i <= n; ++i) f[i] = i; 
		for (int i = 1; i <= n; ++i) G[i].clear();
		for (int i = 1, u, v; i < n; ++i)
		{
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		fa[1] = 1;
		DFS(1); gettop(1, 1);
		int u, c, m;
		while (q--)
		{
			scanf("%d%d%d", &u, &c, &m); 
			work(u, c);
			printf("%d\n", g[m]);
		}
	}
	return 0;
}
