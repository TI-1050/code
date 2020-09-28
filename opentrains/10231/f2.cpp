#include <bits/stdc++.h>

using namespace std;

int n, l, m;

int main() {
	freopen("intset.in", "r", stdin);
	freopen("intset.out", "w", stdout);
	while (scanf("%d %d %d", &n, &l, &m) != EOF) {
		int k = round(1.0 * l * m / n);
		printf("%d\n", k);
	}
	return 0;
}
