#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
const int INF = 0x3f3f3f3f;
int n, m, a, b, e[N][2], uN, tot;  
vector <int> G[N]; 
int Mx[N], My[N], dx[N], dy[N], dis;
bool used[N];
bool SearchP() {
	queue <int> que;
	dis = INF;
	memset(dx, -1, sizeof (dx[0]) * tot);
	memset(dy, -1, sizeof (dy[0]) * tot);
	for (int i = 0; i < uN; ++i) {
		if (Mx[i] == -1) {
			que.push(i);
			dx[i] = 0;
		}
	}
	while (!que.empty()) {
		int u = que.front(); que.pop();
		if (dx[u] > dis) break;
		for (auto &v : G[u]) {
			if (dy[v] == -1) {
				dy[v] = dx[u] + 1;
				if (My[v] == -1) dis = dy[v];
				else {
					dx[My[v]] = dy[v] + 1;
					que.push(My[v]);
				}
			}
		}
	}
	return dis != INF;
}

bool DFS(int u) {
	for (auto &v : G[u]) {
		if (!used[v] && dy[v] == dx[u] + 1) {
			used[v] = true;
			if (My[v] != -1 && dy[v] == dis) continue;
			if (My[v] == -1 || DFS(My[v])) {
				My[v] = u;
				Mx[u] = v;
				return true;
			}
		}
	}
	return false;
}

int MaxMatch() {
	int res = 0;
	memset(Mx, -1, sizeof (Mx[0]) * tot);
	memset(My, -1, sizeof (My[0]) * tot);
	while (SearchP()) {
		memset(used, 0, sizeof (used[0]) * tot);
		for (int i = 0; i < uN; ++i) {
			if (Mx[i] == -1 && DFS(i)) {
				++res;
			}
		}
	}
	return res;
}

//第一种情况 满足除了a之外每个点有且仅有一条入边
//第二种情况 满足除了b之外每个点有且仅有一条出边
int main() {
	while (scanf("%d%d%d%d", &n, &m, &a, &b) != EOF) { 
		uN = m; tot = max(2 * n, m) + 5;
		for (int i = 1; i <= m; ++i) {
			int &u = e[i][0], &v = e[i][1];
			scanf("%d%d", &u, &v);
			G[i - 1].clear();
			if (u != b) G[i - 1].push_back(n + u);
			if (v != a) G[i - 1].push_back(v);
		}
		if (MaxMatch() != 2 * n - 2) puts("NO");
		else {
			puts("YES"); 
			for (int i = 1; i <= n; ++i) if (i != a) {
				printf("%d ", My[i] + 1);		
			}
			puts("");
			for (int i = n + 1; i <= n * 2; ++i) if (i != n + b) {
				printf("%d ", My[i] + 1);
			}
			puts("");
		}
	}
	return 0;
}
