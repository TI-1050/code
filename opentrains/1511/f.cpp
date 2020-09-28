#include <bits/stdc++.h>

using namespace std;

const double PI = acos(-1.0);

int x, y, z, r, a, b, c, d;

int main() {
	int _T;
	scanf("%d", &_T);
	while (_T--) {
		scanf("%d%d%d%d%d%d%d%d", &x, &y, &z, &r, &a, &b, &c, &d);
		printf("%.15f\n", r * r * PI);
	}
	return 0;
}
