#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pLI = pair <ll, int>;
#define fi first
#define se second
const int N = 1e5 + 10;
int n, id[N], pos[2]; 
ll f[N], g[N], pre[N], suf[N], a[N], res; 
void gao() {
	pre[0] = 0;
	for (int i = 1; i <= n; ++i) {
		pre[i] = pre[i - 1] + a[i];
	}
	suf[n + 1] = 0;
	g[n + 1] = 0;
	for (int i = n; i >= 1; --i) {
		suf[i] = suf[i + 1] + a[i];
		g[i] = min(g[i + 1], suf[i]);
	}
	int Max_pos = 1;
	pLI t = pLI(pre[1], 1);
	for (int i = 2; i <= n; ++i) { 
		if (pre[i - 1] - t.fi + a[t.se] + suf[i + 1] - g[i + 1] > res) {
			res = pre[i - 1] - t.fi + a[t.se] + suf[i + 1] - g[i + 1];
			pos[0] = id[t.se];
			pos[1] = id[i];
		}
		if (a[Max_pos] - pre[i] > a[t.se] - t.fi) {
			t = pLI(pre[i], Max_pos);
		}
		if (a[i] > a[Max_pos]) Max_pos = i;
	}	
}

int main() {
	while (scanf("%d", &n) != EOF) {
		res = 0;
		for (int i = 1; i <= n; ++i) scanf("%lld", a + i), res += a[i];
		for (int i = 1; i <= n; ++i) id[i] = i;
		pos[0] = 1, pos[1] = 2;
		gao();
		reverse(a + 1, a + 1 + n);
		reverse(id + 1, id + 1 + n);
		gao();
		printf("%lld\n", res);
		printf("%d %d\n", pos[0], pos[1]);
	}
	return 0;
}
