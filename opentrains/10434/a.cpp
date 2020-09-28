#include <bits/stdc++.h>
using namespace std;

const int N = 1e2 + 10;
int n, m, a[N][N], b[N][N]; char s[N];

int main() {
	int _T; cin >> _T;
	while (_T--) {
		scanf("%d%d", &n, &m);
		scanf("%s", s + 1);
		for (int i = 1; i <= n; ++i) 
			for (int j = 1; j <= m; ++j)
				scanf("%d", a[i] + j);
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				int &res = b[i][j];
				res = a[i][j]; int x = i, y = j;
				for (int k = 1; s[k]; ++k) {
					if (s[k] == 'U') --x;
					else if (s[k] == 'D') ++x;
					else if (s[k] == 'L') --y;
					else if (s[k] == 'R') ++y;
					if (x < 1 || x > n || y < 1 || y > m) {
						res = 0;
						break;
					}
					res += a[x][y];
				}
			}
		}
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				printf("%d%c", b[i][j], " \n"[j == m]);
	}
	return 0;
}
