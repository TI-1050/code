#include <bits/stdc++.h>
using namespace std;

#define N 1000010
int n, m, id;
vector <vector<int>> G;
int st[N], d[N];
char mp[N], s[N];
int num[N], x, y;

int ord[N], cnt;
void Toposort() {
	cnt = 0;
	queue <int> q;
	for (int i = 1; i <= id; ++i) {
		if (d[i] == 0)
			q.push(i);
	} 
	while (!q.empty()) {
		int u = q.front(); q.pop();
		ord[++cnt] = u;
		for (auto v : G[u]) {
			if (--d[v] == 0) {
				q.push(v);
			}
		}
	}
	if (cnt == id && id == n) {
		for (int i = 1; i <= id; ++i) 
			putchar(mp[ord[i]]);
		puts("");
	} else {
		puts("-1");
	}
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		id = 0;
		G.clear(); G.resize(N);
		memset(st, -1, sizeof st);
		memset(num, -1, sizeof num);
		memset(d, 0, sizeof d);
		int len, cntx, cnty; 
		bool F = 1;
		for (int i = 1; i <= (m * (m - 1)) / 2; ++i) {
			scanf(" %s %d ", s, &len);
			x = s[0], y = s[1];
			if (len) {
				scanf("%s", s + 1);
			}
			cntx = cnty = 0;
			for (int i = 1; i <= len; ++i) {
				if (s[i] == x) {
					++cntx;
				} else {
					++cnty;
				}
			} 
			if (num[x] == -1) {
				num[x] = cntx;
			} else if (num[x] != cntx) {
				F = 0;
			}
			if (num[y] == -1) {
				num[y] = cnty;
			} else if (num[y] != cnty) {  
				F = 0;
			}
			if (len == 0) continue;
			if (st[x] == -1) {
				for (int i = 1; i <= cntx; ++i) {
					mp[++id] = x;
					if (i > 1) {
						G[id - 1].push_back(id);
						++d[id]; 
					} else {
						st[x] = id;
					}
				}
			}
			if (st[y] == -1) {
				for (int i = 1; i <= cnty; ++i) {
					mp[++id] = y;
					if (i > 1) {
						G[id - 1].push_back(id);
						++d[id];
					} else {
						st[y] = id;
					}
				}
			}
			int posx = st[x], posy = st[y];     
			--posx, --posy;
			if (s[1] == x) ++posx;
			else if (s[1] == y) ++posy;
			else F = 0;
			for (int i = 2; i <= len; ++i) {
				if (s[i] != x && s[i] != y) { 
					F = 0;
					break; 
				}
				if (s[i] == x) {
					++posx;
					if (posy >= st[y]) {
						G[posy].push_back(posx);
						++d[posx];
					}
				} else {
					++posy;
					if (posx >= st[x]) {
						G[posx].push_back(posy);
						++d[posy];
					}
				}
			}
		}
		if (F && id == n) {
			Toposort();
		} else {
			puts("-1");
		}
	}
	return 0;
}
