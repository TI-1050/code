#include <bits/stdc++.h>
using namespace std;
 
#define N 100010
#define pii pair <int, int>
int n, q, a[N], f[N], g[N];
pii ans[N];
 
void get(int x)
{
	if (ans[x].first != -1)
		return;
	int now = 1; 
	pii tmp = pii(0, 0);
	while (now <= n)
	{
//		printf("%d %d\n", x, now);
		++tmp.first;
		int r = min(now + x - 1, n);
		if (f[now] < r) 
			tmp.second += r - f[now]; 
		now = max(f[now], r) + 1;
	}
	ans[x] = tmp;
}
 
int main()
{
	while (scanf("%d", &n) != EOF)
	{
		for (int i = 1; i <= n; ++i) ans[i] = pii(-1, -1);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		for (int i = 2; i <= n; ++i)
		{
			if (a[i] < a[i - 1])
				g[i] = 0;
			else
				g[i] = 1;
		}
		int last = n; 
		f[n] = last;
		for (int i = n - 1; i >= 1; --i)
		{
			f[i] = last;
			if (g[i] != g[i + 1])
				last = i; 
		}
//		for (int i = 1; i <= n; ++i) printf("%d%c", f[i], " \n"[i == n]);
		scanf("%d", &q);
		int x;
		while (q--)
		{
			scanf("%d", &x); get(x);
			printf("%d %d\n", ans[x].first, ans[x].second);
		}
	}
	return 0;
}
