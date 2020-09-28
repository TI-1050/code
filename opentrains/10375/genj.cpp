#include <bits/stdc++.h>
using namespace std;

#define pii pair <int, int>
#define fi first
#define se second
int rd(int x) {
	return rand() % x;
	return (1ll * (rand() << 5) + rand()) % x;
}
map <pii, int> mp;

int main() {
	int n = 100000, m = 300000, q = 10000;
	printf("%d %d\n", n, m);
	for (int i = 1; i <= m; ++i) {
		pii e;
		do {
			e.fi = rd(n) + 1;
			e.se = rd(n) + 1;
		} while (e.fi == e.se || mp.find(e) != mp.end());
		mp[e] = 1;
		printf("%d %d\n", e.fi, e.se);
	}
	printf("%d\n", q);
	for (int i = 1; i <= q; ++i) {
		pii e;
		do {
			e.fi = rd(n) + 1;
			e.se = rd(n) + 1;
		} while (e.fi == e.se);
		printf("%d %d\n", e.fi, e.se);
	}
	return 0;
}
