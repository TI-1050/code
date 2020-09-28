#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
#define ll long long
const int N = 1e5 + 10;
int d, n, m;
ll res;

ull Hash(int x);
map<ull, int> mp;

struct UF {
	int fa[N]; 
	vector <vector<int>> vec;
	void init(int n) {
		vec.clear(); vec.resize(n + 1);
		for (int i = 1; i <= n; ++i) {
			fa[i] = i;
			vec[i].push_back(i);	
		}
	}
	int find(int x) {
		return fa[x] == x ? x : fa[x] = find(fa[x]);
	}
	void join(int x, int y) {
		x = find(x), y = find(y);
		if (x != y) {
			if (vec[x].size() > vec[y].size()) {
				swap(x, y);
			}
			for (auto it : vec[x]) {
				//Hash recal
				ull h = Hash(it);
				res -= 2ll * (mp[h] - 1);
				mp[h]--;	
			}
			fa[x] = y;
			for (auto it : vec[x]) {
				ull h = Hash(it);
				res += 2ll * mp[h];
				mp[h]++;
				vec[y].push_back(it);
			}
			vec[x].clear();
		}
	}
}uf[220];

ull Hash(int x) {
	ull tmp = 0;
	ull base = 1;
	for (int i = 1; i <= d; ++i) {
		tmp += base * uf[i].find(x);
		base *= 5003;
	}
	return tmp;
}

int main() {
	while (scanf("%d%d%d", &d, &n, &m) != EOF) {
		mp.clear();
		for (int i = 1; i <= d; ++i) uf[i].init(n);
		for (int i = 1; i <= n; ++i) {
			ull h = Hash(i);
			mp[h]++;
		}
		res = n;
		for (int i = 1, a, b, k; i <= m; ++i) {
			scanf("%d %d %d", &a, &b, &k);
			uf[k].join(a, b);
			printf("%lld\n", res);
		}
	}
	return 0;
}
