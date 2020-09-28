#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
const int INF = 0x3f3f3f3f;
int n, m, h, q; 
struct BIT {
	vector <int> t;
	int n, m, h;
	inline int id(int x, int y, int z) {
		return (x - 1) * m * h + (y - 1) * h + z; 
	}
	void init(int _n, int _m, int _h) {
		n = _n; m = _m; h = _h; 
		t.resize(n * m * h + 10, INF);
	}
	inline void update(int x, int y, int z, int v) {
		for (int i = x; i <= n; i += i & -i) {
			for (int j = y; j <= m; j += j & -j) {
				for (int k = z; k <= h; k += k & -k) {
					t[id(i, j, k)] = min(t[id(i, j, k)], v);
				}
			}
		}
	}
	inline int query(int x, int y, int z) {
		int res = INF;
		for (int i = x; i > 0; i -= i & -i) {
			for (int j = y; j > 0; j -= j & -j) {
				for (int k = z; k > 0; k -= k & -k) {
					res = min(res, t[id(i, j, k)]);
				}
			}
		}
		return res;
	}
}bit[8];

inline int f(int x, int n) {
	if (x < 0) return -x;
	else return n - x + 1; 
}

inline int g(int x, int n) {
	if (x < 0) return n + x + 1;
	else return x;
}

int main() {
	while (scanf("%d%d%d%d", &n, &m, &h, &q) != EOF) {
		for (int i = 0; i < 8; ++i) bit[i].init(n, m, h);
		for (int _q = 1, tp, x, y, z; _q <= q; ++_q) {
			scanf("%d%d%d%d", &tp, &x, &y, &z);
			if (tp == 1) {
				int cnt = 0;
				for (int i = 0, _x = x; i < 2; ++i, _x *= -1) {
					for (int j = 0, _y = y; j < 2; ++j, _y *= -1) {
						for (int k = 0, _z = z; k < 2; ++k, _z *= -1) {
							bit[cnt].update(f(_x, n), f(_y, m), f(_z, h), _x + _y + _z); 
							++cnt;
						}
					}
				}
			} else {
				int res = INF, cnt = 0;
				for (int i = 0, _x = -x; i < 2; ++i, _x *= -1) {
					for (int j = 0, _y = -y; j < 2; ++j, _y *= -1) {
						for (int k = 0, _z = -z; k < 2; ++k, _z *= -1) {
							res = min(res, _x + _y + _z + bit[cnt].query(g(_x, n), g(_y, m), g(_z, h)));
							++cnt;
						}
					}
				}
				printf("%d\n", res);
			}
		}
	}
	return 0;
}
