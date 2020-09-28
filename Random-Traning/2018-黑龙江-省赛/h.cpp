#include <bits/stdc++.h>
using namespace std;

int n, m, q;
vector <int> a, b;

void init() {
	a.resize(n + 1, 0);
	b.resize(m + 1, 0);
}
int main() {
	scanf("%d%d%d", &n, &m, &q);
	init();
	int op, x;
	for (int i = 1; i <= q; ++i) {
		scanf("%d%d", &op, &x);
		switch(op) {
			case 1 :
				a[x] = i;
				break;
			case 2 :
				b[x] = i;
				break;
			default :
				assert(0);
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			printf("%d%c", max(a[i], b[j]), " \n"[j == m]);
		}
	}
	return 0;
}
