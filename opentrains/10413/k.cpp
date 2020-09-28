#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pLL = pair <ll, ll>;
using P = pair<pLL, int>;
#define fi first
#define se second
const int N = 1e5 + 10;
int n, q, ans[N]; char s[N], t[N];
struct Hash {
	static ll seed[2], mod[2], base[2][N];
	static void init() {
		base[0][0] = base[1][0] = 1;
		for (int i = 1; i < N; ++i) {
			base[0][i] = base[0][i - 1] * seed[0];
			base[1][i] = base[1][i - 1] * seed[1];
		}
	}
	ll a[2][N];  
	inline void gao(char *s) {  
		a[0][0] = a[1][0] = 0;
		for (int i = 1; s[i]; ++i) {
			a[0][i] = a[0][i - 1] * seed[0] + s[i];
			a[1][i] = a[1][i - 1] * seed[1] + s[i];
		}	
	}
	inline pLL get(int l, int r) { 
		return pLL(a[0][r] - a[0][l - 1] * base[0][r - l + 1], a[1][r] - a[1][l - 1] * base[1][r - l + 1]);
	}
}hs, ht;
ll Hash::base[2][N] = {{0}, {0}}, Hash::seed[2] = {233, 13331}, Hash::mod[2] = {998244353, 1000000007};
map <pLL, int> pre, have;
vector <vector<P>> vec;
void gao(int len) {
	for (int i = 1; i + len - 1 <= n; ++i) {
		pLL now = hs.get(i, i + len - 1);
		if (pre.count(now) == 0 || pre[now] + len - 1 < i) {
			++have[now];
			pre[now] = i;
		}
	}
}

int main() {
	Hash::init();
	while (scanf("%d%d", &n, &q) != EOF) {
		scanf("%s", s + 1);
		hs.gao(s);
		vec.clear(); vec.resize(N);
		for (int i = 1; i <= q; ++i) {
			scanf("%s", t + 1);
			ht.gao(t); 
			int lent = strlen(t + 1);
			vec[lent].push_back(P(ht.get(1, lent), i));
		}
		for (int i = 1; i < N; ++i) if (!vec[i].empty()) {
			pre.clear(); have.clear();
			gao(i);
			for (auto &it : vec[i]) {
				ans[it.se] = 0;
				if (have.count(it.fi)) ans[it.se] = have[it.fi];
			}
		}
		for (int i = 1; i <= q; ++i) printf("%d\n", ans[i]);
	}
	return 0;
}
