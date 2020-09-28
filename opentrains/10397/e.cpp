#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

struct Edge {
	int v, p, id;//p 1 same -1 not same

	Edge() {}

	Edge(int v, int p, int id): v(v), p(p), id(id) {}
};

int F;
int n, m;
int color[N];//1 hor  -1 vert
int used[N];
char s[N];
vector<vector<Edge> >G;
vector<int> res;

void addedge(int u, int v, int p, int id) {
	G[u].push_back(Edge(v, p, id));
	G[v].push_back(Edge(u, p, id));
}

void gao(int u) {
	if (!F) return ;
	for (auto &it : G[u]) {
		if (!color[it.v]) {
			color[it.v] = it.p * color[u];
			used[it.id] = 1;
			gao(it.v);
		} else {
			if (color[it.v] != it.p * color[u]) {
				F = 0;
				return ;
			}
			if (!used[it.id]) {
				used[it.id] = 1;
				res.push_back(it.id);
			}
		}
	}
}

int main() {
	while (scanf("%d %d", &n, &m) != EOF) {
		F = 1;
		res.clear();
		G.clear(), G.resize(n + 3);
		memset(color, 0, sizeof color);
		memset(used, 0, sizeof used);
		int S = n + 1, T = n + 2;//S hor   T  vert
		for (int i = 1, x, y; i <= m; ++i) {
			scanf("%s", s);
			if (s[0] == 'h') {
				scanf("%d", &x);
				addedge(S, x, 1, i);
			} else if (s[0] == 'v') {
				scanf("%d", &x);
				addedge(T, x, 1, i);
			} else if (s[0] == 'p' && s[1] == 'a') {
				scanf("%d %d", &x, &y);
				addedge(x, y, 1, i);
			} else if (s[0] == 'p' && s[1] == 'e') {
				scanf("%d %d", &x, &y);
				addedge(x, y, -1, i);
			}	
		}
		color[S] = 1, color[T] = -1;
		gao(S);
		gao(T);
		for (int i = 1; i <= n; ++i) if (!color[i]) {
			color[i] = 1;
			gao(i);
		}
		if (!F) {
			puts("inconsistent");
			continue;
		}
		puts("consistent");
		int sze = res.size();
		printf("%d\n", sze);
		for (int i = 0; i < sze; ++i) {
			printf("%d%c", res[i],  " \n"[i == sze - 1]);
		}
	}
	return 0;
}
