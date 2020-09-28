#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int dir[5][2] = {0, 0, 1, 0, 0, 1, -1, 0, 0, -1};

bool gao(ll a, ll b, ll &x, ll &y) {
	for (int i = 0; i < 5; ++i) {
		int da = a + dir[i][0];
		int db = b + dir[i][1];
		if ((2ll * da + db) % 5 == 0 && (da - 2ll * db) % 5 == 0) {
			x = (2ll * da + db) / 5;
			y = (da - 2ll * db) / 5;
			return true;
		}
	}
	return false;
}

ll a, b, c, d;
ll x[2], y[2];

int main() {
	while (scanf("%lld %lld %lld %lld", &a, &b, &c, &d) != EOF) {
		if (gao(a, b, x[0], y[0]) && gao(c, d, x[1], y[1])) {
			printf("%lld\n", abs(x[0] - x[1]) + abs(y[0] - y[1]));
		} else {
			assert(0);
		}
	}
	return 0;
}
