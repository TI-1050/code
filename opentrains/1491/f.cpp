#include <bits/stdc++.h>
using namespace std;
using db = double;

const int N = 1e3 + 10;

const db eps = 1e-8;

int sgn(db x) {
	if (fabs(x) < eps) return 0;
	else return x > 0 ? 1 : -1;
}

struct node {
	db x, y;

	node() {}

	node(db x, db y): x(x), y(y) {}

	void input() {
		scanf("%lf %lf", &x, &y);
	}

	db dis(const node &p) const {
		return hypot(x - p.x, y - p.y);
	}
}a[N];

int n;

inline db get(node p) {
	db res = 0;
	for (int i = 1; i <= n; ++i) res += a[i].dis(p);
	return res;
}

void gao() {
	db t = 1000000, pd = 0.98;
	db x = 0, y = 0;
	for (int i = 1; i <= n; ++i) x += a[i].x, y += a[i].y;
	db res = 1e18;
	node now = node(x / n, y / n);
	while (t > eps) {
		db dx = 0, dy = 0;
		for (int i = 1; i <= n; ++i) {
			dx += (a[i].x - now.x) / (a[i].dis(now));
			dy += (a[i].y - now.y) / (a[i].dis(now));
		}
		dx *= t, dy *= t;
		db other = get(node(now.x + dx, now.y + dy));
		if (sgn(other - res) <= 0) {
			res = other;
			now.x += dx, now.y += dy;
		}
		t *= pd;
	}
	if (fabs(now.x) <= 1e-6) now.x = fabs(now.x);
	if (fabs(now.y) <= 1e-6) now.y = fabs(now.y);
	printf("%.15f %.15f\n", now.x, now.y);
}


int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			a[i].input();
		}
		gao();
	}
	return 0;
}
