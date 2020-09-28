#include <bits/stdc++.h>
using namespace std;

#define N 100010
int k, n, m;
int a[N];
char s[N];

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &k);
		scanf("%s", s + 1);
		for (int i = 1; i <= k; ++i) {
			a[i] = s[i] - '0';
		}
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= m; ++i) scanf("%*d%*d");
		int tot = (m - (n - 1));
		printf("%d\n", ((a[tot % k + 1] - 1) ^ 1) + 1);
	}
	return 0;
}
