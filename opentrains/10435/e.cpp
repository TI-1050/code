#include <bits/stdc++.h>
using namespace std;
 
#define N 100010
int n, m;
set <int> G[N];
 
bool ok()
{
	queue <int> q;
	int cnt = 0;
	for (int i = 1; i <= n; ++i)
		if ((int)G[i].size() == 2)
			q.push(i);
	while (!q.empty())
	{
		int u = q.front(); q.pop();
		if (G[u].size() != 2) continue;
		++cnt;
		int x = *G[u].begin();
		G[u].erase(x);
		int y = *G[u].begin(); 
		G[u].erase(y);
		G[x].erase(u);
		G[y].erase(u);
		if (G[x].find(y) != G[x].end())
		{
			if (G[x].size() == 2)
				q.push(x);
			if (G[y].size() == 2)
				q.push(y);
			continue;	
		}
		G[x].insert(y);
		G[y].insert(x); 
	}
	return cnt == n - 2;
}
 
int main()
{
	while (scanf("%d%d", &n, &m) != EOF)
	{
		for (int i = 1; i <= n; ++i) G[i].clear();
		for (int i = 1, u, v; i <= m; ++i)
		{
			scanf("%d%d", &u, &v);
			G[u].insert(v);
			G[v].insert(u);
		}
		puts(ok() ? "Yes" : "No");
	}
	return 0;
}
