#include <bits/stdc++.h>
using namespace std;

#define db double
const int N = 310;
int n; db res, d[N];
struct node {
	db x, y;
	node() {}
	void scan() {
		scanf("%lf%lf", &x, &y);
	}
}a[N];

inline void Max() {
	sort(d + 1, d + 1 + n);
	res = max(res, (d[n / 2 + 1] - d[n / 2]) / 2);
}

inline void gao(db k) {
	for (int i = 1; i <= n; ++i)
		d[i] = (k * a[i].x - a[i].y) / sqrt(k * k + 1);
	Max();
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) a[i].scan();
		res = 0;
		for (int i = 1; i <= n; ++i) d[i] = a[i].x;
		Max();
		for (int i = 1; i <= n; ++i) d[i] = a[i].y;
		Max();
		for (int i = 1; i <= n; ++i)
			for (int j = i + 1; j <= n; ++j) if (a[i].x != a[j].x && a[i].y != a[j].y) {
				db k = (a[i].y - a[j].y) * 1.0 / (a[i].x - a[j].x);
				gao(k); gao(-1.0 / k);
			}
		printf("%.12f\n", res);
	}
	return 0;
}
