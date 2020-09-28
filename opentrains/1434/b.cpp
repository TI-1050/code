#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 5e5 + 10;
int n, m;
struct node {
	int a, b, c;
	node() {}
	node(int a, int b, int c) : a(a), b(b), c(c) {}
	bool operator < (const node &other) const {
		return c < other.c;
	}
}e[N];

int fa[N], sze[N];
vector < vector <int> > vec; 
int find(int x) {
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void merge(int x, int y, int c) {
	x = find(x), y = find(y);
	if (x == y) {
		vec[x].push_back(c);
	} else if (x != y) {
		if (vec[x].size() > vec[y].size()) swap(vec[x], vec[y]);
		fa[x] = y; 
		for (auto it : vec[x]) vec[y].push_back(it);
		vec[y].push_back(c);
		sze[y] += sze[x]; 
	}
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		vec.clear(); vec.resize(n + 1);
		for (int i = 1; i <= n; ++i) fa[i] = i, sze[i] = 1;  
		for (int i = 1, a, b, c; i <= m; ++i) {
			scanf("%d%d%d", &a, &b, &c);
			merge(a, b, c);
		}
		ll res = 0;  
		for (int i = 1; i <= n; ++i) if (fa[i] == i) {
			sort(vec[i].begin(), vec[i].end());
			int _n = sze[i], _m = vec[i].size();
		//	cout << i << " " << _n << " " << _m << endl;
			for (int j = 0; j < _m - _n + 1; ++j) {
				res += vec[i][j];
			}
			for (int j = _m - _n + 1; j < _m; ++j) {
				if (vec[i][j] < 0) res += vec[i][j];
				else break;
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
