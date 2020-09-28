#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200100
#define pii pair <int, int>
#define fi first
#define se second
int n, a[N];
int vis[N];

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n); 
		for (int i = 1; i <= n * 2 + 10; ++i) vis[i] = 0;
		for (int i = 1; i <= n; ++i) scanf("%d", a + i), vis[i] = 1;
		ll res[2] = {0, 0};
		priority_queue <pii> pq;
		for (int i = n; i >= 1; --i) {
			if (vis[n * 2] == 0 && vis[n * 2 + 1] == 0) {
				pq.push(pii(a[i], i));
			}	
		}
		int turn = 0;
		while (!pq.empty()) {
			pii it = pq.top(); pq.pop();
			if (vis[it.se] == 0) continue;
			res[turn] += it.fi;
			turn ^= 1;
			vis[it.se] = 0;
			int fa = it.se / 2;
			if (fa && vis[fa * 2] == 0 && vis[fa * 2 + 1] == 0) {
				pq.push(pii(a[fa], fa));
			}
		}
		printf("%lld %lld\n", res[0], res[1]);
	}
	return 0;
}
