#include <bits/stdc++.h>
using namespace std;

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		int n, k;
		scanf("%d%d", &n, &k);
		while (k-- && n > 1) {
			n = (n + 1) / 2;
		}
		printf("%d\n", n);
	}
	return 0;
}
