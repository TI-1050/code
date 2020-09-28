#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pLL = pair <ll, ll>;
using P = pair<ll, int>;
#define fi first
#define se second
const int N = 4e5 + 10;
int n, m, q, mod, cnt[N], f[N], sta[N]; char s[N]; 
vector <vector<int>> G;
struct Hash {
	constexpr static ll seed[2] = {233, 13331};
	constexpr static ll mod[2] = {998244353, 1000000007};
	static ll base[2][N];
	static void init() {
		base[0][0] = base[1][0] = 1;
		for (int i = 1; i < N; ++i) {
			base[0][i] = base[0][i - 1] * seed[0] % mod[0];
			base[1][i] = base[1][i - 1] * seed[1] % mod[1];
		}
	}
	ll a[2][N];  
	inline void gao(char *s) {  
		a[0][0] = a[1][0] = 0;
		for (int i = 1; s[i]; ++i) {
			a[0][i] = (a[0][i - 1] * seed[0] % mod[0] + s[i]) % mod[0];
			a[1][i] = (a[1][i - 1] * seed[1] % mod[1] + s[i]) % mod[1];
		}	
	}
	inline ll get(int l, int r) {	
		return (a[0][r] - a[0][l - 1] * base[0][r - l + 1] % mod[0] + mod[0]) % mod[0] * mod[0] + (a[1][r] - a[1][l - 1] * base[1][r - l + 1] % mod[1] + mod[1]) % mod[1];
	//	return pLL((a[0][r] - a[0][l - 1] * base[0][r - l + 1] % mod[0] + mod[0]) % mod[0], (a[1][r] - a[1][l - 1] * base[1][r - l + 1] % mod[1] + mod[1]) % mod[1]);
	}
}hs;
ll Hash::base[2][N] = {{0}, {0}};
int querylcp(int a, int b, int c, int d) {
	int l = 1, r = min(b - a + 1, d - c + 1), res = 0;
	while (r - l >= 0) {
		int mid = (l + r) >> 1;
		if (hs.get(a, a + mid - 1) == hs.get(c, c + mid - 1)) {
			res = mid;
			l = mid + 1;
		} else {
			r = mid - 1; 
		}
	}
	return res; 
}
struct node {
	int l, r, len;
	bool operator < (const node &other) const {
		int lcp = querylcp(l, r, other.l, other.r);
		if (lcp == len) {
			if (len == other.len) return 0;
			return 1;
		}
		if (lcp == other.len) return 0;
		return s[l + lcp] < s[other.l + lcp];
	}
}a[N];
bool equal(node &a, node &b) {
	if (a.len != b.len) return 0;
	int lcp = querylcp(a.l, a.r, b.l, b.r);
	return lcp == a.len;
}
bool isprefix(node &a, node &b) {
	int lcp = querylcp(a.l, a.r, b.l, b.r);
	return lcp == a.len;
}
void dfs(int u) {
	f[u] = 1;
	for (auto &v: G[u]) {
		dfs(v);
		f[u] = 1ll * f[u] * f[v] % mod;
	}
	f[u] = (f[u] + cnt[u]) % mod;
}
int main() {
	Hash::init();
	while (scanf("%d%d", &n, &q) != EOF) {
		scanf("%s", s + 1);
		hs.gao(s);
		while (q--) {
			scanf("%d%d", &m, &mod);
			for (int i = 1; i <= m; ++i) {
				scanf("%d%d", &a[i].l, &a[i].r);
				a[i].len = a[i].r - a[i].l + 1;
			}
			sort(a + 1, a + 1 + m);
			*sta = 0;
			memset(cnt, 0, sizeof (cnt[0]) * (m + 10));
			cnt[0] = 1;
			G.clear(); G.resize(m + 1);
			for (int i = 1; i <= m; ++i) {
				if (*sta && equal(a[sta[*sta]], a[i])) {
					++cnt[sta[*sta]];
					continue;
				}
				while (*sta && !isprefix(a[sta[*sta]], a[i])) --*sta;
				if (!*sta) G[0].push_back(i);
				else G[sta[*sta]].push_back(i);
				cnt[i] = 1;
				sta[++*sta] = i; 
			}
			dfs(0);
			printf("%d\n", ((f[0] - 1) % mod + mod) % mod); 
		}
	}
	return 0;
}
