#include <bits/stdc++.h>

using namespace std;

const int N = 60;

struct node {
	int x, y, z;

	node() {}
	
	node(int x, int y, int z): x(x), y(y), z(z) {}
}S, T;

int n, m, h;
char mp[N][N][N];
int vis[N][N][N];
int dir[4][2] = {1, 0, 0, 1, -1, 0, 0, -1};

bool ok(node a) {
	if (a.x < 1 || a.x > n || a.y < 1 || a.y > m || a.z < 1 || a.z > h || vis[a.z][a.x][a.y]) return false;
	else return true;
}

bool f(node a) {
	return a.x == T.x && a.y == T.y && a.z == T.z;
}

void gao() {
	memset(vis, 0, sizeof vis);
	queue<node> q;
	q.push(S);
	vis[S.z][S.x][S.y] = 1;
	while (!q.empty()) {
		node st = q.front();
		q.pop();
		if (f(st)) {
			puts("Yes");	
			return ;
		}
		for (int i = 0; i < 4; ++i) {
			node now = st;
			now.x = st.x + dir[i][0];
			now.y = st.y + dir[i][1];
			if (!ok(now)) continue;
			if (mp[now.z][now.x][now.y] == 's') {
				for (int j = st.z; j <= h; ++j) {
					now.z = j;
					if (mp[now.z][now.x][now.y] != 's') break;
					if (vis[now.z][now.x][now.y]) continue;
					q.push(now);
					vis[now.z][now.x][now.y] = 1;
					if (f(now)) {
						puts("Yes");
						return ;
					}
				}
				for (int j = st.z - 1; j >= 1; --j) {
					now.z = j;
					if (mp[now.z][now.x][now.y] != 's') break;
					if (vis[now.z][now.x][now.y]) continue;
					q.push(now);
					vis[now.z][now.x][now.y] = 1;
					if (f(now)) {
						puts("Yes");
						return ;
					}
				}
			}
			now.z = st.z;
			if (mp[now.z][now.x][now.y] == 'w') {
				for (int j = st.z; j >= 1; --j) {
					now.z = j;
					if (mp[now.z][now.x][now.y] != 'w') {
						now.z++;
						break;
					}
				}
				if (vis[now.z][now.x][now.y]) continue;
				vis[now.z][now.x][now.y] = 1;
				q.push(now);
				if (f(now)) {
					puts("Yes");
					return ;
				}
			}
			now.z = st.z;
			if (mp[now.z][now.x][now.y] == 'w') continue;
			if (vis[now.z][now.x][now.y]) continue;
			vis[now.z][now.x][now.y] = 1;
			q.push(now);
		}
	}
	puts("No");
}

int main() {
	while (scanf("%d %d %d", &n, &m, &h) != EOF) {
		memset(vis, 0, sizeof vis);
		for (int z = h; z >= 1; --z) {
			for (int x = 1; x <= n; ++x) {
				for (int y = 1; y <= m; ++y) {
					scanf(" %c", &mp[z][x][y]);
					if (mp[z][x][y] == 'A') S = node(x, y, z);
					if (mp[z][x][y] == 'E') T = node(x, y, z);
				}
			}
		}
		gao();
	}
	return 0;
}
