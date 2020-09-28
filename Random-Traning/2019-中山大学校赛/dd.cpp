#include <bits/stdc++.h>
using namespace std;

#define N 10000010
struct node {
	int x, y, op;
	node () {}
	node (int x, int y, int op) : x(x), y(y), op(op) {}
};
vector < vector <node> > qrr;
vector < vector <int> > vec;
int n, m, p, q;
int f[N], g[N];

void init() {
	vec.clear();
	vec.resize(n + 2);
	qrr.clear();
	qrr.resize(n + 2);
	for (int i = 0; i <= m + 1; ++i) {
		f[i] = 0;
	}
	for (int i = 0; i <= n + 1; ++i) {
		vec[i].resize(m + 1);
	}
}
int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		init();
		scanf("%d", &p);
		for (int i = 1, x[2], y[2]; i <= p; ++i) {
			scanf("%d%d%d%d", x, y, x + 1, y + 1);
			qrr[x[0]].emplace_back(y[0], y[1], 1);
			qrr[x[1] + 1].emplace_back(y[0], y[1], -1); 
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				g[j] = 0;
			}
			for (auto it : qrr[i]) {
				g[it.x] += it.op;
				g[it.y + 1] -= it.op;
			}
			for (int j = 1; j <= m; ++j) {
				g[j] += g[j - 1];
				f[j] += g[j];
				vec[i][j] = (f[j] >= 1);
			}
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				vec[i][j] += vec[i][j - 1] + vec[i - 1][j] - vec[i - 1][j - 1];
			}
		}
		scanf("%d", &q);
		for (int i = 1, x[2], y[2]; i <= q; ++i)
		{
			scanf("%d%d%d%d", x, y, x + 1, y + 1);
			int area = vec[x[1]][y[1]] - vec[x[0] - 1][y[1]] - vec[x[1]][y[0] - 1] + vec[x[0] - 1][y[0] - 1];
			if (area == ((y[1] - y[0] + 1) * (x[1] - x[0] + 1))) {
				puts("YES");
			} else {
				puts("NO");
			}
		}
	}
	return 0;
}
