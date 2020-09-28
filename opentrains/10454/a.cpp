#include <bits/stdc++.h>

using namespace std;

typedef long double db;

#define N 10010

struct node {
	db x, y;

	void input() {
		scanf("%Lf %Lf", &x, &y);
	}

	db operator ^ (const node &other) const {
		return x * other.y - y * other.x;
	}
}p[N];

int n, k;
db a[N];

int main() {
	while (~scanf("%d %d", &n, &k)) {
		for (int i = 0; i < n; ++i) {
			p[i].input();
			p[i + n] = p[i];
			a[i] = 0.0;
		}
		a[0] = k * (k - 1) * 1.0 / (n * (n - 1));
		for (int i = 1; i <= n - k; ++i) {
			a[i] = a[i - 1] * (n - k + 1 - i) / (n - 1 - i);
		}
		db ans = 0.0;
		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < i + n; ++j) {
				db tmp = p[i] ^ p[j];
				ans += tmp * a[j - i - 1];
			}
		}
		printf("%.10Lf\n", fabs(ans / 2.0));
	}
	return 0;
}
