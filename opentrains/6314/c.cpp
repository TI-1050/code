#include <bits/stdc++.h>

using namespace std;

const int N = 1010;
const double PI = acos(-1.0);

int n, m, sze[N];
vector<vector<int> >G;
complex<double> a[N];

void gao1(int u, int pre = 0) {
	sze[u] = 1;
	for (auto v: G[u]) {
		if (v != pre) {
			gao1(v, u);
			sze[u] += sze[v];
		}
	}
}

void gao2(int u, double arc, int pre = 0) {
	for (auto v : G[u]) {
		if (v != pre) {
			a[v] = a[u] + polar(1.0, arc);
			gao2(v, arc, u);
			arc += PI / N * sze[v];
		}
	}
}

int main() {
	while (scanf("%d", &n) != EOF) {
		G.clear(); G.resize(n + 1);
		memset(sze, 0, sizeof sze);
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d %d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		a[1] = {0.0, 0.0};
		gao1(1, 0);
		m = 0;
		for (int i = 1; i <= n; ++i) {
			for (auto it : G[i]) {
				m += sze[it];
			}
		}
		gao2(1, 0.0);
		for (int i = 1; i <= n; ++i) {
			printf("%.10f %.10f\n", a[i].real(), a[i].imag());
		}
	}
	return 0;
}
