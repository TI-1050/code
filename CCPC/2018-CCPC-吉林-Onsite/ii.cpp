#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, a[N], b[N], c[N]; 

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		assert(n <= 100000);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		sort(a + 1, a + 1 + n);
		int res = 0;
		while (n) {
		//	for (int i = 1; i <= n; ++i) {
		//		printf("%d%c", a[i], " \n"[i == n]);
		//	}
			int x = a[n];
			res += max(0, x - n + 1); 
			b[0] = c[0] = 0;
			for (int i = 1; i < n - 1 - x; ++i) {
				b[++b[0]] = a[i];
			}
			for (int i = max(1, n - 1 - x); i <= n - 1; ++i) if (a[i] - 1 > 0) {   
				c[++c[0]] = a[i] - 1;
			}
			int i = 1, j = 1; n = 0;
			while (i <= b[0] && j <= c[0]) {
				if (b[i] < c[j]) {
					a[++n] = b[i++];
				} else {
					a[++n] = c[j++];
				}
			}
			while (i <= b[0]) {
				a[++n] = b[i++];
			}
			while (j <= c[0]) {
				a[++n] = c[j++];
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
