#include <bits/stdc++.h>
using namespace std;

#define N 101010
int n, a[N], b[N], pre[N];
struct BIT {
	int a[N];
	void init(int n) {
		for (int i = 0; i <= n + 10; ++i) {
			a[i] = 0;
		}
	} 
	void update(int x, int val) {
		for (; x < n + 10; x += x & -x) {
			a[x] += val;
		}
	}
	int query(int x) {
		int res = 0;
		for (; x > 0; x -= x & -x) {
			res += a[x];
		}
		return res;
	}
}bit;

void init() {
	for (int i = 0; i <= n; ++i) {
		b[i] = 0;
		pre[i] = 0;
	}
	bit.init(n);
}
int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		init();
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		for (int i = 1; i <= n; ++i) {
			if (pre[a[i]]) {
				int tot = bit.query(i) - bit.query(pre[a[i]]);
				++b[tot + 1];
				bit.update(pre[a[i]], -1);
			}
			bit.update(i, 1);
			pre[a[i]] = i;
		}
		for (int i = 1; i <= n; ++i) {
			b[i] += b[i - 1];
			printf("%d%c", n - b[i], " \n"[i == n]);
		}
	}
	return 0;
}
