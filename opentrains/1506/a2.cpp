#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
#define ll long long
const int N = 1e5 + 10;
int d, n, m;
ll res;
ull H[N], base[N];

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
	void join(int x, int y, int k) {
		x = find(x), y = find(y);
		if (x != y) {
			if (vec[x].size() > vec[y].size()) {
				swap(x, y);
			}
			for (auto it : vec[x]) {
				//Hash recal
				ull h = H[it];
				res -= 2ll * (mp[h] - 1);
				mp[h]--;
				if (mp[h] == 0) {
					mp.erase(h);
				}
				h -= base[k] * x;
				h += base[k] * y;
				res += 2ll * mp[h];
				mp[h]++;
				H[it] = h;
				vec[y].push_back(it);
			}
			fa[x] = y;
			vec[x].clear();
		}
	}
}uf[220];

ull Hash(int x) {
	ull tmp = 0;
	for (int i = 1; i <= d; ++i) {
		tmp += base[i] * uf[i].find(x);
	}
	return tmp;
}

int main() {
	base[0] = 1ll;
	for (int i = 1; i <= 200; ++i) {
		base[i] = base[i - 1] * 50021;
	}
	while (scanf("%d%d%d", &d, &n, &m) != EOF) {
		mp.clear();
		for (int i = 1; i <= d; ++i) uf[i].init(n);
		for (int i = 1; i <= n; ++i) {
			H[i] = Hash(i);
			mp[H[i]]++;
		}
		res = n;
		for (int i = 1, a, b, k; i <= m; ++i) {
			scanf("%d %d %d", &a, &b, &k);
			uf[k].join(a, b, k);
			printf("%lld\n", res);
		}
	}
	return 0;
}
