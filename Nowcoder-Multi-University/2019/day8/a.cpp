#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;

const int N = 3010;

int n, m;
char s[N];
int G[N][N];
int up[N][N];
pii Sta[N];
int top;

int main() {
	while (scanf("%d %d", &n, &m) != EOF) {
		memset(G, 0, sizeof G);
		memset(up, 0, sizeof up);
		for (int i = 1; i <= n; ++i) {
			scanf("%s", s + 1);
			for (int j = 1; j <= m; ++j) {
				if (s[j] == '1') up[i][j] = up[i - 1][j] + 1;
				G[i][j] = G[i][j - 1] + s[j] - '0';
			}
		}
		int res = 0;
		for (int i = 1; i <= n; ++i) {
			top = 0;
			for (int j = 1; j <= m + 1; ++j) {
				int now = j;
				while (top >= 1 && up[i][j] < Sta[top].first) {
					now = Sta[top].second;
					int left = Sta[top].second;
					if (i == n || (G[i + 1][j - 1] - G[i + 1][left - 1] != j - left)) {
						res++;
					}
					top--;
				}
				if (up[i][j] == 0) continue;
				if (top == 0 || (top >= 1 && up[i][j] > Sta[top].first)) {
					Sta[++top] = pii(up[i][j], now);
				}
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
