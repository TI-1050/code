#include <bits/stdc++.h>

using namespace std;

using db = double;

const db PI = acos(-1.0);
const db eps = 1e-10;

int sgn(db x) {
	if (fabs(x) < eps) return 0;
	else return x > 0 ? 1 : -1;
}

db h, a, b, c, va, vb, vc;

db gao(db h1) {
	db arc1 = atan(h1 / a);
	db arc2 = asin(min(1.0, max(0.0, sin(arc1) * vb / va)));
	db arc3 = asin(min(1.0, max(0.0, sin(arc1) * vc / va)));
	db h = a * tan(arc1) + b * tan(arc2) + c * tan(arc3);
	return h;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%lf %lf %lf %lf %lf %lf %lf", &h, &a, &b, &c, &va, &vb, &vc);
		db l = 0, r = h, h1 = 0.0; 
		while (r - l >= eps) {
			db mid = (l + r) / 2.0;
			db tmp = gao(mid);
			if (sgn(tmp - h) >= 0) {
				r = mid;
				h1 = r;
			} else {
				l = mid;
			}
		}
		db arc1 = atan(h1 / a);
		db arc2 = asin(min(1.0, max(0.0, sin(arc1) * vb / va)));
		db arc3 = asin(min(1.0, max(0.0, sin(arc1) * vc / va)));
		db h2 = b * tan(arc2), h3 = c * tan(arc3);
		db res = sqrt(a * a + h1 * h1) / va + sqrt(b * b + h2 * h2) / vb + sqrt(c * c + h3 * h3) / vc;
		printf("%.10f\n", res);
	}
	return 0;
}
