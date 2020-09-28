#include <bits/stdc++.h>

using namespace std;

const int maxn = 110;

int n, m;
vector<int>G1[maxn], G2[maxn];
int du[maxn];
int up[maxn], down[maxn];
int vis[maxn];
int cnt;

void DFS1(int u,int fa) {
	vis[u] = 1;
	for (auto v : G2[u]) {
		if(!vis[v]) {
			cnt++;
			DFS1(v, u);
		}
	}
}

void DFS2(int u,int fa) {
	vis[u] = 1;
	for (auto v : G1[u]) {
		if(!vis[v]) {
			cnt++;
			DFS2(v, u);
		}
	}
}

bool Topo() {
	cnt = 0;
	queue<int>q;
	for (int i = 1; i <= n; ++i) {
		if(du[i] == 0) {
			q.push(i);
		}
	}
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		cnt++;
		for (auto v : G1[u]) {
			if(--du[v] == 0) {
				q.push(v);
			}
		}
	}
	return cnt == n;
}

void Init() {
	for (int i = 1; i <= n; ++i) {
		G1[i].clear();
		G2[i].clear();
		du[i] = 0;
		up[i] = 0;
		down[i] = 0;
	}
}

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d", &n, &m);
		Init();
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d %d", &u, &v);
			G1[u].push_back(v);
			G2[v].push_back(u);
			du[v]++;
		}
		if(!Topo()) {
			for (int i = 1; i <= n; ++i) {
				putchar('0');
			}
			putchar('\n');
			continue;
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				vis[j] = 0;
			}
			cnt = 0;
			DFS1(i, -1);
			up[i] = cnt;
			for (int j = 1; j <= n; ++j) {
				vis[j] = 0;
			}
			cnt = 0;
			DFS2(i, -1);
			down[i] = cnt;
		}
		for (int i = 1; i <= n; ++i) {
			if(up[i] < (n + 1) / 2 && down[i] < (n + 1) / 2) {
				putchar('1');
			} else {
				putchar('0');
			}
		}
		putchar('\n');
	}
	return 0;
}
