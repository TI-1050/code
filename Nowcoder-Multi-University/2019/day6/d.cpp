#include <bits/stdc++.h>
using namespace std;

#define N 1010
int n, k, a[N];

bool check(int x) {
	multiset <int> se;
	for (int i = 1; i <= n; ++i) {
		se.insert(a[i]);
	}
	for (int i = 1; i <= k; ++i) {
		int remind = x;
		while (!se.empty()) {
			auto pos = se.upper_bound(remind);
			if (pos != se.begin()) {
				--pos;
				remind -= (*pos);
				se.erase(pos);
			} else {
				break;
			}
		}
		if (se.empty()) return 1;
	} 
	return 0;
}

int main() {
	int T; scanf("%d", &T);
	for (int kase = 1; kase <= T; ++kase) {
		printf("Case #%d: ", kase);
		scanf("%d%d", &n, &k);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i); 
		int l = 1, r = 1000000, res = -1;
		while (r - l >= 0) {
			int mid = (l + r) >> 1;
			if (check(mid)) {
				res = mid;
				r = mid - 1;
			} else {
				l = mid + 1;
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
