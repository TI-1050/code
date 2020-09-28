#include <bits/stdc++.h>
using namespace std;

const int N = 2e4 + 10;
const int INF = 0x3f3f3f3f;
int uN, linker[N], flinker[N], used[N], vis[N]; 
vector <vector<int>> G;
int n, num[11], res[N]; 
bool DFS(int u) {
	for (auto v : G[u]) if (!used[v]) {
		used[v] = true;
		if (linker[v] == -1 || DFS(linker[v])) {
			linker[v] = u;
			flinker[u] = v;
			return true;
		}
	}
	return false;
}
void hungary() {
	memset(linker, -1, sizeof linker);
	memset(flinker, -1, sizeof flinker);
	for (int u = 0; u < uN; ++u) {
		int &pre = vis[u % 1000]; 
		if (pre != -1) {
			linker[flinker[pre]] = -1;
			--num[pre / 1000 + 1]; 
			bool F = 0;
			for (int v = 1000 * pre / 1000; v < 1000 * (pre / 1000 + 1); ++v) {
				if (v != pre && vis[v % 1000] == -1) {
					if (DFS(v)) {  
						vis[v % 1000] = v; 
						++num[v / 1000 + 1]; 
						F = 1;
						break;
					}
				}
			}		
			if (!F) {
				linker[flinker[pre]] = pre;
				++num[pre / 1000 + 1];
				continue;
			}
		} 
		memset(used, 0, sizeof used);
		if (DFS(u)) {
			vis[u % 1000] = u;
			++num[u / 1000 + 1];
		}
	}
}

int main() {
	freopen("medals.in", "r", stdin);
	freopen("medals.out", "w", stdout);
	while (scanf("%d", &n) != EOF) {
		G.clear(); G.resize(N); 
		memset(num, 0, sizeof num);
		memset(res, 0, sizeof res);
		memset(vis, -1, sizeof vis);
		for (int i = 1, m; i <= n; ++i) {
			scanf("%d", &m);
			for (int j = 1, x, y; j <= m; ++j) {
				scanf("%d%d", &x, &y);
				G[(y - 1) * 1000 + x - 1].push_back(i);
			}
		}
		uN = 1e4;
		hungary();
		for (int i = 1; i <= n; ++i) {
			if (linker[i] == -1) res[i] = 0;
			else {
				res[i] = linker[i] % 1000 + 1;
			}
		}
		for (int i = 1; i <= 10; ++i)
			printf("%d%c", num[i], " \n"[i == 10]);
		for (int i = 1; i <= n; ++i) {
			printf("%d%c", res[i], " \n"[i == n]);
		}
	}
	return 0;
}
