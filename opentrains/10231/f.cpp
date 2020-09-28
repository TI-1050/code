#include <bits/stdc++.h>

using namespace std;

#define N 1000010

int n, l, m;
int a[N], cnt[N];

int main() {
	for (n = 1; n <= 10; ++n) {
		for (l = 1; l <= n; ++l) {
			for (m = 1; m <= n; ++m) {
				for (int i = 1; i <= n; ++i) {
					a[i] = i;
				}
				memset(cnt, 0, sizeof cnt);
				for (int cas = 1; cas <= 10000; ++cas) {
					random_shuffle(a + 1, a + 1 + n);
					int tmp = 0;
					for (int i = 1; i <= m; ++i) {
						if (a[i] <= l) {
							++tmp;
						}
					}
					cnt[tmp]++;
				}
				for (int i = n; i >= 1; --i) {
					cnt[i] += cnt[i - 1];
				}
				int res = -1;
				for (int i = 1; i <= n; ++i) {
					if (cnt[i] >= 5000) {
						res = i;
						break;
					}
				}
				cout << n << " " << l << " " << m << " " << res << endl;
			}
		}
	}
	return 0;
}
