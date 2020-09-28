#include <bits/stdc++.h>
using namespace std;

#define N 1100
#define ll long long
map <ll, int> mp;
ll n; int m;
int l[N], r[N];

void DFS(ll n) {
	if (mp.find(n) != mp.end()) return;
	if (n == 1) {
		mp[n] = ++m;
		l[m] = -1;
		r[m] = -1;
		return;
	}
	ll mid = n / 2;
	DFS(mid);
	DFS(n - mid);
	mp[n] = ++m;
	l[mp[n]] = mp[n - mid];
	r[mp[n]] = mp[mid];
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%lld", &n);
		m = -1; mp.clear();
		DFS(n);
		printf("%d\n", m + 1);
		for (int i = 0; i <= m; ++i) {
			printf("%d %d\n", l[i], r[i]);
		}
		printf("%d\n", m);
	}
	return 0;
}
