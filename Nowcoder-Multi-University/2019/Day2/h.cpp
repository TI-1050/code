#include <bits/stdc++.h>
using namespace std;

#define N 1010
int n, m;
int G[N][N], T[N][N], l[N][N], r[N][N], up[N][N];

void get(int G[][N], int &x, int &y, int &row, int &col) {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			l[i][j] = r[i][j] = j;
			up[i][j] = 1;
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 2; j <= m; ++j) {
			if (G[i][j] == 1 && G[i][j] == G[i][j - 1]) {
				l[i][j] = l[i][j - 1];
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = m - 1; j >= 1; --j) {
			if (G[i][j] == 1 && G[i][j] == G[i][j + 1]) {
				r[i][j] = r[i][j + 1];
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) { 
			if (i > 1 && G[i][j] == 1 && G[i][j] == G[i - 1][j]) {
				l[i][j] = max(l[i][j], l[i - 1][j]);
				r[i][j] = min(r[i][j], r[i - 1][j]);
				up[i][j] = up[i - 1][j] + 1;
			}
			if (G[i][j] == 1) {
				int tcol = r[i][j] - l[i][j] + 1;
				int trow = up[i][j];
				if (tcol * trow > row * col) {
					col = tcol;
					row = trow;
					x = i - up[i][j] + 1; 
					y = l[i][j];
				}
			}
		}
	}
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				scanf("%1d", G[i] + j);
				T[i][j] = G[i][j];
			}
		}
		int x, y, tx, ty, row = 0, col = 0, trow = 0, tcol = 0;
		get(G, x, y, row, col);
	//	cout << x << " " << y << " " << row << " " << col << endl;
		if (row == 0) {
			printf("0\n");
		} else {
			T[x][y] = 0;
			get(T, tx, ty, trow, tcol);	
			T[x][y] = 1;
			T[x + row - 1][y] = 0;
			get(T, tx, ty, trow, tcol);
			T[x + row - 1][y] = 1;
			T[x][y + col - 1] = 0;
			get(T, tx, ty, trow, tcol);
			T[x][y + col - 1] = 1;
			T[x + row - 1][y + col - 1] = 0;
			get(T, tx, ty, trow, tcol);
			printf("%d\n", trow * tcol);
		}
	}
	return 0;
}
