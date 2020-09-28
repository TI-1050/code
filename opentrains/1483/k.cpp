#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 2e5 + 10;
int n, m;
ll a[N];
multiset <int> se[N]; 
set <int> S;
int vis[N];

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		memset(vis, 0, sizeof vis); 
		for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
		sort(a + 1, a + 1 + n);
		ll res = 0;
		for (int i = 1; i <= n; ++i) se[i].clear();
		for (int i = 2; i <= n; ++i) {
			if (m - a[i] > a[i - 1]) continue;
			int pos = lower_bound(a + 1, a + 1 + i, m - a[i]) - a;
			se[pos].insert(a[i]);
			vis[i] = 1;
			res += (a[i] + a[pos]) % m;
		}
		S.clear();
		for (auto it : se[1]) S.insert(it);
		S.insert(a[1]);
		for (int i = 2; i <= n; ++i) if (!vis[i]) {
			ll Min = (a[1] + a[i]) % m;
			auto pos = S.lower_bound(m - a[i]);
			if (pos != S.end()) Min = min(Min, (1ll * a[i] + *pos) % m);
			for (auto it : se[i]) {
				auto pos = S.lower_bound(m - it);
				if (pos == S.end()) continue;
				Min = min(Min, (1ll * it + *pos) % m);	
			}
			for (auto it : se[i]) S.insert(it);
			S.insert(a[i]);
			res += Min;
		}
		printf("%lld\n", res);
	}
	return 0;
}
