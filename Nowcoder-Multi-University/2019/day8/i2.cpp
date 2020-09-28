#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 3e5 + 10;
int n, m, q, l[N], r[N], in[N], fin[N], out[N], cnt;  
ll res[N];
struct qnode {
	int l, r, id, f;
	qnode() {}
	qnode(int l, int r, int id, int f) : l(l), r(r), id(id), f(f) {}
};
vector <vector<qnode>> qvec; 
vector <vector<int>> G; 
void DFS(int u) {
	in[u] = ++cnt; fin[cnt] = u;  
	for (auto v : G[u]) DFS(v); 
	out[u] = cnt;
}

struct BIT_2D {
    struct BIT {
        ll a[N];
		inline void init() { memset(a, 0, sizeof a); }
        inline void add(ll x, ll v) { for (; x < N; a[x] += v, x += x & -x); }
        inline ll ask(ll x) { ll res = 0; for (; x > 0; res += a[x], x -= x & -x); return res; }
    }bit1, bit2;
	inline void init() { bit1.init(); bit2.init(); }
    inline ll ask(ll x) { return (x + 1) * bit1.ask(x) - bit2.ask(x); }
    inline void add(ll x, ll v) { bit1.add(x, v); bit2.add(x, x * v); }
    inline ll ask(ll l, ll r) { return ask(r) - ask(l - 1); }
    inline void add(ll l, ll r, ll v) { add(l, v); add(r + 1, -v); }
}bit;

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		G.clear(); G.resize(m + 5);
		l[1] = 1; r[1] = n; 
		for (int i = 1, u, v, _l, _r; i <= m; ++i) {
			scanf("%d%d%d%d", &u, &v, &_l, &_r);
			l[v] = _l; r[v] = _r;
			G[u].push_back(v); 
		}
		cnt = 0; DFS(1);
		scanf("%d", &q);
		qvec.clear(); qvec.resize(m + 5); 
		for (int i = 1, x, l, r; i <= q; ++i) {
			scanf("%d%d%d", &x, &l, &r);
			if (in[x] > 1) qvec[in[x] - 1].push_back(qnode(l, r, i, -1)); 
			qvec[out[x]].push_back(qnode(l, r, i, 1));
		}
		memset(res, 0, sizeof res);
		++m;
		bit.init();
		for (int i = 1; i <= m; ++i) {
			int x = fin[i]; 
		//	cout << x << " " << l[x] << " " << r[x] << endl; 
			bit.add(l[x], r[x], 1);
			for (auto &it : qvec[i]) {
				res[it.id] += 1ll * it.f * bit.ask(it.l, it.r);
			}
		}
		for (int i = 1; i <= q; ++i)
			printf("%lld\n", res[i]);
	}
	return 0;
}
