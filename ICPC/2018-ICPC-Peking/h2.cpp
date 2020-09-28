#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e4 + 10, ALP = 2;
int n, m; char s[N];
ll f[50][N];
struct ACAM {
	struct node {
		int nx[ALP], fail;
		int cnt; 
		node() {
			memset(nx, -1, sizeof nx);
			cnt = 0; 
		}
	}t[N];
	int root, tot;
	int que[N], ql, qr;
	int newnode() {
		++tot;
		t[tot] = node();
		return tot;
	}
	void init() {
		tot = 0;
		root = newnode();
	}
	void insert(char *s) {
		int len = strlen(s);
		int now = root;
		for (int i = 0; i < len; ++i) {
			if (t[now].nx[s[i] - '0'] == -1) 
				t[now].nx[s[i] - '0'] = newnode();
			now = t[now].nx[s[i] - '0'];
		}
		++t[now].cnt;
	}
	void build() {
		ql = 1, qr = 0;
		t[root].fail = root;
		for (int i = 0; i < ALP; ++i) {
			if (t[root].nx[i] == -1) {
				t[root].nx[i] = root;
			} else {
				t[t[root].nx[i]].fail = root;
				que[++qr] = t[root].nx[i];
			}
		}
		while (ql <= qr) {
			int now = que[ql++];
			for (int i = 0; i < ALP; ++i) {
				if (t[now].nx[i] == -1) {
					t[now].nx[i] = t[t[now].fail].nx[i];
				} else {
					t[t[now].nx[i]].fail = t[t[now].fail].nx[i];
					que[++qr] = t[now].nx[i];
				}
			}
		}
	}
	ll gao() {
		ll res = 0;
		for (int i = 0; i <= m; ++i)
			for (int j = 0; j <= tot; ++j)
				f[i][j] = 0;
		f[0][root] = 1;
		for (int i = 0; i < m; ++i) {
			for (int j = 1; j <= tot; ++j) {
				if (t[j].cnt > 0) continue;
				for (int k = 0; k < 2; ++k) {
					if (t[j].nx[k] != -1) {
						f[i + 1][t[j].nx[k]] += f[i][j];
					}
				}
			}
		}
		for (int i = 1; i <= m; ++i) {
			for (int j = 1; j <= tot; ++j) {
				if (t[j].cnt > 0) {
					res += f[i][j] * (1 << (m - i));
				}
			}
		}
		return res;
	}
}acam;

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%d%d%s", &n, &m, s);
		acam.init(); acam.insert(s);
	//	for (int i = 1; i <= n; ++i) {
	//		s[i] = ((s[i] - '0') ^ 1) + '0';
	//		acam.insert(s);
	//		s[i] = ((s[i] - '0') ^ 1) + '0';
	//	}
		acam.build();
		printf("%lld\n", acam.gao());
	}
	return 0;
}
