#include <bits/stdc++.h>

using namespace std;

const int N = 2010;

struct node {
	int x, y;

	node() {}

	node(int x, int y): x(x), y(y) {}
};

int vis[N][N];
int n, m, q;
int dir[4][2] = {1, 0, 0, 1, -1, 0, 0, -1};

bool check(int x, int y) {
	if (x < 1 || x > n || y < 1 || y > m || vis[x][y] == 0) return false;
   	else return true;	
}

int gao(int x, int y) {
	if (!vis[x][y]) return 0;
	queue<node> que;
	int res = 0;
	vis[x][y] = 0;
	que.push(node(x, y));
	while (!que.empty()) {
		node st = que.front(); que.pop();
		res++;
		for (int i = 0; i < 4; ++i) {
			int dx = st.x + dir[i][0];
			int dy = st.y + dir[i][1];
			if (check(dx, dy)) {
				int sum1 = vis[dx + 1][dy] + vis[dx - 1][dy], sum2 = vis[dx][dy + 1] + vis[dx][dy - 1];
				if (sum1 < 2 && sum2 < 2) {
					vis[dx][dy] = 0;
					que.push(node(dx, dy));
				}
			}
		}
	}
	return res;
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d %d", &n, &m, &q);
		for (int i = 0; i <= n + 1; ++i) {
			for (int j = 0; j <= m + 1; ++j) {
				vis[i][j] = 1;
			}
		}
		for (int _q = 1, x, y; _q <= q; ++_q) {
			scanf("%d %d", &x ,&y);
			printf("%d\n", gao(x, y));
		}
	}
	return 0;
}
