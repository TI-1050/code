#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 10;
int n, a[N], st[N], ed[N], pre[N], nx[N], cnt[N], f[N]; 
struct Hash {
	int a[N], cnt;
	void init() { cnt = 0; }
	void add(int x) { a[++cnt] = x; }
	void gao() {
		sort(a + 1, a + 1 + cnt);
		cnt = unique(a + 1, a + 1 + cnt) - a - 1;
	}
	int get(int x) { return lower_bound(a + 1, a + 1 + cnt, x) - a; }
}hs;

int main() {
//	freopen("gem.in", "r", stdin);
//	freopen("gem.out", "w", stdout);
	while (scanf("%d", &n) != EOF) { 
	   	hs.init();	
		for (int i = 1; i <= n; ++i) scanf("%d", a + i), hs.add(a[i]);
		hs.gao();
		for (int i = 1; i <= n; ++i) a[i] = hs.get(a[i]);
		memset(st, 0, sizeof st);
		memset(ed, 0, sizeof ed);
		for (int i = 1; i <= n; ++i) ed[a[i]] = i;
		for (int i = n; i >= 1; --i) st[a[i]] = i; 
		memset(cnt, 0, sizeof cnt);
		for (int i = 1; i <= n; ++i) {
			pre[i] = cnt[a[i] - 1]; 
			++cnt[a[i]];
		}
		memset(cnt, 0, sizeof cnt);
		for (int i = n; i >= 1; --i) {
			nx[i] = cnt[a[i] + 1];
			++cnt[a[i]];
		}
		memset(f, 0, sizeof f);
		int res = 0;
		for (int i = 1; i <= hs.cnt; ++i) { 
			if (ed[i - 1] < st[i]) {
				f[i] = cnt[i] + f[i - 1];
			} else {
				f[i] = cnt[i] + pre[st[i]];
			}
			res = max(res, f[i] + nx[ed[i]]);
		}
		printf("%d\n", n - res);
	}
	return 0;
}
