#include <cstdio>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <cmath>
#include <climits>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <stack>
#include <set>
#include <list>
#include <bitset>
#include <numeric>
#include <sstream>
#include <iomanip>
#include <limits>
using namespace std;
typedef long long ll;
#define pLL pair <ll, ll>
#define fi first
#define se second
const int N = 1e5 + 10;
int n, q, fa[N], dep[N]; ll ans[N], del[N]; 
vector<vector<int>> G;
vector<vector<pLL>> add; 
void DFS(int u, ll sum, int sub) {
	sub -= del[dep[u]];
	sum -= sub;
	for (auto &it : add[u]) {
		sum += it.se;
		sub++;
		del[dep[u] + it.fi + 1] += 1; 
	}
	ans[u] = sum;
	for (auto &v : G[u]) if (v != fa[u]) {
		fa[v] = u; 
		dep[v] = dep[u] + 1;
		DFS(v, sum, sub);
	}
	for (auto &it : add[u]) {
		del[dep[u] + it.fi + 1] -= 1; 
	}
}

int main() {
	while (scanf("%d", &n) != EOF) {
		G.clear(); G.resize(n + 1);
		add.clear(); add.resize(n + 1);
		memset(del, 0, sizeof del);
		memset(ans, 0, sizeof ans);
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		scanf("%d", &q);
		int _p; ll _d, _x;
		for (int i = 1; i <= q; ++i) {
			scanf("%d%lld%lld", &_p, &_d, &_x);
			add[_p].push_back(pLL(min(_d, _x - 1), _x));
		}
		fa[1] = 1; dep[1] = 0;
		DFS(1, 0, 0);
		for (int i = 1; i <= n; ++i)
			printf("%lld\n", ans[i]);
	}
	return 0;
}
