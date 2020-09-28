#include <bits/stdc++.h>
using namespace std;

#define db double
int n, a;
db res;
const db eps = 1e-8;

int main() {
	while (scanf("%d", &n) != EOF) {
		res = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a);
			if ((res >= 100 || fabs(res - 100) < eps) && res < 150) {
				res += a * 0.8;
			} else if ((res >= 150 || fabs(res - 150) < eps) && res < 400) {
				res += a * 0.5;
			} else {
				res += a;
			}
		}
		printf("%.2f\n", res);
	}
	return 0;
}
