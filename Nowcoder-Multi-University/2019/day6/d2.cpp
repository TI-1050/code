#include <bits/stdc++.h>
using namespace std;

#define N 1010
#define INF 0x3f3f3f3f
int n, k, a[N];

int check(int x) {
	int sum = 0;
	int box = 0;
	multiset <int> se;
	for (int i = 1; i <= n; ++i) {
		se.insert(a[i]);
		sum += a[i];
	}
	for (int i = 1; i <= k; ++i) {
		int remind = x;
		while (!se.empty()) {
			auto pos = se.upper_bound(remind);
			if (pos != se.begin()) {
				--pos;
				remind -= (*pos);
				sum -= (*pos);
				se.erase(pos);
			} else {
				break;
			}
		}
		box += remind;
		if (se.empty()) return -INF;
	} 
	return sum - box;
}

int main() {
	int T; scanf("%d", &T);
	for (int kase = 1; kase <= T; ++kase) {
		printf("Case #%d: ", kase);
		scanf("%d%d", &n, &k);
		int sum = 0;
		for (int i = 1; i <= n; ++i) scanf("%d", a + i), sum += a[i]; 
		for (int i = sum / k; ; ) {
			int x = check(i);
			if (x == -INF) {
				printf("%d\n", i);
				break;
			} else {
				++i;
			//	i += max(1, x / k + (x % k != 0));
			}
		}
	}
	return 0;
}
