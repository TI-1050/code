#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 10;
int n, q;
struct node { int Rank, cnt, id; }a[N];

int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		for (int i = 1; i <= n; ++i) a[i] = {i, 0, i};
		for (int i = 1, x; i <= q; ++i) {
			scanf("%d", &x);
			if (a[x].Rank == 1) {
				a[x].Rank = n - 1;
			   	++a[x].cnt;
				for (int j = 1; j <= n; ++j) if (j != x) {
					if (a[j].Rank <= n - 1)
						--a[j].Rank;
				}
			} else {
				for (int j = 1; j <= n; ++j) {
					if (a[j].Rank == a[x].Rank - 1) {
						++a[j].Rank;
						--a[x].Rank;
						break;
					}
				}
			}
		}
		sort(a + 1, a + 1 + n, [&](node x, node y) {
			if (x.cnt != y.cnt) return x.cnt > y.cnt;
			return x.Rank < y.Rank;		
		});
		int m = min(n, 6);
		for (int i = 1; i <= m; ++i)
			printf("%d%c", a[i].id, " \n"[i == m]);
	}
	return 0;
}
