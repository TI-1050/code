#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, c, a[N];
int f[N][110], nx[110];

int main() {
	scanf("%d%d", &n, &c);	
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	for (int i = 1; i <= c; ++i) nx[i] = n + 1, f[n + 1][i] = n + 1;
	for (int i = n; i >= 0; --i) {
		for (int j = 1; j <= c; ++j) {
			f[i][j] = nx[j];
		}
		if (i) nx[a[i]] = i;
	}
	int res = 0;
	for (int i = 1; i <= c; ++i) {
		for (int j = 1; j <= c; ++j) if (i != j) {
			int tmp = 0;
			int it = 0;
			while (it <= n) {
				it = f[it][i];
				if (it <= n) {
					tmp += 1;
				} else break;
				it = f[it][j];
				if (it <= n) {
					tmp += 1;
				} else break; 
			}
			if (tmp > 1) {
				res = max(res, tmp);	
			}
		}
	}
	printf("%d\n", res);
	return 0;
}
