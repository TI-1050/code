#include <bits/stdc++.h>

using namespace std;

using db = double;

const db PI = acos(-1.0);
const db eps = 1e-8;

int sgn(db x) {
	if (fabs(x) < eps) return 0;
	else return x > 0 ? 1 : -1;
}

int main() {
	db ans = 1e18, tmp;
	db h = 21, a = 5, b = 12, c = 4, va = 4, vb = 3, vc = 4;
	for (db h1 = 0.0; h1 <= 21; h1 += 0.01) {
		db h3 = h1 * c / a;
		db h2 = h - h1 - h3;
		db res = sqrt(a * a + h1 * h1) / va + sqrt(b * b + h2 * h2) / vb + sqrt(c * c + h3 * h3) / vc;
		if (ans > res) {
			ans = res, tmp = h1;
		}
	}
	cout << ans << " " << tmp << endl;
	db h1 = tmp, h3 = h1 * c / a, h2 = h - h1 - h3;
	db arc1 = atan(tmp / a), arc2 = atan(h2 / b);
	cout << va << " " << vb << " " << va / vb << endl;
	cout << arc1 << " " << arc2 << " " << arc1 / arc2 << endl;
	cout << sin(arc1) << " " << sin(arc2) << " " << sin(arc1) / sin(arc2) << endl;
	cout << cos(arc1) << " " << cos(arc2) << " " << cos(arc1) / cos(arc2) << endl;
	cout << "#############3\n";
	arc1 = PI / 2 - arc1, arc2 = PI / 2 - arc2;
	cout << va << " " << vb << " " << va / vb << endl;
	cout << arc1 << " " << arc2 << " " << arc1 / arc2 << endl;
	cout << sin(arc1) << " " << sin(arc2) << " " << sin(arc1) / sin(arc2) << endl;
	cout << cos(arc1) << " " << cos(arc2) << " " << cos(arc1) / cos(arc2) << endl;

	return 0;
}
