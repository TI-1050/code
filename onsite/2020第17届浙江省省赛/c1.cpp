#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 4e6 + 10;
const int M = 1e3 + 10;
const int ALP = 26;
#define fi first
#define se second
int n, m;
char s[N];
char t[M][M];

struct Trie {
	struct node {
		int nx[ALP];
		int v;
		int cnt;
		void init() {
			memset(nx, -1, sizeof nx);
			v = 0;
			cnt = 0;
		}	
	}t[N];
	int root, tot;
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
		t[now].cnt++;
	}
	int query(char *s) {
		int len = strlen(s);
		int now = root;
		for (int i = 0; i < len; ++i) {
			int ch = s[i] - 'a';
			if (t[now].nx[ch] == -1) return -1;
			now = t[now].nx[ch];
		}
		if (t[now].cnt == 0) return -1;
		return t[now].v;
	}
}trie;

ll gao() {
		ll res = 0;
		for (int i = 1; i <= n; ++i) {
			int len = 0;
			for (int j = 1; j <= n; ++j) {
				if (t[i][j] == '#') {
					s[len] = 0;
					if (len) {
						int now = trie.query(s);
						if (now == -1) return -1ll;
						res += now;
					}
					len = 0; 
				} else {
					s[len] = t[i][j];
					len++;
				}
			}	
			if (len) {
				s[len] = 0;
						int now = trie.query(s);
						if (now == -1) return -1ll;
						res += now;
			}
		}
		for (int i = 1; i <= n; ++i) {
			int len = 0;
			for (int j = 1; j <= n; ++j) {
				if (t[j][i] == '#') {
					s[len] = 0;
					if (len) {
						int now = trie.query(s);
						if (now == -1) return -1ll;
						res += now;
					}
					len = 0;
				} else {
					s[len] = t[j][i];
					len++;
				}
			}
			if (len) {
				s[len] = 0;
						int now = trie.query(s);
						if (now == -1) return -1ll;
						res += now;
			}
		}
		return res;
}

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i) {
			scanf("%s", t[i] + 1);
		}
		trie.init();
		for (int i = 1, v; i <= m; ++i) {
			scanf("%s%d", s, &v);
			trie.insert(s, v);
		}
		printf("%lld\n", gao());
	}
	return 0;
}
