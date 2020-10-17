#include <bits/stdc++.h>
using namespace std;

const int N = 4e6 + 10;
const int M = 1e3 + 10;
const int ALP = 26;
int n, m;
char s[N];
char t[M][M];

struct ACAM {
	struct node {
		int nx[ALP], fail;
		bool vis;
		int cnt;
		ll v;
		void init() {
			memset(nx, -1, sizeof nx);
			vis = 0;
			v = 0;
			cnt = 0;
			
		}	
	}t[N];
	int root, tot;
	int que[N], ql, qr;
	vector <vector<int>> G;
	int newnode() {
		++tot;
		t[tot].init();
		return tot;
	}
	void init() {
		tot = 0;
		root = newnode();
	}
	void insert(char *s, int v) {
		int len = strlen(s);
		int now = root;
		for (int i = 0; i < len; ++i) {
			if (t[now].nx[s[i] - 'a'] == -1) {
				t[now].nx[s[i] - 'a'] = newnode();
			}
			now = t[now].nx[s[i] - 'a'];
		}
		t[now].v += v;
	}
	void build() {
		ql = 1, qr = 0;
		t[root].fail = root;
		for (int i = 0; i < ALP; ++i) {
			if (t[root].nx[i] == -1) {
				t[root].nx[i] == root;
			} else {
				t[t[[root].nx[i]].fail = root;
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
	void query(char *s) {
		int len = strlen(s);
		int now = root;
		int res = 0;
		for (int i = 0; i < len; ++i) {
			now = t[now].nx[s[i] - 'a'];
			++t[now].cnt;
		}
	}
	ll gao() {
		G.clear(); G.resize(tot + 1);
		for (int i = 1; i <= tot; ++i) {
			int fail = t[i].fail;
			if (fail != i) G[fail].push_back(i);
		}
		queue <int> que;
		
		
	}
}acam;

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i) {
			scanf("%s", t[i] + 1);
		}
		acam.init();
		for (int i = 1; i <= m; ++i) {
			scanf("%s%d", s, &v);
			acam.add(s, v);
		}
		acam.build();
		for (int i = 1; i <= n; ++i) {
			int len = 0;
			for (int j = 1; j <= n; ++j) {
				if (t[i][j] == '#') {
					s[len] = 0;
					if (len) {
						acam.query(s);
					}
					len = 0; 
				} else {
					s[len] = t[i][j];
					len = 0;
				}
			}	
			if (len) acam.query(s);
		}
		for (int i = 1; i <= n; ++i) {
			int len = 0;
			for (int j = 1; j <= n; ++j) {
				if (t[j][i] == '#') {
					s[len] = 0;
					if (len) {
						acam.query(s);
					}
					len = 0;
				} else {
					s[len] = t[j][i];
					len = 0;
				}
			}
			if (len) acam.query(s);
		}
		printf("%lld\n", acam.gao());
	}
	return 0;
}
