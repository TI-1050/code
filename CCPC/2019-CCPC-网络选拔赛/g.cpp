#include <bits/stdc++.h>
using namespace std;

const int N = 1100;
int n, k;
char s[N][N]; 

void gao(int x, int y, int k) {
	if (k == 1) {
		s[x][y] = 'C';
		s[x][y + 1] = 'C';
		s[x + 1][y] = 'P';
		s[x + 1][y + 1] = 'C';
		return;
	} else {
	//	cout << x << " " << y << " " << k << endl;
		int n = 1 << (k - 1);
		gao(x, y, k - 1);
		gao(x, y + n, k - 1);
		gao(x + n, y, k - 1);
		gao(x + n, y + n, k - 1);
		for (int i = x + n; i < x + 2 * n; ++i) {
			for (int j = y; j < y + n; ++j) {
				if (s[i][j] == 'C') s[i][j] = 'P';
				else s[i][j] = 'C';
			}
		}
	}
}

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		int k; scanf("%d", &k);
		n = 1 << k;
		gao(1, 1, k);	
		for (int i = 1; i <= n; ++i) {
			s[i][n + 1] = 0;
			printf("%s\n", s[i] + 1);
		}
	}
	return 0;
}
