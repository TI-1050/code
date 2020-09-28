#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
const int N = 2e5 + 10; 
const int mod = 1e9 + 7;
int n, m, q, a[N]; ll ans[N], f[N][30], g[N][30]; 
struct qnode {
	int id, l, r; 
	qnode() {}
	void input(int _id) { 
		id = _id;
		scanf("%d%d", &l, &r);
	}
};  
inline void chadd(ll &x, ll y) {
	x += y;
	while (x >= mod) x -= mod; 
	while (x < 0) x += mod;
}
void gao(int l, int r, vector <qnode> qvec) { 
	if (l == r) {
		f[l][a[l]] = 1;
		++f[l][0];
		g[r][a[r]] = 1;
		++g[r][0];
		for (auto &it : qvec) {
			ans[it.id] = f[l][0];
		}
		return;
	}
	int mid = (l + r) >> 1;
	vector <qnode> lvec, rvec, now;
	for(auto &it : qvec) {
		if (it.r <= mid) lvec.push_back(it);
		else if (it.l > mid) rvec.push_back(it);
		else now.push_back(it);
	}
	gao(l, mid, lvec); gao(mid + 1, r, rvec);  
	for (auto &it : now) {
		int L = it.l, R = it.r, id = it.id;
		ans[id] = 0;
		for (int j = 0; j < m; ++j) {
			chadd(ans[id], f[L][j] * g[R][(m - j) % m] % mod);
		}
	}
	for (int i = mid + 1; i <= r; ++i) {
		for (int j = 0; j < m; ++j) g[i][j] = g[i - 1][j];
		for (int j = 0; j < m; ++j) {
			chadd(g[i][(j + a[i]) % m], g[i - 1][j]);
		}
	} 
	for (int i = mid; i >= l; --i) {
		for (int j = 0; j < m; ++j) f[i][j] = f[i + 1][j];
		for (int j = 0; j < m; ++j) {
			chadd(f[i][(j + a[i]) % m], f[i + 1][j]);
		}
	}
//	printf("%d %d\n", l, r);
//	for (int i = l; i <= r; ++i) {
//		printf("%d\n", i);
//		for (int j = 0; j < m; ++j)
//			printf("%lld%c", f[i][j], " \n"[j == m - 1]);
//		for (int j = 0; j < m; ++j)
//			printf("%lld%c", g[i][j], " \n"[j == m - 1]);
//	}
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		memset(f, 0, sizeof f);
		memset(g, 0, sizeof g);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i), a[i] %= m;
		scanf("%d", &q);
		vector <qnode> qvec; qvec.resize(q);
		for (int i = 0; i < q; ++i) qvec[i].input(i + 1);
		gao(1, n, qvec);
		for (int i = 1; i <= q; ++i) printf("%lld\n", ans[i]);		
	}
	return 0;
}
