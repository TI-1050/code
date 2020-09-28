#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 1e5 + 10;
int n, x, a[N], p[N];

bool check(int now) {
	int score = a[1] + p[now];
	multiset <int> se;
	for (int i = 1; i <= n; ++i) if (i != now) se.insert(p[i]);
	int cnt = 0;
	for (int i = n; i >= 2; --i) {
		int need = score - a[i];
		auto pos = se.upper_bound(need);
		if (pos == se.end()) continue;
		++cnt;
		se.erase(pos);
	}
	return cnt <= x - 1;
}

int main() {
	freopen("hop.in", "r", stdin);
	freopen("hop.out", "w", stdout);
	while (scanf("%d%d", &n, &x) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		sort(a + 2, a + 1 + n); 
		for (int i = 1; i <= n; ++i) scanf("%d", p + i);
		int l = 1, r = n, res = -1;
		while (r - l >= 0) {
			int mid = (l + r) >> 1;
			if (check(mid)) {
				l = mid + 1;
				res = mid;
			} else {
				r = mid - 1;
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
