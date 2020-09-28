#include <bits/stdc++.h>

using namespace std;

const int N = 2e3 + 10;
const int INF = 0x3f3f3f3f;

int n, m;
int a[N], b[N];

struct node {
	int len, lst;

	node() {}

	node(int len, int lst): len(len), lst(lst) {}

}f[N][N][2];//0 Up 1 Down

node Up(node a, node b) {
	if (a.len > b.len) return a;
	else if (a.lst > b.lst) return a;
	else return b;
}

node Down(node a, node b) {
	if (a.len > b.len) return a;
	else if (a.lst < b.lst) return a;
	else return b;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		scanf("%d", &m);
		for (int i = 1; i <= m; ++i) scanf("%d", b + i);
		for (int i = 0; i <= n; ++i) {
			for (int j = 0; j <= m; ++j) {
				f[i][j][0] = node(0, -INF);
				f[i][j][1] = node(0, INF);
			}
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				if (a[i] == b[j]) {
					if (a[i] < f[i][j][1].lst)
					f[i][j][0] = node(f[i - 1][j - 1][1].len + 1, a[i]);
					f[i][j][1] = node(f[i - 1][j - 1][0].len + 1, a[i]);
				}
				f[i][j][0] = Up(f[i - 1][j][0], f[i][j][0]);
				f[i][j][0] = Up(f[i][j - 1][0], f[i][j][0]);
				f[i][j][1] = Down(f[i - 1][j][1], f[i][j][1]);
				f[i][j][1] = Down(f[i][j - 1][1], f[i][j][1]);
			}
		}
		printf("%d\n", max(f[n][m][0].len, f[n][m][1].len));
	}	
	return 0;
}
