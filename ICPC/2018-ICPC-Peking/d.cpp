#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 110;

ll m;
ll f[N];
int a[N];

int main() {
	f[0] = 1, f[1] = 1;
	for (int i = 2; i <= 50; ++i) {
		f[i] = f[i - 1] + f[i - 2];
	}
	while (scanf("%lld", &m) != EOF) {
		if (m == 0) {
			puts("2\n1 1\n2 1");
			continue;
		}
		*a = 0;
		for (int i = 50; i >= 1; --i) {
			if (m >= f[i]) {
				a[++*a] = i;
				m -= f[i];
			}
		}
		printf("%d\n", *a + 1);
		for (int i = 1; i <= *a; ++i) {
			printf("%d %d\n", 2 * i - 1, 200 - a[i]);
		}
		printf("%d %d\n", 2 * (*a), 2 * (*a));
	}
	return 0;
}
