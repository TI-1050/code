#include <bits/stdc++.h>
using namespace std;

#define pii pair <int, int>
#define fi first
#define se second
#define ll long long
const int N = 3e5 + 10;
int n, m, fa[N], a[N], d[N];
vector < vector <pii> > vec;
vector < map <int, ll> > T;

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%d%d", &n, &m);
		vec.clear(); vec.resize(n + 1);
		T.clear(); T.resize(n + 1);
		fa[1] = 1; d[1] = 1; 
		ll ans = 0;
		for (int i = 2; i <= n; ++i) scanf("%d", fa + i), d[i] = d[fa[i]] + 1;
		for (int i = 1; i <= n; ++i) scanf("%d", a + i), ans += a[i];
		for (int i = 1, x, k, c; i <= m; ++i) {
			scanf("%d%d%d", &x, &k, &c);
			vec[x].push_back(pii(k, c));
		}
		for (int i = n; i >= 1; --i) {
			T[i][d[i]] += a[i];
			for (auto it : vec[i]) {
				int A = d[i] + it.fi, B = it.se;
				while (B && T[i].size()) {
					auto pos = T[i].upper_bound(A);
					if (pos == T[i].begin()) break;
					--pos;
					int x = min(1ll * B, pos->se);
					B -= x;
					pos->se -= x;
					ans -= x;
					if (pos->se == 0) T[i].erase(pos);
				}
			}
			if (i > 1) {
				int ff = fa[i];
				if (T[i].size() > T[ff].size()) swap(T[i], T[ff]);
				for (auto it : T[i]) T[ff][it.fi] += it.se;
			}
		}	
		printf("%lld\n", ans);
	}
	return 0;
}
